# Adopting reno or another tool for migration records

Research for hjmjohnson/ITK#34 (map: hjmjohnson/ITK#22). Builds on
`research/prior-art.md` (#23) and `research/inventory.md` (#24) without
repeating them. Sources were read on 2026-11-06. The reno source is the
`master` branch of <https://opendev.org/openstack/reno> at `7a0bd5d`
(2026-10-12), and the release prototyped is reno 4.1.0 from PyPI. Claims
are tagged **[verified]** (checked in source, docs, a registry, or the
prototype) or **[inference]** (my judgment). The prototype commands and
their output are in `tool-adoption/transcript.md`.

## Recommendation

**(c) A small custom tool that borrows reno's YAML note format and
validates it with a JSON Schema.** The tool has three parts:

1. **Records.** One YAML file per change in a records directory, named
   `YYYYMMDD_<PR>_<CamelCaseDescriptor>.yaml`. Every key is optional, so
   `{}` is a valid record. YAML block scalars (`|`) hold multi-line code,
   as they do in reno, and comments can carry template guidance.
2. **Schema and check.** `migration-record.schema.json` (JSON Schema
   2020-12) is enforced by the existing `check-jsonschema` pre-commit hook
   and in CI. A short script checks the file name pattern. This adds no
   new tool.
3. **Assembler.** A Sphinx extension of about 60 lines. On
   `builder-inited` it groups records by an explicit `release` field (no
   field means Unreleased), orders them by impact, and writes a MyST page
   with one `sphinx_design` dropdown per record. It also writes the
   records to the HTML output as JSON for AI agents and other machine
   consumers. The page is never committed. The same function can run
   locally to preview.

The prototype in `tool-adoption/custom/` builds with Sphinx 9.2,
myst-parser 5.1, sphinx-design, and Furo. It renders collapsible entries
that the search index covers, and it needs no git history [verified].

Option (b), reno with a thin layer, is not thin. The layer would have to
replace three of reno's parts. Its own linter, because `reno lint` exits
1 on every custom key. Its own renderer, because reno drops custom keys.
Its own release assignment, because reno ignores a `release` field, drops
notes that ITK's merge-back topology brings in, and fails on a shallow
clone. Once those are replaced, what remains of reno is the YAML
convention, which (c) keeps [inference from the verified findings below].

Option (a), reno as-is, fails on release membership alone [verified, §3].

## reno in depth

### 1. Custom sections and fields

**Custom sections [verified].** The `sections` option is configurable
and supports subsections. Each entry is `[key, title]`, optionally with
a level of 1 to 3 (`reno/config.py`, `sections`). ITK's categories could
be sections such as `ApiRemoved: [...]`.

**Unknown keys [verified].** `Loader.parse_note_file` (`reno/loader.py`)
does three things with a key outside `sections`:

- logs "is not a recognized section". Release 4.1.0 adds "This will be an
  error in a future release", and its source carries a
  `TODO(stephenfin)` to that effect.
- raises `ValueError` when the new `strict` option is set (`master`,
  commit `52ade22`, unreleased).
- requires every value to be a string or a list of strings. Integers
  (`impact: 3`, `pr: 7001`) and mappings (`examples: [{before: ...}]`)
  each produce a further warning.

The key is kept in the parsed dict, but `formatter.format_report`
iterates only `config.sections`, so custom keys never render. In the
prototype, `categories`, `impact`, `pr`, `release`, `examples`, and
`schema_version` are all silently missing from the output. `reno lint`
reports `unrecognized section name ...` for each one and exits 1.

**Rendering custom fields [verified, with inference].** The Sphinx
directive calls `formatter.format_report` directly
(`reno/sphinxext.py`), and the formatter has no hook or template. To
render custom fields, ITK would need its own directive that reuses
`reno.loader.Loader` and replaces the formatter. That means depending on
internal, unversioned APIs [inference].

**Section keys and categories are not the same thing [inference].** A
reno section holds prose bullets. An ITK record is one change with
several categories, so the same text would be repeated under each
category's section. ITK's model (one change carrying many categories)
does not fit reno's model (one section carrying many bullets).

### 2. File naming

**[verified]** `reno new <slug>` always writes `<slug>-<16 hex>.yaml`
(`create.py`, `_pick_note_file_name`), and no option changes the
pattern. The scanner accepts any `*.yaml` file in the notes directory
(`scanner._note_file`), so hand-made ITK names work. The UID is the last
16 characters of the file stem, or the first 16 if those contain `-`
(`scanner._get_unique_id`). For the prototype's names that gives
`050_RenameWidget`, `7051_EmptyRecord`, and `_RemoveLegacyFoo`.

Two ITK records whose descriptors share their last 16 characters would
collide. reno's documentation warns that a collision means "scanner
operations may fail or shadow one of the notes". `master` adds a
duplicate-UID check and a `uid_overrides` map (`e686f07`, `fe5b7c7`,
both unreleased) [verified]. reno's own design goal is that authors
"shouldn't need to know any special values for naming their notes"
(`design.rst`), which runs against ITK's PR-in-the-name convention
[verified].

### 3. Release membership

**How it is computed [verified].** The scanner walks the current
branch's history in topological order. It assigns each note to the
earliest version tag whose history contains the commit that added it.
Untagged notes go under `<last tag>-<n>`, retitled by
`unreleased_version_title`. The prototype placed a note carrying
`release: v6.0.0` into `v1.0.0`, the first tag that contained it.

**Overrides [verified].** No note-level release field exists. The
options `earliest_version`, `version` (Sphinx), `branch`,
`stop_at_branch_base`, `ignore_notes`, and `collapse_pre_releases` all
choose which part of the history to scan. None of them sets a note's
release. `reno cache` writes the scan result to
`releasenotes/notes/reno.cache`, and the loader reads it in place of git
when it is present (`loader._load_data`). Using it would mean committing
generated output, or producing it from a full clone before the docs
build.

**Shallow clone [verified].** `reno list` on a `--depth 1` clone fails
with `KeyError` in `_get_current_version`. With `--no-single-branch`
followed by `git fetch --tags` it fails again, in `_topo_traversal`. It
works after `git fetch --unshallow --tags`. reno's usage guide says that
GitHub Actions and Read the Docs "use shallow clones by default" and
that clones must include all tags and branches. On Read the Docs that
means a `post_checkout` step that unshallows ITK's full history on every
docs build. That history is large: 586 `Merge branch 'release...'`
commits on `main` alone [verified count; build-time cost inferred].

**Merge-back topology [verified].** The prototype mirrored ITK's
pattern. A note was added on `release`, tagged `v1.0.1`, and merged into
`main` with `--no-ff`. reno on `main` lists neither `v1.0.1` nor that
note, gives no warning, and exits 0. reno's `design.rst` states the
limitation: git-flow, where a stable branch "is later merged back into
`master`", is "not compatible with *reno*". `reno list --branch release`
also fails until `default_branch` is set, because the default is
`master`.

### 4. Sphinx and MyST

**[verified]** The directive is registered by `reno.sphinxext` as
`release-notes`. It generates reStructuredText and parses it with
`nested_parse_with_titles` in the calling document's parser. On a MyST
page, a fenced ` ```{release-notes} ` therefore runs reno's rst through
the Markdown parser, and anchors (`.. _relnotes_...:`) and source
comments appear on the page as literal text. Wrapping the directive in
` ```{eval-rst} ` renders correctly.

The output is one heading per version and per section with plain
bullets. It has no collapsible form. A note's text could include a raw
`.. dropdown::`, but each bullet is one string, so per-change metadata
has nowhere to go [verified output; workaround inferred].

### 5. Health

| Item | Finding |
|---|---|
| License | Apache-2.0 |
| Last release | 4.1.0, 2024-03-04 (PyPI) |
| Since release | 28 commits, unreleased |
| Active authors | 1 since 2025 (S. Finucane) |
| Python | `>=3.11` on `master` |
| Dependencies | PyYAML, dulwich, packaging |

Sources: `pyproject.toml`, `requirements.txt`, the PyPI JSON API, and
`git log` [verified]. Commits per year since 2021: 16, 4, 11, 1, 2, 25.
The 2026 burst (strict mode, typing, pyproject configuration, UID checks)
is almost entirely one maintainer's work, and none of it is released.
The project is alive but has a bus factor of one, and its next release
will change behavior that matters to ITK (strict validation) [inference].

## Alternatives

**towncrier [verified].** MIT, 26.9.0 released 2026-09-04, 70 open
issues. Fragments are free text, and all metadata sits in the file name
(`<issue>.<type>`). `towncrier build` consumes the fragments into a
committed news file. `sphinxcontrib-towncrier` (BSD, 0.5.0a0, 2025-02)
renders only the unreleased draft. `sphinx-changelog` (BSD, 1.6.0,
2024-08) pins `towncrier==24.8.0`. None of them supports structured
fields or keeps fragments forever.

**scriv [verified].** Apache-2.0, 1.8.0 released 2025-12-30. Its
date-first names are the closest match to ITK's. Fragments are free rst
or Markdown with category headings, and `scriv collect` consumes them
into a committed changelog. It has no structured fields and no Sphinx
directive.

**changie [verified].** MIT, a Go binary, v1.26.0 released 2026-08-20.
Fragments are YAML (`kind`, `body`, `time`, `custom`), and
`fragmentFileFormat` sets the name from a template. However, `custom` is
`map[string]string` (`core/change.go`), so lists and before/after pairs
do not fit. `changie batch` consumes fragments into committed version
files. It has no Sphinx integration and adds a non-Python tool.

**YAML, JSON Schema, and a small assembler [verified by prototype].**
JSON Schema 2020-12 validates YAML data unchanged. `check-jsonschema`
(0.39.0, 2026-10-26) ships a `check-jsonschema` pre-commit hook for
"JSON or YAML files" (`.pre-commit-hooks.yaml`). `jsonschema` is MIT.
The assembler is ITK code, but it is about 60 lines that use only PyYAML
and Sphinx's public `builder-inited` event.

| Tool | License | Active | Custom fields | No git | Sphinx | Cost |
|---|---|---|---|---|---|---|
| reno | Apache | 1 dev | dropped | no | rst only | med |
| towncrier | MIT | yes | none | yes | draft | low |
| scriv | Apache | yes | none | yes | none | low |
| changie | MIT | yes | strings | yes | none | med |
| YAML+schema | MIT* | n/a | full | yes | MyST | low |

Notes on the table:

- "No git" means a release can be assigned without walking git
  history.
- `*` marks the license of `jsonschema`. `check-jsonschema` reports no
  SPDX ID on GitHub.
- Cost is my estimate of ITK-side setup and upkeep [inference].
- towncrier, scriv, and changie consume their fragments at release
  time, which conflicts with ITK's rule that records are kept forever.

## Trade-offs of the recommendation

**Gained [inference].**

- Every ITK requirement is met with no fight against a tool's model:
  - the file name;
  - optional fields, with `{}` valid;
  - an explicit release;
  - lists of categories;
  - several before/after pairs in several languages;
  - collapsible, searchable MyST;
  - JSON output for agents;
  - a shallow-clone build.
- Validation reuses a pre-commit hook ITK can pin like its others.

**Cost [inference].**

- ITK owns about 60 lines of assembler, a schema, and a name check.
- Authors, or a release script, must set `release`. The prior-art note
  covers the mitigation: an absent release means Unreleased, and the
  release manager stamps records when a release is cut.
- Nobody outside ITK maintains the format.

**What to borrow from reno [inference].**

- YAML block scalars for code.
- Records kept forever and rendered at docs-build time.
- A configurable section or category registry, held in the schema's
  `enum`.
- reno's lesson that a validation step must run on every PR.
- Field names that do not clash with reno's section keys, which leaves
  a later move to reno open.

## Open questions for the spec (#25, #28)

- Should `release` be stamped by a release script, or written by the
  author with a CI warning when it names an already-tagged release?
- Should the name check require the PR in the file name to match the PR
  being built, and what placeholder applies before a PR exists?
