"""Sphinx extension: assemble YAML migration records into a MyST page."""

import json
import pathlib

import yaml

FENCE = "````"


def _version_key(release):
    return [int(p) if p.isdigit() else p for p in release.split(".")]


def assemble(records_dir, out_md, out_json):
    records = []
    for path in sorted(pathlib.Path(records_dir).glob("*.yaml")):
        data = yaml.safe_load(path.read_text()) or {}
        data["id"] = path.stem
        records.append(data)
    out_json.write_text(json.dumps(records, indent=2))
    by_release = {}
    for r in records:
        by_release.setdefault(r.get("release", "Unreleased"), []).append(r)
    order = sorted(
        (k for k in by_release if k != "Unreleased"), key=_version_key, reverse=True
    )
    if "Unreleased" in by_release:
        order.insert(0, "Unreleased")
    lines = ["# Migration guide (generated)", ""]
    for rel in order:
        lines += [f"## {rel}", ""]
        for r in sorted(by_release[rel], key=lambda r: -r.get("impact", 0)):
            title = r.get("title", r["id"])
            cats = ", ".join(r.get("categories", []))
            lines += [f"{FENCE}{{dropdown}} {title}", f":name: {r['id']}"]
            if cats:
                lines += [f"*{cats}*", ""]
            lines += [r.get("summary", ""), ""]
            for ex in r.get("examples", []):
                lang = ex.get("language", "")
                for label in ("before", "after"):
                    if label in ex:
                        lines += [
                            f"{label.title()}:",
                            "",
                            f"```{lang}",
                            ex[label].rstrip(),
                            "```",
                            "",
                        ]
            lines += [FENCE, ""]
    out_md.write_text("\n".join(lines))


def _on_init(app):
    src = pathlib.Path(app.srcdir)
    assemble(
        src / app.config.itk_migration_records,
        src / "migration_generated.md",
        pathlib.Path(app.outdir) / "migration-records.json",
    )


def setup(app):
    app.add_config_value("itk_migration_records", "records", "env")
    app.connect("builder-inited", _on_init)
    return {"parallel_read_safe": True}
