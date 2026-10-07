module;
#include <SDL3/SDL_scancode.h>

export module engine.platform.sdlplatform:sdlinputadapter;
import engine.platform.inputcode;
import std;

export namespace engine::platform
{
    inline EKeyCode translateSDLScancode(SDL_Scancode scancode);
    inline EMouseButton translateSDLMouseButton(Uint8 button);
}

namespace engine::platform
{
    EKeyCode translateSDLScancode(const SDL_Scancode scancode)
    {
        switch (scancode)
        {
            case SDL_SCANCODE_UNKNOWN: return EKeyCode::KEY_UNKNOWN;

            case SDL_SCANCODE_A: return EKeyCode::KEY_A;
            case SDL_SCANCODE_B: return EKeyCode::KEY_B;
            case SDL_SCANCODE_C: return EKeyCode::KEY_C;
            case SDL_SCANCODE_D: return EKeyCode::KEY_D;
            case SDL_SCANCODE_E: return EKeyCode::KEY_E;
            case SDL_SCANCODE_F: return EKeyCode::KEY_F;
            case SDL_SCANCODE_G: return EKeyCode::KEY_G;
            case SDL_SCANCODE_H: return EKeyCode::KEY_H;
            case SDL_SCANCODE_I: return EKeyCode::KEY_I;
            case SDL_SCANCODE_J: return EKeyCode::KEY_J;
            case SDL_SCANCODE_K: return EKeyCode::KEY_K;
            case SDL_SCANCODE_L: return EKeyCode::KEY_L;
            case SDL_SCANCODE_M: return EKeyCode::KEY_M;
            case SDL_SCANCODE_N: return EKeyCode::KEY_N;
            case SDL_SCANCODE_O: return EKeyCode::KEY_O;
            case SDL_SCANCODE_P: return EKeyCode::KEY_P;
            case SDL_SCANCODE_Q: return EKeyCode::KEY_Q;
            case SDL_SCANCODE_R: return EKeyCode::KEY_R;
            case SDL_SCANCODE_S: return EKeyCode::KEY_S;
            case SDL_SCANCODE_T: return EKeyCode::KEY_T;
            case SDL_SCANCODE_U: return EKeyCode::KEY_U;
            case SDL_SCANCODE_V: return EKeyCode::KEY_V;
            case SDL_SCANCODE_W: return EKeyCode::KEY_W;
            case SDL_SCANCODE_X: return EKeyCode::KEY_X;
            case SDL_SCANCODE_Y: return EKeyCode::KEY_Y;
            case SDL_SCANCODE_Z: return EKeyCode::KEY_Z;

            case SDL_SCANCODE_1: return EKeyCode::KEY_1;
            case SDL_SCANCODE_2: return EKeyCode::KEY_2;
            case SDL_SCANCODE_3: return EKeyCode::KEY_3;
            case SDL_SCANCODE_4: return EKeyCode::KEY_4;
            case SDL_SCANCODE_5: return EKeyCode::KEY_5;
            case SDL_SCANCODE_6: return EKeyCode::KEY_6;
            case SDL_SCANCODE_7: return EKeyCode::KEY_7;
            case SDL_SCANCODE_8: return EKeyCode::KEY_8;
            case SDL_SCANCODE_9: return EKeyCode::KEY_9;
            case SDL_SCANCODE_0: return EKeyCode::KEY_0;

            case SDL_SCANCODE_RETURN: return EKeyCode::KEY_RETURN;
            case SDL_SCANCODE_ESCAPE: return EKeyCode::KEY_ESCAPE;
            case SDL_SCANCODE_BACKSPACE: return EKeyCode::KEY_BACKSPACE;
            case SDL_SCANCODE_TAB: return EKeyCode::KEY_TAB;
            case SDL_SCANCODE_SPACE: return EKeyCode::KEY_SPACE;

            case SDL_SCANCODE_MINUS: return EKeyCode::KEY_MINUS;
            case SDL_SCANCODE_EQUALS: return EKeyCode::KEY_EQUALS;
            case SDL_SCANCODE_LEFTBRACKET: return EKeyCode::KEY_LEFTBRACKET;
            case SDL_SCANCODE_RIGHTBRACKET: return EKeyCode::KEY_RIGHTBRACKET;
            case SDL_SCANCODE_BACKSLASH: return EKeyCode::KEY_BACKSLASH;
            case SDL_SCANCODE_NONUSHASH: return EKeyCode::KEY_NONUSHASH;
            case SDL_SCANCODE_SEMICOLON: return EKeyCode::KEY_SEMICOLON;
            case SDL_SCANCODE_APOSTROPHE: return EKeyCode::KEY_APOSTROPHE;
            case SDL_SCANCODE_GRAVE: return EKeyCode::KEY_GRAVE;
            case SDL_SCANCODE_COMMA: return EKeyCode::KEY_COMMA;
            case SDL_SCANCODE_PERIOD: return EKeyCode::KEY_PERIOD;
            case SDL_SCANCODE_SLASH: return EKeyCode::KEY_SLASH;

            case SDL_SCANCODE_CAPSLOCK: return EKeyCode::KEY_CAPSLOCK;

            case SDL_SCANCODE_F1: return EKeyCode::KEY_F1;
            case SDL_SCANCODE_F2: return EKeyCode::KEY_F2;
            case SDL_SCANCODE_F3: return EKeyCode::KEY_F3;
            case SDL_SCANCODE_F4: return EKeyCode::KEY_F4;
            case SDL_SCANCODE_F5: return EKeyCode::KEY_F5;
            case SDL_SCANCODE_F6: return EKeyCode::KEY_F6;
            case SDL_SCANCODE_F7: return EKeyCode::KEY_F7;
            case SDL_SCANCODE_F8: return EKeyCode::KEY_F8;
            case SDL_SCANCODE_F9: return EKeyCode::KEY_F9;
            case SDL_SCANCODE_F10: return EKeyCode::KEY_F10;
            case SDL_SCANCODE_F11: return EKeyCode::KEY_F11;
            case SDL_SCANCODE_F12: return EKeyCode::KEY_F12;

            case SDL_SCANCODE_PRINTSCREEN: return EKeyCode::KEY_PRINTSCREEN;
            case SDL_SCANCODE_SCROLLLOCK: return EKeyCode::KEY_SCROLLLOCK;
            case SDL_SCANCODE_PAUSE: return EKeyCode::KEY_PAUSE;
            case SDL_SCANCODE_INSERT: return EKeyCode::KEY_INSERT;
            case SDL_SCANCODE_HOME: return EKeyCode::KEY_HOME;
            case SDL_SCANCODE_PAGEUP: return EKeyCode::KEY_PAGEUP;
            case SDL_SCANCODE_DELETE: return EKeyCode::KEY_DELETE;
            case SDL_SCANCODE_END: return EKeyCode::KEY_END;
            case SDL_SCANCODE_PAGEDOWN: return EKeyCode::KEY_PAGEDOWN;

            case SDL_SCANCODE_RIGHT: return EKeyCode::KEY_RIGHT;
            case SDL_SCANCODE_LEFT: return EKeyCode::KEY_LEFT;
            case SDL_SCANCODE_DOWN: return EKeyCode::KEY_DOWN;
            case SDL_SCANCODE_UP: return EKeyCode::KEY_UP;

            case SDL_SCANCODE_NUMLOCKCLEAR: return EKeyCode::KEY_NUMLOCKCLEAR;

            case SDL_SCANCODE_KP_DIVIDE: return EKeyCode::KEY_KP_DIVIDE;
            case SDL_SCANCODE_KP_MULTIPLY: return EKeyCode::KEY_KP_MULTIPLY;
            case SDL_SCANCODE_KP_MINUS: return EKeyCode::KEY_KP_MINUS;
            case SDL_SCANCODE_KP_PLUS: return EKeyCode::KEY_KP_PLUS;
            case SDL_SCANCODE_KP_ENTER: return EKeyCode::KEY_KP_ENTER;

            case SDL_SCANCODE_KP_1: return EKeyCode::KEY_KP_1;
            case SDL_SCANCODE_KP_2: return EKeyCode::KEY_KP_2;
            case SDL_SCANCODE_KP_3: return EKeyCode::KEY_KP_3;
            case SDL_SCANCODE_KP_4: return EKeyCode::KEY_KP_4;
            case SDL_SCANCODE_KP_5: return EKeyCode::KEY_KP_5;
            case SDL_SCANCODE_KP_6: return EKeyCode::KEY_KP_6;
            case SDL_SCANCODE_KP_7: return EKeyCode::KEY_KP_7;
            case SDL_SCANCODE_KP_8: return EKeyCode::KEY_KP_8;
            case SDL_SCANCODE_KP_9: return EKeyCode::KEY_KP_9;
            case SDL_SCANCODE_KP_0: return EKeyCode::KEY_KP_0;

            case SDL_SCANCODE_KP_PERIOD: return EKeyCode::KEY_KP_PERIOD;

            case SDL_SCANCODE_NONUSBACKSLASH: return EKeyCode::KEY_NONUSBACKSLASH;
            case SDL_SCANCODE_APPLICATION: return EKeyCode::KEY_APPLICATION;
            case SDL_SCANCODE_POWER: return EKeyCode::KEY_POWER;
            case SDL_SCANCODE_KP_EQUALS: return EKeyCode::KEY_KP_EQUALS;

            case SDL_SCANCODE_F13: return EKeyCode::KEY_F13;
            case SDL_SCANCODE_F14: return EKeyCode::KEY_F14;
            case SDL_SCANCODE_F15: return EKeyCode::KEY_F15;
            case SDL_SCANCODE_F16: return EKeyCode::KEY_F16;
            case SDL_SCANCODE_F17: return EKeyCode::KEY_F17;
            case SDL_SCANCODE_F18: return EKeyCode::KEY_F18;
            case SDL_SCANCODE_F19: return EKeyCode::KEY_F19;
            case SDL_SCANCODE_F20: return EKeyCode::KEY_F20;
            case SDL_SCANCODE_F21: return EKeyCode::KEY_F21;
            case SDL_SCANCODE_F22: return EKeyCode::KEY_F22;
            case SDL_SCANCODE_F23: return EKeyCode::KEY_F23;
            case SDL_SCANCODE_F24: return EKeyCode::KEY_F24;

            case SDL_SCANCODE_EXECUTE: return EKeyCode::KEY_EXECUTE;
            case SDL_SCANCODE_HELP: return EKeyCode::KEY_HELP;
            case SDL_SCANCODE_MENU: return EKeyCode::KEY_MENU;
            case SDL_SCANCODE_SELECT: return EKeyCode::KEY_SELECT;
            case SDL_SCANCODE_STOP: return EKeyCode::KEY_STOP;
            case SDL_SCANCODE_AGAIN: return EKeyCode::KEY_AGAIN;
            case SDL_SCANCODE_UNDO: return EKeyCode::KEY_UNDO;
            case SDL_SCANCODE_CUT: return EKeyCode::KEY_CUT;
            case SDL_SCANCODE_COPY: return EKeyCode::KEY_COPY;
            case SDL_SCANCODE_PASTE: return EKeyCode::KEY_PASTE;
            case SDL_SCANCODE_FIND: return EKeyCode::KEY_FIND;

            case SDL_SCANCODE_MUTE: return EKeyCode::KEY_MUTE;
            case SDL_SCANCODE_VOLUMEUP: return EKeyCode::KEY_VOLUMEUP;
            case SDL_SCANCODE_VOLUMEDOWN: return EKeyCode::KEY_VOLUMEDOWN;

            case SDL_SCANCODE_KP_COMMA: return EKeyCode::KEY_KP_COMMA;
            case SDL_SCANCODE_KP_EQUALSAS400: return EKeyCode::KEY_KP_EQUALSAS400;

            case SDL_SCANCODE_INTERNATIONAL1: return EKeyCode::KEY_INTERNATIONAL1;
            case SDL_SCANCODE_INTERNATIONAL2: return EKeyCode::KEY_INTERNATIONAL2;
            case SDL_SCANCODE_INTERNATIONAL3: return EKeyCode::KEY_INTERNATIONAL3;
            case SDL_SCANCODE_INTERNATIONAL4: return EKeyCode::KEY_INTERNATIONAL4;
            case SDL_SCANCODE_INTERNATIONAL5: return EKeyCode::KEY_INTERNATIONAL5;
            case SDL_SCANCODE_INTERNATIONAL6: return EKeyCode::KEY_INTERNATIONAL6;
            case SDL_SCANCODE_INTERNATIONAL7: return EKeyCode::KEY_INTERNATIONAL7;
            case SDL_SCANCODE_INTERNATIONAL8: return EKeyCode::KEY_INTERNATIONAL8;
            case SDL_SCANCODE_INTERNATIONAL9: return EKeyCode::KEY_INTERNATIONAL9;

            case SDL_SCANCODE_LANG1: return EKeyCode::KEY_LANG1;
            case SDL_SCANCODE_LANG2: return EKeyCode::KEY_LANG2;
            case SDL_SCANCODE_LANG3: return EKeyCode::KEY_LANG3;
            case SDL_SCANCODE_LANG4: return EKeyCode::KEY_LANG4;
            case SDL_SCANCODE_LANG5: return EKeyCode::KEY_LANG5;
            case SDL_SCANCODE_LANG6: return EKeyCode::KEY_LANG6;
            case SDL_SCANCODE_LANG7: return EKeyCode::KEY_LANG7;
            case SDL_SCANCODE_LANG8: return EKeyCode::KEY_LANG8;
            case SDL_SCANCODE_LANG9: return EKeyCode::KEY_LANG9;

            case SDL_SCANCODE_ALTERASE: return EKeyCode::KEY_ALTERASE;
            case SDL_SCANCODE_SYSREQ: return EKeyCode::KEY_SYSREQ;
            case SDL_SCANCODE_CANCEL: return EKeyCode::KEY_CANCEL;
            case SDL_SCANCODE_CLEAR: return EKeyCode::KEY_CLEAR;
            case SDL_SCANCODE_PRIOR: return EKeyCode::KEY_PRIOR;
            case SDL_SCANCODE_RETURN2: return EKeyCode::KEY_RETURN2;
            case SDL_SCANCODE_SEPARATOR: return EKeyCode::KEY_SEPARATOR;
            case SDL_SCANCODE_OUT: return EKeyCode::KEY_OUT;
            case SDL_SCANCODE_OPER: return EKeyCode::KEY_OPER;
            case SDL_SCANCODE_CLEARAGAIN: return EKeyCode::KEY_CLEARAGAIN;
            case SDL_SCANCODE_CRSEL: return EKeyCode::KEY_CRSEL;
            case SDL_SCANCODE_EXSEL: return EKeyCode::KEY_EXSEL;

            case SDL_SCANCODE_KP_00: return EKeyCode::KEY_KP_00;
            case SDL_SCANCODE_KP_000: return EKeyCode::KEY_KP_000;
            case SDL_SCANCODE_THOUSANDSSEPARATOR: return EKeyCode::KEY_THOUSANDSSEPARATOR;
            case SDL_SCANCODE_DECIMALSEPARATOR: return EKeyCode::KEY_DECIMALSEPARATOR;
            case SDL_SCANCODE_CURRENCYUNIT: return EKeyCode::KEY_CURRENCYUNIT;
            case SDL_SCANCODE_CURRENCYSUBUNIT: return EKeyCode::KEY_CURRENCYSUBUNIT;
            case SDL_SCANCODE_KP_LEFTPAREN: return EKeyCode::KEY_KP_LEFTPAREN;
            case SDL_SCANCODE_KP_RIGHTPAREN: return EKeyCode::KEY_KP_RIGHTPAREN;
            case SDL_SCANCODE_KP_LEFTBRACE: return EKeyCode::KEY_KP_LEFTBRACE;
            case SDL_SCANCODE_KP_RIGHTBRACE: return EKeyCode::KEY_KP_RIGHTBRACE;
            case SDL_SCANCODE_KP_TAB: return EKeyCode::KEY_KP_TAB;
            case SDL_SCANCODE_KP_BACKSPACE: return EKeyCode::KEY_KP_BACKSPACE;

            case SDL_SCANCODE_KP_A: return EKeyCode::KEY_KP_A;
            case SDL_SCANCODE_KP_B: return EKeyCode::KEY_KP_B;
            case SDL_SCANCODE_KP_C: return EKeyCode::KEY_KP_C;
            case SDL_SCANCODE_KP_D: return EKeyCode::KEY_KP_D;
            case SDL_SCANCODE_KP_E: return EKeyCode::KEY_KP_E;
            case SDL_SCANCODE_KP_F: return EKeyCode::KEY_KP_F;

            case SDL_SCANCODE_KP_XOR: return EKeyCode::KEY_KP_XOR;
            case SDL_SCANCODE_KP_POWER: return EKeyCode::KEY_KP_POWER;
            case SDL_SCANCODE_KP_PERCENT: return EKeyCode::KEY_KP_PERCENT;
            case SDL_SCANCODE_KP_LESS: return EKeyCode::KEY_KP_LESS;
            case SDL_SCANCODE_KP_GREATER: return EKeyCode::KEY_KP_GREATER;
            case SDL_SCANCODE_KP_AMPERSAND: return EKeyCode::KEY_KP_AMPERSAND;
            case SDL_SCANCODE_KP_DBLAMPERSAND: return EKeyCode::KEY_KP_DBLAMPERSAND;
            case SDL_SCANCODE_KP_VERTICALBAR: return EKeyCode::KEY_KP_VERTICALBAR;
            case SDL_SCANCODE_KP_DBLVERTICALBAR: return EKeyCode::KEY_KP_DBLVERTICALBAR;
            case SDL_SCANCODE_KP_COLON: return EKeyCode::KEY_KP_COLON;
            case SDL_SCANCODE_KP_HASH: return EKeyCode::KEY_KP_HASH;
            case SDL_SCANCODE_KP_SPACE: return EKeyCode::KEY_KP_SPACE;
            case SDL_SCANCODE_KP_AT: return EKeyCode::KEY_KP_AT;
            case SDL_SCANCODE_KP_EXCLAM: return EKeyCode::KEY_KP_EXCLAM;

            case SDL_SCANCODE_KP_MEMSTORE: return EKeyCode::KEY_KP_MEMSTORE;
            case SDL_SCANCODE_KP_MEMRECALL: return EKeyCode::KEY_KP_MEMRECALL;
            case SDL_SCANCODE_KP_MEMCLEAR: return EKeyCode::KEY_KP_MEMCLEAR;
            case SDL_SCANCODE_KP_MEMADD: return EKeyCode::KEY_KP_MEMADD;
            case SDL_SCANCODE_KP_MEMSUBTRACT: return EKeyCode::KEY_KP_MEMSUBTRACT;
            case SDL_SCANCODE_KP_MEMMULTIPLY: return EKeyCode::KEY_KP_MEMMULTIPLY;
            case SDL_SCANCODE_KP_MEMDIVIDE: return EKeyCode::KEY_KP_MEMDIVIDE;
            case SDL_SCANCODE_KP_PLUSMINUS: return EKeyCode::KEY_KP_PLUSMINUS;
            case SDL_SCANCODE_KP_CLEAR: return EKeyCode::KEY_KP_CLEAR;
            case SDL_SCANCODE_KP_CLEARENTRY: return EKeyCode::KEY_KP_CLEARENTRY;
            case SDL_SCANCODE_KP_BINARY: return EKeyCode::KEY_KP_BINARY;
            case SDL_SCANCODE_KP_OCTAL: return EKeyCode::KEY_KP_OCTAL;
            case SDL_SCANCODE_KP_DECIMAL: return EKeyCode::KEY_KP_DECIMAL;
            case SDL_SCANCODE_KP_HEXADECIMAL: return EKeyCode::KEY_KP_HEXADECIMAL;

            case SDL_SCANCODE_LCTRL: return EKeyCode::KEY_LCTRL;
            case SDL_SCANCODE_LSHIFT: return EKeyCode::KEY_LSHIFT;
            case SDL_SCANCODE_LALT: return EKeyCode::KEY_LALT;
            case SDL_SCANCODE_LGUI: return EKeyCode::KEY_LGUI;
            case SDL_SCANCODE_RCTRL: return EKeyCode::KEY_RCTRL;
            case SDL_SCANCODE_RSHIFT: return EKeyCode::KEY_RSHIFT;
            case SDL_SCANCODE_RALT: return EKeyCode::KEY_RALT;
            case SDL_SCANCODE_RGUI: return EKeyCode::KEY_RGUI;

            case SDL_SCANCODE_MODE: return EKeyCode::KEY_MODE;

            case SDL_SCANCODE_SLEEP: return EKeyCode::KEY_SLEEP;
            case SDL_SCANCODE_WAKE: return EKeyCode::KEY_WAKE;

            case SDL_SCANCODE_CHANNEL_INCREMENT: return EKeyCode::KEY_CHANNEL_INCREMENT;
            case SDL_SCANCODE_CHANNEL_DECREMENT: return EKeyCode::KEY_CHANNEL_DECREMENT;

            case SDL_SCANCODE_MEDIA_PLAY: return EKeyCode::KEY_MEDIA_PLAY;
            case SDL_SCANCODE_MEDIA_PAUSE: return EKeyCode::KEY_MEDIA_PAUSE;
            case SDL_SCANCODE_MEDIA_RECORD: return EKeyCode::KEY_MEDIA_RECORD;
            case SDL_SCANCODE_MEDIA_FAST_FORWARD: return EKeyCode::KEY_MEDIA_FAST_FORWARD;
            case SDL_SCANCODE_MEDIA_REWIND: return EKeyCode::KEY_MEDIA_REWIND;
            case SDL_SCANCODE_MEDIA_NEXT_TRACK: return EKeyCode::KEY_MEDIA_NEXT_TRACK;
            case SDL_SCANCODE_MEDIA_PREVIOUS_TRACK: return EKeyCode::KEY_MEDIA_PREVIOUS_TRACK;
            case SDL_SCANCODE_MEDIA_STOP: return EKeyCode::KEY_MEDIA_STOP;
            case SDL_SCANCODE_MEDIA_EJECT: return EKeyCode::KEY_MEDIA_EJECT;
            case SDL_SCANCODE_MEDIA_PLAY_PAUSE: return EKeyCode::KEY_MEDIA_PLAY_PAUSE;
            case SDL_SCANCODE_MEDIA_SELECT: return EKeyCode::KEY_MEDIA_SELECT;

            case SDL_SCANCODE_AC_NEW: return EKeyCode::KEY_AC_NEW;
            case SDL_SCANCODE_AC_OPEN: return EKeyCode::KEY_AC_OPEN;
            case SDL_SCANCODE_AC_CLOSE: return EKeyCode::KEY_AC_CLOSE;
            case SDL_SCANCODE_AC_EXIT: return EKeyCode::KEY_AC_EXIT;
            case SDL_SCANCODE_AC_SAVE: return EKeyCode::KEY_AC_SAVE;
            case SDL_SCANCODE_AC_PRINT: return EKeyCode::KEY_AC_PRINT;
            case SDL_SCANCODE_AC_PROPERTIES: return EKeyCode::KEY_AC_PROPERTIES;

            case SDL_SCANCODE_AC_SEARCH: return EKeyCode::KEY_AC_SEARCH;
            case SDL_SCANCODE_AC_HOME: return EKeyCode::KEY_AC_HOME;
            case SDL_SCANCODE_AC_BACK: return EKeyCode::KEY_AC_BACK;
            case SDL_SCANCODE_AC_FORWARD: return EKeyCode::KEY_AC_FORWARD;
            case SDL_SCANCODE_AC_STOP: return EKeyCode::KEY_AC_STOP;
            case SDL_SCANCODE_AC_REFRESH: return EKeyCode::KEY_AC_REFRESH;
            case SDL_SCANCODE_AC_BOOKMARKS: return EKeyCode::KEY_AC_BOOKMARKS;

            case SDL_SCANCODE_SOFTLEFT: return EKeyCode::KEY_SOFTLEFT;
            case SDL_SCANCODE_SOFTRIGHT: return EKeyCode::KEY_SOFTRIGHT;
            case SDL_SCANCODE_CALL: return EKeyCode::KEY_CALL;
            case SDL_SCANCODE_ENDCALL: return EKeyCode::KEY_ENDCALL;

            case SDL_SCANCODE_RESERVED: return EKeyCode::KEY_RESERVED;
            case SDL_SCANCODE_COUNT: return EKeyCode::KEY_COUNT;

            default:
                return EKeyCode::KEY_UNKNOWN;
        }
    }

    EMouseButton translateSDLMouseButton(const Uint8 button)
    {
        switch(button)
        {
            case 1 : return EMouseButton::MOUSE_LEFT;
            case 2 : return EMouseButton::MOUSE_MIDDLE;
            case 3 : return EMouseButton::MOUSE_RIGHT;
            case 4 : return EMouseButton::MOUSE_EXTRA1;
            case 5 : return EMouseButton::MOUSE_EXTRA2;
            default: std::unreachable();
        }
    }
}
