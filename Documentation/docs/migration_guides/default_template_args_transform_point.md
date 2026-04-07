# Proposal: Default Template Arguments for Transform\*Point Return-Value Overloads

## Problem

ITK 5.x added single-argument return-value overloads for the `ImageBase`
`Transform*Point` family (PR [#868](https://github.com/InsightSoftwareConsortium/ITK/pull/868)).
These overloads are function templates where the coordinate/index precision
type appears **only in the return type** and cannot be deduced by the compiler:

```cpp
// itkImageBase.h — current signatures
template <typename TCoordinate>
Point<TCoordinate, VImageDimension>
TransformIndexToPhysicalPoint(const IndexType & index) const;

template <typename TCoordinate, typename TIndexRep>
Point<TCoordinate, VImageDimension>
TransformContinuousIndexToPhysicalPoint(const ContinuousIndex<TIndexRep, VImageDimension> &) const;

template <typename TIndexRep, typename TCoordinate>
ContinuousIndex<TIndexRep, VImageDimension>
TransformPhysicalPointToContinuousIndex(const Point<TCoordinate, VImageDimension> &) const;
```

Because `TCoordinate` (or `TIndexRep`) cannot be deduced from the function
arguments, every caller must write an explicit template argument **and** the
`template` disambiguation keyword in dependent contexts:

```cpp
// What callers must write today:
const auto pnt = image->template TransformIndexToPhysicalPoint<double>(idx);

// What callers WANT to write:
const auto pnt = image->TransformIndexToPhysicalPoint(idx);
```

The explicit `<double>` and `template` keyword requirements are:
- Error-prone (two independent failure modes, each with a cryptic compiler diagnostic)
- Visually noisy in code that should be a simple point lookup
- A barrier to adoption of the preferred return-value API

## Proposed Fix

Add `= PointValueType` as the default template argument for the non-deducible
parameter on each of the three one-argument overloads:

```cpp
template <typename TCoordinate = PointValueType>
[[nodiscard]] Point<TCoordinate, VImageDimension>
TransformIndexToPhysicalPoint(const IndexType & index) const;

template <typename TCoordinate = PointValueType, typename TIndexRep>
[[nodiscard]] Point<TCoordinate, VImageDimension>
TransformContinuousIndexToPhysicalPoint(const ContinuousIndex<TIndexRep, VImageDimension> &) const;

template <typename TIndexRep = PointValueType, typename TCoordinate>
[[nodiscard]] ContinuousIndex<TIndexRep, VImageDimension>
TransformPhysicalPointToContinuousIndex(const Point<TCoordinate, VImageDimension> &) const;
```

### Why `PointValueType`?

`PointValueType` is defined in `ImageBase` as:

```cpp
using PointValueType = SpacePrecisionType;
```

where `SpacePrecisionType` is `double` by default, or `float` when
`ITK_USE_FLOAT_SPACE_PRECISION` is enabled at CMake configure time.
Using `PointValueType` rather than hardcoding `double` ensures the default
tracks the image's own coordinate precision — the natural choice for a
method that converts between index space and physical space.

### C++ Validity

C++ permits default template arguments before deducible parameters in
function templates (unlike class templates). In the
`TransformContinuousIndexToPhysicalPoint` overload, `TIndexRep` is
deducible from the `ContinuousIndex` argument, so
`template <typename TCoordinate = PointValueType, typename TIndexRep>`
is well-formed.  Similarly for `TransformPhysicalPointToContinuousIndex`.

## Backward Compatibility Analysis

### Theoretical Guarantee

Adding a default template argument to a function template is a
purely additive, ABI-compatible change:

| Existing call pattern | Effect of this change |
|-----------------------|-----------------------|
| `image->TransformIndexToPhysicalPoint<double>(idx)` | **No change** — explicit arg overrides default |
| `image->template TransformIndexToPhysicalPoint<float>(idx)` | **No change** — explicit arg overrides default |
| `image->template TransformIndexToPhysicalPoint<TCoordinate>(idx)` | **No change** — forwarded type overrides default |
| `image->TransformIndexToPhysicalPoint(idx, pnt)` (two-arg) | **No change** — different overload, unaffected |
| No call to these methods | **No change** |

No existing valid code changes meaning. No existing compilation that
succeeds will fail. No ABI symbol changes.

### Empirical Verification: Cross-Project Census

A census of all explicit template arguments used with the one-argument
return-value overloads was performed across four major ITK downstream
projects: **ITK** (Modules/), **BRAINSTools**, **ANTs**, and **3D Slicer**.

#### TransformIndexToPhysicalPoint (76 call sites)

| Explicit type | Count | Resolves to | Would use default? |
|---------------|------:|-------------|--------------------|
| `<double>` | 66 | `double` | Yes |
| `<float>` | 4 | `float` | No — intentional single-precision |
| `<SpacePrecisionType>` | 2 | `double`\* | Yes (already matches default) |
| `<PointType::ValueType>` | 1 | `SpacePrecisionType` → `double`\* | Yes |
| `<TCoordinate>` | 1 | Forwarded (ImageBase internal) | Would keep explicit |
| **Subtotals** | **70 default-compatible** | | **92%** could drop `<double>` |
| | **4 intentionally different** | | **5%** would keep `<float>` |
| | **2 internal forwarding** | | **3%** would keep forwarded type |

#### TransformContinuousIndexToPhysicalPoint (16 call sites)

| Explicit type | Count | Resolves to | Would use default? |
|---------------|------:|-------------|--------------------|
| `<double>` | 10 | `double` | Yes |
| `<double, SpacePrecisionType>` | 2 | `double` | Yes |
| `<float>` | 3 | `float` | No — intentional |
| `<TIndexRep>` | 1 | Forwarded (ImageBase internal) | Would keep explicit |
| **Subtotals** | **12 default-compatible** | | **75%** could drop `<double>` |
| | **3 intentionally different** | | **19%** would keep `<float>` |
| | **1 internal forwarding** | | **6%** |

#### TransformPhysicalPointToContinuousIndex (66 call sites)

| Explicit type | Count | Resolves to | Would use default? |
|---------------|------:|-------------|--------------------|
| `<double>` | 13 | `double` | Yes |
| `<double, SpacePrecisionType>` | 5 | `double` | Yes |
| `<TCoordinate>` | 12 | `double` via `InterpolateImageFunction` | Would keep (generic context) |
| `<CoordinateType>` | 9 | `OutputPointType::CoordinateType` → `double` | Would keep (generic context) |
| `<ContinuousIndexValueType>` | 5 | `ContinuousIndex::ValueType` → `double` | Would keep (generic context) |
| `<ContinuousIndexType::ValueType>` | 4 | Same → `double` | Would keep (generic context) |
| `<TInterpolatorPrecisionType>` | 4 | Default `double` in ResampleImageFilter | Would keep (generic context) |
| `<TIndexRep>` | 3 | Forwarded (ImageBase internal) | Would keep |
| `<TParametersValueType>` | 2 | Transform default `double` | Would keep (generic context) |
| `<float>` | 3 | `float` | No — intentional |
| Other `ValueType` aliases | 6 | `double` | Would keep (generic context) |
| **Subtotals** | **18 could drop `<double>`** | | **27%** |
| | **45 generic forwarding** | | **68%** (all resolve to `double`) |
| | **3 intentionally `<float>`** | | **5%** |

#### Aggregate Summary

| Category | Count | % |
|----------|------:|--:|
| **Could drop explicit arg** (literal `<double>` or `<SpacePrecisionType>`) | 100 | 63% |
| **Generic forwarding** (type aliases that resolve to `double` in practice) | 48 | 31% |
| **Intentionally `<float>`** | 10 | 6% |
| **Total call sites** | **158** | 100% |

\* When `ITK_USE_FLOAT_SPACE_PRECISION` is OFF (the overwhelmingly common case).

### Key Findings

1. **Zero breaking changes.** Every existing call site — whether using
   `<double>`, `<float>`, `<TCoordinate>`, or any other type — continues to
   compile and behave identically.

2. **100% of forwarded types resolve to `double`** (`= SpacePrecisionType`)
   in standard ITK configurations. The forwarded aliases (`TCoordinate`,
   `CoordinateType`, `ContinuousIndexValueType`, etc.) exist for generic
   correctness in template code, not because the underlying type differs
   from the image's coordinate precision.

3. **Only 6% of calls use `<float>`**, all intentionally. These are in
   ITK's `ImageAdaptor` GTest (verifying `<float>` works), one BRAINSTools
   site (processing float-precision segmentation masks), and ITK's
   `TriangleMeshToBinaryImageFilter`. All would continue to specify
   `<float>` explicitly.

4. **`ITK_USE_FLOAT_SPACE_PRECISION` is respected.** If a downstream
   project configures ITK with single-precision spatial coordinates,
   `PointValueType = SpacePrecisionType = float`, and the default
   automatically tracks that choice — no code changes needed.

## Impact on Downstream Projects

| Project | Sites that could drop `<double>` | Breaking changes |
|---------|--------------------------------:|:----------------:|
| **BRAINSTools** | 60+ (entire migration PR #592) | None |
| **ANTs** | ~20 (estimated from build/ snapshot) | None |
| **3D Slicer** | ~10 (via embedded BRAINSTools + Slicer modules) | None |
| **ITK itself** | ~20 (tests + internal) | None |

## Implementation

The change is three lines in `Modules/Core/Common/include/itkImageBase.h`:

```diff
-  template <typename TCoordinate>
+  template <typename TCoordinate = PointValueType>
   [[nodiscard]] Point<TCoordinate, VImageDimension>
   TransformIndexToPhysicalPoint(const IndexType & index) const

-  template <typename TCoordinate, typename TIndexRep>
+  template <typename TCoordinate = PointValueType, typename TIndexRep>
   [[nodiscard]] Point<TCoordinate, VImageDimension>
   TransformContinuousIndexToPhysicalPoint(const ContinuousIndex<TIndexRep, VImageDimension> &) const

-  template <typename TIndexRep, typename TCoordinate>
+  template <typename TIndexRep = PointValueType, typename TCoordinate>
   [[nodiscard]] ContinuousIndex<TIndexRep, VImageDimension>
   TransformPhysicalPointToContinuousIndex(const Point<TCoordinate, VImageDimension> &) const
```

Branch: [`enh/default-template-arg-transform-point`](https://github.com/hjmjohnson/ITK/tree/enh/default-template-arg-transform-point)

Follow-up to PR [#868](https://github.com/InsightSoftwareConsortium/ITK/pull/868)
(the original PR that added the one-argument overloads).
