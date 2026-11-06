# Prototype transcript (2026-11-06)

Environment: Linux, Python 3.13 in a uv venv. Installed from PyPI:
reno 4.1.0, dulwich 1.2.21, Sphinx 9.2.0, myst-parser 5.1.0,
sphinx-design, furo, check-jsonschema. Log noise from dulwich
(`Exception ignored in ... PackData.__del__`) is trimmed below.

## 1. reno with ITK-style custom keys

The repository has `releasenotes/config.yaml` and three notes, copied in
`reno-notes/`. One commit holds note 1 and is tagged `v1.0.0`; a second
commit holds notes 2 and 3 and is untagged.

```bash
reno report --no-show-source .
```

Each custom key produces a warning, and the render omits all of them:

```text
The categories section of .../20261001_7050_RenameWidget.yaml is not a
recognized section. It should be one of: ResultsChange, ApiRemoved,
BuildSystem, ApiRenamed. This will be an error in a future release.
The impact section of .../20260901_7001_RemoveLegacyFoo.yaml does not
parse as a string or list of strings. Is the YAML input escaped properly?
The item {'language': 'cpp', 'before': 'foo->Bar();\n', 'after':
'foo->Baz();\n'} in the examples section of ... parses as a
<class 'dict'> instead of a string.
```

```text
Unreleased
==========
API renamed
-----------
- ``Widget`` is now ``Gadget``.

v1.0.0
======
API removed
-----------
- ``itk::Foo::Bar()`` was removed. Use ``Baz()``.
```

Findings:

- `release: v6.0.0` in note 1 is ignored. The note is placed in `v1.0.0`
  because that tag first contains it.
- `categories`, `impact`, `pr`, and `examples` are not rendered.
- The near-empty record (`categories` only) does not appear.
- The UIDs reno derives from ITK names are the last 16 characters of the
  stem: `050_RenameWidget`, `7051_EmptyRecord`, `_RemoveLegacyFoo`.

```bash
reno lint .; echo "exit=$?"
```

```text
unrecognized section name schema_version in .../20260901_7001_...yaml
unrecognized section name categories in ...
unrecognized section name impact in ...
unrecognized section name pr in ...
unrecognized section name release in ...
unrecognized section name examples in ...
exit=1
```

## 2. Shallow clone

```bash
git clone -q --depth 1 file://$P/repo shallow && cd shallow
reno list
```

```text
  File ".../reno/scanner.py", ... in _get_current_version
    commit = self._repo[commit.parents[0]]
KeyError: b'5fab6948a82f22bbb54622e22a4569b6dfe218f2'
exit=1
```

The same crash occurs with `--no-single-branch` followed by
`git fetch --tags`, this time in `_topo_traversal`. After
`git fetch --unshallow --tags`, `reno list` succeeds and matches
section 1.

## 3. Release branch merged back into main (ITK topology)

```text
* b51e13a (HEAD -> main, tag: v2.0.0) main change
*   02df63c Merge branch 'release'
|\
| * ab11656 (tag: v1.0.1, release) Fix on release
* | a1bbb6e Add notes 2,3
|/
* 5fab694 (tag: v1.0.0) Add note 1
```

`ab11656` adds `20261010_7060_ReleaseFix.yaml`, and the file is present in
the `main` tree. `reno list` on `main` returns:

```text
v2.0.0
    releasenotes/notes/20261001_7050_RenameWidget.yaml
    releasenotes/notes/20261002_7051_EmptyRecord.yaml
    releasenotes/notes/20261020_7070_MainAfterMerge.yaml
v1.0.0
    releasenotes/notes/20260901_7001_RemoveLegacyFoo.yaml
```

The output has no `v1.0.1` and no `ReleaseFix` note, and reno gives no
warning. `reno list --branch release` fails with
`ValueError: Unknown reference 'master'`, because `default_branch` is
`master` unless it is configured.

## 4. Sphinx with MyST

The `conf.py` loads `myst_parser`, `sphinx_design`, and `reno.sphinxext`.

`direct.md` uses ` ```{release-notes} ` with `:reporoot: ..`. The build
exits 0, but MyST parses reno's generated reStructuredText as Markdown,
so rst syntax shows up as page text:

```text
.. _relnotes_Unreleased:
Unreleased
.. releasenotes/notes/20261001_7050_RenameWidget.yaml @ b'a1bbb6e...'
Widget is now Gadget.
```

`evalrst.md` wraps the directive in ` ```{eval-rst} `, and it renders
cleanly:

```text
Unreleased / API renamed / Widget is now Gadget.
v1.0.0 / API removed / itk::Foo::Bar() was removed. Use Baz().
```

Neither page has collapsible output, because reno emits a heading per
version and per section with plain bullets beneath them.

## 5. YAML plus JSON Schema plus a small Sphinx extension

The files are in `custom/`.

```bash
check-jsonschema --schemafile migration-record.schema.json records/*.yaml
```

```text
ok -- validation done
exit=0
```

The three records pass, and one of them is `{}`. Then a bad record:

```text
bad_20261003_0_Bad.yaml::$.categories[0]: 'NotACategory' is not one of
['ApiRemoved', ...]
bad_20261003_0_Bad.yaml::$.impact: 'high' is not of type 'integer'
exit=1
```

`itk_migration.py` (58 lines) runs on `builder-inited`. It reads the
records, groups them by `release` (records with no release go under
Unreleased), sorts by `impact`, writes `migration_generated.md` with one
`{dropdown}` per record, and writes `migration-records.json` into the
HTML output for machine consumers.

```bash
sphinx-build -q -b html . _build; echo "exit=$?"
```

```text
exit=0
3 x <details class="sd-sphinx-override sd-dropdown sd-card sd-mb-3">
searchindex.js contains "gadget" and "baz"  (dropdown text is indexed)
```

The build needs no git history, so a shallow clone is fine.
