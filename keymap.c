/* Copyright 2023 Brian Low
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


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
     if (is_keyboard_master()) {
         return OLED_ROTATION_270;
     }
     if (!is_keyboard_master()) {
         return OLED_ROTATION_180;
     }

     return rotation;
 }

static void print_status_narrow(void) {
    oled_set_cursor(0,1);
    
    oled_write_ln_P(PSTR("Julio"), false);

    oled_write_ln_P(PSTR("-----"), false);

    // Mostrar la capa activa
    if (layer_state_is(0)) {
        oled_write_ln_P(PSTR("- DEF"), false);
    } else if (layer_state_is(1)) {
        oled_write_ln_P(PSTR("- FUN"), false);
    } else if (layer_state_is(2)) {
        oled_write_ln_P(PSTR("- ADT"), false);
    } else {
        oled_write_ln_P(PSTR("UNDEF"), false);
    }

    oled_write_ln_P(PSTR("-----"), false);

    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock ? PSTR(" CAP") : PSTR(" LOW"), false);

    oled_write_ln_P(PSTR("-----"), false);

    oled_write_ln_P(PSTR(" :D "), false);
}

static void print_status_2(void) {
    oled_set_cursor(0,1);
    
    oled_write_ln_P(PSTR("Getsemani <3"), false);

    oled_write_ln_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("(=^_^=)"), false);

}

 bool oled_task_user(void) {
     if (is_keyboard_master()) {
        print_status_narrow();
     } else {
        print_status_2();
        //oled_draw_bitmap(0, 0, qmk_logo); // Esto debería mostrar el logo QMK por defecto

     }
     return false;
 }

#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    // Layer 0: Default Layer (QWERTY)
    /*
    * QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | CAPS |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------|  Mute |    | Play  |------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | MINS |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTL | LGUI | LALT | MO 1 | / Space /       \Enter \  | MO 2 | LBRC | RBRC | BSLS |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */

    [0] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,     KC_MPLY, KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                        KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC,      KC_ENT,  MO(2),    KC_LBRC,  KC_RBRC, KC_BSLS
    ),

    /*
    * Layer 1: Function Layer
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  | F11  |  F12 |      |      |      |                    |      | HOME |  UP  | END  |      |  =   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | CAPS |      |      |      |      |      |-------.    ,-------|      | LEFT | DOWN | RIGHT|   ;  |  '   |
    * |------+------+------+------+------+------|  Mute |    | Play |------+------+------+------+------+------|
    * |LShift|      |      |      |      |      |-------|    |-------|      |      |   ,  |   .  |   /  | MINS |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTL | LGUI | LALT | MO 1 | / Space /       \Enter \  | MENU | LBRC | RBRC | BSLS |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */

    // Layer 1: Function Layer
    [1] = LAYOUT(
        KC_GRV ,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,                         KC_F6  ,  KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  KC_TRNS,
        KC_TRNS,  KC_F11 ,  KC_F12 ,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  KC_HOME,  KC_UP  ,  KC_END ,  XXXXXXX,  KC_TRNS,
        KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                 KC_TRNS,  KC_APP ,  KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    /*
    * Layer 2: Additional Layer
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  | F11  |  F12 |      |      |      |                    |      | HOME |  UP  | END  |      |  =   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | CAPS |      |      |      |      |      |-------.    ,-------|      | LEFT | DOWN | RIGHT|   ;  |  '   |
    * |------+------+------+------+------+------|  Mute |    | Play |------+------+------+------+------+------|
    * |LShift|      |      |      |      |      |-------|    |-------|      |      |   ,  |   .  |   /  | MINS |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTL | LGUI | LALT | MO 1 | / Space /       \Enter \  | MENU | LBRC | RBRC | BSLS |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */

    [2] = LAYOUT(
        KC_GRV ,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,                         KC_F6  ,  KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  KC_TRNS,
        KC_TRNS,  KC_F11 ,  KC_F12 ,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  KC_HOME,  KC_UP  ,  KC_END ,  XXXXXXX,  KC_TRNS,
        KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                 KC_TRNS,  KC_APP ,  KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =
        {
            ENCODER_CCW_CW(KC_VOLU, KC_VOLD),   
            ENCODER_CCW_CW(KC_MNXT, KC_MPRV) 
        },

    [1] =
        {
            ENCODER_CCW_CW(MS_WHLD, MS_WHLU),    // Encoder : Desplazamiento hacia arriba/abajo
            ENCODER_CCW_CW(MS_WHLL, MS_WHLR)   // Encoder : Desplazamiento lateral (derecha/izquierda)
        },

    [2] =
        {
            ENCODER_CCW_CW(MS_WHLD, MS_WHLU),    // Encoder : Desplazamiento hacia arriba/abajo
            ENCODER_CCW_CW(MS_WHLL, MS_WHLR)   // Encoder : Desplazamiento lateral (derecha/izquierda)
        },
};
#endif
                                                                                                                                    