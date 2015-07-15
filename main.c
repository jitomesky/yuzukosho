#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "atag.h"
#include "fb.h"
#include "console.h"
#include "block.h"
#include "vfs.h"
#include "memchunk.h"
#include "usb.h"
#include "dwc_usb.h"
#include "output.h"
#include "log.h"
#include "gpio.h"
#include "jtag.h"

extern int (*stdout_putc)(int);
extern int (*stderr_putc)(int);
extern int (*stream_putc)(int, FILE*);
extern int def_stream_putc(int, FILE*);

int main(void){
    jtag_enable();

    // set actled on
    gpio_t act;
    gpio_init_out(&act, LED_ACT);

    // First use the serial console
    stdout_putc = split_putc;
    stderr_putc = split_putc;
    stream_putc = def_stream_putc;

    output_init();
    output_enable_uart();


    while(1){
        printf("led off\n");
        gpio_write(&act, 0);
        usleep(1000000);
        printf("led on\n");
        gpio_write(&act, 1);
        usleep(1000000);
    }

    return 0;
}
