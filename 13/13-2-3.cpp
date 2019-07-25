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
    zumo.driveTank(0,0);
    dly_tsk(500);

    unsigned int IR_values[6];
    int left = -1, right = -1;
    double x = 5.9, y;
    double angle;
    double rotate;

    pc.baud(115200);
    Timer timer1;

    timer1.reset();
    timer1.start();

    while(1)
    {
        zumo.readAnalogIrValue(IR_values);

        if((IR_values[5] > 200)&&(IR_values[0] <= 200)){
            left = timer1.read_ms();
            pc.printf("left_time: %d\r\n", left);
            break;
        }else if((IR_values[5] <= 200)&&(IR_values[0] > 200)){
            right = timer1.read_ms();
            pc.printf("light_time: %d\r\n", right);
            break;
        }else if((IR_values[5] > 200)&&(IR_values[0] > 200)){
            break;
        }
        zumo.driveTank(100,100);
        dly_tsk(10);

    }

    while(1)
    {
        zumo.readAnalogIrValue(IR_values);

        if((left == -1)&&(right == -1)){
            left = timer1.read_ms();
            right = timer1.read_ms();
            pc.printf("left_time: %d\r\n", left);
            pc.printf("light_time: %d\r\n", right);
            break;
        }else if((IR_values[0] > 200)&&(right == -1)){
            right = timer1.read_ms();
            pc.printf("light_time: %d\r\n", right);
            break;
        }else if((IR_values[5] > 200)&&(left == -1)){
            left = timer1.read_ms();
            pc.printf("left_time: %d\r\n", left);
            break;
        }
        zumo.driveTank(100,100);
        dly_tsk(10);

    }

    zumo.driveTank(0,0);
    dly_tsk(500);

    y = 22.69 * (left - right) / 1000;    // 22.69[cm/s]:出力100でZUMOが進む速さ
    if(y < 0)
    	y *= -1;

    angle = 90 - (atan2(y,x) / M_PI * 180);

    pc.printf("angle = %f\r\n", angle);

    rotate = (90 - angle) * 10;

    if(angle < 88){
    	if(right < left){
            zumo.driveTank(100,-100);
            dly_tsk(rotate);

      	}else if(left < right){
            zumo.driveTank(-100,100);
            dly_tsk(rotate);

        }
    }
    zumo.driveTank(0,0);
    dly_tsk(500);

}
