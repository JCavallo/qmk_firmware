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
    ALPHA, NAV, ACCENT, NUM, SYM, FUN,
};

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
    COMPOSE_U_CIRC,
    COMPOSE_I_CIRC,
    COMPOSE_O_CIRC,
};

void quote(void) {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_QUOTE));
}

void circ(void) {
    SEND_STRING(SS_TAP(X_SLCK));
    tap_code16(KC_CIRC);
}

void grave(void) {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_GRV));
}

void trema(void) {
    SEND_STRING(SS_TAP(X_SLCK));
    register_code(KC_LSFT);
    SEND_STRING(SS_TAP(X_QUOTE));
    unregister_code(KC_LSFT);
}

void cedille(void) {
    SEND_STRING(SS_TAP(X_SLCK) SS_TAP(X_COMM));
}

bool handle_compose_macros(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COMPOSE_QUOTE:
        if (record->event.pressed) {
            quote();
            return false;
        }
        break;
    case COMPOSE_CIRC:
        if (record->event.pressed) {
            circ();
            return false;
        }
        break;
    case COMPOSE_GRAVE:
        if (record->event.pressed) {
            grave();
            return false;
        }
        break;
    case COMPOSE_TREMA:
        if (record->event.pressed) {
            trema();
            return false;
        }
        break;
    case COMPOSE_A_GRAVE:
        if (record->event.pressed) {
            grave();
            SEND_STRING("a");
            return false;
        }
        break;
    case COMPOSE_CAPS_A_GRAVE:
        if (record->event.pressed) {
            grave();
            SEND_STRING("A");
            return false;
        }
        break;
    case COMPOSE_C_CEDILLE:
        if (record->event.pressed) {
            cedille();
            SEND_STRING("c");
            return false;
        }
        break;
    case COMPOSE_CAPS_C_CEDILLE:
        if (record->event.pressed) {
            cedille();
            SEND_STRING("C");
            return false;
        }
        break;
    case COMPOSE_E_QUOTE:
        if (record->event.pressed) {
            quote();
            SEND_STRING("e");
            return false;
        }
        break;
    case COMPOSE_E_GRAVE:
        if (record->event.pressed) {
            grave();
            SEND_STRING("e");
            return false;
        }
        break;
    case COMPOSE_E_CIRC:
        if (record->event.pressed) {
            circ();
            SEND_STRING("e");
            return false;
        }
        break;
    case COMPOSE_U_GRAVE:
        if (record->event.pressed) {
            grave();
            SEND_STRING("u");
            return false;
        }
        break;
    case COMPOSE_U_CIRC:
        if (record->event.pressed) {
            circ();
            SEND_STRING("u");
            return false;
        }
        break;
    case COMPOSE_I_CIRC:
        if (record->event.pressed) {
            circ();
            SEND_STRING("i");
            return false;
        }
        break;
    case COMPOSE_O_CIRC:
        if (record->event.pressed) {
            circ();
            SEND_STRING("o");
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
// Combos for frequently used compose
///////////////////////////////////////////////////////////////////////////////
enum combo_events {
  COMBO_RSHIFT,
  COMBO_LSHIFT,
  COMBO_RCTL,
  COMBO_LCTL,
  COMBO_BCKSPC,
  COMBO_FAST_BCKSPC,
  COMBO_UNDERSCORE,
  COMBO_DASH,
  COMBO_BACKTICK,
  COMBO_CAPS_WORD,
  COMBO_ESCAPE,
  COMBO_COMPOSE_E_ACUTE,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_rshift[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM combo_lshift[] = {KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM combo_rctl[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_lctl[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM combo_bckspc[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_fast_bckspc[] = {KC_QUOT, KC_Y, COMBO_END};
const uint16_t PROGMEM underscore[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM dash[] = {KC_E, KC_S, COMBO_END};
const uint16_t PROGMEM escape[] = {KC_R, KC_I, COMBO_END};
const uint16_t PROGMEM backtick[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM caps_word[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM compose_e_acute[] = {KC_N, KC_I, COMBO_END};

combo_t key_combos[] = {
  [COMBO_RSHIFT] = COMBO(combo_rshift, KC_LSFT),
  [COMBO_LSHIFT] = COMBO(combo_lshift, KC_LSFT),
  [COMBO_RCTL] = COMBO(combo_rctl, KC_LCTL),
  [COMBO_LCTL] = COMBO(combo_lctl, KC_LCTL),
  [COMBO_BCKSPC] = COMBO(combo_bckspc, KC_BSPC),
  [COMBO_FAST_BCKSPC] = COMBO(combo_fast_bckspc, RCTL(KC_BSPC)),
  [COMBO_UNDERSCORE] = COMBO(underscore, KC_UNDS),
  [COMBO_DASH] = COMBO(dash, KC_MINS),
  [COMBO_BACKTICK] = COMBO(backtick, KC_GRV),
  [COMBO_ESCAPE] = COMBO(escape, KC_ESC),
  [COMBO_CAPS_WORD] = COMBO_ACTION(caps_word),
  [COMBO_COMPOSE_E_ACUTE] = COMBO(compose_e_acute, COMPOSE_E_QUOTE),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    // case COMBO_RSHIFT:
    // case COMBO_LSHIFT:
    //   if (pressed) {
    //     register_code(KC_LSFT);
    //   } else {
    //     unregister_code(KC_LSFT);
    //   }
    //   break;
    // case COMBO_RCTL:
    // case COMBO_LCTL:
    //   if (pressed) {
    //     register_code(KC_LCTL);
    //   } else {
    //     unregister_code(KC_LCTL);
    //   }
    //   break;
    // case COMBO_BCKSPC:
    //   if (pressed) {
    //     SEND_STRING(SS_TAP(X_BSPC));
    //   }
    //   break;
    // case COMBO_FAST_BCKSPC:
    //   if (pressed) {
    //     register_code(KC_RCTL);
    //     SEND_STRING(SS_TAP(X_BSPC));
    //     unregister_code(KC_RCTL);
    //   }
    //   break;
    // case COMBO_UNDERSCORE:
    //   if (pressed) {
    //     SEND_STRING("_");
    //   }
    //   break;
    // case COMBO_DASH:
    //   if (pressed) {
    //     SEND_STRING("-");
    //   }
    //   break;
    case COMBO_CAPS_WORD:
      if (pressed) {
        caps_word_on();
      }
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Layers
///////////////////////////////////////////////////////////////////////////////
#define KC_MUTE_MIC KC_F20
// Base => Colemak DH
#define ALPHA_LAYER \
U_NU,              KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,             KC_LEAD, \
/*KC_ESC*/U_NU,            KC_A,              KC_R,              KC_S,              KC_T,              KC_G,              KC_M,              KC_N,              KC_E,              KC_I,              KC_O,                U_NU, \
U_NU,              LGUI_T(KC_Z),      LALT_T(KC_X),      LCTL_T(KC_C),      LSFT_T(KC_D),      KC_V,              KC_K,              LSFT_T(KC_H),      LCTL_T(KC_COMM),   LALT_T(KC_DOT),    LGUI_T(KC_SLSH),     KC_MUTE_MIC, \
                                                         OSL(ACCENT),       KC_SPC,            LT(NAV, KC_TAB),   LT(FUN, KC_ENT),   LT(NUM, KC_BSPC),  OSL(SYM)
// Right hand thumb left
#define SYMBOL_LAYER \
U_NU,              U_NA,              KC_AMPR,           KC_ASTR,           U_NA,              KC_PLUS,           KC_BSLS,           U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_SCLN,           KC_LCBR,           KC_LBRC,           KC_LPRN,           /*KC_UNDS*/U_NU,           /*KC_MINS*/U_NU,           KC_RPRN,           KC_RBRC,           KC_RCBR,           KC_COLN,             U_NU, \
U_NU,              KC_GRV,            KC_EXLM,           KC_AT,             KC_HASH,           KC_EQL,            KC_PIPE,           KC_CIRC,           KC_PERC,           KC_DLR,            KC_TILD,             U_NU, \
                                                         U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA

// Right hand thumb middle
#define NUMBER_LAYER \
U_NU,              KC_LBRC,           KC_4,              KC_5,              KC_6,              KC_PLUS,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_0,              KC_1,              KC_2,              KC_3,              KC_DOT,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             U_NU, \
U_NU,              KC_COMM,           KC_7,              KC_8,              KC_9,              KC_EQL,            U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NA,              U_NA,              U_NA

// Right hand thumb right
#define FUNCTION_LAYER \
U_NU,              KC_F12,            KC_F4,             KC_F5,             KC_F6,             U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                RESET, \
U_NU,              KC_F11,            KC_F1,             KC_F2,             KC_F3,             U_NU,              U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             U_NU, \
U_NU,              KC_F10,            KC_F7,             KC_F8,             KC_F9,             U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NA,              U_NA,              U_NA

// Left hand thumb left
#define ACCENT_LAYER \
U_NU,              COMPOSE_CAPS_A_GRAVE, LCTL(KC_C),     LCTL(KC_V),        LCTL(LSFT(KC_C)), LCTL(LSFT(KC_V)),   U_NU,              U_NU,              COMPOSE_U_GRAVE,   COMPOSE_U_CIRC,   U_NU,                U_NU, \
U_NU,              COMPOSE_A_GRAVE,   COMPOSE_QUOTE,     COMPOSE_GRAVE,     COMPOSE_CIRC,     COMPOSE_TREMA,      U_NU,              COMPOSE_E_GRAVE,   COMPOSE_E_QUOTE,   COMPOSE_I_CIRC,   COMPOSE_O_CIRC,     U_NU, \
U_NU,              U_NU,              U_NU,              COMPOSE_C_CEDILLE, COMPOSE_CAPS_C_CEDILLE, U_NU,         U_NU,              U_NU,              COMPOSE_E_CIRC,    U_NU,              U_NU,                U_NU, \
                                                         U_NU,              U_NU,              U_NU,              U_NU,              U_NU,              KC_SLCK

// Left hand thumb middle
#define NAVIGATION_LAYER \
RESET,             U_NU,              U_NU,              U_NU,              U_NU,              U_NU,              U_RDO,             KC_MUTE,           KC_VOLD,           KC_VOLU,           U_NU,                U_NU, \
U_NU,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_CAPS,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,             U_NU, \
U_NU,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,              U_NU, \
                                                         U_NA,              U_NA,              U_NA,              U_NU,              KC_DEL,              U_NU

/*// Game mode, enabled by media + Right-hand top-most key
// #define GAME_ALPHA_LAYER \
// KC_T,              KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,                KC_P, \
// KC_G,              KC_LSFT,           KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,                KC_M, \
// KC_B,              KC_LCTL,           KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,              U_NU, \
//                                                          LT(GAME_FUN, KC_ESC),KC_SPC,          LT(GAME_NUM, KC_TAB),KC_ENT,          KC_BSPC,           LALT_T(KC_DEL)
*/
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
/*#ifdef OLED_ENABLE*/
/*  if (record->event.pressed) {*/
/*    set_keylog(keycode, record);*/
/*  }*/
/*#endif // OLED_ENABLE*/
  return handle_compose_macros(keycode, record);
}
