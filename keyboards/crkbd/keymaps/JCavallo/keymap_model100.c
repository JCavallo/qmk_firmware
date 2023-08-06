/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Usage for Colemak + French + Dev
///////////////////////////////////////////////////////////////////////////////

/*

General idea is to use ScrollLock as a compose key, because, French.
Accents are triggered through combos on the left hand.
On Windows, we need to use a custom kb layout because dead keys are enabled in
the default us-intl layout, which messes things up a bit.

On Linux, in xinitrc:

- `xmodmap -e "keycode 78 = Multi_key"`
- `setxkbmap -layout us -variant altgr-intl`

(to switch back to fr layout, use `setxkbmap -layout fr -variant latin9`)

On Windows:

- Install Wincompose: http://wincompose.info/
- Configure it to use the ScrollLock key
- Download and install https://www.microsoft.com/en-us/download/confirmation.aspx?id=102134
- Load this kb: https://raw.githubusercontent.com/umanovskis/win-kbd-usint-nodead/master/us_international_no_dead_keys.klc#fromHistory

*/

///////////////////////////////////////////////////////////////////////////////
// Layer List
///////////////////////////////////////////////////////////////////////////////

enum layers {
    ALPHA, NAV, MOUSE, MEDIA, NUM, SYM, FUN, GAME_ALPHA, GAME_NUM, GAME_FUN
};

///////////////////////////////////////////////////////////////////////////////
// Combos for frequently used compose
///////////////////////////////////////////////////////////////////////////////
enum combo_events {
  COMBO_COMPOSE_QUOTE,
  COMBO_COMPOSE_E_QUOTE,
  COMBO_COMPOSE_GRAVE,
  COMBO_COMPOSE_GRAVE_RIGHT,
  COMBO_COMPOSE_CIRC,
  COMBO_COMPOSE_COMMA,
  COMBO_COMPOSE_DOUBLE_QUOTE,
  COMBO_UNDERSCORE,
  COMBO_DASH,
  COMBO_CAPS_WORD,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM compose_quote[] = {LALT_T(KC_R), LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM compose_e_quote[] = {LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM compose_grave[] = {LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM compose_grave_right[] = {LSFT_T(KC_N), LCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM compose_circ[] = {LALT_T(KC_R), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM compose_comma[] = {LALT_T(KC_I), LCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM compose_double_quote[] = {LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM underscore[] = {LSFT_T(KC_T), LSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM dash[] = {LCTL_T(KC_S), LCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM caps_word[] = {LALT_T(KC_R), LALT_T(KC_I), COMBO_END};

combo_t key_combos[] = {
  [COMBO_COMPOSE_QUOTE] = COMBO_ACTION(compose_quote),
  [COMBO_COMPOSE_E_QUOTE] = COMBO_ACTION(compose_e_quote),
  [COMBO_COMPOSE_GRAVE] = COMBO_ACTION(compose_grave),
  [COMBO_COMPOSE_GRAVE_RIGHT] = COMBO_ACTION(compose_grave_right),
  [COMBO_COMPOSE_CIRC] = COMBO_ACTION(compose_circ),
  [COMBO_COMPOSE_COMMA] = COMBO_ACTION(compose_comma),
  [COMBO_COMPOSE_DOUBLE_QUOTE] = COMBO_ACTION(compose_double_quote),
  [COMBO_UNDERSCORE] = COMBO_ACTION(underscore),
  [COMBO_DASH] = COMBO_ACTION(dash),
  [COMBO_CAPS_WORD] = COMBO_ACTION(caps_word),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO_COMPOSE_QUOTE:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_QUOTE));
      }
      break;
    case COMBO_COMPOSE_E_QUOTE:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_QUOTE) "e");
      }
      break;
    case COMBO_COMPOSE_GRAVE:
    case COMBO_COMPOSE_GRAVE_RIGHT:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_GRV));
      }
      break;
    case COMBO_COMPOSE_CIRC:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK));
        tap_code16(KC_CIRC);
      }
      break;
    case COMBO_COMPOSE_COMMA:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_COMM));
      }
      break;
    case COMBO_COMPOSE_DOUBLE_QUOTE:
      if (pressed) {
        SEND_STRING(SS_TAP(X_SLCK));
        register_code(KC_LSFT);
        SEND_STRING(SS_TAP(X_QUOTE));
        unregister_code(KC_LSFT);
      }
      break;
    case COMBO_UNDERSCORE:
      if (pressed) {
        SEND_STRING("_");
      }
      break;
    case COMBO_DASH:
      if (pressed) {
        SEND_STRING("-");
      }
      break;
    case COMBO_CAPS_WORD:
      if (pressed) {
        caps_word_on();
      }
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Leader
///////////////////////////////////////////////////////////////////////////////

// LEADER_EXTERNS();
//
// void matrix_scan_user(void) {
//   LEADER_DICTIONARY() {
//     leading = false;
//     leader_end();
//
//     SEQ_ONE_KEY(KC_W) {
//       // Anything you can do in a macro.
//       SEND_STRING(":w" SS_TAP(X_ENT));
//     }
//     /*SEQ_TWO_KEYS(KC_D, KC_D) {*/
//     /*  SEND_STRING(SS_LCTL("a") SS_LCTL("c"));*/
//     /*}*/
//     /*SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {*/
//     /*  SEND_STRING("https://start.duckduckgo.com\n");*/
//     /*}*/
//     /*SEQ_TWO_KEYS(KC_A, KC_S) {*/
//     /*  register_code(KC_LGUI);*/
//     /*  register_code(KC_S);*/
//     /*  unregister_code(KC_S);*/
//     /*  unregister_code(KC_LGUI);*/
//     /*}*/
//   }
// }

///////////////////////////////////////////////////////////////////////////////
// Macros
///////////////////////////////////////////////////////////////////////////////
enum custom_keycodes {
    COMPOSE_QUOTE = SAFE_RANGE,
    COMPOSE_CIRC,
    COMPOSE_GRAVE,
    COMPOSE_TREMA,
    COMPOSE_A_GRAVE,
    COMPOSE_CAPS_A_GRAVE,
    COMPOSE_C_CEDILLE,
    COMPOSE_CAPS_C_CEDILLE,
    COMPOSE_E_QUOTE,
    COMPOSE_E_GRAVE,
    COMPOSE_E_CIRC,
    COMPOSE_U_GRAVE,
    COMPOSE_U_TREMA,
    COMPOSE_I_TREMA,
    COMPOSE_O_TREMA,
};

void _quote() {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_QUOTE));
}

void _circ() {
    SEND_STRING(SS_TAP(X_SLCK));
    tap_code16(KC_CIRC);
}

void _grave() {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_GRV));
}

void _trema() {
    SEND_STRING(SS_TAP(X_SLCK));
    register_code(KC_LSFT);
    SEND_STRING(SS_TAP(X_QUOTE));
    unregister_code(KC_LSFT);
}

void _cedille() {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_COMM));
}

bool handle_compose_macros(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COMPOSE_QUOTE:
        if (record->tap.count && record->event.pressed) {
            _quote();
            return false;
        }
        break;
    case COMPOSE_CIRC:
        if (record->tap.count && record->event.pressed) {
            _circ();
            return false;
        }
        break;
    case COMPOSE_GRAVE:
        if (record->tap.count && record->event.pressed) {
            _grave();
            return false;
        }
        break;
    case COMPOSE_TREMA:
        if (record->event.pressed) {
            _trema();
            return false;
        }
        break;
    case COMPOSE_A_GRAVE:
        if (record->tap.count && record->event.pressed) {
            _grave();
            SEND_STRING(SS_TAP(KC_A));
            return false;
        }
        break;
    case COMPOSE_CAPS_A_GRAVE:
        if (record->tap.count && record->event.pressed) {
            _grave();
            register_code(KC_LSFT);
            SEND_STRING(SS_TAP(KC_A));
            unregister_code(KC_LSFT);
            return false;
        }
        break;
    case COMPOSE_C_CEDILLE:
        if (record->tap.count && record->event.pressed) {
            _cedille();
            SEND_STRING(SS_TAP(KC_C));
            return false;
        }
        break;
    case COMPOSE_CAPS_C_CEDILLE:
        if (record->tap.count && record->event.pressed) {
            _cedille();
            register_code(KC_LSFT);
            SEND_STRING(SS_TAP(KC_C));
            unregister_code(KC_LSFT);
            return false;
        }
        break;
    case COMPOSE_E_QUOTE:
        if (record->tap.count && record->event.pressed) {
            _quote();
            SEND_STRING(SS_TAP(KC_E));
            return false;
        }
        break;
    case COMPOSE_E_GRAVE:
        if (record->tap.count && record->event.pressed) {
            _grave();
            SEND_STRING(SS_TAP(KC_E));
            return false;
        }
        break;
    case COMPOSE_E_CIRC:
        if (record->tap.count && record->event.pressed) {
            _circ();
            SEND_STRING(SS_TAP(KC_E));
            return false;
        }
        break;
    case COMPOSE_U_GRAVE:
        if (record->tap.count && record->event.pressed) {
            _grave();
            SEND_STRING(SS_TAP(KC_U));
            return false;
        }
        break;
    case COMPOSE_U_TREMA:
        if (record->tap.count && record->event.pressed) {
            _trema();
            SEND_STRING(SS_TAP(KC_U));
            return false;
        }
        break;
    case COMPOSE_I_TREMA:
        if (record->tap.count && record->event.pressed) {
            _trema();
            SEND_STRING(SS_TAP(KC_I));
            return false;
        }
        break;
    case COMPOSE_O_TREMA:
        if (record->tap.count && record->event.pressed) {
            _trema();
            SEND_STRING(SS_TAP(KC_O));
            return false;
        }
        break;
    }
    return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_T):
            return TAPPING_TERM - 20;
        case LSFT_T(KC_N):
            return TAPPING_TERM - 20;
        default:
            return TAPPING_TERM;
    }
}

/* bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_T):
            return false;
        case LSFT_T(KC_N):
            return false;
        default:
            return true;
    }
} */

///////////////////////////////////////////////////////////////////////////////
// Layers
///////////////////////////////////////////////////////////////////////////////
#define KC_MUTE_MIC KC_F20
// Base => Colemak DH
#define ALPHA_LAYER \
U_NU,              KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,             KC_LEAD, \
KC_ESC,            KC_A,              KC_R,              KC_S,              KC_T,              KC_G,              KC_M,              LSFT_T(KC_N),      KC_E,              KC_I,              KC_O,                U_NU, \
U_NU,              LGUI_T(KC_Z),      LALT_T(KC_X),      LCTL_T(KC_C),      LSFT_T(KC_D),      KC_V,              KC_K,              LSFT_T(KC_H),      LCTL_T(KC_COMM),   LALT_T(KC_DOT),    LGUI_T(KC_SLSH),     KC_MUTE_MIC, \
                                                         OSL(ACCENT),       KC_SPC,            LT(NAVIGATION, KC_TAB), LT(FUNCTION, KC_ENT), LT(NUM, KC_BSPC), OSL(SYMBOL)
// Right hand thumb left
#define SYMBOL_LAYER \
U_NU,              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_COLN,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             U_NU, \
U_NU,              KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE,           U_NA,              U_NA,              U_NA,              U_NU,              U_NA,                U_NU, \
                                                         KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA

// Right hand thumb middle
#define NUMBER_LAYER \
U_NU,              KC_LBRC,           KC_4,              KC_5,              KC_6,              KC_PLUS,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_0,              KC_1,              KC_2,              KC_3,              KC_DOT,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             U_NU, \
U_NU,              KC_COMM,           KC_7,              KC_8,              KC_9,              KC_EQU,            U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NA,              U_NA,              U_NA

// Right hand thumb right
#define FUNCTION_LAYER \
U_NU,              KC_F12,            KC_F4,             KC_F5,             KC_F6,             U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_F11,            KC_F1,             KC_F2,             KC_F3,             U_NU,              U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             U_NU, \
U_NU,              KC_F10,            KC_F7,             KC_F8,             KC_F9,             U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NA,              U_NA,              U_NA

// Left hand thumb left
#define ACCENT_LAYER \
U_NU,              COMPOSE_CAPS_A_GRAVE, LCTL(KC_C),     LCTL(KC_V),        LCTL(LSFT(KC_C),  LCTL(LSFT(KC_V),    U_NU,              U_NU,              COMPOSE_U_GRAVE,   COMPOSE_U_TREMA,   U_NU,                U_NU, \
U_NU,              COMPOSE_A_GRAVE,   COMPOSE_QUOTE,     COMPOSE_GRAVE,     COMPOSE_CIRC,     COMPOSE_TREMA,      U_NU,              COMPOSE_E_GRAVE,   COMPOSE_E_QUOTE,   COMPOSE_I_TREMA,   COMPOSE_O_TRMEA,     U_NU, \
U_NU,              U_NU,              U_NU,              COMPOSE_C_CEDILLE, COMPOSE_CAPS_C_CEDILLE, U_NU,         U_NU,              U_NU,              COMPOSE_E_CIRC,    U_NU,              U_NU,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NU,              U_NU,              KC_SCLK

// Left hand thumb middle
#define NAVIGATION_LAYER \
RESET,             U_NU,              U_NU,              U_NU,              U_NU,              U_NU,              U_RDO,             KC_MUTE,           KC_VOLD,           KC_VOLU,           U_NU,                U_NU, \
U_NU,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_CAPS,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,             U_NU, \
U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,              U_NU, \
                                                         U_NA,              U_NA,              U_NA,              U_NU,              U_NU,              U_NU

// Game mode, enabled by media + Right-hand top-most key
// #define GAME_ALPHA_LAYER \
// KC_T,              KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,                KC_P, \
// KC_G,              KC_LSFT,           KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,                KC_M, \
// KC_B,              KC_LCTL,           KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,              U_NU, \
//                                                          LT(GAME_FUN, KC_ESC),KC_SPC,          LT(GAME_NUM, KC_TAB),KC_ENT,          KC_BSPC,           LALT_T(KC_DEL)

///////////////////////////////////////////////////////////////////////////////
// Actually apply layers
///////////////////////////////////////////////////////////////////////////////
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPHA]       = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, ALPHA_LAYER),
  [NAV]         = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, NAVIGATION_LAYER),
  [NUM]         = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, NUMBER_LAYER),
  [SYM]         = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, SYMBOL_LAYER),
  [FUN]         = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, FUNCTION_LAYER),
  [ACCENT]      = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, ACCENT_LAYER),
  // [GAME_ALPHA]  = U_MACRO_VA_ARGS(LAYOUT_split_3x6_3, GAME_ALPHA_LAYER),
};

///////////////////////////////////////////////////////////////////////////////
// Oled screen
///////////////////////////////////////////////////////////////////////////////

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    // if (layer_state_is(GAME_ALPHA) || layer_state_is(GAME_NUM) || layer_state_is(GAME_FUN)) {
    //     oled_write_ln_P(PSTR("GAMING"), false);
    // } else if (layer_state_is(NAV)) {
    if (layer_state_is(NAV)) {
        oled_write_ln_P(PSTR("Navigation"), false);
    } else if (layer_state_is(ACCENT)) {
        oled_write_ln_P(PSTR("Accent"), false);
    } else if (layer_state_is(NUM)) {
        oled_write_ln_P(PSTR("Numbers"), false);
    } else if (layer_state_is(SYM)) {
        oled_write_ln_P(PSTR("Symbols"), false);
    } else if (layer_state_is(FUN)) {
        oled_write_ln_P(PSTR("Fn keys"), false);
    } else {
        oled_write_ln_P(PSTR("Alpha"), false);
    }
}


/*char keylog_str[24] = {};*/

/*const char code_to_name[60] = {*/
/*    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',*/
/*    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',*/
/*    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',*/
/*    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',*/
/*    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',*/
/*    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};*/

/*void set_keylog(uint16_t keycode, keyrecord_t *record) {*/
/*  char name = ' ';*/
/*    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||*/
/*        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }*/
/*  if (keycode < 60) {*/
/*    name = code_to_name[keycode];*/
/*  }*/

/*  // update keylog*/
/*  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",*/
/*           record->event.key.row, record->event.key.col,*/
/*           keycode, name);*/
/*}*/

/*void oled_render_keylog(void) {*/
/*    oled_write(keylog_str, false);*/
/*}*/

/*void oled_render_logo(void) {*/
/*    static const char PROGMEM crkbd_logo[] = {*/
/*        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,*/
/*        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,*/
/*        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,*/
/*        0};*/
/*    oled_write_P(crkbd_logo, false);*/
/*}*/

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        /*oled_render_keylog();*/
    /*} else {*/
    /*    oled_render_logo();*/
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool res = true;
  res = handle_compose_macros(keycode, record);
/*#ifdef OLED_ENABLE*/
/*  if (record->event.pressed) {*/
/*    set_keylog(keycode, record);*/
/*  }*/
/*#endif // OLED_ENABLE*/
  return true;
}
