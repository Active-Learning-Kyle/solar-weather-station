# Anomaly and Action Guide

Use this guide to classify observations; it is not a substitute for locked sensor specifications, battery limits or the approved weather envelope.

| Observation | Classification | Immediate action | Escalation / evidence |
|---|---|---|---|
| Battery swelling, leakage, damage, abnormal heat, smell, smoke or short-circuit risk | **STOP NOW** | isolate safely; do not handle beyond competence | inform TA/instructor; competent staff handles incident |
| Water inside near energised electronics or exposed wet live connection | **STOP NOW** | isolate power if safe; do not reopen/handle unsupervised | photos only if safe; inform TA/instructor |
| Loose/unstable mounting, fall/trip risk or uncontrolled public contact | **STOP NOW** | secure area and isolate/remove if safe | contact instructor and site responsible person |
| Weather outside approved envelope, including named strong-wind/heavy-rain trigger | **STOP NOW** | stop/isolate according to removal plan | record weather source/time and notify contacts |
| Missing data, reboot, long network outage or missing local log | **INVESTIGATE / ESCALATE** | preserve logs; check power/logging/recovery without hiding failure | student → TA; instructor decides continuation if test quality is affected |
| Sensor stuck, jump/outlier or clearly implausible reading | **INVESTIGATE / ESCALATE** | mark invalid; compare range/trend/reference; do not tune values to look correct | link raw data and hypothesis; apply approved calibration/replacement rule |
| Battery voltage steadily falls or reaches project threshold | **INVESTIGATE / STOP AT APPROVED LIMIT** | check trend and supply/solar state; follow approved shutdown threshold | instructor decides continuation unless immediate safety risk |
| Significant condensation, connector movement or cable change without immediate electrical risk | **INVESTIGATE / ESCALATE** | inspect without unsafe energised handling; record change | TA verifies; instructor decides revise/retrieve |
| Normal variation inside project range with continuous logging/recovery | **CONTINUE** | record routine observation | no escalation unless trend changes |

## Project-specific normal-behaviour fields—complete before deployment

| Variable/state | Sensor/model/source | Expected range/behaviour | Investigate threshold | Stop threshold | Approved by |
|---|---|---|---|---|---|
| Battery voltage | | | | | |
| Temperature | | | | | |
| Relative humidity | | | | | |
| Pressure | | | | | |
| Wind speed/direction | | | | | |
| Data interval/completeness | | | | | |
| Restart/recovery | | | | | |
| RS-485/network/GNSS fault | | | | | |
| Weather envelope | | | | | |
