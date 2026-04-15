#ifndef PS2_PAD_H
#define PS2_PAD_H
#ifdef TARGET_PS2
void ps2_pad_init(void);
void ps2_pad_activate(void);
void ps2_pad_poll(void);
#endif
#endif
