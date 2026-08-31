# Release Checklist

Complete this checklist before a tagged public release.

## Build and evidence

- [ ] Continuous integration passes on the release commit.
- [ ] Changed hardware has a named procedure and evidence record.
- [ ] The README status table matches the milestone and test matrix.
- [ ] Planned, compiled, bench-verified, integrated and field-verified claims are distinguishable.
- [ ] Known failures and deferred work remain visible.
- [ ] A clean clone can follow the documented software setup.

## Safety, security and privacy

- [ ] No credentials, private endpoints, tokens or private keys are present in tracked files or release assets.
- [ ] GNSS coordinates, site access details and personal information are removed or approved.
- [ ] The local-network security boundary is stated.
- [ ] Outdoor, battery, 12 V, fabrication and mounting limits are current.
- [ ] Images and databases have been reviewed for sensitive information.

## Reuse and attribution

- [ ] The MIT licence is present.
- [ ] New dependencies are listed in `THIRD_PARTY.md`.
- [ ] Reused code, CAD, data and media have compatible terms and attribution.
- [ ] AI-assisted work has been checked by a responsible contributor and recorded when material.
- [ ] Contribution and security contact routes are working.

## Release decision

| Item | Record |
| --- | --- |
| Release version | |
| Commit | |
| Reviewer | |
| Approved claims | |
| Required redactions | |
| Known limitations | |
| Decision and date | |
