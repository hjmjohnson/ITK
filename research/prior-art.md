# Prior art for fragment-based change notes

Research for hjmjohnson/ITK#23 (map: hjmjohnson/ITK#22). Sources were read on
2026-11-06 from each project's own repository or documentation. Each claim is
marked **[verified]** (read in the primary source) or **[inference]** (my
reading of what it means for ITK).

## Summary

Every surveyed system avoids merge conflicts the same way: one file per change,
with a name that two PRs cannot both pick. They differ on three questions:

- When a fragment is assigned to a release: when it is consumed, from git
  history, or (in no surveyed tool) from a field inside the fragment.
- Whether fragments survive the release.
- Whether rendering happens at release time (output committed) or at docs-build
  time (output never committed).

ITK's design (an explicit `release` field, records kept forever, guide generated
at Sphinx time) is closest to **reno** plus CMake's development-mode rendering.
Nothing surveyed argues against generating at docs-build time. Two points argue
against plain JSON for hand editing. JSON has no multi-line strings, so code
examples must be escaped. JSON also has no comments, so a template cannot carry
inline guidance. Every tool that people edit by hand uses YAML or plain markup.

## CMake: `Help/release/dev/*.rst`

**Naming [verified].** One reStructuredText file per topic branch, named after
the topic. The sample file says: "Each document should be named and titled to
match the topic name to avoid merge conflicts."
<https://github.com/Kitware/CMake/blob/master/Help/release/dev/0-sample-topic.rst>
The review guide requires a `Help/release/dev/$topic.rst` for any new feature
or user-facing behavior change.
<https://github.com/Kitware/CMake/blob/master/Help/dev/maint.rst>

**Rendering during development [verified].** `Help/release/index.rst` includes
`dev.txt`, which renders the fragments through a toctree with `:glob:` and
`dev/*`. Unreleased fragments therefore appear in the development docs build,
at docs-build time, under "Changes Since Release".
<https://github.com/Kitware/CMake/blob/master/Help/release/dev.txt>
Sphinx sorts a globbed toctree alphabetically, so the order is by topic name
and carries no meaning [inference].

**Release cut-off [verified].** At release, `consolidate-relnotes.bash`
concatenates every `dev/*.rst` except the sample into `Help/release/$ver.rst`,
deletes the fragments, and adds the version to the index. A maintainer then
commits a second, hand-made pass: "Organize and revise $ver release notes ...
move each individual bullet into an appropriate section. Revise a few bullets."
<https://github.com/Kitware/CMake/blob/master/Utilities/Release/consolidate-relnotes.bash>

**Lessons for ITK [inference].**

- The release a note belongs to is decided by *where the file is* when the
  release is cut, not by a field. No author has to guess a version.
- CMake values a human editorial pass on the assembled notes. ITK never commits
  the generated guide, so that pass has nowhere to land. Grouping and wording
  must come from the records (impact, section, title) and from a hand-written
  wrapper page, or be fixed in the records themselves.
- Rendering fragments at docs-build time during development is long-standing
  CMake practice, which supports ITK's build-time generation.

## towncrier

**Naming [verified].** `<issue>.<type>[.<suffix>]`, for example
`1234.bugfix`. The type is the second dot-component, and "towncrier does not
care about the fragment's suffix." Orphan fragments with no issue start with
`+`. `issue_pattern` can enforce a regex on the issue part, and
`towncrier check` fails on fragment files with invalid names.
<https://github.com/twisted/towncrier/blob/trunk/docs/tutorial.rst>
<https://github.com/twisted/towncrier/blob/trunk/docs/configuration.rst>

**Content [verified].** The fragment body is free markup (rst or Markdown)
with no structured metadata. All metadata lives in the file name.

**Ordering [verified].** Categories come in configured order. Within a
category, entries are sorted by issue (`issue_key` groups by non-numeric
prefix, then by integer), and orphans sort last.
<https://github.com/twisted/towncrier/blob/trunk/src/towncrier/_builder.py>

**Release cut-off [verified].** `towncrier build --version X` writes the
release section into the news file after a start marker. It then deletes the
consumed fragments (`--keep` retains them). `--draft` renders to stdout
without writing. `towncrier check` verifies that a branch adds a fragment, and
it is skipped when the branch edits the news file itself.
<https://github.com/twisted/towncrier/blob/trunk/docs/cli.rst>

**Docs-build rendering [verified].** The third-party `sphinxcontrib-towncrier`
renders only the *unreleased* draft into Sphinx through a
`towncrier-draft-entries` directive. Released notes remain a committed file.
Its README names pip and ansible/pylibssh as users.
<https://github.com/sphinx-contrib/sphinxcontrib-towncrier>

**Lessons for ITK [inference].**

- Putting the PR number in the name gives uniqueness for free and enables a
  CI name check. The PR number is unknown until the PR is opened, though.
  Towncrier's `+orphan` prefix is its answer to that bootstrap problem. ITK
  needs a rule for records written before a PR exists, such as a placeholder
  rename or a check that the name's PR matches the PR being built.
- A `check` command that fails a PR with a malformed or missing record is the
  piece that keeps the system honest. ITK's schema validator can play that
  role in CI.
- Sorting by an identifier is deterministic but meaningless to readers. ITK's
  impact score is a better primary key.

## reno (OpenStack)

**Naming [verified].** `reno new <slug>` creates
`releasenotes/notes/<slug>-<16 hex>.yaml`. The unique ID is the last 16
characters of the name, and the design notes say authors "shouldn't need to
know any special values for naming their notes files (i.e., no change id or
SHA value that has special meaning)."
<https://opendev.org/openstack/reno/src/branch/master/doc/source/user/usage.rst>
<https://opendev.org/openstack/reno/src/branch/master/doc/source/user/design.rst>
<https://opendev.org/openstack/reno/src/branch/master/reno/scanner.py>
(`_get_unique_id`)

**Format [verified].** YAML with configurable sections (`prelude`,
`features`, `issues`, `upgrade`, `deprecations`, `critical`, `security`,
`fixes`, `other`). Section values are lists of rst strings. Multi-line rst uses
the YAML `|` block scalar. Empty sections are omitted, and validation runs in
the loader during every report and Sphinx build.

**Release cut-off [verified].** None by hand. reno scans git history and
assigns each note to the earliest version tag whose history contains it
(`earliest_seen` in the scanner). It assumes trunk-based development with
backports cherry-picked. It "does not currently support" git-flow, where
stable branches merge back into `master`. A note edited later is reported in
its original release, so typos can be fixed after release.

**Ordering [verified].** "Notes are output in the order they are found when
scanning the git history of the branch using topological ordering. This is
deterministic, but not necessarily predictable." The design goals reject
custom ordering within a release.

**Rendering [verified].** The `reno.sphinxext` `release-notes` directive
renders notes at Sphinx build time, so fragments are kept forever and never
consolidated. Scanning cost grows with history: one design goal is "We must
not make things progressively slow down to a crawl over years of usage". A
`reno cache` command writes the scan result so builds without git history can
still render.
<https://opendev.org/openstack/reno/src/branch/master/doc/source/user/sphinxext.rst>
<https://opendev.org/openstack/reno/src/branch/master/reno/cache.py>

**Lessons for ITK [inference].**

- reno is the closest precedent for ITK: structured fragments, kept forever,
  rendered at docs-build time. It shows the model works at scale across
  OpenStack.
- reno derives the release from git so authors never write it. Read the Docs
  performs a shallow clone of only the branch being built, so git-derived
  release assignment would need `git fetch --unshallow` in a `post_checkout`
  job. <https://docs.readthedocs.com/platform/stable/build-customization.html>
  ITK's explicit `release` field avoids that dependency and survives backports
  that git-flow merges would confuse. ITK merges release branches back into
  `main` (for example `ca333c20af1 Merge branch 'release'`), which is the
  git-flow pattern reno rejects. The cost is that a PR
  author must guess the release, and a PR that slips past a release then
  carries the wrong value.
- reno uses YAML, not JSON, specifically so that multi-line rst survives hand
  editing.

## scriv

**Naming [verified].** `changelog.d/<YYYYMMDD>_<HHMMSS>_<git user>_<branch>`
plus `.rst` or `.md`. "The file name starts with the current date and time, so
that entries can later be collected in chronological order." Main-branch names
are left out. `fragment_name_fields` configures the components.
<https://github.com/nedbat/scriv/blob/main/docs/commands.rst>

**Content [verified].** Free rst or Markdown, with category headings left
commented out in the template for the author to uncomment. Fragments are
"re-parsed when collected", so heading underlines need not match.

**Ordering [verified].** "The fragments are combined in each category, in
chronological order", which is file-name order.
<https://github.com/nedbat/scriv/blob/main/docs/concepts.rst>

**Release cut-off [verified].** `scriv collect --version X` inserts the entry
at a `scriv-insert-here` marker and deletes the fragments (`--keep` retains
them). Its philosophy states "The changelog file in the repo should be the
source of truth."
<https://github.com/nedbat/scriv/blob/main/docs/philosophy.rst>

**Lessons for ITK [inference].**

- scriv's date-first name is the nearest match to ITK's
  `YYYYMMDD_<PR>_<Descriptor>`, and it confirms that a date prefix gives a
  useful default sort and easy browsing.
- The date is the *creation* date, not the merge date. A record started early
  and merged late sorts early. ITK should treat the date as an authoring hint,
  not as release evidence.
- scriv's philosophy argues *for* a committed changelog. That runs against
  ITK's never-commit rule. The concern is real for consumers who read the repo
  without building docs, but ITK's JSON records are themselves that
  repository-resident source of truth.

## LLVM release notes

**Current practice [verified].** One hand-edited `docs/ReleaseNotes.md` per
subproject (MyST Markdown), with section headers and HTML comments that tell
authors to "just add an entry at the end of this list." When the version is
bumped on `main`, `clear-release-notes.py` overwrites each file with its
`ReleaseNotesTemplate.txt`. The release branch keeps the populated copy.
<https://github.com/llvm/llvm-project/blob/main/llvm/docs/ReleaseNotes.md>
<https://github.com/llvm/llvm-project/blob/main/llvm/utils/release/clear-release-notes.py>
<https://github.com/llvm/llvm-project/blob/main/llvm/docs/HowToReleaseLLVM.md>
The developer policy asks that potentially breaking changes go in a
"Potentially Breaking Changes" section "with sufficient information and
examples" and be announced on Discourse.
<https://github.com/llvm/llvm-project/blob/main/llvm/docs/DeveloperPolicy.md>

**libc++ [verified].** `libcxx/docs/ReleaseNotes.rst` only includes
`ReleaseNotes/<N>.rst`, keeping one file per release (now `23.rst` and
`24.rst`).

**Fragment RFC [summarized from the thread, not independently verified].**
"[RFC] Reducing release note merge conflicts with per-change fragments"
(2026-10-16) proposes `ReleaseNotes.d/next/<timestamp>.<random-id>.md`. Each
file would carry YAML front matter (`schema_version`, `module`, `section`,
`tags`, and optional `pull_requests` and `issues`), a Markdown body, a
`ReleaseNotes.yaml` registry of sections, and assembly during the Sphinx
build. Replies called it over-engineered and said resolving conflicts "tends
to be a few seconds of work". They objected to requiring a tool to add a note
and preferred a filesystem-only layout (directories per section,
concatenated). As of 2026-10-19 it had no consensus.
<https://discourse.llvm.org/t/rfc-reducing-release-note-merge-conflicts-with-per-change-fragments/92533>

**Lessons for ITK [inference].**

- LLVM's RFC independently arrives at ITK's design: a schema version,
  structured metadata, a Markdown body, and Sphinx-time assembly. Its
  reception is the main warning. Contributors resist a mandatory tool and
  heavy metadata. ITK's "nearly every field optional, editable by hand, no
  tool needed to create one" stance answers the strongest objection.
- Putting `schema_version` in each record is cheap insurance for later schema
  changes.
- A "Potentially Breaking Changes" section with examples is LLVM's version of
  ITK's before/after examples plus impact score.

## Comparison

Naming:

- CMake: `<topic>.rst`
- towncrier: `<issue>.<type>.md`
- reno: `<slug>-<16hex>.yaml`
- scriv: `<date>_<time>_<user>_<branch>.md`
- LLVM RFC: `<timestamp>.<random>.md`
- ITK plan: `YYYYMMDD_<PR>_<Descriptor>.json`

| System    | Release set by  | Kept? | Rendered at  |
|-----------|-----------------|-------|--------------|
| CMake     | file location   | no    | dev: docs    |
| towncrier | consumed at cut | no    | release      |
| reno      | git tag history | yes   | docs build   |
| scriv     | consumed at cut | no    | release      |
| LLVM now  | file reset      | n/a   | docs build   |
| ITK plan  | `release` field | yes   | docs build   |

Format: CMake rst; towncrier rst or md; reno YAML; scriv rst or md; LLVM
MyST md, with the RFC proposing YAML front matter plus md.

## What this implies for ITK's decisions [inference]

**Schema.**

- Add a `schema_version` field (LLVM RFC) and keep everything else optional
  (answers LLVM's objections).
- Section and category sets live in one registry or enum in the schema, as
  reno's `sections` config and LLVM's `ReleaseNotes.yaml` do.
- Validate in CI on every PR, as towncrier `check` and reno's loader do.

**Against plain JSON.** JSON has no comments and no multi-line strings.
Before/after code would become `\n`-escaped strings, which nobody can review
in a diff. Options, in order of least disruption:

1. Allow `code` as an array of lines.
2. Let examples reference sidecar files (`<record>.before.cxx`).
3. Accept YAML or JSON5 input, validated against the same JSON Schema (JSON
   Schema validates YAML data unchanged), and emit JSON for machine consumers
   at build time.

Every hand-edited system surveyed uses YAML or plain markup. None uses JSON.

**Naming.**

- The PR number gives uniqueness, as towncrier does, but is unknown until the
  PR opens. Define the pre-PR state, for example `YYYYMMDD_0_<Descriptor>`,
  with CI checking that the PR in the name matches the PR being built.
- Treat the date as authoring order (the scriv caveat), not as release
  evidence.

**Release cut-off.** The explicit field suits RTD's shallow clone and ITK's
merge-back branching, where reno's git derivation would not.

- Allow an absent `release` to mean "next / unreleased", as CMake's `dev/`
  and towncrier's draft do, so authors need not guess.
- Stamp the release with a script at release time, mirroring
  `consolidate-relnotes.bash` as an in-place JSON edit.
- CI can warn when a record's release is already tagged and the PR has not
  merged.

**Ordering.** Group by release, then section, then impact descending, then
file name. Every surveyed tool falls back to a mechanical order. None lets
authors order entries by hand within a release (reno rejects it explicitly).

**Rendering.** Docs-build generation has direct precedent: reno, CMake dev
notes, sphinxcontrib-towncrier, and the LLVM RFC. The cost is losing CMake's
editorial pass and scriv's committed changelog. Mitigate with the local
preview command, a hand-written static intro per release, and editing records
directly when wording needs revision.
