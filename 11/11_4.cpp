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
	unsigned int IR_values[6];

	pc.baud(9600);

	while(1){
		zumo.readAnalogIrValue(IR_values);

		if(IR_values[3]>= 200){
			if(IR_values[0] <= 200){
				zumo.driveTank(10,60);
			}
		} else {
			zumo.driveTank(60,10);
		}
	}
}
