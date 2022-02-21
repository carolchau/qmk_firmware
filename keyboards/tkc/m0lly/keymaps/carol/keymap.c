/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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

#include QMK_KEYBOARD_H

enum keycode {
    _ZOOM = SAFE_RANGE,
    _MPF1, // ¯\_(ツ)_/¯
    _MPF8  // (´.• ᵕ •.`) ♡
};

enum layer_names {
    _BASE,
    _FUNC,
    _WASD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
     *
     * ,-----------------------------------------------------------. .-------------------.
     * | ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |FN  | /  | *  | -  |
     * |-----------------------------------------------------------| |-------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | | 7  | 8  | 9  |    |
     * |-----------------------------------------------------------| |--------------| +  |
     * |  FN |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return   | | 4  | 5  | 6  |    |
     * |-----------------------------------------------------------| |-------------------|
     * |Shift |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shft | ESC | | 1  | 2  | 3  | Ent|
     * |-----------------------------------------------------------| |--------------|    |
     * |Ctrl|Gui |Alt |      Space           | Alt | FN | PLY |Ctr | |   0     | .  |    |
     * `-----------------------------------------------------------' '-------------------'
     */
    [_BASE] = LAYOUT_all(
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,  KC_BSPC, XXXXXXX,     TG(_WASD), KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,   KC_RBRC, KC_BSLS,              KC_P7,     KC_P8,   KC_P9,   XXXXXXX,
        MO(_FUNC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,   XXXXXXX, KC_ENT,               KC_P4,     KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT,   XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT, KC_ESC,               KC_P1,     KC_P2,   KC_P3,   XXXXXXX,
        KC_LCTL,   KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FUNC), KC_MPLY, KC_RCTL,              KC_P0,     XXXXXXX, KC_PDOT, KC_PENT
    ),
    [_FUNC] = LAYOUT_all(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,   KC_F12,  KC_DEL,  XXXXXXX,     KC_NLCK, KC_CAPS, KC_SCRL, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______,              _______, KC_VOLU, _______, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, XXXXXXX, _______,              KC_MPRV, KC_VOLD, KC_MNXT, _______,
        _______, XXXXXXX, _ZOOM,   _MPF1,   _MPF8,   _______, _______, _______, KC_MUTE, _______, _______, _______, _______, _______,              _______, _______, _______, XXXXXXX,
        _______, RESET,   _______,                            _______,                            _______, _______, _______, _______,              _______, XXXXXXX, _______, _______
    ),
    [_WASD] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, KC_UP,   _______, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______,              KC_LEFT, KC_DOWN, KC_RGHT, _______,
        _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, XXXXXXX,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,              _______, XXXXXXX, _______, _______
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("M0lly\n"),false);

    // Layer status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            print("Base\n");
            break;
        case _FUNC:
            print("Func\n");
            break;
        case _WASD:
            print("WASD\n");
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            print("default\n")
    }

    // Indicators
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR(`"NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif

// https://docs.qmk.fm/#/feature_led_indicators?id=led_update_
bool led_update_kb(led_t led_state) {
    
    bool res = led_update_user(led_state);
    if (res) {
        // Layer ON
        if (IS_LAYER_ON(_BASE)) {
            writePinHigh(LED_NUM_LOCK_PIN);
        }
        if (IS_LAYER_ON(_FUNC)) {
            writePinHigh(LED_CAPS_LOCK_PIN);
        }
        if (IS_LAYER_ON(_WASD)) {
            writePinHigh(LED_SCROLL_LOCK_PIN);
        }
        // Layer OFF
        if (IS_LAYER_OFF(_BASE)) {
            writePinLow(LED_NUM_LOCK_PIN);
        }
        if (IS_LAYER_OFF(_FUNC)) {
            writePinLow(LED_CAPS_LOCK_PIN);
        }
        if (IS_LAYER_OFF(_WASD)) {
            writePinLow(LED_SCROLL_LOCK_PIN);
        }
    }
    return res;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case _ZOOM:
            if (record->event.pressed) { SEND_STRING("zoom: caroli (837 837 0176)"); }
            return false;
        case _MPF1:
            if (record->event.pressed) { send_unicode_string("¯\\_(ツ)_/¯"); }
            return false;
        case _MPF8:
            if (record->event.pressed) { send_unicode_string("(´.• ᵕ •.`) ♡"); }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}