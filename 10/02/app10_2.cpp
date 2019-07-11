
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

    pc.baud(115200);
    while(1){
    	zumo.getAcceleration(&x,&y,&z);
    	pc.printf("%d,%d,%d\r\n",x,y,z);

    	zumo.driveTank(0,0);

     	if(x < 0|| y > 2000 || y < -2000){
    		//â
    		if(x < -100){
    			zumo.driveTank(80,-80);
    			dly_tsk(50);
    		} else {
    			if(y > 1000){
    				zumo.driveTank(-80,80);
    				dly_tsk(50);
    			}

    			if(y <-1000){
    				zumo.driveTank(80,-80);
    				dly_tsk(50);
    			}
    		}
    	}
     	zumo.driveTank(0,0);

    }
    dly_tsk(500);
}
