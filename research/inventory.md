# Inventory of existing migration-guide entries

Ticket: hjmjohnson/ITK#24 (map hjmjohnson/ITK#22). Snapshot of
`origin/main` at 4902ee99b7c (2026-11-06). Per-entry data is in
`inventory.csv` beside this file.

## Method

- Source files: everything in `Documentation/docs/migration_guides/`.
- An entry is a level-2 section, in either heading style: setext `----`
  or ATX `##`. Fenced code was skipped, so `# comment` lines in code
  blocks were not counted. Each topic file is one entry, and the
  "Fine-grained versioning" section of `index.md` is one more.
- Introducing commit: `git log -S'<heading>' --reverse -- Documentation/`,
  checked against the oldest commit from
  `git log -L<start>,<end>:<file>`. Where the two differ, the `-L`
  commit was read by hand (see "Attribution").
- PR: `gh api repos/InsightSoftwareConsortium/ITK/commits/<sha>/pulls`,
  merged PRs only. The PR is the one that added the guide text, which is
  sometimes a separate DOC commit in the same PR as the code change.
- Environment, before/after, and impact were judged by reading every
  section. `has_before_after` values: `yes` (explicit old/new code pair),
  `code-only` (code shown, no pair), `mapping` (old name to new name in
  prose, a list, or a table), `no` (prose only).

## Counts

| Source               | Entries |
|----------------------|--------:|
| itk_6 guide          |      42 |
| itk_5 guide          |      12 |
| python_spatial_key   |       1 |
| joint_histogram (MI) |       1 |
| index.md             |       1 |
| **Total**            |  **57** |

The ITK 5 guide also has one empty grouping heading, "Backported ITKv6
features", which is not counted.

Environment, by tag (an entry can carry several tags; 57 entries, 74
tags):

| Environment     | Tagged | Primary |
|-----------------|-------:|--------:|
| C++             |     35 |      33 |
| CMake           |     12 |       7 |
| Python          |      8 |       6 |
| build/toolchain |      8 |       5 |
| IO/data         |      7 |       5 |
| wrapping        |      4 |       1 |

Before/after code:

| has_before_after | Entries | Share |
|------------------|--------:|------:|
| yes              |       7 |   12% |
| code-only        |      11 |   19% |
| mapping          |      16 |   28% |
| no               |      23 |   40% |

Only 7 of 57 entries (12%) carry an explicit before/after code pair;
18 (32%) carry any code at all. Rough impact: 7 high, 23 medium, 27 low.

## Attribution

- **No GitHub PR (6):** the ITK 5 sections "Legacy code removed",
  "C++11", "Modern CMake requirement", "Updated style", "Multithreading
  refactored", and "Update scripts" came from bf1bf57 (2018-04-09), and
  "Class changes" came from 04b132c. Both commits carry a Gerrit
  `Change-Id` and predate ITK's move to GitHub PRs. These sections were
  then extended by 3 to 35 later commits each, so no single PR describes
  their current content.
- **Ambiguous with a PR (5, all ITK 6):** "Class changes" is a bucket of
  4 unrelated changes from 7 commits; the CSV gives the PR of the first
  (#4925). "ITKFEM ... removed" (#6524) replaced an earlier FEM entry
  from #5995. "Optional Eigen-backed `itk::bridge::Math::SVD`" came from
  #6487 and was renamed in #6768. "GradientStructureTensorImageFilter"
  came from #6602 and was rewritten in #7061. "`ITK_AUTOLOAD_PATH`" came
  from #6985 and was renamed in #7043.
- **Total with unattributable or ambiguous provenance: 11 of 57.** The
  other 46 map to one PR.
- Three PRs introduced two entries each: #4715 and #4744 (ITK 6), and
  #6569 introduced both an ITK 6 stub and the topic file. #7061
  introduced one entry and rewrote another.

## Content patterns the schema must handle

1. **Multiple before/after pairs per entry.** "Modern CMake Interface
   Libraries" has 5 pairs across 4 subsections; "Byte-order macros" has
   2; ITK 5 "Multithreading refactored" has several. Code examples must
   be a list, each with its own language and caption.
2. **Code in many languages:** cpp, cmake, python, bash/sh, plus `txt`
   and `text` blocks holding mapping tables and error messages. An
   error-message field is worth having ("AnatomicalOrientation", ITK 5
   "Strongly Typed Enumerations").
3. **Prose-only entries are the plurality (40%).** Body prose must be
   enough for a valid record.
4. **Rename mappings** (old symbol to new symbol) appear in 28% of
   entries, as inline prose, bulleted lists, or a two-column text block
   (19 macro pairs). A structured `renames` list would serve tools.
5. **Option and toolchain changes, not API:** CMake options
   (`ITKV4_COMPATIBILITY`, `ITK_PYTHON_RELEASE_GIL`,
   `ITK_ALPHA_FEATURE_CXX*`), targets (`GTest::gtest`, `ITK::<M>Module`),
   minimum versions (VTK 9.1, Python 3.11, CMake 3.10.2).
6. **Deprecation timelines:** deprecated now, removed under
   `ITK_FUTURE_LEGACY_REMOVE` or `ITK_LEGACY_REMOVE`, removed in ITK 7
   (FEM, issue #6511), or "available since v5.4.5" (backport).
7. **Behavior changes with no code edit:** numeric results, output
   origin, eigenvector signs, file content. These need a "re-baseline"
   flag and the affected classes.
8. **Standard subsections** recur in newer entries: "What you need to
   do" (23 ITK 6 entries), "Concerns", "Rationale"/"Why this changed".
9. **Links:** GitHub issues (#6468, #6511, #6706, #7057), commit
   permalinks (ITK 5 C++11 list), external docs (PEP 562, cppreference),
   and a pinned commit hash for vendoring.
10. **Cross-references and duplicates:** the ITK 6 MI entry is a stub
    pointing to its topic file; AnatomicalOrientation appears in both
    guides; "Accessing outdated ITKv5 migration scripts" is a sub-note
    of the entry above it.
11. **Bucket sections** ("Class changes" in both guides) hold many
    unrelated changes and must be split into one record per change. ITK
    5 "Class changes" holds about 23 paragraphs.
12. **Long entries with tables:** the SVD entry has a performance table;
    the Python spatial-key file has a key table; the MI topic file is a
    multi-section impact report with a checklist.
13. **Non-change entries:** "The `itk::bridge` namespace" is a support
    policy, and `index.md` describes a versioning facility. The schema
    needs a kind such as `policy` or `note` alongside `change`.
14. **Multi-environment entries** (16 of 57) need environment as a list.

## Categories

Each CSV row carries a `categories` list (CamelCase, `;`-separated).
`ResultsChange` and `CompilerEnvironment` are the user's; the rest are
proposed from the entries. Every category covers at least 3 entries, so
none was merged. Counts are entries tagged (57 entries, 102 tags).

- **ApiRemoved** (17): a public class, macro, header, option, or script
  is gone.
- **ResultsChange** (16): numerical or behavioral output differs with
  unchanged calling code.
- **ApiDeprecated** (13): still present, warned or removed under
  `ITK_LEGACY_REMOVE` / `ITK_FUTURE_LEGACY_REMOVE`.
- **ApiRenamed** (13): a one-to-one replacement name or type exists.
- **BuildSystem** (12): CMake options, variables, targets, or module
  declarations.
- **PythonWrapping** (11): the Python package or its wrapping changes.
- **FileFormat** (7): what an ImageIO/TransformIO reads or writes.
- **CompilerEnvironment** (4): compiler, C++ standard, or header-form
  requirements.
- **Dependency** (3): a minimum version of a third-party tool or
  library (VTK, Python, CMake).
- **Performance** (3): speed or memory change worth acting on (GIL,
  PocketFFT, SVD).
- **DefaultChanged** (3): a default value flipped (HDF5 compression,
  NIfTI non-finite handling, `GetUseSeriesDetails`).

Performance, DefaultChanged, and Dependency sit at 3 entries each. If
the vocabulary must shrink, fold Dependency into CompilerEnvironment
(both are toolchain floors) and DefaultChanged into ResultsChange.

**No category:** "The `itk::bridge` namespace" (a support policy) and
ITK 5 "Updated style" (ITK's own style, nothing for downstream to do).
These suggest a record kind such as `note`, separate from categories.

**Hard to tell apart:**

- ApiRemoved vs ApiDeprecated: many entries are both over time
  (deprecated in 6.0, removed under `ITK_FUTURE_LEGACY_REMOVE`). A
  deprecation-timeline field would carry this better than two tags.
- ApiRenamed vs ApiDeprecated: a rename that keeps the old name as a
  deprecated alias fits both (C++11 macros, `CoordRepType`).
- FileFormat vs ResultsChange: IO changes alter output files, so the
  tags co-occur in 4 of 7 FileFormat entries.
- DefaultChanged vs ResultsChange: a flipped default changes results
  for anyone who never set it.
- BuildSystem vs Dependency: VTK and CMake minimums carry both.

## Defects found while reading

The problem in ITK#7131 shows in the file itself. Line 2 of
`itk_6_migration_guide.md` reads `========This guide documents ...`:
the H1 underline and the first paragraph were joined, so the title does
not render as a heading. `git blame` puts it in 993f310 (PR #6594),
which was appended at the end of the guide. Three ITK 6 headings
(lines 1053, 1064, 1215) also lack a blank line before them, a sign of
appends during conflict resolution. The ITK 6 guide mixes setext (19)
and ATX (23) level-2 headings.
