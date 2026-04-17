#include QMK_KEYBOARD_H

enum layers {
    LAYER_DEFAULT = 0,
    LAYER_NAV,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_SHORTCUT,
};

enum tap_dance_codes {
    TD_SHIFT_CAPS,
};

enum custom_keycodes {
    AT_OR_HIDE = SAFE_RANGE, // W+E: KC_AT on DEFAULT, LCTL(KC_B) on NAV
    AND_OR_DOT,              // ,+.: KC_AMPR on DEFAULT, KC_DOT on NUM
};

// ── Combo key arrays ────────────────────────────────────────────
const uint16_t PROGMEM hash_combo[]        = {KC_K,    KC_L,                              COMBO_END};
const uint16_t PROGMEM we_combo[]          = {KC_W,    KC_E,                              COMBO_END};
const uint16_t PROGMEM mul_combo[]         = {KC_U,    KC_I,                              COMBO_END};
const uint16_t PROGMEM scrl_up_combo[]     = {KC_Y,    KC_U,                              COMBO_END};
const uint16_t PROGMEM scrl_dn_combo[]     = {KC_H,    KC_J,                              COMBO_END};
const uint16_t PROGMEM equal_combo[]       = {KC_J,    KC_K,                              COMBO_END};
const uint16_t PROGMEM plus_combo[]        = {KC_M,    KC_COMM,                           COMBO_END};
const uint16_t PROGMEM comma_dot_combo[]   = {KC_COMM, KC_DOT,                            COMBO_END};
const uint16_t PROGMEM excl_combo[]        = {KC_C,    KC_V,                              COMBO_END};
const uint16_t PROGMEM tab_combo[]         = {KC_S,    KC_D,                              COMBO_END};
const uint16_t PROGMEM shift_tab_combo[]   = {KC_S,    KC_F,                              COMBO_END};
const uint16_t PROGMEM sel_home_combo[]    = {KC_Q,    KC_W,                              COMBO_END};
const uint16_t PROGMEM sel_end_combo[]     = {KC_O,    KC_P,                              COMBO_END};
const uint16_t PROGMEM paste_hist_combo[]  = {KC_X,    KC_C,                              COMBO_END};
const uint16_t PROGMEM bksp_combo[]        = {KC_L,    KC_ENT,                            COMBO_END};
const uint16_t PROGMEM cmd_palette_combo[] = {KC_D,    KC_K,                              COMBO_END};
const uint16_t PROGMEM find_combo[]        = {KC_F,    KC_J,                              COMBO_END};
const uint16_t PROGMEM top_combo[]         = {KC_W,    KC_R,                              COMBO_END};
const uint16_t PROGMEM bot_combo[]         = {KC_X,    KC_V,                              COMBO_END};
const uint16_t PROGMEM ctrl_tab_combo[]    = {KC_J,    KC_K,    KC_L,                     COMBO_END};
const uint16_t PROGMEM terminal_combo[]    = {KC_S,    KC_L,                              COMBO_END};
const uint16_t PROGMEM cst_combo[]         = {KC_U,    KC_I,    KC_O,                     COMBO_END};
const uint16_t PROGMEM win_left_combo[]    = {KC_Q,    KC_Y,                              COMBO_END};
const uint16_t PROGMEM win_right_combo[]   = {KC_T,    KC_P,                              COMBO_END};
const uint16_t PROGMEM win_max_combo[]     = {KC_E,    KC_U,                              COMBO_END};
const uint16_t PROGMEM win_ctr_combo[]     = {KC_Q,    KC_P,                              COMBO_END};
const uint16_t PROGMEM win_ctrb_combo[]    = {KC_A,    KC_ENT,                            COMBO_END};
const uint16_t PROGMEM cursor_combo[]      = {LT(LAYER_NUM, KC_SPC), TD(TD_SHIFT_CAPS),   COMBO_END};
const uint16_t PROGMEM chrome_combo[]      = {KC_C,    KC_COMM,                           COMBO_END};
const uint16_t PROGMEM edge_combo[]        = {KC_X,    KC_DOT,                            COMBO_END};
const uint16_t PROGMEM term_app_combo[]    = {KC_B,    KC_N,                              COMBO_END};
const uint16_t PROGMEM claude_combo[]      = {KC_V,    KC_M,                              COMBO_END};
const uint16_t PROGMEM lgui_a_combo[]      = {KC_J,    KC_L,                              COMBO_END};

// ── Combo index enum ────────────────────────────────────────────
enum combo_events {
    COMBO_HASH,
    COMBO_AT_HIDE,
    COMBO_MUL,
    COMBO_SCROLL_UP,
    COMBO_SCROLL_DOWN,
    COMBO_EQUAL,
    COMBO_PLUS,
    COMBO_AND_DOT,
    COMBO_EXCL,
    COMBO_TAB,
    COMBO_SHIFT_TAB,
    COMBO_SEL_HOME,
    COMBO_SEL_END,
    COMBO_PASTE_HIST,
    COMBO_BKSP,
    COMBO_CMD_PALETTE,
    COMBO_FIND,
    COMBO_TOP,
    COMBO_BOT,
    COMBO_CTRL_TAB,
    COMBO_TERMINAL,
    COMBO_CTRL_SHIFT_TAB,
    COMBO_WIN_LEFT,
    COMBO_WIN_RIGHT,
    COMBO_WIN_MAX,
    COMBO_WIN_CENTER,
    COMBO_WIN_CENTER_BIG,
    COMBO_CURSOR_APP,
    COMBO_CHROME_APP,
    COMBO_EDGE_APP,
    COMBO_TERMINAL_APP,
    COMBO_CLAUDE_APP,
    COMBO_LGUI_A,
};

// ── Combo table ─────────────────────────────────────────────────
combo_t key_combos[] = {
    [COMBO_HASH]           = COMBO(hash_combo,        KC_HASH),
    [COMBO_AT_HIDE]        = COMBO(we_combo,          AT_OR_HIDE),
    [COMBO_MUL]            = COMBO(mul_combo,         KC_KP_ASTERISK),
    [COMBO_SCROLL_UP]      = COMBO(scrl_up_combo,     MS_WHLU),
    [COMBO_SCROLL_DOWN]    = COMBO(scrl_dn_combo,     MS_WHLD),
    [COMBO_EQUAL]          = COMBO(equal_combo,       KC_EQL),
    [COMBO_PLUS]           = COMBO(plus_combo,        KC_KP_PLUS),
    [COMBO_AND_DOT]        = COMBO(comma_dot_combo,   AND_OR_DOT),
    [COMBO_EXCL]           = COMBO(excl_combo,        KC_EXCLAIM),
    [COMBO_TAB]            = COMBO(tab_combo,         KC_TAB),
    [COMBO_SHIFT_TAB]      = COMBO(shift_tab_combo,   LSFT(KC_TAB)),
    [COMBO_SEL_HOME]       = COMBO(sel_home_combo,    LSFT(KC_HOME)),
    [COMBO_SEL_END]        = COMBO(sel_end_combo,     LSFT(KC_END)),
    [COMBO_PASTE_HIST]     = COMBO(paste_hist_combo,  LGUI(KC_V)),
    [COMBO_BKSP]           = COMBO(bksp_combo,        KC_BSPC),
    [COMBO_CMD_PALETTE]    = COMBO(cmd_palette_combo, LCTL(LSFT(KC_P))),
    [COMBO_FIND]           = COMBO(find_combo,        LCTL(KC_F)),
    [COMBO_TOP]            = COMBO(top_combo,         LCTL(KC_HOME)),
    [COMBO_BOT]            = COMBO(bot_combo,         LCTL(KC_END)),
    [COMBO_CTRL_TAB]       = COMBO(ctrl_tab_combo,    LCTL(KC_TAB)),
    [COMBO_TERMINAL]       = COMBO(terminal_combo,    LCTL(KC_J)),
    [COMBO_CTRL_SHIFT_TAB] = COMBO(cst_combo,         LCTL(LSFT(KC_TAB))),
    [COMBO_WIN_LEFT]       = COMBO(win_left_combo,    MEH(KC_X)),
    [COMBO_WIN_RIGHT]      = COMBO(win_right_combo,   MEH(KC_B)),
    [COMBO_WIN_MAX]        = COMBO(win_max_combo,     MEH(KC_M)),
    [COMBO_WIN_CENTER]     = COMBO(win_ctr_combo,     MEH(KC_L)),
    [COMBO_WIN_CENTER_BIG] = COMBO(win_ctrb_combo,    MEH(KC_K)),
    [COMBO_CURSOR_APP]     = COMBO(cursor_combo,      MEH(KC_V)),
    [COMBO_CHROME_APP]     = COMBO(chrome_combo,      MEH(KC_C)),
    [COMBO_EDGE_APP]       = COMBO(edge_combo,        MEH(KC_E)),
    [COMBO_TERMINAL_APP]   = COMBO(term_app_combo,    MEH(KC_T)),
    [COMBO_CLAUDE_APP]     = COMBO(claude_combo,      MEH(KC_S)),
    [COMBO_LGUI_A]         = COMBO(lgui_a_combo,      LGUI(KC_A)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_DEFAULT] = LAYOUT(
        KC_Q,           KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,
        KC_A,           KC_S,   KC_D,   KC_F,   KC_G,       KC_H,   KC_J,    KC_K,    KC_L,   KC_ENT,
        LCTL_T(KC_Z),   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,   KC_M,    KC_COMM, KC_DOT, LT(LAYER_SHORTCUT, KC_SLSH),
                KC_LGUI, MO(LAYER_NAV), LT(LAYER_NUM, KC_SPC),       TD(TD_SHIFT_CAPS), MO(LAYER_SYM)
    ),

    [LAYER_NAV] = LAYOUT(
        KC_HOME,    KC_UP,      KC_END,     KC_ENT,  KC_KP_PLUS,         KC_KP_ASTERISK,      LGUI(LCTL(KC_RGHT)), KC_MINS, KC_QUOT,  LALT(KC_BSPC),
        KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_DEL,  KC_EQL,             LCTL(LALT(KC_TAB)),  KC_BSPC,             KC_UNDS, KC_DQUO,  KC_COLN,
        LCTL(KC_C), LCTL(KC_V), KC_LALT,   KC_BSPC, KC_BSLS,            KC_PIPE,             LGUI(LCTL(KC_LEFT)), KC_LT,   KC_GT,    KC_QUES,
                        LCTL(KC_A), _______, KC_TILD,                    KC_LSFT, KC_ESC
    ),

    [LAYER_SYM] = LAYOUT(
        KC_LPRN, LGUI(KC_LEFT),        LGUI(KC_UP),   LGUI(KC_RGHT),        LGUI(KC_TAB),    KC_DLR,  KC_PERC, KC_CIRC, KC_0,    KC_RPRN,
        KC_LCBR, LSFT(LCTL(KC_LEFT)),  KC_P5,         LSFT(LCTL(KC_RGHT)), KC_AT,            KC_MINS, KC_TAB,  KC_HASH, KC_SCLN, KC_RCBR,
        KC_LBRC, KC_P1,                KC_P2,          KC_P3,               KC_P0,            KC_AMPR, XXXXXXX, XXXXXXX, XXXXXXX, KC_RBRC,
                        KC_LALT, MO(LAYER_NAV), LCTL(KC_DEL),               KC_QUES, _______
    ),

    [LAYER_NUM] = LAYOUT(
        KC_BTN1,    XXXXXXX,  KC_BTN2,  LCTL(LSFT(KC_F5)), XXXXXXX,    XXXXXXX, KC_7, KC_8, KC_9, KC_BTN1,
        XXXXXXX,    XXXXXXX,  XXXXXXX,  LCTL(LSFT(KC_F6)), XXXXXXX,    KC_PGDN, KC_4, KC_5, KC_6, KC_BTN2,
        LCTL(KC_Z), XXXXXXX,  XXXXXXX,  _______,           _______,    KC_0,    KC_1, KC_2, KC_3, KC_BSPC,
                        _______, _______, KC_NUM_LOCK,                  MS_WHLU, MS_WHLD
    ),

    [LAYER_SHORTCUT] = LAYOUT(
        KC_BTN1,     LGUI(KC_UP),   KC_BTN2,      LCTL(LSFT(KC_F5)), XXXXXXX,    XXXXXXX, KC_7, KC_8, KC_9, KC_BTN1,
        LGUI(KC_LEFT), XXXXXXX, LGUI(KC_RGHT), LCTL(LSFT(KC_F6)),   XXXXXXX,    KC_PGDN, KC_4, KC_5, KC_6, KC_BTN2,
        LCTL(KC_Z), XXXXXXX, XXXXXXX, _______, _______,                          KC_0,    KC_1, KC_2, KC_3, KC_BSPC,
                        _______, _______, KC_GRV,                                LGUI(KC_I), XXXXXXX
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AT_OR_HIDE:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LAYER_NAV)) {
                    tap_code16(LCTL(KC_B));
                } else {
                    tap_code16(KC_AT);
                }
            }
            return false;
        case AND_OR_DOT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(LAYER_NUM)) {
                    tap_code(KC_DOT);
                } else {
                    tap_code16(KC_AMPR);
                }
            }
            return false;
    }
    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_SHIFT_CAPS):
            return 200;
        default:
            return TAPPING_TERM;
    }
}
