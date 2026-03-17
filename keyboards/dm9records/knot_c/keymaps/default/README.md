# knot_c Default keymap

A minimal QMK keymap for a knot-c with a dedicated scroll layer.

## Layers

| #   | Name      | Description                                       |
| --- | --------- | ------------------------------------------------- |
| 0   | `_BASE`   | Default layer — cursor movement and mouse buttons |
| 4   | `_SCROLL` | Scroll mode — trackball acts as a scroll wheel    |

> Layers 1–3 are intentionally left unused, reserving them for future expansion.
> `_SCROLL` is fixed at layer 4 so that any layers added in between will fall
> through correctly via transparency.

## Key Layout

```
_BASE (Layer 0)
┌──────────┬──────────┬─────────┬─────────┬─────────┬─────────┐
│MO(_SCROLL)│MO(_SCROLL)│ MS_BTN1 │ MS_BTN3 │ MS_BTN2 │ MS_BTN4 │
└──────────┴──────────┴─────────┴─────────┴─────────┴─────────┘
  Touch 1    Touch 2    Left      Middle    Right     Back/Fwd

_SCROLL (Layer 4)
┌──────────┬──────────┬─────────┬─────────┬─────────┬─────────┐
│ KC_TRNS  │ KC_TRNS  │ KC_TRNS │ KC_TRNS │ KC_TRNS │ KC_TRNS │
└──────────┴──────────┴─────────┴─────────┴─────────┴─────────┘
  (all keys transparent — falls through to the active layer below)
```

## Scroll Mode (`MO(_SCROLL)`)

Holding either of the two touch keys activates `_SCROLL` (layer 4) via `MO(_SCROLL)`.

While held:

- The trackball **X/Y movement** is converted into **horizontal/vertical scroll** (`mouse_report.h` / `mouse_report.v`).
- Cursor movement is suppressed (`mouse_report.x = mouse_report.y = 0`).
- Y-axis is inverted for **natural scrolling** (trackball up → page up).
- Releasing the key immediately returns the trackball to normal cursor mode.

### Scroll Sensitivity

Scroll speed is controlled by `SCROLL_DIVISOR` (default: `4`).

```c
#define SCROLL_DIVISOR 4
```

Increase the value to slow down scrolling; decrease it to speed it up.

## Layer Stack Behavior

QMK resolves each keypress by scanning the layer stack **from the highest active
layer downward**, stopping at the first non-transparent keycode. Because `_SCROLL`
defines no keycodes of its own, all button presses fall through to whichever layer
was active before scroll mode was engaged.

```
Layer 4 (_SCROLL):  [ TRNS ][ TRNS ][ TRNS ][ TRNS ][ TRNS ][ TRNS ]
                         ↓       ↓       ↓       ↓       ↓       ↓
Layer 0 (_BASE):    [MO(4) ][MO(4) ][BTN1 ][BTN3 ][BTN2 ][BTN4 ]
```

This means **mouse buttons remain fully functional during scroll mode** — there is
no need to duplicate button definitions in `_SCROLL`.

If layers 1–3 are added in the future, the same principle applies: `_SCROLL` will
always inherit the button assignments of whatever lower layer is currently active,
with no changes required to layer 4.
