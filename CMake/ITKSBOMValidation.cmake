#[=============================================================================[
  ITKSBOMValidation.cmake - Validate the generated SPDX SBOM document

  Adds a CTest test that validates the SBOM JSON file produced by
  ITKSBOMGeneration.cmake. Checks:
    1. Valid JSON syntax
    2. Required SPDX 2.3 top-level fields present
    3. At least one package (ITK itself)
    4. DESCRIBES relationship present
#]=============================================================================]

if(NOT ITK_GENERATE_SBOM OR NOT BUILD_TESTING)
  return()
endif()

set(_sbom_file "${CMAKE_BINARY_DIR}/sbom.spdx.json")
if(NOT EXISTS "${_sbom_file}")
  return()
endif()

add_test(
  NAME ITKSBOMValidation
  COMMAND
    ${Python3_EXECUTABLE} -c
    "
import json, sys

with open(sys.argv[1]) as f:
    doc = json.load(f)

errors = []

# Required SPDX 2.3 fields
for field in ['spdxVersion', 'dataLicense', 'SPDXID', 'name',
              'documentNamespace', 'creationInfo', 'packages',
              'relationships']:
    if field not in doc:
        errors.append(f'Missing required field: {field}')

if doc.get('spdxVersion') != 'SPDX-2.3':
    errors.append(f'Expected spdxVersion SPDX-2.3, got {doc.get(\"spdxVersion\")}')

if doc.get('dataLicense') != 'CC0-1.0':
    errors.append(f'Expected dataLicense CC0-1.0, got {doc.get(\"dataLicense\")}')

# Must have at least ITK package
packages = doc.get('packages', [])
if len(packages) < 1:
    errors.append('No packages found')

itk_pkg = next((p for p in packages if p.get('name') == 'ITK'), None)
if itk_pkg is None:
    errors.append('ITK package not found')

# Check DESCRIBES relationship exists
rels = doc.get('relationships', [])
describes = [r for r in rels if r.get('relationshipType') == 'DESCRIBES']
if not describes:
    errors.append('No DESCRIBES relationship found')

# Validate package SPDX IDs are unique
spdx_ids = [p.get('SPDXID') for p in packages]
dupes = set(x for x in spdx_ids if spdx_ids.count(x) > 1)
if dupes:
    errors.append(f'Duplicate SPDX IDs: {dupes}')

# Check hasExtractedLicensingInfo references are valid
extracted = doc.get('hasExtractedLicensingInfo', [])
for entry in extracted:
    if 'licenseId' not in entry:
        errors.append(f'Extracted license missing licenseId')
    if 'extractedText' not in entry:
        errors.append(f'Extracted license missing extractedText')

if errors:
    for e in errors:
        print(f'SBOM ERROR: {e}', file=sys.stderr)
    sys.exit(1)

print(f'SBOM valid: {len(packages)} packages, {len(rels)} relationships, '
      f'{len(extracted)} extracted licenses')
"
    "${_sbom_file}"
)
set_tests_properties(
  ITKSBOMValidation
  PROPERTIES
    LABELS
      "SBOM"
)
