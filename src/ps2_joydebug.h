#ifdef TARGET_PS2
static inline void ps2_joy_debug(void) {
    static int tw_log = 0;
    if (tw_log < 120) {
        SDL_JoystickUpdate();
        int j;
        for (j = 0; j < 2; j++) {
            if (joystick[j].handle) {
                int hat = SDL_JoystickGetHat(joystick[j].handle, 0);
                int btn0 = SDL_JoystickGetButton(joystick[j].handle, 0);
                int btn1 = SDL_JoystickGetButton(joystick[j].handle, 1);
                int btn2 = SDL_JoystickGetButton(joystick[j].handle, 2);
                int btn3 = SDL_JoystickGetButton(joystick[j].handle, 3);
                if (hat != 0 || btn0 || btn1 || btn2 || btn3) {
                    char buf[128];
                    sprintf(buf, "joy%d hat=%d b0=%d b1=%d b2=%d b3=%d", j, hat, btn0, btn1, btn2, btn3);
                    ps2_log(buf);
                }
            }
        }
        tw_log++;
    }
}
#endif
