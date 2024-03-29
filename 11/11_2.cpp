#include <kernel.h>
#include "kernel_cfg.h"
#include "app.h"

#include "mbed.h"
#include "app_config.h"
#include "Zumo.h"
#include "Milkcocoa.h"

Serial pc(USBTX, USBRX);
Zumo zumo;

DigitalIn sw1(D12);

void task_main(intptr_t exinf)
{
    int n;
    int t;
    unsigned int IR_values[6];

    Timer timer1;
    sw1.mode(PullUp);
    pc.baud(9600);

    n = sw1;
    while (sw1 != 0)
    {
    }
    pc.printf("To Start\r\n");
    dly_tsk(1000);

    timer1.reset();
    timer1.start();
    zumo.driveTank(100,100);
    while(1)
    {
        t = timer1.read_ms();
        if (t > 1000)
        {
            break;
        }
        zumo.readAnalogIrValue(IR_values);
        pc.printf("%d,%d\r\n", t, IR_values[3]);
    }
    pc.printf("Finish\r\n");
    zumo.driveTank(0,0);
}
