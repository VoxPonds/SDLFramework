module;
#include "SDL3/SDL_scancode.h"

export module engine.platform.inputcode;
import std;

export namespace engine::platform
{
    enum class EInputCode : std::uint32_t
    {
        KEY_UNKNOWN,

        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,

        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,

        KEY_RETURN,
        KEY_ESCAPE,
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_SPACE,

        KEY_MINUS,
        KEY_EQUALS,
        KEY_LEFTBRACKET,
        KEY_RIGHTBRACKET,
        KEY_BACKSLASH,
        KEY_NONUSHASH,
        KEY_SEMICOLON,
        KEY_APOSTROPHE,
        KEY_GRAVE,
        KEY_COMMA,
        KEY_PERIOD,
        KEY_SLASH,

        KEY_CAPSLOCK,

        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,

        KEY_PRINTSCREEN,
        KEY_SCROLLLOCK,
        KEY_PAUSE,
        KEY_INSERT,
        KEY_HOME,
        KEY_PAGEUP,
        KEY_DELETE,
        KEY_END,
        KEY_PAGEDOWN,

        KEY_RIGHT,
        KEY_LEFT,
        KEY_DOWN,
        KEY_UP,

        KEY_NUMLOCKCLEAR,

        KEY_KP_DIVIDE,
        KEY_KP_MULTIPLY,
        KEY_KP_MINUS,
        KEY_KP_PLUS,
        KEY_KP_ENTER,

        KEY_KP_1,
        KEY_KP_2,
        KEY_KP_3,
        KEY_KP_4,
        KEY_KP_5,
        KEY_KP_6,
        KEY_KP_7,
        KEY_KP_8,
        KEY_KP_9,
        KEY_KP_0,

        KEY_KP_PERIOD,

        KEY_NONUSBACKSLASH,
        KEY_APPLICATION,
        KEY_POWER,
        KEY_KP_EQUALS,

        KEY_F13,
        KEY_F14,
        KEY_F15,
        KEY_F16,
        KEY_F17,
        KEY_F18,
        KEY_F19,
        KEY_F20,
        KEY_F21,
        KEY_F22,
        KEY_F23,
        KEY_F24,

        KEY_EXECUTE,
        KEY_HELP,
        KEY_MENU,
        KEY_SELECT,
        KEY_STOP,
        KEY_AGAIN,
        KEY_UNDO,
        KEY_CUT,
        KEY_COPY,
        KEY_PASTE,
        KEY_FIND,

        KEY_MUTE,
        KEY_VOLUMEUP,
        KEY_VOLUMEDOWN,

        KEY_KP_COMMA,
        KEY_KP_EQUALSAS400,

        KEY_INTERNATIONAL1,
        KEY_INTERNATIONAL2,
        KEY_INTERNATIONAL3,
        KEY_INTERNATIONAL4,
        KEY_INTERNATIONAL5,
        KEY_INTERNATIONAL6,
        KEY_INTERNATIONAL7,
        KEY_INTERNATIONAL8,
        KEY_INTERNATIONAL9,

        KEY_LANG1,
        KEY_LANG2,
        KEY_LANG3,
        KEY_LANG4,
        KEY_LANG5,
        KEY_LANG6,
        KEY_LANG7,
        KEY_LANG8,
        KEY_LANG9,

        KEY_ALTERASE,
        KEY_SYSREQ,
        KEY_CANCEL,
        KEY_CLEAR,
        KEY_PRIOR,
        KEY_RETURN2,
        KEY_SEPARATOR,
        KEY_OUT,
        KEY_OPER,
        KEY_CLEARAGAIN,
        KEY_CRSEL,
        KEY_EXSEL,

        KEY_KP_00,
        KEY_KP_000,
        KEY_THOUSANDSSEPARATOR,
        KEY_DECIMALSEPARATOR,
        KEY_CURRENCYUNIT,
        KEY_CURRENCYSUBUNIT,
        KEY_KP_LEFTPAREN,
        KEY_KP_RIGHTPAREN,
        KEY_KP_LEFTBRACE,
        KEY_KP_RIGHTBRACE,
        KEY_KP_TAB,
        KEY_KP_BACKSPACE,

        KEY_KP_A,
        KEY_KP_B,
        KEY_KP_C,
        KEY_KP_D,
        KEY_KP_E,
        KEY_KP_F,

        KEY_KP_XOR,
        KEY_KP_POWER,
        KEY_KP_PERCENT,
        KEY_KP_LESS,
        KEY_KP_GREATER,
        KEY_KP_AMPERSAND,
        KEY_KP_DBLAMPERSAND,
        KEY_KP_VERTICALBAR,
        KEY_KP_DBLVERTICALBAR,
        KEY_KP_COLON,
        KEY_KP_HASH,
        KEY_KP_SPACE,
        KEY_KP_AT,
        KEY_KP_EXCLAM,

        KEY_KP_MEMSTORE,
        KEY_KP_MEMRECALL,
        KEY_KP_MEMCLEAR,
        KEY_KP_MEMADD,
        KEY_KP_MEMSUBTRACT,
        KEY_KP_MEMMULTIPLY,
        KEY_KP_MEMDIVIDE,
        KEY_KP_PLUSMINUS,
        KEY_KP_CLEAR,
        KEY_KP_CLEARENTRY,
        KEY_KP_BINARY,
        KEY_KP_OCTAL,
        KEY_KP_DECIMAL,
        KEY_KP_HEXADECIMAL,

        KEY_LCTRL,
        KEY_LSHIFT,
        KEY_LALT,
        KEY_LGUI,
        KEY_RCTRL,
        KEY_RSHIFT,
        KEY_RALT,
        KEY_RGUI,

        KEY_MODE,

        KEY_SLEEP,
        KEY_WAKE,

        KEY_CHANNEL_INCREMENT,
        KEY_CHANNEL_DECREMENT,

        KEY_MEDIA_PLAY,
        KEY_MEDIA_PAUSE,
        KEY_MEDIA_RECORD,
        KEY_MEDIA_FAST_FORWARD,
        KEY_MEDIA_REWIND,
        KEY_MEDIA_NEXT_TRACK,
        KEY_MEDIA_PREVIOUS_TRACK,
        KEY_MEDIA_STOP,
        KEY_MEDIA_EJECT,
        KEY_MEDIA_PLAY_PAUSE,
        KEY_MEDIA_SELECT,

        KEY_AC_NEW,
        KEY_AC_OPEN,
        KEY_AC_CLOSE,
        KEY_AC_EXIT,
        KEY_AC_SAVE,
        KEY_AC_PRINT,
        KEY_AC_PROPERTIES,

        KEY_AC_SEARCH,
        KEY_AC_HOME,
        KEY_AC_BACK,
        KEY_AC_FORWARD,
        KEY_AC_STOP,
        KEY_AC_REFRESH,
        KEY_AC_BOOKMARKS,


        KEY_SOFTLEFT,
        KEY_SOFTRIGHT,
        KEY_CALL,
        KEY_ENDCALL,

        KEY_RESERVED,

        KEY_COUNT,
    };

    inline SDL_Scancode translateInputCode(EInputCode inputCode);
}

namespace engine::platform
{
    SDL_Scancode translateInputCode(const EInputCode inputCode)
    {
        switch (inputCode)
        {
            case EInputCode::KEY_UNKNOWN: return SDL_SCANCODE_UNKNOWN;

            case EInputCode::KEY_A: return SDL_SCANCODE_A;
            case EInputCode::KEY_B: return SDL_SCANCODE_B;
            case EInputCode::KEY_C: return SDL_SCANCODE_C;
            case EInputCode::KEY_D: return SDL_SCANCODE_D;
            case EInputCode::KEY_E: return SDL_SCANCODE_E;
            case EInputCode::KEY_F: return SDL_SCANCODE_F;
            case EInputCode::KEY_G: return SDL_SCANCODE_G;
            case EInputCode::KEY_H: return SDL_SCANCODE_H;
            case EInputCode::KEY_I: return SDL_SCANCODE_I;
            case EInputCode::KEY_J: return SDL_SCANCODE_J;
            case EInputCode::KEY_K: return SDL_SCANCODE_K;
            case EInputCode::KEY_L: return SDL_SCANCODE_L;
            case EInputCode::KEY_M: return SDL_SCANCODE_M;
            case EInputCode::KEY_N: return SDL_SCANCODE_N;
            case EInputCode::KEY_O: return SDL_SCANCODE_O;
            case EInputCode::KEY_P: return SDL_SCANCODE_P;
            case EInputCode::KEY_Q: return SDL_SCANCODE_Q;
            case EInputCode::KEY_R: return SDL_SCANCODE_R;
            case EInputCode::KEY_S: return SDL_SCANCODE_S;
            case EInputCode::KEY_T: return SDL_SCANCODE_T;
            case EInputCode::KEY_U: return SDL_SCANCODE_U;
            case EInputCode::KEY_V: return SDL_SCANCODE_V;
            case EInputCode::KEY_W: return SDL_SCANCODE_W;
            case EInputCode::KEY_X: return SDL_SCANCODE_X;
            case EInputCode::KEY_Y: return SDL_SCANCODE_Y;
            case EInputCode::KEY_Z: return SDL_SCANCODE_Z;

            case EInputCode::KEY_1: return SDL_SCANCODE_1;
            case EInputCode::KEY_2: return SDL_SCANCODE_2;
            case EInputCode::KEY_3: return SDL_SCANCODE_3;
            case EInputCode::KEY_4: return SDL_SCANCODE_4;
            case EInputCode::KEY_5: return SDL_SCANCODE_5;
            case EInputCode::KEY_6: return SDL_SCANCODE_6;
            case EInputCode::KEY_7: return SDL_SCANCODE_7;
            case EInputCode::KEY_8: return SDL_SCANCODE_8;
            case EInputCode::KEY_9: return SDL_SCANCODE_9;
            case EInputCode::KEY_0: return SDL_SCANCODE_0;

            case EInputCode::KEY_RETURN: return SDL_SCANCODE_RETURN;
            case EInputCode::KEY_ESCAPE: return SDL_SCANCODE_ESCAPE;
            case EInputCode::KEY_BACKSPACE: return SDL_SCANCODE_BACKSPACE;
            case EInputCode::KEY_TAB: return SDL_SCANCODE_TAB;
            case EInputCode::KEY_SPACE: return SDL_SCANCODE_SPACE;

            case EInputCode::KEY_MINUS: return SDL_SCANCODE_MINUS;
            case EInputCode::KEY_EQUALS: return SDL_SCANCODE_EQUALS;
            case EInputCode::KEY_LEFTBRACKET: return SDL_SCANCODE_LEFTBRACKET;
            case EInputCode::KEY_RIGHTBRACKET: return SDL_SCANCODE_RIGHTBRACKET;
            case EInputCode::KEY_BACKSLASH: return SDL_SCANCODE_BACKSLASH;
            case EInputCode::KEY_NONUSHASH: return SDL_SCANCODE_NONUSHASH;
            case EInputCode::KEY_SEMICOLON: return SDL_SCANCODE_SEMICOLON;
            case EInputCode::KEY_APOSTROPHE: return SDL_SCANCODE_APOSTROPHE;
            case EInputCode::KEY_GRAVE: return SDL_SCANCODE_GRAVE;
            case EInputCode::KEY_COMMA: return SDL_SCANCODE_COMMA;
            case EInputCode::KEY_PERIOD: return SDL_SCANCODE_PERIOD;
            case EInputCode::KEY_SLASH: return SDL_SCANCODE_SLASH;

            case EInputCode::KEY_CAPSLOCK: return SDL_SCANCODE_CAPSLOCK;

            case EInputCode::KEY_F1: return SDL_SCANCODE_F1;
            case EInputCode::KEY_F2: return SDL_SCANCODE_F2;
            case EInputCode::KEY_F3: return SDL_SCANCODE_F3;
            case EInputCode::KEY_F4: return SDL_SCANCODE_F4;
            case EInputCode::KEY_F5: return SDL_SCANCODE_F5;
            case EInputCode::KEY_F6: return SDL_SCANCODE_F6;
            case EInputCode::KEY_F7: return SDL_SCANCODE_F7;
            case EInputCode::KEY_F8: return SDL_SCANCODE_F8;
            case EInputCode::KEY_F9: return SDL_SCANCODE_F9;
            case EInputCode::KEY_F10: return SDL_SCANCODE_F10;
            case EInputCode::KEY_F11: return SDL_SCANCODE_F11;
            case EInputCode::KEY_F12: return SDL_SCANCODE_F12;

            case EInputCode::KEY_PRINTSCREEN: return SDL_SCANCODE_PRINTSCREEN;
            case EInputCode::KEY_SCROLLLOCK: return SDL_SCANCODE_SCROLLLOCK;
            case EInputCode::KEY_PAUSE: return SDL_SCANCODE_PAUSE;
            case EInputCode::KEY_INSERT: return SDL_SCANCODE_INSERT;
            case EInputCode::KEY_HOME: return SDL_SCANCODE_HOME;
            case EInputCode::KEY_PAGEUP: return SDL_SCANCODE_PAGEUP;
            case EInputCode::KEY_DELETE: return SDL_SCANCODE_DELETE;
            case EInputCode::KEY_END: return SDL_SCANCODE_END;
            case EInputCode::KEY_PAGEDOWN: return SDL_SCANCODE_PAGEDOWN;

            case EInputCode::KEY_RIGHT: return SDL_SCANCODE_RIGHT;
            case EInputCode::KEY_LEFT: return SDL_SCANCODE_LEFT;
            case EInputCode::KEY_DOWN: return SDL_SCANCODE_DOWN;
            case EInputCode::KEY_UP: return SDL_SCANCODE_UP;

            case EInputCode::KEY_NUMLOCKCLEAR: return SDL_SCANCODE_NUMLOCKCLEAR;

            case EInputCode::KEY_KP_DIVIDE: return SDL_SCANCODE_KP_DIVIDE;
            case EInputCode::KEY_KP_MULTIPLY: return SDL_SCANCODE_KP_MULTIPLY;
            case EInputCode::KEY_KP_MINUS: return SDL_SCANCODE_KP_MINUS;
            case EInputCode::KEY_KP_PLUS: return SDL_SCANCODE_KP_PLUS;
            case EInputCode::KEY_KP_ENTER: return SDL_SCANCODE_KP_ENTER;

            case EInputCode::KEY_KP_1: return SDL_SCANCODE_KP_1;
            case EInputCode::KEY_KP_2: return SDL_SCANCODE_KP_2;
            case EInputCode::KEY_KP_3: return SDL_SCANCODE_KP_3;
            case EInputCode::KEY_KP_4: return SDL_SCANCODE_KP_4;
            case EInputCode::KEY_KP_5: return SDL_SCANCODE_KP_5;
            case EInputCode::KEY_KP_6: return SDL_SCANCODE_KP_6;
            case EInputCode::KEY_KP_7: return SDL_SCANCODE_KP_7;
            case EInputCode::KEY_KP_8: return SDL_SCANCODE_KP_8;
            case EInputCode::KEY_KP_9: return SDL_SCANCODE_KP_9;
            case EInputCode::KEY_KP_0: return SDL_SCANCODE_KP_0;

            case EInputCode::KEY_KP_PERIOD: return SDL_SCANCODE_KP_PERIOD;

            case EInputCode::KEY_NONUSBACKSLASH: return SDL_SCANCODE_NONUSBACKSLASH;
            case EInputCode::KEY_APPLICATION: return SDL_SCANCODE_APPLICATION;
            case EInputCode::KEY_POWER: return SDL_SCANCODE_POWER;
            case EInputCode::KEY_KP_EQUALS: return SDL_SCANCODE_KP_EQUALS;

            case EInputCode::KEY_F13: return SDL_SCANCODE_F13;
            case EInputCode::KEY_F14: return SDL_SCANCODE_F14;
            case EInputCode::KEY_F15: return SDL_SCANCODE_F15;
            case EInputCode::KEY_F16: return SDL_SCANCODE_F16;
            case EInputCode::KEY_F17: return SDL_SCANCODE_F17;
            case EInputCode::KEY_F18: return SDL_SCANCODE_F18;
            case EInputCode::KEY_F19: return SDL_SCANCODE_F19;
            case EInputCode::KEY_F20: return SDL_SCANCODE_F20;
            case EInputCode::KEY_F21: return SDL_SCANCODE_F21;
            case EInputCode::KEY_F22: return SDL_SCANCODE_F22;
            case EInputCode::KEY_F23: return SDL_SCANCODE_F23;
            case EInputCode::KEY_F24: return SDL_SCANCODE_F24;

            case EInputCode::KEY_EXECUTE: return SDL_SCANCODE_EXECUTE;
            case EInputCode::KEY_HELP: return SDL_SCANCODE_HELP;
            case EInputCode::KEY_MENU: return SDL_SCANCODE_MENU;
            case EInputCode::KEY_SELECT: return SDL_SCANCODE_SELECT;
            case EInputCode::KEY_STOP: return SDL_SCANCODE_STOP;
            case EInputCode::KEY_AGAIN: return SDL_SCANCODE_AGAIN;
            case EInputCode::KEY_UNDO: return SDL_SCANCODE_UNDO;
            case EInputCode::KEY_CUT: return SDL_SCANCODE_CUT;
            case EInputCode::KEY_COPY: return SDL_SCANCODE_COPY;
            case EInputCode::KEY_PASTE: return SDL_SCANCODE_PASTE;
            case EInputCode::KEY_FIND: return SDL_SCANCODE_FIND;

            case EInputCode::KEY_MUTE: return SDL_SCANCODE_MUTE;
            case EInputCode::KEY_VOLUMEUP: return SDL_SCANCODE_VOLUMEUP;
            case EInputCode::KEY_VOLUMEDOWN: return SDL_SCANCODE_VOLUMEDOWN;

            case EInputCode::KEY_KP_COMMA: return SDL_SCANCODE_KP_COMMA;
            case EInputCode::KEY_KP_EQUALSAS400: return SDL_SCANCODE_KP_EQUALSAS400;

            case EInputCode::KEY_INTERNATIONAL1: return SDL_SCANCODE_INTERNATIONAL1;
            case EInputCode::KEY_INTERNATIONAL2: return SDL_SCANCODE_INTERNATIONAL2;
            case EInputCode::KEY_INTERNATIONAL3: return SDL_SCANCODE_INTERNATIONAL3;
            case EInputCode::KEY_INTERNATIONAL4: return SDL_SCANCODE_INTERNATIONAL4;
            case EInputCode::KEY_INTERNATIONAL5: return SDL_SCANCODE_INTERNATIONAL5;
            case EInputCode::KEY_INTERNATIONAL6: return SDL_SCANCODE_INTERNATIONAL6;
            case EInputCode::KEY_INTERNATIONAL7: return SDL_SCANCODE_INTERNATIONAL7;
            case EInputCode::KEY_INTERNATIONAL8: return SDL_SCANCODE_INTERNATIONAL8;
            case EInputCode::KEY_INTERNATIONAL9: return SDL_SCANCODE_INTERNATIONAL9;

            case EInputCode::KEY_LANG1: return SDL_SCANCODE_LANG1;
            case EInputCode::KEY_LANG2: return SDL_SCANCODE_LANG2;
            case EInputCode::KEY_LANG3: return SDL_SCANCODE_LANG3;
            case EInputCode::KEY_LANG4: return SDL_SCANCODE_LANG4;
            case EInputCode::KEY_LANG5: return SDL_SCANCODE_LANG5;
            case EInputCode::KEY_LANG6: return SDL_SCANCODE_LANG6;
            case EInputCode::KEY_LANG7: return SDL_SCANCODE_LANG7;
            case EInputCode::KEY_LANG8: return SDL_SCANCODE_LANG8;
            case EInputCode::KEY_LANG9: return SDL_SCANCODE_LANG9;

            case EInputCode::KEY_ALTERASE: return SDL_SCANCODE_ALTERASE;
            case EInputCode::KEY_SYSREQ: return SDL_SCANCODE_SYSREQ;
            case EInputCode::KEY_CANCEL: return SDL_SCANCODE_CANCEL;
            case EInputCode::KEY_CLEAR: return SDL_SCANCODE_CLEAR;
            case EInputCode::KEY_PRIOR: return SDL_SCANCODE_PRIOR;
            case EInputCode::KEY_RETURN2: return SDL_SCANCODE_RETURN2;
            case EInputCode::KEY_SEPARATOR: return SDL_SCANCODE_SEPARATOR;
            case EInputCode::KEY_OUT: return SDL_SCANCODE_OUT;
            case EInputCode::KEY_OPER: return SDL_SCANCODE_OPER;
            case EInputCode::KEY_CLEARAGAIN: return SDL_SCANCODE_CLEARAGAIN;
            case EInputCode::KEY_CRSEL: return SDL_SCANCODE_CRSEL;
            case EInputCode::KEY_EXSEL: return SDL_SCANCODE_EXSEL;

            case EInputCode::KEY_KP_00: return SDL_SCANCODE_KP_00;
            case EInputCode::KEY_KP_000: return SDL_SCANCODE_KP_000;
            case EInputCode::KEY_THOUSANDSSEPARATOR: return SDL_SCANCODE_THOUSANDSSEPARATOR;
            case EInputCode::KEY_DECIMALSEPARATOR: return SDL_SCANCODE_DECIMALSEPARATOR;
            case EInputCode::KEY_CURRENCYUNIT: return SDL_SCANCODE_CURRENCYUNIT;
            case EInputCode::KEY_CURRENCYSUBUNIT: return SDL_SCANCODE_CURRENCYSUBUNIT;
            case EInputCode::KEY_KP_LEFTPAREN: return SDL_SCANCODE_KP_LEFTPAREN;
            case EInputCode::KEY_KP_RIGHTPAREN: return SDL_SCANCODE_KP_RIGHTPAREN;
            case EInputCode::KEY_KP_LEFTBRACE: return SDL_SCANCODE_KP_LEFTBRACE;
            case EInputCode::KEY_KP_RIGHTBRACE: return SDL_SCANCODE_KP_RIGHTBRACE;
            case EInputCode::KEY_KP_TAB: return SDL_SCANCODE_KP_TAB;
            case EInputCode::KEY_KP_BACKSPACE: return SDL_SCANCODE_KP_BACKSPACE;

            case EInputCode::KEY_KP_A: return SDL_SCANCODE_KP_A;
            case EInputCode::KEY_KP_B: return SDL_SCANCODE_KP_B;
            case EInputCode::KEY_KP_C: return SDL_SCANCODE_KP_C;
            case EInputCode::KEY_KP_D: return SDL_SCANCODE_KP_D;
            case EInputCode::KEY_KP_E: return SDL_SCANCODE_KP_E;
            case EInputCode::KEY_KP_F: return SDL_SCANCODE_KP_F;

            case EInputCode::KEY_KP_XOR: return SDL_SCANCODE_KP_XOR;
            case EInputCode::KEY_KP_POWER: return SDL_SCANCODE_KP_POWER;
            case EInputCode::KEY_KP_PERCENT: return SDL_SCANCODE_KP_PERCENT;
            case EInputCode::KEY_KP_LESS: return SDL_SCANCODE_KP_LESS;
            case EInputCode::KEY_KP_GREATER: return SDL_SCANCODE_KP_GREATER;
            case EInputCode::KEY_KP_AMPERSAND: return SDL_SCANCODE_KP_AMPERSAND;
            case EInputCode::KEY_KP_DBLAMPERSAND: return SDL_SCANCODE_KP_DBLAMPERSAND;
            case EInputCode::KEY_KP_VERTICALBAR: return SDL_SCANCODE_KP_VERTICALBAR;
            case EInputCode::KEY_KP_DBLVERTICALBAR: return SDL_SCANCODE_KP_DBLVERTICALBAR;
            case EInputCode::KEY_KP_COLON: return SDL_SCANCODE_KP_COLON;
            case EInputCode::KEY_KP_HASH: return SDL_SCANCODE_KP_HASH;
            case EInputCode::KEY_KP_SPACE: return SDL_SCANCODE_KP_SPACE;
            case EInputCode::KEY_KP_AT: return SDL_SCANCODE_KP_AT;
            case EInputCode::KEY_KP_EXCLAM: return SDL_SCANCODE_KP_EXCLAM;

            case EInputCode::KEY_KP_MEMSTORE: return SDL_SCANCODE_KP_MEMSTORE;
            case EInputCode::KEY_KP_MEMRECALL: return SDL_SCANCODE_KP_MEMRECALL;
            case EInputCode::KEY_KP_MEMCLEAR: return SDL_SCANCODE_KP_MEMCLEAR;
            case EInputCode::KEY_KP_MEMADD: return SDL_SCANCODE_KP_MEMADD;
            case EInputCode::KEY_KP_MEMSUBTRACT: return SDL_SCANCODE_KP_MEMSUBTRACT;
            case EInputCode::KEY_KP_MEMMULTIPLY: return SDL_SCANCODE_KP_MEMMULTIPLY;
            case EInputCode::KEY_KP_MEMDIVIDE: return SDL_SCANCODE_KP_MEMDIVIDE;
            case EInputCode::KEY_KP_PLUSMINUS: return SDL_SCANCODE_KP_PLUSMINUS;
            case EInputCode::KEY_KP_CLEAR: return SDL_SCANCODE_KP_CLEAR;
            case EInputCode::KEY_KP_CLEARENTRY: return SDL_SCANCODE_KP_CLEARENTRY;
            case EInputCode::KEY_KP_BINARY: return SDL_SCANCODE_KP_BINARY;
            case EInputCode::KEY_KP_OCTAL: return SDL_SCANCODE_KP_OCTAL;
            case EInputCode::KEY_KP_DECIMAL: return SDL_SCANCODE_KP_DECIMAL;
            case EInputCode::KEY_KP_HEXADECIMAL: return SDL_SCANCODE_KP_HEXADECIMAL;

            case EInputCode::KEY_LCTRL: return SDL_SCANCODE_LCTRL;
            case EInputCode::KEY_LSHIFT: return SDL_SCANCODE_LSHIFT;
            case EInputCode::KEY_LALT: return SDL_SCANCODE_LALT;
            case EInputCode::KEY_LGUI: return SDL_SCANCODE_LGUI;
            case EInputCode::KEY_RCTRL: return SDL_SCANCODE_RCTRL;
            case EInputCode::KEY_RSHIFT: return SDL_SCANCODE_RSHIFT;
            case EInputCode::KEY_RALT: return SDL_SCANCODE_RALT;
            case EInputCode::KEY_RGUI: return SDL_SCANCODE_RGUI;

            case EInputCode::KEY_MODE: return SDL_SCANCODE_MODE;

            case EInputCode::KEY_SLEEP: return SDL_SCANCODE_SLEEP;
            case EInputCode::KEY_WAKE: return SDL_SCANCODE_WAKE;

            case EInputCode::KEY_CHANNEL_INCREMENT: return SDL_SCANCODE_CHANNEL_INCREMENT;
            case EInputCode::KEY_CHANNEL_DECREMENT: return SDL_SCANCODE_CHANNEL_DECREMENT;

            case EInputCode::KEY_MEDIA_PLAY: return SDL_SCANCODE_MEDIA_PLAY;
            case EInputCode::KEY_MEDIA_PAUSE: return SDL_SCANCODE_MEDIA_PAUSE;
            case EInputCode::KEY_MEDIA_RECORD: return SDL_SCANCODE_MEDIA_RECORD;
            case EInputCode::KEY_MEDIA_FAST_FORWARD: return SDL_SCANCODE_MEDIA_FAST_FORWARD;
            case EInputCode::KEY_MEDIA_REWIND: return SDL_SCANCODE_MEDIA_REWIND;
            case EInputCode::KEY_MEDIA_NEXT_TRACK: return SDL_SCANCODE_MEDIA_NEXT_TRACK;
            case EInputCode::KEY_MEDIA_PREVIOUS_TRACK: return SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
            case EInputCode::KEY_MEDIA_STOP: return SDL_SCANCODE_MEDIA_STOP;
            case EInputCode::KEY_MEDIA_EJECT: return SDL_SCANCODE_MEDIA_EJECT;
            case EInputCode::KEY_MEDIA_PLAY_PAUSE: return SDL_SCANCODE_MEDIA_PLAY_PAUSE;
            case EInputCode::KEY_MEDIA_SELECT: return SDL_SCANCODE_MEDIA_SELECT;

            case EInputCode::KEY_AC_NEW: return SDL_SCANCODE_AC_NEW;
            case EInputCode::KEY_AC_OPEN: return SDL_SCANCODE_AC_OPEN;
            case EInputCode::KEY_AC_CLOSE: return SDL_SCANCODE_AC_CLOSE;
            case EInputCode::KEY_AC_EXIT: return SDL_SCANCODE_AC_EXIT;
            case EInputCode::KEY_AC_SAVE: return SDL_SCANCODE_AC_SAVE;
            case EInputCode::KEY_AC_PRINT: return SDL_SCANCODE_AC_PRINT;
            case EInputCode::KEY_AC_PROPERTIES: return SDL_SCANCODE_AC_PROPERTIES;

            case EInputCode::KEY_AC_SEARCH: return SDL_SCANCODE_AC_SEARCH;
            case EInputCode::KEY_AC_HOME: return SDL_SCANCODE_AC_HOME;
            case EInputCode::KEY_AC_BACK: return SDL_SCANCODE_AC_BACK;
            case EInputCode::KEY_AC_FORWARD: return SDL_SCANCODE_AC_FORWARD;
            case EInputCode::KEY_AC_STOP: return SDL_SCANCODE_AC_STOP;
            case EInputCode::KEY_AC_REFRESH: return SDL_SCANCODE_AC_REFRESH;
            case EInputCode::KEY_AC_BOOKMARKS: return SDL_SCANCODE_AC_BOOKMARKS;

            case EInputCode::KEY_SOFTLEFT: return SDL_SCANCODE_SOFTLEFT;
            case EInputCode::KEY_SOFTRIGHT: return SDL_SCANCODE_SOFTRIGHT;
            case EInputCode::KEY_CALL: return SDL_SCANCODE_CALL;
            case EInputCode::KEY_ENDCALL: return SDL_SCANCODE_ENDCALL;

            case EInputCode::KEY_RESERVED: return SDL_SCANCODE_RESERVED;

            // InputCode::KEY_COUNT is a sentinel, not an actual key.
            case EInputCode::KEY_COUNT: return SDL_SCANCODE_UNKNOWN;
            default: return SDL_SCANCODE_UNKNOWN;
        }
        return SDL_SCANCODE_UNKNOWN;
    }
}

