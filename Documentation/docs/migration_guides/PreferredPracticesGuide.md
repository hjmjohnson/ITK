ITK Preferred Practices Guide
=============================

This guide documents recommended style and correctness patterns adopted
in the ITK v6 codebase, distilled from ~920 STYLE, PERF, and COMP
commits across all contributors. These are not breaking changes but are
strongly encouraged for consistency with the ITK codebase and to prepare
for future deprecation cycles.

External projects (remote modules, applications) should adopt these
patterns. A migration script for macro replacements is provided at
`Utilities/Maintenance/migrate-itk6-code-recommendations.sh`.


Variable initialization at declaration
--------------------------------------

Prefer initializing variables at the point of declaration rather than
declaring first and assigning later. This eliminates uninitialized-variable
bugs and often enables `const` or `constexpr`.

### `Type var; var.Fill(0)` &rarr; `Type var{}`

Zero-initialization via `{}` is the canonical C++ idiom for FixedArray-derived
types (IndexType, SizeType, SpacingType, PointType, VectorType). It preserves
the correct derived type and is shorter than `.Fill(0)`.

```cpp
// Before:
ImageType::IndexType start;
start.Fill(0);

// After:
ImageType::IndexType start{};
```

**Reference:** N-Dekker commits `e1e06b50`, `36a7f6a7`, `51976ee9`, `669ae8b7`.

### `Type var; var.Fill(N)` &rarr; `auto var = itk::MakeFilled<Type>(N)`

For non-zero fill values, use the `MakeFilled` helper from `itkMakeFilled.h`
(included transitively via `itkFixedArray.h`). Use `itk::` qualification
when outside `namespace itk`.

```cpp
// Before:
ImageType::SizeType size;
size.Fill(16);

// After (in test files -- outside namespace itk):
auto size = itk::MakeFilled<ImageType::SizeType>(16);

// After (in .hxx files -- inside namespace itk):
auto size = MakeFilled<ImageType::SizeType>(16);
```

**Reference:** N-Dekker commit `6cb6bf98`.

### `Type var; var[0]=x; var[1]=y; ...` &rarr; brace initialization or `::Filled()`

Per-element assignment can be replaced with brace initialization (different
values) or `::Filled()` (same value):

```cpp
// Before:
SizeType size;
size[0] = 128;
size[1] = 256;

// After (different values):
SizeType size{ 128, 256 };

// Before:
SizeType size;
size[0] = 64;
size[1] = 64;

// After (same values):
auto size = SizeType::Filled(64);
```

**Reference:** N-Dekker commits `9962e2f9`, `03941e42`.

### Use `constexpr` where possible

When a Filled/brace-initialized variable is never modified, mark it `constexpr`:

```cpp
constexpr auto radius = SizeType::Filled(2);
constexpr ImageType::IndexType start{};
```

**Reference:** N-Dekker commits `c77f9f8d`, `fd144827`.


Smart pointer and object creation
---------------------------------

### `T::Pointer var = T::New()` &rarr; `auto var = T::New()`

Use `auto` when the type is obvious from the right-hand side:

```cpp
// Before:
MedianFilterType::Pointer filter = MedianFilterType::New();

// After:
auto filter = MedianFilterType::New();
```

**Reference:** N-Dekker STYLE commits replacing `T::Pointer` with `auto`.

### Remove redundant `Initialize()` after `New()`

ITK objects are fully initialized by `New()`. Calling `Initialize()` immediately
after construction is redundant.

```cpp
// Before:
auto optimizer = OptimizerType::New();
optimizer->Initialize();   // unnecessary

// After:
auto optimizer = OptimizerType::New();
```

**Reference:** N-Dekker commits removing `p->Initialize()` calls after `New()`.

### Prefer `std::unique_ptr` for private implementation members

For PIMPL and internal owning pointers, prefer `std::unique_ptr` over raw
`new`/`delete`:

```cpp
// Before:
InternalType * m_Impl;
// in constructor: m_Impl = new InternalType;
// in destructor: delete m_Impl;

// After:
std::unique_ptr<InternalType> m_Impl;
// constructor: m_Impl = std::make_unique<InternalType>();
// destructor: = default (in .cxx, not header -- see compiler-cautions.md)
```

**Reference:** N-Dekker commits on `unique_ptr` for HDF5ImageIO, GiplImageIO,
MINCImageIO, GradientImageFilter.


Image allocation and buffer initialization
------------------------------------------

### `Allocate(true)` &rarr; `AllocateInitialized()`

The boolean argument to `Allocate()` is easy to misread.
`AllocateInitialized()` is self-documenting:

```cpp
// Before:
image->Allocate(true);  // initialize buffer to zero

// After:
image->AllocateInitialized();
```

**Reference:** N-Dekker commit `527843e9` (PR #4479), hjmjohnson PR #6009.

### `Allocate(); FillBuffer({})` &rarr; `AllocateInitialized()`

When allocation is immediately followed by zero-fill, combine into one call:

```cpp
// Before:
image->Allocate();
image->FillBuffer(PixelType{});

// After:
image->AllocateInitialized();
```

**Reference:** N-Dekker commits `eb4386f3`, `081e135c`.


Iterator modernization
----------------------

### Remove redundant `GoToBegin()` after construction

Image iterators are already positioned at the beginning of the region after
construction. Calling `GoToBegin()` immediately after is redundant:

```cpp
// Before:
ImageRegionIterator<ImageType> it(image, region);
it.GoToBegin();

// After:
ImageRegionIterator<ImageType> it(image, region);
```

**Reference:** N-Dekker commits `b1162f4a`, `b3a3e4b4`, `d4d5e3af`.

### Use Class Template Argument Deduction (CTAD) for iterators

C++17 CTAD eliminates the need for explicit template arguments when the
image type can be deduced from the constructor arguments:

```cpp
// Before:
ImageRegionConstIterator<ImageType> it(image, region);

// After:
ImageRegionConstIterator it(image, region);
```

**Reference:** N-Dekker commits `350447b1`, `ce1caafb`, `50210af9`.

### Remove local iterator type aliases

When CTAD is used, the local `using IteratorType = ...` alias becomes
unnecessary:

```cpp
// Before:
using IteratorType = ImageRegionConstIterator<TImage>;
IteratorType it(image, region);

// After:
ImageRegionConstIterator it(image, region);
```

**Reference:** N-Dekker commits `901ea167`, `3cd638a0`, `6ee4c37e`.

### Use `ComputeIndex()` instead of `GetIndex()` on iterators without index

`ImageConstIterator::GetIndex()` performs an expensive index computation on
every call. It is deprecated in favor of the explicitly-named `ComputeIndex()`,
or use an iterator type that natively tracks the index (e.g.,
`ImageIteratorWithIndex`):

```cpp
// Before:
auto idx = it.GetIndex();   // deprecated -- expensive computation

// After:
auto idx = it.ComputeIndex();
```

**Reference:** N-Dekker commits `a84cb8c8`, `f39b7597`, `481f802e`.

### Prefer `ImageRegionRange` / `ImageBufferRange` / `MakeIndexRange`

Modern range types provide cleaner, range-for-compatible iteration:

```cpp
// Before:
ImageRegionIterator<ImageType> it(image, region);
for (it.GoToBegin(); !it.IsAtEnd(); ++it)
{
  it.Set(value);
}

// After:
for (auto && pixel : ImageRegionRange(*image, region))
{
  pixel = value;
}

// Index iteration -- before:
ImageRegionIteratorWithIndex<ImageType> it(image, region);
for (it.GoToBegin(); !it.IsAtEnd(); ++it)
{
  auto index = it.GetIndex();
  // ...
}

// After:
for (auto index : MakeIndexRange(region))
{
  // ...
}
```

**Reference:** N-Dekker commits on `ImageRegionRange`, `ImageBufferRange`,
`MakeIndexRange` across Core, Filtering, Registration modules.


Const-correctness and the Rule of Zero
--------------------------------------

### Mark local variables `const` when unmodified

Add `const` to local variables that are never modified after initialization
(C++ Core Guideline ES.25):

```cpp
// Before:
std::pair<Iterator, bool> result = m_HashMap.insert(ValueType(a, b));

// After:
const auto result = m_HashMap.insert(ValueType(a, b));
```

**Reference:** Commits `05318b345b`, `ab16e66e95`, `61520de598`.

### Rule of Zero: remove user-declared defaulted special members

If a class has no custom resource management, declare no special member
functions. User-declared `= default` destructors or assignment operators
cause GCC 11+ to warn under C++20 deprecated-copy rules:

```cpp
// Before:
class NthElementPixelAccessor
{
public:
  NthElementPixelAccessor() = default;
  NthElementPixelAccessor & operator=(const NthElementPixelAccessor &) = default;
  // ...
};

// After (remove both -- compiler generates them):
class NthElementPixelAccessor
{
public:
  // ...
};
```

**Reference:** Commits `00ead18cd1`, `291eb13baf`, `630b6f4472`.

### Add `[[nodiscard]]` to non-const accessors

Prevent silently discarding return values from `data()`, `begin()`, `end()`:

```cpp
// Before:
ElementType * data() { return m_Data; }

// After:
[[nodiscard]] ElementType * data() { return m_Data; }
```

**Reference:** Commits `13e653326a`, `85aa7bddf8`.

### Add `noexcept` to move operations

Move constructors and move-assignment operators should be `noexcept` to
enable efficient `std::vector` reallocation:

```cpp
// Before:
Array2D(Array2D &&) = default;
Array2D & operator=(Array2D &&) = default;

// After:
Array2D(Array2D &&) noexcept = default;
Array2D & operator=(Array2D &&) noexcept = default;
```

**Reference:** Commits `9979c7d7c9`, `eaadb8c68a`, `7bceae7a2e`.


C++17 language features
-----------------------

### Use `override` instead of `virtual` on overriding methods

When `override` is present, the `virtual` keyword is redundant and should
be removed (C++ Core Guideline C.128):

```cpp
// Before:
virtual ~PyCommand();
virtual void VerifyPreconditions() const override;

// After:
~PyCommand() override;
void VerifyPreconditions() const override;
```

**Reference:** Commits `b06c36a366`, `a76ce8f101`, `7afd586737`.

### Use `[[fallthrough]]` in switch statements

Replace `/* fall through */` comments with the standard attribute:

```cpp
// Before:
case 1:
  doSomething();
  /* fall through */
case 2:

// After:
case 1:
  doSomething();
  [[fallthrough]];
case 2:
```

**Reference:** Commit `9243a075cd`.

### Prefer C++17 nested namespace syntax

```cpp
// Before:
namespace itk {
namespace Statistics {
// ...
} // namespace Statistics
} // namespace itk

// After:
namespace itk::Statistics {
// ...
} // namespace itk::Statistics
```

**Reference:** Commit `50272388c3`.

### Use raw string literals for embedded markup and regex

```cpp
// Before:
std::cout << "<DartMeasurement name=\"BaselineImageName\" type=\"text/string\">";

// After:
std::cout << R"(<DartMeasurement name="BaselineImageName" type="text/string">)";
```

**Reference:** Commits `155555ff27`, `fe37dc184b`.


Type safety
-----------

### Prefer `using` over `typedef`

The `using` alias declaration is more readable and supports template aliases:

```cpp
// Before:
typedef OutputSpatialObjectT                       OutObjectType;
typedef std::list<typename OutObjectType::Pointer> OutListType;

// After:
using OutObjectType = OutputSpatialObjectT;
using OutListType = std::list<typename OutObjectType::Pointer>;
```

**Reference:** Commits `1b78f3c28e`, `8d52dcaf50`, `d72c9930a7`.

### Use `int8_t` instead of `char` for numeric data

`char` signedness is platform-dependent (unsigned on ARM). Use explicit
fixed-width types for numeric data:

```cpp
// Before:
char value = -1;   // unsigned on ARM -- wraps to 255

// After:
int8_t value = -1; // always signed, always 8-bit
```

**Reference:** Commit `944f3b09b1`.

### Replace `#define` constants with enums or `constexpr`

```cpp
// Before:
#define PAR_DEFAULT_STRING_LENGTH 32

// After:
constexpr int PAR_DEFAULT_STRING_LENGTH = 32;
// or:
enum { PAR_DEFAULT_STRING_LENGTH = 32 };
```

**Reference:** Commits `1f88a09bc0`, `a5329b3798`.


Default member initializers
---------------------------

Move member variable initialization from constructor initializer lists to
in-class initializers. This prevents uninitialized-member bugs when new
constructors are added:

```cpp
// Before (in constructor):
MyFilter::MyFilter()
  : m_Radius(0)
  , m_UseImageSpacing(true)
{}

// After (in class declaration):
SizeValueType m_Radius{ 0 };
bool m_UseImageSpacing{ true };
```

**Reference:** Commits `4327c3ca12`, `47b47b9c89`.


STL and language modernization
------------------------------

### `push_back(T(...))` &rarr; `emplace_back(...)`

Use `emplace_back` to construct elements in-place, avoiding a temporary:

```cpp
// Before:
points.push_back(PointType(x, y, z));

// After:
points.emplace_back(x, y, z);
```

**Reference:** N-Dekker commit `289f59e3`.

### Prefer `std::array` over C arrays and `std::vector` for fixed-size locals

When the size is known at compile time, `std::array` provides bounds safety
and STL compatibility:

```cpp
// Before:
double weights[3];

// After:
std::array<double, 3> weights;
```

**Reference:** N-Dekker commits on `std::array` in tests, IO, QuadEdgeMesh.

### Use range-based `for` loops

Replace index-based or iterator-based loops with range-based `for` when
the entire container is traversed:

```cpp
// Before:
for (unsigned int i = 0; i < children.size(); ++i)
{
  Process(children[i]);
}

// After:
for (auto & child : children)
{
  Process(child);
}
```

### Simplify boolean expressions

Replace `if`/`else` assignments to `bool` with direct expressions:

```cpp
// Before:
bool isValid;
if (condition)
{
  isValid = true;
}
else
{
  isValid = false;
}

// After:
bool isValid = condition;
```

**Reference:** N-Dekker commit `2a117384`.


Performance patterns
--------------------

### `itkExceptionStringMacro` for plain string exceptions

Use `itkExceptionStringMacro("msg")` instead of `itkExceptionMacro("msg")`
when the argument is a plain string with no `<<` streaming. This avoids
unnecessary `std::ostringstream` allocation:

```cpp
// Before:
itkExceptionMacro("Division by zero");

// After:
itkExceptionStringMacro("Division by zero");
```

**Reference:** Commits `82627756f0`, `0907661ad4`, `2bc2a2b9d7`.

### Use character literals in single-character string searches

Pass `char` instead of `const char*` to `find()` / `rfind()` to avoid
constructing a temporary string:

```cpp
// Before:
filename.rfind(".")

// After:
filename.rfind('.')
```

**Reference:** Commits `54b147e42f`, `ef08441394`.

### Use `container.empty()` over size comparisons

```cpp
// Before:
if (diff.size() != 0) { ... }

// After:
if (!diff.empty()) { ... }
```

**Reference:** Commits `519d054b23`, `b66b586962`.

### Use `container.data()` instead of `&*(container.begin())`

```cpp
// Before:
&*(myVector.begin())

// After:
myVector.data()
```

**Reference:** Commit `80477bfff3`.


Macro replacements (external module conformance)
-------------------------------------------------

These replacements are enforced by `ITK_LEGACY_REMOVE=ON` and should be
adopted by all external modules. A migration script is provided at
`Utilities/Maintenance/migrate-itk6-code-recommendations.sh`.

| Deprecated | Replacement |
|-----------|-------------|
| `itkTypeMacro(Self, Super)` | `itkOverrideGetNameOfClassMacro(Self)` |
| `itkTypeMacroNoParent(Self)` | `itkVirtualGetNameOfClassMacro(Self)` |
| `ITK_DISALLOW_COPY_AND_ASSIGN(T)` | `ITK_DISALLOW_COPY_AND_MOVE(T)` |
| `itkStaticConstMacro(N, T, v)` | `static constexpr T N = v;` |
| `itkGetStaticConstMacro(N)` | `Self::N` |
| `ITKv5_CONST` | `const` |
| `CoordRepType` | `CoordinateType` |
| `InputCoordRepType` | `InputCoordinateType` |
| `OutputCoordRepType` | `OutputCoordinateType` |


Code cleanup patterns
---------------------

### Remove `this->` in template implementation files

Within class method implementations, `this->` is only required when accessing
dependent names in template code. In non-dependent contexts it is unnecessary
clutter:

```cpp
// Before (non-dependent context):
this->m_Radius = radius;

// After:
m_Radius = radius;
```

Note: `this->` IS required in dependent base class member access within
template code. Only remove it where it is genuinely redundant.

**Reference:** N-Dekker commits removing `this->` across multiple modules.

### Remove trailing `std::endl` from exception/warning macros

ITK macros (`itkExceptionMacro`, `itkWarningMacro`) append a newline
automatically. Trailing `<< std::endl` is redundant and can cause double
line breaks:

```cpp
// Before:
itkExceptionMacro("Failed to read " << filename << std::endl);

// After:
itkExceptionMacro("Failed to read " << filename);
```

**Reference:** N-Dekker PERF commit `2bc2a2b9`.

### Remove empty `protected:` / `private:` sections

Empty access specifier sections add noise without semantic value:

```cpp
// Before:
class MyFilter : public ImageToImageFilter<TInput, TOutput>
{
public:
  // ...
protected:
  // ...
private:
};

// After:
class MyFilter : public ImageToImageFilter<TInput, TOutput>
{
public:
  // ...
protected:
  // ...
};
```

**Reference:** N-Dekker commits `9846ad3c`, `dad3fd3b`.


Naming and declaration consistency
----------------------------------

### Remove redundant `(void)` in parameter lists

```cpp
// Before:
unsigned int GetMetaIOVersion(void) const;

// After:
unsigned int GetMetaIOVersion() const;
```

**Reference:** Commits `5edc651aba`, `3c291261f6`.

### Match prototype parameter names to definitions

Ensure function declarations use the same parameter names as their
definitions for documentation accuracy:

```cpp
// Header (before):
void SetNumberOfWorkUnits(ThreadIdType numThreads);

// Header (after -- matching .cxx):
void SetNumberOfWorkUnits(ThreadIdType numWorkUnits);
```

**Reference:** Commits `d0b5aa42bd`, `6a5f942684`.


CMake modernization
-------------------

### Use lowercase CMake commands

```cmake
# Before:
IF(condition)
  SET(VAR value)
ENDIF()

# After:
if(condition)
  set(VAR value)
endif()
```

ITK uses the `gersemi` formatter to enforce this automatically.

**Reference:** Commits `928d7f1dbf`, `e4d6989cfa`.
