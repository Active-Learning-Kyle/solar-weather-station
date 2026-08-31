# Mechanical assembly guide

This sequence reconstructs the supplied prototype at a practical, non-electrical level. It does not establish a production enclosure or a weatherproof installation. Disconnect external power and isolate the 18650 pack before fitting or moving electronics.

## Before assembly

- Print the quantities in the [printing guide](README.md), clean all support material, and dry-fit every interface.
- Print every model in PLA using the normal/default PLA profile with supports enabled. For the Power Module Mount, use the dedicated `Support for PLA` material for its support system.
- Review the [CAD index](../cad/README.md), [wiring guide](../wiring.md), and [power-system notes](../power-system.md).
- Prepare the ESP32-S3/perfboard assembly, PMS7003, GNSS board and antenna, small sensor boards, battery pack, Waveshare Solar Power Manager (D), and XL6009 module.
- Do not select fasteners, clips, or adhesive by assumption. The supplied reference does not identify an attachment method or hardware size.

## A. Weather Station Body

1. Place the main body shell upright and verify that its three side openings and internal board supports are unobstructed.
2. Fit the ESP32-S3/perfboard assembly into its internal location without pinching cables.
3. Install the small sensor boards on the sensor rod. Route their wiring through the intended openings, then fit the sensor-rod lid to stabilize the sensor installation.
4. Position the sensor rod inside the main shell with the GNSS antenna at the top, matching the supplied build evidence.
5. Fit the PMS7003 in its lower station-body location. Install the GNSS mount above it and secure the GNSS board to the mount.
6. Install the cable-slot part and organize sensor wiring so it does not obstruct the vents, lid, PMS7003 airflow, or board removal.
7. Insert three vent parts, one in each open side of the shell. Treat them as ventilation panels; weatherproof performance has not been verified.
8. Fit the lid to close the top of the shell. Confirm it seats without forcing the shell walls outward.

![Station-body interior showing the sensor rod and PMS7003/GNSS area](../cad/images/station-body-internal-sensors.jpg)

## B. Power Module

1. Remove the power-module cover and keep the 18650 pack electrically isolated.
2. Fit the Waveshare Solar Power Manager (D) and XL6009 module on the power-module mount in the positions defined by the model.
3. Fit the 18650 battery pack in its holder area. Do not use a cell with damaged wrapping, and prevent tools or fasteners from bridging terminals.
4. Route power wiring through the modeled openings without trapping it under a board, cell holder, or cover edge.
5. Refit the cover and confirm that it closes without pressing on cells, boards, connectors, or wiring.

![Open power module with battery pack and power electronics fitted](../cad/images/power-module-open.jpg)

## C. Join the two assemblies

The final mechanical sequence is:

```text
Build Weather Station Body
        ↓
Install sensors/electronics
        ↓
Complete Power Module Assembly
        ↓
Position both main assemblies
        ↓
Install Connecting Base
        ↓
Join station body and power module
        ↓
Check cable clearance
        ↓
Verify mechanical fit
        ↓
Complete mechanical assembly
```

1. Place the [`connecting-base.f3d`](../cad/assembly/connecting-base.f3d) part on a flat surface and identify its pentagonal station-body side and long rectangular power-module side from the [reference preview](../cad/images/connecting-base-cad.png).
2. Seat the Weather Station Body on the matching end, then seat the Power Module on the rectangular extension.
3. Align the Power Module so it extends horizontally from the vertical station body, matching the final prototype photograph.
4. Route the inter-module cable with enough slack for service but clear of exposed edges and the base interface.
5. Do not add screws, clips, or adhesive by assumption; the supplied project evidence does not specify an attachment method.

![Complete mechanical prototype — the main weather-station enclosure and power-module assembly joined using the Connecting Base](../cad/images/assembled-two-module-system.jpg)

*Complete mechanical prototype — the main weather-station enclosure and power-module assembly joined using the Connecting Base.*

## Final inspection

- Both assemblies sit fully on the connecting base without rocking or visible stress.
- Lid, three vents, sensor-rod lid, and power-module cover remain seated.
- GNSS antenna and light/UV sensing surfaces are not shadowed by loose wiring.
- PMS7003 inlet/outlet and the side vents are unobstructed.
- No conductor is pinched, abraded, or able to contact a battery terminal.
- Electronics can be reached for service without destructive disassembly.

The supplied photograph verifies that the Connecting Base was printed, fit to both assemblies, and integrated into the completed bench prototype. It is not evidence of quantified tolerances, outdoor durability, or weather certification.
