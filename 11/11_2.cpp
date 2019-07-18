
#include <kernel.h>
#include "kernel_cfg.h"
#include "app.h"
#include "mbed.h"
#include "app_config.h"
#include "Zumo.h"
#include "Milkcocoa.h"

Serial pc(USBTX, USBRX);
Zumo zumo;

DigitalOut led_red(LED1);
DigitalOut led_green(LED2);
DigitalOut led_blue(LED3);


DigitalIn sw1(D12);



void task_main(intptr_t exinf)
{
    int n;
    sw1.mode(PullUp);
    pc.baud(115200);
    int i = 1; //呼び出すモードを管理
    bool rel = false; //長押ししても単押しになるように

    while(1)
    {
    	n = sw1;
    	if ((n == 0) && (rel == false)) { //初めて押されたら(次にループに入ってきたときに走らないように）
    		rel = true;
    		i++;
    	} else if (n == 1){ //離されたら
    		rel = false;
    	}

    	pc.printf("SW1=%d\r\n",n);

    	switch (i) {
    		case 1:				//最初　（青点灯)
    			led_blue = 1;
    			break;
    		case 2:				//青点滅
    			led_blue = 1;
    			dly_tsk(100);
    			led_blue = 0;
    			dly_tsk(100);
    			break;
    		case 3:				//赤点灯
    			led_blue = 0;
    			led_red = 1;
    			break;
    		case 4:				//青点灯に戻る
    			led_red = 0;
    			i = 1;
    			break;
    		default:
    			break;
    	}
    }
}
