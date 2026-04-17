# ZMK to QMK Keymap Migration Design

**Date:** 2026-04-17
**Source:** ZMK Microdox v2 (`zmk-config-microdox_v2/config/microdox.keymap`)
**Target:** QMK Charybdis Nano 3x5 (`qmk_userspace/keyboards/bastardkb/charybdis/3x5/keymaps/santu/`)

---

## Scope

Full replacement: translate the ZMK Microdox keymap 1:1 into a new QMK keymap folder `santu`. The existing `vendor` keymap is preserved untouched.

### Out of scope
- Bluetooth profile switching (`bt BT_SEL`, `bt BT_CLR`) — Charybdis Nano is wired only → `XXXXXXX`
- Software mouse movement (`mmv MOVE_*`) — trackball handles this → `XXXXXXX`
- 6th thumb key (`LALT` on default, `KC_GRV` on nav) — dropped, not used

---

## Files Created

```
keyboards/bastardkb/charybdis/3x5/keymaps/santu/
├── keymap.c     # full layer + combo + tap-dance definitions
├── config.h     # TAPPING_TERM, COMBO_ENABLE, TAP_DANCE_ENABLE
└── rules.mk     # COMBO_ENABLE = yes, TAP_DANCE_ENABLE = yes
```

---

## Layer Structure

5 layers, same order as ZMK:

| Index | Name | ZMK name |
|---|---|---|
| 0 | `LAYER_DEFAULT` | `default_layer` |
| 1 | `LAYER_NAV` | `nav_layer` |
| 2 | `LAYER_SYM` | `sym_layer` |
| 3 | `LAYER_NUM` | `num_layer` |
| 4 | `LAYER_SHORTCUT` | `shortcut_layer` |

### Thumb rows (5 keys: left 3 + right 2)

| Layer | L1 | L2 | L3 | R1 | R2 |
|---|---|---|---|---|---|
| DEFAULT | `KC_LGUI` | `MO(1)` | `LT(3,KC_SPC)` | `TD(TD_SHIFT_CAPS)` | `MO(2)` |
| NAV | `LCTL(KC_A)` | `_______` | `KC_TILDE` | `KC_LSFT` | `KC_ESC` |
| SYM | `KC_LALT` | `MO(1)` | `LCTL(KC_DEL)` | `KC_QUES` | `_______` |
| NUM | `_______` | `_______` | `KC_NUM_LOCK` | `MS_WHLU` | `MS_WHLD` |
| SHORTCUT | `_______` | `_______` | `KC_GRV` | `LGUI(KC_I)` | `XXXXXXX` |

---

## Key Translation Reference

| ZMK | QMK |
|---|---|
| `mt LCTRL Z` | `LCTL_T(KC_Z)` |
| `lt 4 FSLH` | `LT(4, KC_SLSH)` |
| `lt 3 SPACE` | `LT(3, KC_SPC)` |
| `mo 1` / `mo 2` | `MO(1)` / `MO(2)` |
| `td1` (shift/caps) | `TD(TD_SHIFT_CAPS)` |
| `MEH(kc)` | `MEH(KC_x)` (native QMK) |
| `mkp LCLK/RCLK` | `KC_BTN1` / `KC_BTN2` |
| `mmv MOVE_*` | `XXXXXXX` |
| `msc SCRL_UP/DOWN` | `MS_WHLU` / `MS_WHLD` |
| `msc SCRL_LEFT/RIGHT` | `XXXXXXX` |
| `bt BT_SEL 0/1/2` | `XXXXXXX` |
| `bt BT_CLR` | `XXXXXXX` |
| `kp LOCKING_NUM` | `KC_NUM_LOCK` |
| `kp KP_N1..N5` | `KC_P1..P5` |
| `kp LC(LA(TAB))` | `LCTL(LALT(KC_TAB))` |
| `kp LG(LC(RIGHT/LEFT))` | `LGUI(LCTL(KC_RGHT/LEFT))` |

---

## Combos

All 30 ZMK combos port without position changes — both keyboards are 3×5 so positions 0–29 are identical. Thumb combo `combo_cursor_app` (positions 32+33 = SPC+Shift) also maps correctly.

Scroll combos (`combo_scroll_up` pos 5+6, `combo_scroll_down` pos 15+16) translate to `MS_WHLU`/`MS_WHLD`.

Window management combos use QMK native `MEH(KC_x)` directly.

---

## Tap Dance

`TD_SHIFT_CAPS`: single tap = `KC_LSFT`, double tap = `KC_CAPS`
- `tapping_term` = 200ms (matches ZMK `tapping-term-ms = <200>`)

---

## Timing Config

- `TAPPING_TERM 150` — matches ZMK `mt` global `tapping-term-ms = <150>`
- Tap dance uses its own 200ms term set per-entry in `tap_dance_actions[]`
