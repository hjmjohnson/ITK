import sys, pathlib

sys.path.insert(0, str(pathlib.Path(__file__).parent / "_ext"))
project = "ITK migration records prototype"
extensions = ["myst_parser", "sphinx_design", "itk_migration_records"]
myst_enable_extensions = ["colon_fence", "dollarmath", "fieldlist", "linkify"]
myst_heading_anchors = 3
html_theme = "furo"
exclude_patterns = ["_build"]
