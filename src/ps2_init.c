#ifdef TARGET_PS2
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <iopcontrol.h>
#include <sbv_patches.h>
#include <debug.h>
#include <unistd.h>



extern unsigned char sio2man_irx[];
extern unsigned int size_sio2man_irx;
extern unsigned char padman_irx[];
extern unsigned int size_padman_irx;

extern unsigned char usbd_irx[];
extern unsigned int size_usbd_irx;
extern unsigned char bdm_irx[];
extern unsigned int size_bdm_irx;
extern unsigned char bdmfs_fatfs_irx[];
extern unsigned int size_bdmfs_fatfs_irx;
extern unsigned char usbmass_bd_irx[];
extern unsigned int size_usbmass_bd_irx;

void ps2_init(void)
{
    int ret;

    init_scr();
    scr_printf("PS2: Resetting IOP...\n");

    SifIopReset(NULL, 0);
    while (!SifIopSync()) {};
    SifInitRpc(0);
    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();


    scr_printf("PS2: Loading pad drivers...\n");
    ret = SifExecModuleBuffer(sio2man_irx, size_sio2man_irx, 0, NULL, NULL);
    scr_printf("  sio2man: %d\n", ret);
    ret = SifExecModuleBuffer(padman_irx, size_padman_irx, 0, NULL, NULL);
    scr_printf("  padman: %d\n", ret);

    scr_printf("PS2: Loading USB drivers...\n");

    ret = SifExecModuleBuffer(usbd_irx, size_usbd_irx, 0, NULL, NULL);
    scr_printf("  usbd: %d\n", ret);

    ret = SifExecModuleBuffer(bdm_irx, size_bdm_irx, 0, NULL, NULL);
    scr_printf("  bdm: %d\n", ret);

    ret = SifExecModuleBuffer(bdmfs_fatfs_irx, size_bdmfs_fatfs_irx, 0, NULL, NULL);
    scr_printf("  fatfs: %d\n", ret);

    ret = SifExecModuleBuffer(usbmass_bd_irx, size_usbmass_bd_irx, 0, NULL, NULL);

    scr_printf("PS2: Loading pad drivers...\n");
    scr_printf("PS2: Waiting for USB device...\n");
    sleep(4);

    scr_printf("PS2: Ready!\n");
}
#endif

#ifdef TARGET_PS2
#include <stdio.h>
void ps2_log(const char *msg)
{
    FILE *f = fopen("mass0:/OPENTYRI/log.txt", "a");
    if (f) {
        fprintf(f, "%s\n", msg);
        fclose(f);
    }
}
#endif
