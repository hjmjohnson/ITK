"""Generate ITK migration guides from YAML migration records (prototype)."""

import json
import pathlib
import re

import jsonschema
import yaml
from sphinx.util import logging

logger = logging.getLogger(__name__)

IMPACT_RANK = {"high": 0, "medium": 1, "low": 2}
IMPACT_BADGE = {"high": "bdg-danger", "medium": "bdg-warning", "low": "bdg-secondary"}
NAME_RE = re.compile(r"^(\d{8})_([A-Z][A-Za-z0-9]{2,59})$")
GH = "https://github.com/InsightSoftwareConsortium/ITK"


def _version_key(version):
    return [int(p) if p.isdigit() else p for p in re.split(r"[.ab]|rc", version)] + [
        version
    ]


def _words(descriptor):
    return re.sub(r"(?<=[a-z0-9])(?=[A-Z])|(?<=[A-Za-z])(?=[0-9])", " ", descriptor)


def load_records(major_dir, schema):
    manifest_path = major_dir / "releases.yaml"
    manifest = (
        yaml.safe_load(manifest_path.read_text()) if manifest_path.exists() else {}
    )
    release_of = {rid: rel for rel, ids in (manifest or {}).items() for rid in ids}
    records = []
    for path in sorted(major_dir.glob("*.yaml")):
        if path.name == "releases.yaml":
            continue
        m = NAME_RE.match(path.stem)
        if not m:
            logger.warning(
                "migration record %s: name does not match YYYYMMDD_Descriptor",
                path.name,
            )
            continue
        data = yaml.safe_load(path.read_text()) or {}
        try:
            jsonschema.validate(data, schema)
        except jsonschema.ValidationError as err:
            logger.warning("migration record %s: %s", path.name, err.message)
            continue
        rid = m.group(2)
        data.update(
            id=f"{major_dir.name}/{rid}",
            descriptor=rid,
            date=m.group(1),
            file=path.name,
        )
        data["release"] = release_of.get(rid)
        data.setdefault("title", _words(rid))
        records.append(data)
    return records


def _order(r):
    return (IMPACT_RANK.get(r.get("impact"), 3), r["file"])


def _badges(r):
    impact = r.get("impact")
    out = [
        (
            f"{{{IMPACT_BADGE[impact]}}}`{impact}`"
            if impact
            else "{bdg-light}`impact not rated`"
        )
    ]
    out += [f"{{bdg-info-line}}`{c}`" for c in r.get("categories", [])]
    out += [f"{{bdg-primary-line}}`{e}`" for e in r.get("environment", [])]
    return " ".join(out)


def _provenance(r):
    parts = []
    pr = r.get("pr")
    if pr and pr > 0:
        parts.append(f"[PR #{pr}]({GH}/pull/{pr})")
    if r.get("commit"):
        parts.append(f"[`{r['commit'][:11]}`]({GH}/commit/{r['commit']})")
    for key, label in (
        ("deprecated_in", "Deprecated in"),
        ("removed_in", "Removed in"),
    ):
        if r.get(key):
            parts.append(f"{label} {r[key]}")
    if r.get("legacy_guard"):
        parts.append(f"Old form available until `{r['legacy_guard']}`")
    return " · ".join(parts)


def render_record(r):
    anchor = r["id"].replace("/", "-")
    lines = [f"({anchor})=", f"### {r['title']}", "", _badges(r), ""]
    if r.get("summary"):
        lines += [r["summary"].rstrip(), ""]
    prov = _provenance(r)
    body = []
    if r.get("actions"):
        body += (
            ["**What you need to do**", ""] + [f"1. {a}" for a in r["actions"]] + [""]
        )
    for ex in r.get("examples", []):
        lang = ex.get("language", "text")
        if ex.get("note"):
            body += [ex["note"].rstrip(), ""]
        for side in ("before", "after"):
            if side in ex:
                body += [
                    f"*{side.title()}:*",
                    "",
                    f"```{lang}",
                    ex[side].rstrip(),
                    "```",
                    "",
                ]
    if r.get("renames"):
        body += ["| Old | New |", "| --- | --- |"]
        body += [f"| `{x['old']}` | `{x['new']}` |" for x in r["renames"]] + [""]
    if r.get("details"):
        body += [r["details"].rstrip(), ""]
    if r.get("links"):
        body += ["**Links:** " + ", ".join(f"<{u}>" for u in r["links"]), ""]
    if prov:
        body += [prov, ""]
    if body:
        lines += (
            [":::{dropdown} Details and examples", ":class-container: sd-mb-4", ""]
            + body
            + [":::", ""]
        )
    return lines


def render_guide(major, records):
    released = sorted(
        {r["release"] for r in records if r["release"]}, key=_version_key, reverse=True
    )
    groups = [
        (
            "Unreleased (on `main`)",
            [r for r in records if not r["release"] and not r.get("withdrawn")],
        )
    ]
    groups += [
        (
            f"ITK {rel}",
            [r for r in records if r["release"] == rel and not r.get("withdrawn")],
        )
        for rel in released
    ]
    lines = [
        f"# ITK {major} Migration Guide",
        "",
        f"Changes that downstream code may need to act on when moving to ITK {major}.",
        "This page is generated from the records in",
        f"[`migration_guides/records/itk{major}/`]({GH}/tree/main/Documentation/docs/migration_guides/records/itk{major}).",
        "",
        "## At a glance",
        "",
        "| Impact | Change | Release |",
        "| --- | --- | --- |",
    ]
    for title, recs in groups:
        for r in sorted(recs, key=_order):
            anchor = r["id"].replace("/", "-")
            lines.append(
                f"| {r.get('impact', 'not rated')} | [{r['title']}](#{anchor}) | {r['release'] or 'unreleased'} |"
            )
    lines.append("")
    for title, recs in groups:
        if not recs:
            continue
        lines += [f"## {title}", ""]
        for r in sorted(recs, key=_order):
            lines += render_record(r)
    return "\n".join(lines)


def _on_builder_inited(app):
    src = pathlib.Path(app.srcdir)
    root = src / app.config.itk_migration_records_dir
    schema = json.loads((root / "migration-record.schema.json").read_text())
    exports = {}
    for major_dir in sorted(
        p for p in root.iterdir() if p.is_dir() and re.fullmatch(r"itk\d+", p.name)
    ):
        major = major_dir.name[3:]
        records = load_records(major_dir, schema)
        out = src / "migration_guides" / f"itk_{major}_migration_guide.md"
        text = render_guide(major, records)
        if not out.exists() or out.read_text() != text:
            out.write_text(text)
        exports[major_dir.name] = records
    app.env.itk_migration_exports = exports


def _on_build_finished(app, exc):
    if exc is None:
        out = pathlib.Path(app.outdir) / "migration-records.json"
        out.write_text(
            json.dumps(getattr(app.env, "itk_migration_exports", {}), indent=2)
        )


def setup(app):
    app.add_config_value("itk_migration_records_dir", "migration_guides/records", "env")
    app.connect("builder-inited", _on_builder_inited)
    app.connect("build-finished", _on_build_finished)
    return {"parallel_read_safe": True}
