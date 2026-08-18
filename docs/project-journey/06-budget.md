# 06 — Budget and Procurement

The BOM is a design document, not only a shopping list.

## Planning ranges

| Build level | Early range (USD) | Main uncertainty |
|---|---:|---|
| Bench prototype | 100–180 | Sensor and development-board choice |
| Outdoor prototype | 180–300 | Power, enclosure, mounting, and outdoor sensors |
| Ruggedised build | 300–450+ | Protection, connectors, fabrication, spares, and validation |

Update `bom/bom.csv` with quotations, quantity, lead time, alternatives, and actual cost. Include shipping, fasteners, connectors, consumables, failed parts, and spares where relevant.

## v0.2 teaching-preview total

The current [BOM](../../bom/bom.csv) totals **HKD 3,715** in synthetic planning values, including the controller, selected sensing set, wind/GNSS, power classes, enclosure materials and freestanding mount. A borrowed reference is shown as HKD 0 only to expose the strategy; it is not a confirmed loan or zero-cost quotation.

| Cost layer | Status |
|---|---|
| Part/specification baseline | selected for the preview where identified |
| Unit costs | synthetic planning estimates |
| Supplier/lead time | incomplete until quotation |
| Shipping/tax/failed parts/labour/tools | excluded |
| Approved procurement | none |

Use the [synthetic power budget](power-budget-v0.2.md) to understand why battery/panel size affects cost. Procurement must wait for measured load, exact battery safety evidence, site/mounting constraints and current quotations.

