# ITK 6 Migration Guide

Changes that downstream code may need to act on when moving to ITK 6.
This page is generated from the records in
[`migration_guides/records/itk6/`](https://github.com/InsightSoftwareConsortium/ITK/tree/main/Documentation/docs/migration_guides/records/itk6).

## At a glance

| Impact | Change | Release |
| --- | --- | --- |
| high | [Modern CMake interface libraries](#itk6-ModernCMakeInterfaceLibraries) | unreleased |
| high | [NumPy bridge: `image_from_array(arr.T)` is no longer equivalent to `image_from_array(arr)`](#itk6-NumpyTransposeNotEquivalent) | unreleased |
| medium | [`GetIndex()` is replaced by `ComputeIndex()` for iterators without an index](#itk6-GetIndexToComputeIndex) | unreleased |
| medium | [32-bit x86 requires SSE2 floating-point math](#itk6-RequireSse2On32BitX86) | unreleased |
| low | [`itk::Math::sqrteps` changed by 1 ULP](#itk6-SqrtEpsOneUlp) | unreleased |
| not rated | [Nearly Empty Record](#itk6-NearlyEmptyRecord) | unreleased |
| low | [The ITKVNLInstantiation library is removed](#itk6-RemoveItkVnlInstantiation) | 6.0b01 |
| high | [Remove support for ITKv5 interfaces](#itk6-RemoveItkV5Support) | 6.0a01 |

## Unreleased (on `main`)

(itk6-ModernCMakeInterfaceLibraries)=
### Modern CMake interface libraries

{bdg-danger}`high` {bdg-info-line}`ApiDeprecated` {bdg-primary-line}`cmake`

ITK modules are now imported targets with usage requirements; `ITK_LIBRARIES`
and `include(${ITK_USE_FILE})` are deprecated.

:::{dropdown} Details and examples
:class-container: sd-mb-4

*Before:*

```cmake
find_package(ITK REQUIRED COMPONENTS ITKCommon ITKIOImageBase)
include(${ITK_USE_FILE})
target_link_libraries(myApp ${ITK_LIBRARIES})
```

*After:*

```cmake
find_package(ITK REQUIRED COMPONENTS ITKCommon ITKIOImageBase)
target_link_libraries(myApp PRIVATE ITK::ITKCommon ITK::ITKIOImageBase)
```

[PR #5721](https://github.com/InsightSoftwareConsortium/ITK/pull/5721) · [`93df383cb9b`](https://github.com/InsightSoftwareConsortium/ITK/commit/93df383cb9b) · Deprecated in 6.0

:::

(itk6-NumpyTransposeNotEquivalent)=
### NumPy bridge: `image_from_array(arr.T)` is no longer equivalent to `image_from_array(arr)`

{bdg-danger}`high` {bdg-info-line}`ResultsChange` {bdg-primary-line}`python`

Non-C-contiguous arrays are now copied, and the image size always equals
`array.shape[::-1]`, so a transposed array gives a transposed image.

:::{dropdown} Details and examples
:class-container: sd-mb-4

*Before:*

```python
image = itk.image_from_array(arr.T)   # same image as arr
```

*After:*

```python
image = itk.image_from_array(arr)     # pass the array you mean
```

Earlier versions special-cased F-contiguous inputs, so the transpose was a
silent no-op and round trips could transpose data. The result for `arr.T`
changes without any error, which is why this is rated high.

[PR #5775](https://github.com/InsightSoftwareConsortium/ITK/pull/5775) · [`fdee9cb6d89`](https://github.com/InsightSoftwareConsortium/ITK/commit/fdee9cb6d89)

:::

(itk6-GetIndexToComputeIndex)=
### `GetIndex()` is replaced by `ComputeIndex()` for iterators without an index

{bdg-warning}`medium` {bdg-info-line}`ApiDeprecated` {bdg-info-line}`ApiRenamed` {bdg-primary-line}`cxx`

Iterators that do not store an index compute it on request, so the method is
renamed to show that it costs time.

:::{dropdown} Details and examples
:class-container: sd-mb-4

| Old | New |
| --- | --- |
| `itk::ImageRegionConstIterator::GetIndex()` | `itk::ImageRegionConstIterator::ComputeIndex()` |
| `itk::ImageScanlineConstIterator::GetIndex()` | `itk::ImageScanlineConstIterator::ComputeIndex()` |

[PR #5803](https://github.com/InsightSoftwareConsortium/ITK/pull/5803) · [`2b7c0770f96`](https://github.com/InsightSoftwareConsortium/ITK/commit/2b7c0770f96) · Old form available until `ITK_FUTURE_LEGACY_REMOVE`

:::

(itk6-RequireSse2On32BitX86)=
### 32-bit x86 requires SSE2 floating-point math

{bdg-warning}`medium` {bdg-info-line}`CompilerEnvironment` {bdg-primary-line}`cxx` {bdg-primary-line}`cmake`

A 32-bit x86 build or client without SSE2 math now stops at an `#error` in
`itkConfigure.h`.

:::{dropdown} Details and examples
:class-container: sd-mb-4

**What you need to do**

1. Build through ITK's CMake targets or `UseITK.cmake`, which add the flags.
1. Otherwise add `-msse2 -mfpmath=sse` (GCC, Clang) or `/arch:SSE2` (MSVC).

The error a client sees without the flags.

*After:*

```text
itkConfigure.h: error: "ITK requires SSE2 floating-point math on 32-bit x86:
use -msse2 -mfpmath=sse (GCC, Clang) or /arch:SSE2 (MSVC)"
```

[PR #7125](https://github.com/InsightSoftwareConsortium/ITK/pull/7125)

:::

(itk6-SqrtEpsOneUlp)=
### `itk::Math::sqrteps` changed by 1 ULP

{bdg-secondary}`low` {bdg-info-line}`ResultsChange` {bdg-primary-line}`cxx`

`itk::Math::sqrteps` is now `0x1p-26`, the exact `sqrt(eps)`.

:::{dropdown} Details and examples
:class-container: sd-mb-4

Rated low despite `ResultsChange`: the value moves by one unit in the last
place, which affects only tolerance comparisons at the edge of precision.

[PR #6427](https://github.com/InsightSoftwareConsortium/ITK/pull/6427) · [`589d68004ab`](https://github.com/InsightSoftwareConsortium/ITK/commit/589d68004ab)

:::

(itk6-NearlyEmptyRecord)=
### Nearly Empty Record

{bdg-light}`impact not rated`

## ITK 6.0b01

(itk6-RemoveItkVnlInstantiation)=
### The ITKVNLInstantiation library is removed

{bdg-secondary}`low` {bdg-info-line}`ApiRemoved` {bdg-primary-line}`cmake`

`ITKVNLInstantiation` was an empty compatibility library. Link `ITKVNL` instead.

:::{dropdown} Details and examples
:class-container: sd-mb-4

*Before:*

```cmake
target_link_libraries(myApp PRIVATE ITKVNLInstantiation)
```

*After:*

```cmake
target_link_libraries(myApp PRIVATE ITKVNL)
```

[PR #5286](https://github.com/InsightSoftwareConsortium/ITK/pull/5286) · [`db104239cf8`](https://github.com/InsightSoftwareConsortium/ITK/commit/db104239cf8)

:::

## ITK 6.0a01

(itk6-RemoveItkV5Support)=
### Remove support for ITKv5 interfaces

{bdg-danger}`high` {bdg-info-line}`ApiRemoved` {bdg-primary-line}`cxx`

The Deprecated module and every `ITKV5_COMPATIBILITY` interface are removed.

:::{dropdown} Details and examples
:class-container: sd-mb-4

**What you need to do**

1. Replace `itk::TreeContainer` uses with a standard container.
1. Replace `itk::Atomic` and `itk::SimpleFastMutexLock` with `std::atomic` and `std::mutex`.

This includes `TreeContainer` and related classes, the atomic primitives and
mutexes now provided by the C++ standard library, and the specialized vector
filters, since the regular filters work with vector images.

**Links:** <https://github.com/InsightSoftwareConsortium/ITK/blob/main/Documentation/docs/migration_guides/itk_5_migration_guide.md>

[PR #4729](https://github.com/InsightSoftwareConsortium/ITK/pull/4729) · [`91251de596f`](https://github.com/InsightSoftwareConsortium/ITK/commit/91251de596f)

:::
