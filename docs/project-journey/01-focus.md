# Gate 01: Focus

## Decision

Develop a modular Solar Weather Station that can observe local environmental conditions and make the engineering process inspectable. The project should connect sensing, communications, mechanical design, testing and responsible data release instead of treating them as separate demonstrations.

## Why this direction

Regional weather services describe broad conditions, but engineering decisions are often made at a specific site and height, near particular surfaces, buildings, vegetation or equipment. A local station can help investigate these differences when its placement, calibration and limitations are documented.

The challenge connects most directly to:

- **SDG 7:** future solar and battery operation must be measured rather than assumed;
- **SDG 9:** the project develops a reusable sensing and data infrastructure; and
- **SDG 13:** local observations may support climate-related investigation, but the station alone does not prove climate impact.

## Scope chosen

The first useful direction is an inspectable prototype that:

- reads several environmental sensors without one failure stopping the system;
- records whether each value is valid, stale or unavailable;
- exposes current and historical data on a trusted local network;
- keeps location and safety risks visible; and
- can be extended and reproduced from public source files.

## Directions not selected

- a commercial weather service;
- a certified meteorological instrument;
- a public cloud monitoring product;
- an autonomous outdoor station before power and enclosure testing; and
- a sustainability claim based only on using a solar panel.

## Gate decision

Proceed to problem definition with a local microclimate and engineering-validation focus. Keep the intended user, deployment site, reference method and field decision open until they are supported by evidence.
