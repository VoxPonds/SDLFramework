module;
#include <SDL3/SDL_scancode.h>

export module engine.platform.sdlplatform:sdlinputadapter;
import engine.platform.inputcode;

export namespace engine::platform
{
    inline EInputCode translateSDLScancode(SDL_Scancode scancode);
}

namespace engine::platform
{
    EInputCode translateSDLScancode(const SDL_Scancode scancode)
    {
        switch (scancode)
        {
            case SDL_SCANCODE_UNKNOWN: return EInputCode::KEY_UNKNOWN;

            case SDL_SCANCODE_A: return EInputCode::KEY_A;
            case SDL_SCANCODE_B: return EInputCode::KEY_B;
            case SDL_SCANCODE_C: return EInputCode::KEY_C;
            case SDL_SCANCODE_D: return EInputCode::KEY_D;
            case SDL_SCANCODE_E: return EInputCode::KEY_E;
            case SDL_SCANCODE_F: return EInputCode::KEY_F;
            case SDL_SCANCODE_G: return EInputCode::KEY_G;
            case SDL_SCANCODE_H: return EInputCode::KEY_H;
            case SDL_SCANCODE_I: return EInputCode::KEY_I;
            case SDL_SCANCODE_J: return EInputCode::KEY_J;
            case SDL_SCANCODE_K: return EInputCode::KEY_K;
            case SDL_SCANCODE_L: return EInputCode::KEY_L;
            case SDL_SCANCODE_M: return EInputCode::KEY_M;
            case SDL_SCANCODE_N: return EInputCode::KEY_N;
            case SDL_SCANCODE_O: return EInputCode::KEY_O;
            case SDL_SCANCODE_P: return EInputCode::KEY_P;
            case SDL_SCANCODE_Q: return EInputCode::KEY_Q;
            case SDL_SCANCODE_R: return EInputCode::KEY_R;
            case SDL_SCANCODE_S: return EInputCode::KEY_S;
            case SDL_SCANCODE_T: return EInputCode::KEY_T;
            case SDL_SCANCODE_U: return EInputCode::KEY_U;
            case SDL_SCANCODE_V: return EInputCode::KEY_V;
            case SDL_SCANCODE_W: return EInputCode::KEY_W;
            case SDL_SCANCODE_X: return EInputCode::KEY_X;
            case SDL_SCANCODE_Y: return EInputCode::KEY_Y;
            case SDL_SCANCODE_Z: return EInputCode::KEY_Z;

            case SDL_SCANCODE_1: return EInputCode::KEY_1;
            case SDL_SCANCODE_2: return EInputCode::KEY_2;
            case SDL_SCANCODE_3: return EInputCode::KEY_3;
            case SDL_SCANCODE_4: return EInputCode::KEY_4;
            case SDL_SCANCODE_5: return EInputCode::KEY_5;
            case SDL_SCANCODE_6: return EInputCode::KEY_6;
            case SDL_SCANCODE_7: return EInputCode::KEY_7;
            case SDL_SCANCODE_8: return EInputCode::KEY_8;
            case SDL_SCANCODE_9: return EInputCode::KEY_9;
            case SDL_SCANCODE_0: return EInputCode::KEY_0;

            case SDL_SCANCODE_RETURN: return EInputCode::KEY_RETURN;
            case SDL_SCANCODE_ESCAPE: return EInputCode::KEY_ESCAPE;
            case SDL_SCANCODE_BACKSPACE: return EInputCode::KEY_BACKSPACE;
            case SDL_SCANCODE_TAB: return EInputCode::KEY_TAB;
            case SDL_SCANCODE_SPACE: return EInputCode::KEY_SPACE;

            case SDL_SCANCODE_MINUS: return EInputCode::KEY_MINUS;
            case SDL_SCANCODE_EQUALS: return EInputCode::KEY_EQUALS;
            case SDL_SCANCODE_LEFTBRACKET: return EInputCode::KEY_LEFTBRACKET;
            case SDL_SCANCODE_RIGHTBRACKET: return EInputCode::KEY_RIGHTBRACKET;
            case SDL_SCANCODE_BACKSLASH: return EInputCode::KEY_BACKSLASH;
            case SDL_SCANCODE_NONUSHASH: return EInputCode::KEY_NONUSHASH;
            case SDL_SCANCODE_SEMICOLON: return EInputCode::KEY_SEMICOLON;
            case SDL_SCANCODE_APOSTROPHE: return EInputCode::KEY_APOSTROPHE;
            case SDL_SCANCODE_GRAVE: return EInputCode::KEY_GRAVE;
            case SDL_SCANCODE_COMMA: return EInputCode::KEY_COMMA;
            case SDL_SCANCODE_PERIOD: return EInputCode::KEY_PERIOD;
            case SDL_SCANCODE_SLASH: return EInputCode::KEY_SLASH;

            case SDL_SCANCODE_CAPSLOCK: return EInputCode::KEY_CAPSLOCK;

            case SDL_SCANCODE_F1: return EInputCode::KEY_F1;
            case SDL_SCANCODE_F2: return EInputCode::KEY_F2;
            case SDL_SCANCODE_F3: return EInputCode::KEY_F3;
            case SDL_SCANCODE_F4: return EInputCode::KEY_F4;
            case SDL_SCANCODE_F5: return EInputCode::KEY_F5;
            case SDL_SCANCODE_F6: return EInputCode::KEY_F6;
            case SDL_SCANCODE_F7: return EInputCode::KEY_F7;
            case SDL_SCANCODE_F8: return EInputCode::KEY_F8;
            case SDL_SCANCODE_F9: return EInputCode::KEY_F9;
            case SDL_SCANCODE_F10: return EInputCode::KEY_F10;
            case SDL_SCANCODE_F11: return EInputCode::KEY_F11;
            case SDL_SCANCODE_F12: return EInputCode::KEY_F12;

            case SDL_SCANCODE_PRINTSCREEN: return EInputCode::KEY_PRINTSCREEN;
            case SDL_SCANCODE_SCROLLLOCK: return EInputCode::KEY_SCROLLLOCK;
            case SDL_SCANCODE_PAUSE: return EInputCode::KEY_PAUSE;
            case SDL_SCANCODE_INSERT: return EInputCode::KEY_INSERT;
            case SDL_SCANCODE_HOME: return EInputCode::KEY_HOME;
            case SDL_SCANCODE_PAGEUP: return EInputCode::KEY_PAGEUP;
            case SDL_SCANCODE_DELETE: return EInputCode::KEY_DELETE;
            case SDL_SCANCODE_END: return EInputCode::KEY_END;
            case SDL_SCANCODE_PAGEDOWN: return EInputCode::KEY_PAGEDOWN;

            case SDL_SCANCODE_RIGHT: return EInputCode::KEY_RIGHT;
            case SDL_SCANCODE_LEFT: return EInputCode::KEY_LEFT;
            case SDL_SCANCODE_DOWN: return EInputCode::KEY_DOWN;
            case SDL_SCANCODE_UP: return EInputCode::KEY_UP;

            case SDL_SCANCODE_NUMLOCKCLEAR: return EInputCode::KEY_NUMLOCKCLEAR;

            case SDL_SCANCODE_KP_DIVIDE: return EInputCode::KEY_KP_DIVIDE;
            case SDL_SCANCODE_KP_MULTIPLY: return EInputCode::KEY_KP_MULTIPLY;
            case SDL_SCANCODE_KP_MINUS: return EInputCode::KEY_KP_MINUS;
            case SDL_SCANCODE_KP_PLUS: return EInputCode::KEY_KP_PLUS;
            case SDL_SCANCODE_KP_ENTER: return EInputCode::KEY_KP_ENTER;

            case SDL_SCANCODE_KP_1: return EInputCode::KEY_KP_1;
            case SDL_SCANCODE_KP_2: return EInputCode::KEY_KP_2;
            case SDL_SCANCODE_KP_3: return EInputCode::KEY_KP_3;
            case SDL_SCANCODE_KP_4: return EInputCode::KEY_KP_4;
            case SDL_SCANCODE_KP_5: return EInputCode::KEY_KP_5;
            case SDL_SCANCODE_KP_6: return EInputCode::KEY_KP_6;
            case SDL_SCANCODE_KP_7: return EInputCode::KEY_KP_7;
            case SDL_SCANCODE_KP_8: return EInputCode::KEY_KP_8;
            case SDL_SCANCODE_KP_9: return EInputCode::KEY_KP_9;
            case SDL_SCANCODE_KP_0: return EInputCode::KEY_KP_0;

            case SDL_SCANCODE_KP_PERIOD: return EInputCode::KEY_KP_PERIOD;

            case SDL_SCANCODE_NONUSBACKSLASH: return EInputCode::KEY_NONUSBACKSLASH;
            case SDL_SCANCODE_APPLICATION: return EInputCode::KEY_APPLICATION;
            case SDL_SCANCODE_POWER: return EInputCode::KEY_POWER;
            case SDL_SCANCODE_KP_EQUALS: return EInputCode::KEY_KP_EQUALS;

            case SDL_SCANCODE_F13: return EInputCode::KEY_F13;
            case SDL_SCANCODE_F14: return EInputCode::KEY_F14;
            case SDL_SCANCODE_F15: return EInputCode::KEY_F15;
            case SDL_SCANCODE_F16: return EInputCode::KEY_F16;
            case SDL_SCANCODE_F17: return EInputCode::KEY_F17;
            case SDL_SCANCODE_F18: return EInputCode::KEY_F18;
            case SDL_SCANCODE_F19: return EInputCode::KEY_F19;
            case SDL_SCANCODE_F20: return EInputCode::KEY_F20;
            case SDL_SCANCODE_F21: return EInputCode::KEY_F21;
            case SDL_SCANCODE_F22: return EInputCode::KEY_F22;
            case SDL_SCANCODE_F23: return EInputCode::KEY_F23;
            case SDL_SCANCODE_F24: return EInputCode::KEY_F24;

            case SDL_SCANCODE_EXECUTE: return EInputCode::KEY_EXECUTE;
            case SDL_SCANCODE_HELP: return EInputCode::KEY_HELP;
            case SDL_SCANCODE_MENU: return EInputCode::KEY_MENU;
            case SDL_SCANCODE_SELECT: return EInputCode::KEY_SELECT;
            case SDL_SCANCODE_STOP: return EInputCode::KEY_STOP;
            case SDL_SCANCODE_AGAIN: return EInputCode::KEY_AGAIN;
            case SDL_SCANCODE_UNDO: return EInputCode::KEY_UNDO;
            case SDL_SCANCODE_CUT: return EInputCode::KEY_CUT;
            case SDL_SCANCODE_COPY: return EInputCode::KEY_COPY;
            case SDL_SCANCODE_PASTE: return EInputCode::KEY_PASTE;
            case SDL_SCANCODE_FIND: return EInputCode::KEY_FIND;

            case SDL_SCANCODE_MUTE: return EInputCode::KEY_MUTE;
            case SDL_SCANCODE_VOLUMEUP: return EInputCode::KEY_VOLUMEUP;
            case SDL_SCANCODE_VOLUMEDOWN: return EInputCode::KEY_VOLUMEDOWN;

            case SDL_SCANCODE_KP_COMMA: return EInputCode::KEY_KP_COMMA;
            case SDL_SCANCODE_KP_EQUALSAS400: return EInputCode::KEY_KP_EQUALSAS400;

            case SDL_SCANCODE_INTERNATIONAL1: return EInputCode::KEY_INTERNATIONAL1;
            case SDL_SCANCODE_INTERNATIONAL2: return EInputCode::KEY_INTERNATIONAL2;
            case SDL_SCANCODE_INTERNATIONAL3: return EInputCode::KEY_INTERNATIONAL3;
            case SDL_SCANCODE_INTERNATIONAL4: return EInputCode::KEY_INTERNATIONAL4;
            case SDL_SCANCODE_INTERNATIONAL5: return EInputCode::KEY_INTERNATIONAL5;
            case SDL_SCANCODE_INTERNATIONAL6: return EInputCode::KEY_INTERNATIONAL6;
            case SDL_SCANCODE_INTERNATIONAL7: return EInputCode::KEY_INTERNATIONAL7;
            case SDL_SCANCODE_INTERNATIONAL8: return EInputCode::KEY_INTERNATIONAL8;
            case SDL_SCANCODE_INTERNATIONAL9: return EInputCode::KEY_INTERNATIONAL9;

            case SDL_SCANCODE_LANG1: return EInputCode::KEY_LANG1;
            case SDL_SCANCODE_LANG2: return EInputCode::KEY_LANG2;
            case SDL_SCANCODE_LANG3: return EInputCode::KEY_LANG3;
            case SDL_SCANCODE_LANG4: return EInputCode::KEY_LANG4;
            case SDL_SCANCODE_LANG5: return EInputCode::KEY_LANG5;
            case SDL_SCANCODE_LANG6: return EInputCode::KEY_LANG6;
            case SDL_SCANCODE_LANG7: return EInputCode::KEY_LANG7;
            case SDL_SCANCODE_LANG8: return EInputCode::KEY_LANG8;
            case SDL_SCANCODE_LANG9: return EInputCode::KEY_LANG9;

            case SDL_SCANCODE_ALTERASE: return EInputCode::KEY_ALTERASE;
            case SDL_SCANCODE_SYSREQ: return EInputCode::KEY_SYSREQ;
            case SDL_SCANCODE_CANCEL: return EInputCode::KEY_CANCEL;
            case SDL_SCANCODE_CLEAR: return EInputCode::KEY_CLEAR;
            case SDL_SCANCODE_PRIOR: return EInputCode::KEY_PRIOR;
            case SDL_SCANCODE_RETURN2: return EInputCode::KEY_RETURN2;
            case SDL_SCANCODE_SEPARATOR: return EInputCode::KEY_SEPARATOR;
            case SDL_SCANCODE_OUT: return EInputCode::KEY_OUT;
            case SDL_SCANCODE_OPER: return EInputCode::KEY_OPER;
            case SDL_SCANCODE_CLEARAGAIN: return EInputCode::KEY_CLEARAGAIN;
            case SDL_SCANCODE_CRSEL: return EInputCode::KEY_CRSEL;
            case SDL_SCANCODE_EXSEL: return EInputCode::KEY_EXSEL;

            case SDL_SCANCODE_KP_00: return EInputCode::KEY_KP_00;
            case SDL_SCANCODE_KP_000: return EInputCode::KEY_KP_000;
            case SDL_SCANCODE_THOUSANDSSEPARATOR: return EInputCode::KEY_THOUSANDSSEPARATOR;
            case SDL_SCANCODE_DECIMALSEPARATOR: return EInputCode::KEY_DECIMALSEPARATOR;
            case SDL_SCANCODE_CURRENCYUNIT: return EInputCode::KEY_CURRENCYUNIT;
            case SDL_SCANCODE_CURRENCYSUBUNIT: return EInputCode::KEY_CURRENCYSUBUNIT;
            case SDL_SCANCODE_KP_LEFTPAREN: return EInputCode::KEY_KP_LEFTPAREN;
            case SDL_SCANCODE_KP_RIGHTPAREN: return EInputCode::KEY_KP_RIGHTPAREN;
            case SDL_SCANCODE_KP_LEFTBRACE: return EInputCode::KEY_KP_LEFTBRACE;
            case SDL_SCANCODE_KP_RIGHTBRACE: return EInputCode::KEY_KP_RIGHTBRACE;
            case SDL_SCANCODE_KP_TAB: return EInputCode::KEY_KP_TAB;
            case SDL_SCANCODE_KP_BACKSPACE: return EInputCode::KEY_KP_BACKSPACE;

            case SDL_SCANCODE_KP_A: return EInputCode::KEY_KP_A;
            case SDL_SCANCODE_KP_B: return EInputCode::KEY_KP_B;
            case SDL_SCANCODE_KP_C: return EInputCode::KEY_KP_C;
            case SDL_SCANCODE_KP_D: return EInputCode::KEY_KP_D;
            case SDL_SCANCODE_KP_E: return EInputCode::KEY_KP_E;
            case SDL_SCANCODE_KP_F: return EInputCode::KEY_KP_F;

            case SDL_SCANCODE_KP_XOR: return EInputCode::KEY_KP_XOR;
            case SDL_SCANCODE_KP_POWER: return EInputCode::KEY_KP_POWER;
            case SDL_SCANCODE_KP_PERCENT: return EInputCode::KEY_KP_PERCENT;
            case SDL_SCANCODE_KP_LESS: return EInputCode::KEY_KP_LESS;
            case SDL_SCANCODE_KP_GREATER: return EInputCode::KEY_KP_GREATER;
            case SDL_SCANCODE_KP_AMPERSAND: return EInputCode::KEY_KP_AMPERSAND;
            case SDL_SCANCODE_KP_DBLAMPERSAND: return EInputCode::KEY_KP_DBLAMPERSAND;
            case SDL_SCANCODE_KP_VERTICALBAR: return EInputCode::KEY_KP_VERTICALBAR;
            case SDL_SCANCODE_KP_DBLVERTICALBAR: return EInputCode::KEY_KP_DBLVERTICALBAR;
            case SDL_SCANCODE_KP_COLON: return EInputCode::KEY_KP_COLON;
            case SDL_SCANCODE_KP_HASH: return EInputCode::KEY_KP_HASH;
            case SDL_SCANCODE_KP_SPACE: return EInputCode::KEY_KP_SPACE;
            case SDL_SCANCODE_KP_AT: return EInputCode::KEY_KP_AT;
            case SDL_SCANCODE_KP_EXCLAM: return EInputCode::KEY_KP_EXCLAM;

            case SDL_SCANCODE_KP_MEMSTORE: return EInputCode::KEY_KP_MEMSTORE;
            case SDL_SCANCODE_KP_MEMRECALL: return EInputCode::KEY_KP_MEMRECALL;
            case SDL_SCANCODE_KP_MEMCLEAR: return EInputCode::KEY_KP_MEMCLEAR;
            case SDL_SCANCODE_KP_MEMADD: return EInputCode::KEY_KP_MEMADD;
            case SDL_SCANCODE_KP_MEMSUBTRACT: return EInputCode::KEY_KP_MEMSUBTRACT;
            case SDL_SCANCODE_KP_MEMMULTIPLY: return EInputCode::KEY_KP_MEMMULTIPLY;
            case SDL_SCANCODE_KP_MEMDIVIDE: return EInputCode::KEY_KP_MEMDIVIDE;
            case SDL_SCANCODE_KP_PLUSMINUS: return EInputCode::KEY_KP_PLUSMINUS;
            case SDL_SCANCODE_KP_CLEAR: return EInputCode::KEY_KP_CLEAR;
            case SDL_SCANCODE_KP_CLEARENTRY: return EInputCode::KEY_KP_CLEARENTRY;
            case SDL_SCANCODE_KP_BINARY: return EInputCode::KEY_KP_BINARY;
            case SDL_SCANCODE_KP_OCTAL: return EInputCode::KEY_KP_OCTAL;
            case SDL_SCANCODE_KP_DECIMAL: return EInputCode::KEY_KP_DECIMAL;
            case SDL_SCANCODE_KP_HEXADECIMAL: return EInputCode::KEY_KP_HEXADECIMAL;

            case SDL_SCANCODE_LCTRL: return EInputCode::KEY_LCTRL;
            case SDL_SCANCODE_LSHIFT: return EInputCode::KEY_LSHIFT;
            case SDL_SCANCODE_LALT: return EInputCode::KEY_LALT;
            case SDL_SCANCODE_LGUI: return EInputCode::KEY_LGUI;
            case SDL_SCANCODE_RCTRL: return EInputCode::KEY_RCTRL;
            case SDL_SCANCODE_RSHIFT: return EInputCode::KEY_RSHIFT;
            case SDL_SCANCODE_RALT: return EInputCode::KEY_RALT;
            case SDL_SCANCODE_RGUI: return EInputCode::KEY_RGUI;

            case SDL_SCANCODE_MODE: return EInputCode::KEY_MODE;

            case SDL_SCANCODE_SLEEP: return EInputCode::KEY_SLEEP;
            case SDL_SCANCODE_WAKE: return EInputCode::KEY_WAKE;

            case SDL_SCANCODE_CHANNEL_INCREMENT: return EInputCode::KEY_CHANNEL_INCREMENT;
            case SDL_SCANCODE_CHANNEL_DECREMENT: return EInputCode::KEY_CHANNEL_DECREMENT;

            case SDL_SCANCODE_MEDIA_PLAY: return EInputCode::KEY_MEDIA_PLAY;
            case SDL_SCANCODE_MEDIA_PAUSE: return EInputCode::KEY_MEDIA_PAUSE;
            case SDL_SCANCODE_MEDIA_RECORD: return EInputCode::KEY_MEDIA_RECORD;
            case SDL_SCANCODE_MEDIA_FAST_FORWARD: return EInputCode::KEY_MEDIA_FAST_FORWARD;
            case SDL_SCANCODE_MEDIA_REWIND: return EInputCode::KEY_MEDIA_REWIND;
            case SDL_SCANCODE_MEDIA_NEXT_TRACK: return EInputCode::KEY_MEDIA_NEXT_TRACK;
            case SDL_SCANCODE_MEDIA_PREVIOUS_TRACK: return EInputCode::KEY_MEDIA_PREVIOUS_TRACK;
            case SDL_SCANCODE_MEDIA_STOP: return EInputCode::KEY_MEDIA_STOP;
            case SDL_SCANCODE_MEDIA_EJECT: return EInputCode::KEY_MEDIA_EJECT;
            case SDL_SCANCODE_MEDIA_PLAY_PAUSE: return EInputCode::KEY_MEDIA_PLAY_PAUSE;
            case SDL_SCANCODE_MEDIA_SELECT: return EInputCode::KEY_MEDIA_SELECT;

            case SDL_SCANCODE_AC_NEW: return EInputCode::KEY_AC_NEW;
            case SDL_SCANCODE_AC_OPEN: return EInputCode::KEY_AC_OPEN;
            case SDL_SCANCODE_AC_CLOSE: return EInputCode::KEY_AC_CLOSE;
            case SDL_SCANCODE_AC_EXIT: return EInputCode::KEY_AC_EXIT;
            case SDL_SCANCODE_AC_SAVE: return EInputCode::KEY_AC_SAVE;
            case SDL_SCANCODE_AC_PRINT: return EInputCode::KEY_AC_PRINT;
            case SDL_SCANCODE_AC_PROPERTIES: return EInputCode::KEY_AC_PROPERTIES;

            case SDL_SCANCODE_AC_SEARCH: return EInputCode::KEY_AC_SEARCH;
            case SDL_SCANCODE_AC_HOME: return EInputCode::KEY_AC_HOME;
            case SDL_SCANCODE_AC_BACK: return EInputCode::KEY_AC_BACK;
            case SDL_SCANCODE_AC_FORWARD: return EInputCode::KEY_AC_FORWARD;
            case SDL_SCANCODE_AC_STOP: return EInputCode::KEY_AC_STOP;
            case SDL_SCANCODE_AC_REFRESH: return EInputCode::KEY_AC_REFRESH;
            case SDL_SCANCODE_AC_BOOKMARKS: return EInputCode::KEY_AC_BOOKMARKS;

            case SDL_SCANCODE_SOFTLEFT: return EInputCode::KEY_SOFTLEFT;
            case SDL_SCANCODE_SOFTRIGHT: return EInputCode::KEY_SOFTRIGHT;
            case SDL_SCANCODE_CALL: return EInputCode::KEY_CALL;
            case SDL_SCANCODE_ENDCALL: return EInputCode::KEY_ENDCALL;

            case SDL_SCANCODE_RESERVED: return EInputCode::KEY_RESERVED;
            case SDL_SCANCODE_COUNT: return EInputCode::KEY_COUNT;

            default:
                return EInputCode::KEY_UNKNOWN;
        }
    }
}
