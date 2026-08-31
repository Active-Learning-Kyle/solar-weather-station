# Gate 02: Define

## Working problem

Teams investigating a local environment need a traceable way to collect site-specific observations and judge whether the sensing system itself is reliable enough for the next test. A reading without sensor health, placement context, time, configuration and known limits is difficult to trust or reproduce.

## Intended users and decisions

The current system is designed for engineering teams conducting supervised bench and site tests. It should help them decide whether to:

- continue with the current configuration;
- revise a sensor, interface, enclosure or software path;
- return a subsystem to isolated bench testing; or
- retain the work as a reference without making a field-performance claim.

## Evidence boundary

The current repository supports claims about staged prototype integration. It does not yet support claims of:

- meteorological-grade accuracy;
- weatherproof or unattended outdoor operation;
- reliable solar energy balance;
- long-duration field reliability;
- environmental benefit or carbon reduction; or
- safe exposure of precise GNSS data on the public internet.

## Success criteria for the present prototype

1. The documented firmware environments build from a clean checkout.
2. Each active sensor reports explicit health and unavailable values remain distinct from valid zero readings.
3. A failed sensor or network path does not stop unrelated sensing.
4. The backend validates, stores and returns compatible measurement records.
5. The dashboard presents current data, health and history without hiding missing values.
6. A reproducer can find wiring, configuration, CAD, tests and known limitations from the repository front page.

## Evidence still needed before field use

- an approved site and responsible authority;
- the exact mounting location and exposure conditions;
- a documented comparison or reference instrument;
- complete power, enclosure and retrieval checks; and
- stop criteria for unsafe or unreliable operation.

## Gate decision

Use staged engineering reliability as the immediate problem. Treat any outdoor environmental interpretation as a later validation task, not as a property already established by the prototype.
