# 3D-printing guide

The current mechanical prototype was developed for PLA printing. Fusion 360 (`.f3d`) remains the released editable source format; export a mesh from the applicable file in the [CAD index](../cad/README.md) when preparing a print.

## Prototype printing configuration

### Common settings

- Model material: PLA
- Slicer settings: normal/default PLA profile
- Supports: **enabled for every printed part**

The project intentionally does not prescribe a nozzle size, layer height, infill, wall count, nozzle or bed temperature, print speed, support angle, or support density because those values were not supplied. Confirm the Fusion document units before export and do not rescale by assumption.

### Power Module Mount exception

The Power Module Mount uses a different support-material configuration:

- Model material: PLA
- Supports: enabled
- Support material: dedicated `Support for PLA` material

The support body/interface split is not documented. Do not infer which portion uses the dedicated material; configure the support system according to the printer/slicer capability while preserving the stated `Support for PLA` requirement.

## Printable-part and quantity table

| Part | Qty. | Model material | Supports | Support material | Evidence status |
| --- | ---: | --- | --- | --- | --- |
| Main body shell | 1 | PLA | Enabled | Standard | Printed and integrated |
| Lid | 1 | PLA | Enabled | Standard | Printed and integrated |
| Vent | 3 | PLA | Enabled | Standard | Printed and integrated; weatherproofing unverified |
| Sensor rod | 1 | PLA | Enabled | Standard | Printed and integrated |
| Sensor-rod lid | 1 | PLA | Enabled | Standard | Released model; not independently visible in photographs |
| Cable slot | 1 | PLA | Enabled | Standard | Released model; not independently visible in photographs |
| GNSS mount | 1 | PLA | Enabled | Standard | Printed and integrated |
| Power-module mount | 1 | PLA | Enabled | **`Support for PLA`** | Printed and integrated |
| Power-module cover | 1 | PLA | Enabled | Standard | Printed and integrated |
| Connecting base | 1 | PLA | Enabled | Standard | Designed, printed, fit verified, and integrated |

“Standard” means the ordinary support configuration associated with the selected normal/default PLA profile; it does not mean the dedicated product named `Support for PLA`. Support geometry and interface settings remain at the slicer's normal/default values because no project-specific values were supplied.

The complete print set contains ten part types and twelve pieces because three identical vents are required.

## Print workflow

1. Open the required `.f3d` file from the [CAD index](../cad/README.md) in Fusion 360.
2. Confirm the model's document units, then export an STL or 3MF for the slicer without changing scale.
3. Select PLA and the printer's normal/default PLA profile.
4. Enable supports for every part.
5. For the Power Module Mount, configure the support system to use `Support for PLA`; keep the model itself in PLA.
6. Inspect the sliced layers for missing geometry, unintended scaling, and inaccessible support material before printing.
7. Remove supports, clean mating surfaces and cable passages, then dry-fit before installing electronics.

## Post-processing and fit checks

- Remove support material without cutting into rails, slots, board ledges, cover interfaces, or the connecting-base footprints.
- Deburr cable passages and check that no printed edge can abrade insulation.
- Dry-fit the three vents, lid, sensor rod and lid, cable slot, GNSS mount, power-module mount and cover, and connecting base.
- Check that the PMS7003 openings remain unobstructed and that sensor faces are exposed as intended.
- Confirm that the 18650 pack and both power boards are restrained without compressing cells or shorting contacts.
- Reject cracked, warped, delaminated, or heat-damaged parts.

## Remaining reproducibility work

- Record the exact printer and saved slicer profile used in the next controlled build.
- Add verified STL or 3MF exports if the project later chooses to distribute ready-to-slice files.
- Measure critical fits and define clearances in CAD rather than compensating with undocumented slicer scaling.
- Record fastening or retention methods once confirmed by the original design or a controlled rebuild.

Continue with the [mechanical assembly guide](assembly-guide.md). Electrical connections remain documented in the separate [wiring guide](../wiring.md) and [power-system notes](../power-system.md).
