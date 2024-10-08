/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 // command key = Windows
 // Option key = ALT

#include QMK_KEYBOARD_H
#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_FUNCTION, KC_SPC)
#define TAB_FUN LT(LAYER_POINTER, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_LSFT)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_N
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

enum combos { 
    WE_AT,
    SD_TAB,
    XC_PASTE,
    KL_HASH,
    CV_EXCLAMATION,
    JK_EQUAL,
    KL_PLUS,
    UI_STAR,
    UIO_NEXT_DESKTOP,
    QWE_PREV_DESKTOP,
    JKL_TERMINAL_SWITCH,
    M_UNDO,
    OP_SELECT_TILL_END,
    QW_SELECT_TILL_START,
    SF_SHIFT_TAB
};

const uint16_t PROGMEM at_combo[]       = {KC_W, KC_E, COMBO_END};           // we @
const uint16_t PROGMEM tab_combo[]      = {KC_S, KC_D, COMBO_END};           // sd TAB
const uint16_t PROGMEM paste_combo[]    = {KC_X, KC_C, COMBO_END};           // xc PASTE
const uint16_t PROGMEM hash_combo[]     = {KC_K, KC_L, COMBO_END};           // kl HASH
const uint16_t PROGMEM and_combo[]      = {KC_COMM, KC_DOT, COMBO_END};      // ,. AND
const uint16_t PROGMEM exlm_combo[]      = {KC_C, KC_V, COMBO_END};           // cv EXCLAMATION
const uint16_t PROGMEM equal_combo[]    = {KC_J, KC_K, COMBO_END};           // jk EQUAL
const uint16_t PROGMEM plus_combo[]     = {KC_M, KC_COMM, COMBO_END};        // kl PLUS
const uint16_t PROGMEM star_combo[]     = {KC_U, KC_I, COMBO_END};           // ui STAR
const uint16_t PROGMEM nextw_combo[]    = {KC_U, KC_I, KC_O, COMBO_END};     // uio NEXT DESKTOP
const uint16_t PROGMEM prev_combo[]     = {KC_W, KC_E, KC_R, COMBO_END};     // qwe PREV DESKTOP
const uint16_t PROGMEM term_combo[]     = {KC_J, KC_K, KC_L, COMBO_END};     // jkl TERMINAL SWITCH
const uint16_t PROGMEM undo_combo[]     = {KC_M, KC_COMM, KC_DOT, COMBO_END}; // m,. UNDO
const uint16_t PROGMEM s_end_combo[]    = {KC_O, KC_P, COMBO_END};            // op SELECT TILL END
const uint16_t PROGMEM s_start_combo[]  = {KC_Q, KC_W, COMBO_END};            // qw SELECT TILL START
const uint16_t PROGMEM s_tab_combo[]    = {KC_S, KC_F, COMBO_END};            // sf SHIFT TAB

combo_t key_combos[] = {
    [WE_AT]      = COMBO(at_combo, KC_AT),
    [SD_TAB]     = COMBO(tab_combo, KC_TAB),
    [XC_PASTE]   = COMBO(paste_combo, LGUI(KC_V)),
    [KL_HASH]    = COMBO(hash_combo, KC_HASH),
    [CV_EXCLAMATION] = COMBO(and_combo, KC_EXCLAIM),
    [JK_EQUAL]   = COMBO(equal_combo, KC_EQUAL),
    [KL_PLUS]    = COMBO(plus_combo, KC_PLUS),
    [UI_STAR]    = COMBO(star_combo, KC_ASTERISK),
    [UIO_NEXT_DESKTOP] = COMBO(nextw_combo, LCTL(KC_RIGHT)),
    [QWE_PREV_DESKTOP] = COMBO(prev_combo, LCTL(KC_LEFT)),
    [JKL_TERMINAL_SWITCH] = COMBO(prev_combo, LCTL(LSFT(KC_T))),
    [M_UNDO]     = COMBO(undo_combo, LGUI(KC_Z)),
    [OP_SELECT_TILL_END] = COMBO(s_end_combo, LSFT(KC_END)),
    [QW_SELECT_TILL_START] = COMBO(s_start_combo, LSFT(KC_HOME)),
    [SF_SHIFT_TAB] = COMBO(s_tab_combo, LSFT(KC_TAB))
};

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
// TAB_FUN = MOUSE
// SPC_NAV = MAIN_LAYER 1
// ESC_MED = NUMBERS
// 
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, ENT_SYM, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                      TAB_FUN, SPC_NAV, ESC_MED, KC_LSFT, BSP_NUM 

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

#define LAYOUT_LAYER_FUNCTION                                                                \
    KC_HOME, KC_UP, KC_END, KC_ENT, KC_PLUS, KC_ASTERISK,   LSFT(KC_TAB),  KC_MINUS,   KC_QUOTE,  LALT(KC_BSPC), \
    KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL, KC_EQUAL, XXXXXXX,   KC_BSPC,   KC_UNDERSCORE,   KC_DOUBLE_QUOTE,  KC_SEMICOLON, \
    LGUI(KC_C), LGUI(KC_V),  KC_LEFT_ALT, KC_BSPC, KC_BACKSLASH, KC_PIPE, XXXXXXX, KC_LEFT_ANGLE_BRACKET,   KC_RIGHT_ANGLE_BRACKET,  KC_QUESTION, \
                      LGUI(KC_A), XXXXXXX, KC_TILDE, KC_TAB, KC_ESC 

#define LAYOUT_LAYER_MEDIA                                                                    \
    XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, KC_CAPS_LOCK, KC_7, KC_8, KC_9, KC_DOT, \
    KC_MPRV, KC_VOLD, KC_MUTE, LGUI(KC_F), KC_MNXT, XXXXXXX, KC_4, KC_5, KC_6, KC_MINUS, \
    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT, KC_0,    KC_1, KC_2, KC_3, KC_QUESTION, \
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_EQUAL

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MS_WHLU, MS_WHLD, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

z/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                               \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    _______________DEAD_HALF_ROW_______________,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC
/*
&kp LPAR    &kp LS(LC(HOME))          &trans    &kp LS(LC(END))            &kp EXCL        &kp DOLLAR &kp PRCNT     &kp CARET         &kp 0     &kp RPAR
&kp LBRC    &kp LS(LC(LEFT))          &kp KP_N5     &kp LS(LC(RIGHT))          &kp AT          &kp MINUS  &kp TAB       &kp HASH          &kp SEMI       &kp RBRC
&kp LBKT    &kp KP_N1                 &kp KP_N2     &kp KP_N3  &kp KP_N0       &kp AMPS   &bt BT_SEL 0  &bt BT_SEL 1      &bt BT_SEL 2   &kp RBKT
                    &kp LALT  &mo 1 &kp LC(DEL)             &kp LS(FSLH)      &trans         &kp LS(TAB)
*/

#define LAYOUT_LAYER_NUMERAL                                                                  \
    LSFT(KC_9),       LGUI(KC_HOME),    LGUI(KC_END),    KC_9, KC_RBRC, LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),XXXXXXX,LSFT(KC_0), \
    LSFT(KC_LBRC),    XXXXXXX,    KC_5,    KC_6,  KC_EQL, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,LSFT(KC_RBRC), \
    KC_LBRC,          KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_RBRC, \
                      KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                  \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, _______________DEAD_HALF_ROW_______________, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GACS_R______________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, _______________DEAD_HALF_ROW_______________, \
                      KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
