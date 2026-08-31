# Gate 04: Learn

Each working version was kept small enough to expose a specific integration problem. Later milestones preserve the earlier diagnostics and failure behavior.

## Core v0.1: integrated sensing

**Question:** Can four I²C devices and the PMS7003 operate together without one failure stopping the rest?

**Learned:** A shared snapshot and per-sensor health model are more useful than printing isolated values. Range, staleness and failure counters make unavailable data visible.

**Evidence:** [v0.1 milestone](../milestones/v0.1-core-sensors.md), diagnostic environments and bench images.

## Core v0.2: connected data path

**Question:** Can a local service receive, validate, store and display station snapshots without making sensing depend on the network?

**Learned:** Networking needs independent reconnect timing and bounded uploads. Typed API validation and nullable data make failures inspectable. Database migrations must preserve existing records.

**Evidence:** [v0.2 milestone](../milestones/v0.2-connected-iot.md), backend tests and dashboard screenshot.

## Core v0.3: GNSS integration

**Question:** Can the receiver report communication, no-fix and valid-fix states without blocking the rest of the station?

**Learned:** Communication and position validity are different states. The installed library required a documented hemisphere workaround based on checksum-valid NMEA fields. Precise coordinates need a publication rule.

**Evidence:** [v0.3 milestone](../milestones/v0.3-gnss-integration.md), GNSS diagnostics and privacy-safe images.

## Core v0.4: wind-speed integration

**Question:** Can verified RS485 wind speed enter the complete data path while timeouts remain isolated?

**Learned:** Native USB CDC frees UART0 for production RS485. A calm `0.0 m/s` reading must remain valid, while a timeout must become unavailable. The schema and database can extend additively without breaking v0.3 payloads.

**Evidence:** [v0.4 milestone](../milestones/v0.4-wind-speed-integration.md), backend compatibility tests and the preserved standalone diagnostic.

## Current working version

The repository contains a complete software path for Core v0.4. The next action is not another feature. It is the combined hardware verification procedure in [`core-v0.4.md`](../core-v0.4.md).
