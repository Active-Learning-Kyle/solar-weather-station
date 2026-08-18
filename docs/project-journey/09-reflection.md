# 09 — Reflection and Teaching Transfer

This project is also an ENGG2202 course-design experiment.

After each milestone, record:

- What engineering assumption changed?
- Which evidence caused the change?
- Where would a student team likely become stuck?
- What template, mini-lesson, lab, or TA intervention would help?
- What should remain deliberately open for student judgement?
- How was AI used and verified?
- What can the next cohort teach forward?

The final exemplar should display honest iteration, including failures, rather than presenting engineering as a straight path to a polished result.

## v0.2 teaching-preview reflection

The most important change was not a sensor or battery: it was separating a **complete presentation** from a **validated product**. Students can now inspect a coherent selection, BOM, architecture, power calculation, data pipeline, field report and decision. At the same time, every generated value declares its evidence level and the real test matrix remains open.

The preview also makes iteration visible. The Gate D case returned `revise` because of power margin, sensor disagreement and condensation. The later v0.2 synthetic case assumes targeted changes, defines acceptance criteria before analysis and advances only to a longer supervised comparison test. It does not erase the earlier failure.

Likely student sticking points are now concrete:

- treating a datasheet number as system accuracy;
- sizing solar/battery from nominal power rather than measured duty cycle;
- confusing a firmware scaffold with an integrated build;
- hiding network loss by drawing a continuous chart;
- calling an enclosure weatherproof before a defined test; and
- interpreting “Issue closed” as “project finished.”

The teaching response should be short decision reviews, version/evidence labels, peer challenge of assumptions and replacement of one synthetic layer at a time with measured evidence.

