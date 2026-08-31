# Mechanical CAD index

The enclosure is a two-assembly prototype: the vertical **Weather Station Body** contains the ESP32-S3, sensor interfaces, PMS7003, GNSS hardware, and the sensor rod; the horizontal **Power Module** contains the 18650 battery pack, Waveshare Solar Power Manager (D), and XL6009 DC-DC module. The two assemblies are joined by a **Connecting Base**.

![Printed weather-station body and power module joined as one prototype](images/assembled-two-module-system.jpg)

The ten editable source models are Autodesk Fusion 360 archives (`.f3d`). Fusion 360 is the released editable format so builders can inspect and modify the design. No STL, 3MF, or STEP exports were supplied. Open a model in Fusion 360, confirm its document units, and export a mesh for your slicer without changing scale.

## Directory layout

```text
hardware/cad/
├── station-body/       # seven editable station-body parts
├── power-module/       # mount and cover
├── assembly/           # editable connecting base and part documentation
└── images/             # CAD previews and physical-build evidence
```

## Part catalog

“Photo assembled” means the part is visible or its installed function is evidenced in the supplied prototype photographs. It is not a dimensional inspection or a field-weatherproofing claim.

| Assembly | Part | Qty. | Editable CAD | Preview | Function | Evidence status |
| --- | --- | ---: | --- | --- | --- | --- |
| Weather Station Body | Main body shell | 1 | [`station-body/main-body-shell.f3d`](station-body/main-body-shell.f3d) | [`main-body-shell-cad.png`](images/main-body-shell-cad.png) | Primary vertical enclosure and internal mounting structure | Photo assembled |
| Weather Station Body | Lid | 1 | [`station-body/lid.f3d`](station-body/lid.f3d) | [`lid-cad.png`](images/lid-cad.png) | Closes the top of the main shell | Photo assembled |
| Weather Station Body | Vent | 3 | [`station-body/vent.f3d`](station-body/vent.f3d) | [`vent-cad.png`](images/vent-cad.png) | Inserts into the three open sides of the shell | Photo assembled; weatherproofing not validated |
| Weather Station Body | Sensor rod | 1 | [`station-body/sensor-rod.f3d`](station-body/sensor-rod.f3d) | [`sensor-rod-cad.png`](images/sensor-rod-cad.png) | Holds the smaller environmental sensors; GNSS antenna sits at the top | Photo assembled |
| Weather Station Body | Sensor-rod lid | 1 | [`station-body/sensor-rod-lid.f3d`](station-body/sensor-rod-lid.f3d) | [`sensor-rod-lid-cad.png`](images/sensor-rod-lid-cad.png) | Fits into the sensor rod to stabilize installed sensors | Included in source; not independently visible in the photos |
| Weather Station Body | Cable slot | 1 | [`station-body/cable-slot.f3d`](station-body/cable-slot.f3d) | [`cable-slot-cad.png`](images/cable-slot-cad.png) | Organizes sensor wiring | Included in source; not independently identifiable in the photos |
| Weather Station Body | GNSS mount | 1 | [`station-body/gnss-mount.f3d`](station-body/gnss-mount.f3d) | [`gnss-mount-cad.png`](images/gnss-mount-cad.png) | Supports the GNSS board above the PMS7003 | Photo assembled |
| Power Module | Power-module mount | 1 | [`power-module/power-module-mount.f3d`](power-module/power-module-mount.f3d) | [`power-module-mount-cad.png`](images/power-module-mount-cad.png) | Holds the battery pack and power boards | Photo assembled |
| Power Module | Power-module cover | 1 | [`power-module/power-module-cover.f3d`](power-module/power-module-cover.f3d) | [`power-module-cover-cad.png`](images/power-module-cover-cad.png) | Closes the power-module mount | Photo assembled |
| Combined assembly | Connecting base | 1 | [`assembly/connecting-base.f3d`](assembly/connecting-base.f3d) | [`connecting-base-cad.png`](images/connecting-base-cad.png) | Joins the station body to the power module | Designed, printed, fit verified, and integrated |

## Printing rule

Every released part in the catalog is printed in PLA using the normal/default PLA profile with supports enabled. The Power Module Mount is the sole documented material exception: its model remains PLA, while its support system uses the dedicated `Support for PLA` material. No support-interface configuration or numeric slicer settings are specified because none were supplied.

## Source-name normalization

The supplied files were copied into the repository with descriptive, lowercase, hyphenated names. The source folder remains unchanged.

| Supplied name | Repository name |
| --- | --- |
| `mainbodyshell.f3d` | `station-body/main-body-shell.f3d` |
| `Lid.f3d` | `station-body/lid.f3d` |
| `vent.f3d` | `station-body/vent.f3d` |
| `sensorrod.f3d` | `station-body/sensor-rod.f3d` |
| `rodlid.f3d` | `station-body/sensor-rod-lid.f3d` |
| `cableslot.f3d` | `station-body/cable-slot.f3d` |
| `gpsmount.f3d` | `station-body/gnss-mount.f3d` |
| `powermodulemount.f3d` | `power-module/power-module-mount.f3d` |
| `powermodulecover.f3d` | `power-module/power-module-cover.f3d` |
| `connectbase.f3d` | `assembly/connecting-base.f3d` |

## Visual evidence

- [`station-body-assembled-front.jpg`](images/station-body-assembled-front.jpg) — completed station-body exterior.
- [`station-body-internal-sensors.jpg`](images/station-body-internal-sensors.jpg) — sensor rod and PMS7003/GNSS area.
- [`station-body-internal-electronics.jpg`](images/station-body-internal-electronics.jpg) — installed ESP32-S3, interface board, and wiring.
- [`power-module-open.jpg`](images/power-module-open.jpg) — battery pack and power electronics on the open mount.
- [`power-module-closed.jpg`](images/power-module-closed.jpg) — installed cover.
- [`assembled-two-module-system.jpg`](images/assembled-two-module-system.jpg) — both assemblies joined by the printed connecting base.

The physical photographs and connecting-base render were extracted from the supplied 14-page Word reference. The individual CAD previews came from the matching source-folder screenshots.

## Known gaps

- Record Fusion document units and export tested STL or 3MF files before calling the print package turnkey-reproducible.
- Record dimensions, tolerances, fastening/adhesive method, print orientation, and slicer settings after a controlled reprint.
- Validate enclosure drainage, sealing, UV/heat resistance, and long-duration outdoor fit. The reference calls the vents waterproof, but no test evidence supports that claim.
- Confirm whether future manufacturing exports need a dedicated open-hardware licence in addition to the repository-wide MIT License. Until that decision is recorded, describe the editable CAD as source material rather than a certified, turnkey open-hardware package.

See the [printing guide](../printing/README.md), [assembly guide](../printing/assembly-guide.md), and milestone records for [v0.1](../../docs/milestones/v0.1-core-sensors.md), [v0.2](../../docs/milestones/v0.2-connected-iot.md), and [v0.3](../../docs/milestones/v0.3-gnss-integration.md).
