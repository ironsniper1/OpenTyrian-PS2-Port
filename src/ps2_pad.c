#ifdef TARGET_PS2
#include <tamtypes.h>
#include <stdio.h>
#include "ps2_init.h"
#include "joystick.h"
#include "SDL.h"

static int pad_active = 0;
static u32 old_pad = 0;

void ps2_pad_init(void) {}

void ps2_pad_activate(void)
{
    pad_active = 1;
    ps2_log("pad activated");
}

void ps2_pad_poll(void)
{
    SDLKey keymap[] = {
        SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT,
        SDLK_RETURN, SDLK_ESCAPE, SDLK_SPACE, SDLK_LALT
    };
    SDL_Event ev;
    u32 paddata = 0, new_press, released;
    int i;

    if (!pad_active || joysticks < 1) return;
    if (!joystick[0].handle) return;

    SDL_JoystickUpdate();

    int hat = SDL_JoystickGetHat(joystick[0].handle, 0);
    if (hat & SDL_HAT_UP)    paddata |= (1<<0);
    if (hat & SDL_HAT_DOWN)  paddata |= (1<<1);
    if (hat & SDL_HAT_LEFT)  paddata |= (1<<2);
    if (hat & SDL_HAT_RIGHT) paddata |= (1<<3);

    if (SDL_JoystickGetButton(joystick[0].handle, 0)) paddata |= (1<<4); // cross
    if (SDL_JoystickGetButton(joystick[0].handle, 1)) paddata |= (1<<5); // circle
    if (SDL_JoystickGetButton(joystick[0].handle, 2)) paddata |= (1<<6); // square
    if (SDL_JoystickGetButton(joystick[0].handle, 3)) paddata |= (1<<7); // triangle

    static int plog = 0;
    if (plog < 50 && paddata != 0) {
        char buf[80];
        sprintf(buf, "pad: 0x%04x hat=%d", (unsigned)paddata, hat);
        ps2_log(buf);
        plog++;
    }

    new_press = paddata & ~old_pad;
    released = old_pad & ~paddata;
    old_pad = paddata;

    for (i = 0; i < 8; i++) {
        if (new_press & (1 << i)) {
            ev.type = SDL_KEYDOWN;
            ev.key.keysym.sym = keymap[i];
            ev.key.keysym.mod = KMOD_NONE;
            ev.key.keysym.unicode = 0;
            SDL_PushEvent(&ev);
        }
        if (released & (1 << i)) {
            ev.type = SDL_KEYUP;
            ev.key.keysym.sym = keymap[i];
            ev.key.keysym.mod = KMOD_NONE;
            ev.key.keysym.unicode = 0;
            SDL_PushEvent(&ev);
        }
    }
}
#endif
