
#include <kernel.h>
#include "kernel_cfg.h"
#include "app.h"
#include "mbed.h"
#include "app_config.h"
#include "Zumo.h"
#include "Milkcocoa.h"

Serial pc(USBTX, USBRX);
Zumo zumo;

void task_main(intptr_t exinf)
{

    short int x,y,z;

    pc.baud(9600);
    while(1){
    	zumo.getAcceleration(&x,&y,&z);
    	pc.printf("%d,%d,%d\r\n",x,y,z);
    }
    dly_tsk(500);
}
