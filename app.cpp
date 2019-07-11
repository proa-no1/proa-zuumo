
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
    dly_tsk(500);

    zumo.driveTank(100,100);
    dly_tsk(300);
    zumo.driveTank(0,0);
    dly_tsk(500);

    zumo.driveTank(-100,-100);
    dly_tsk(300);
    zumo.driveTank(0,0);
    dly_tsk(500);
}
