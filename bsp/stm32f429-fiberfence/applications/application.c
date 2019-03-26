/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>
#include <dfs_posix.h>
#include <drivers/mtd_nand.h>
#include "finsh.h"
#include "time.h"
#include "drv_gpio.h"
#include "key.h"
#include "key_app.h"

#include <rtthread.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>

#ifdef RT_USING_DFS
/* dfs init */

/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>

#endif

#ifdef RT_USING_LWIP
#include <lwip/lwip_sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "drv_eth.h"
#endif

rt_thread_t tid, tid1, keyid, udp_server_id, alarm_log_id;

struct rt_mailbox mb_udp, mb_alarm;

static char mb_udp_pool[4], mb_alarm_pool[40];


void rt_init_thread_entry(void* parameter)
{    
     /* initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
    
#ifdef RT_USING_DFS   
	dfs_init();
        
#ifdef RT_USING_DFS_ELMFAT
	elm_init();
    
    /* mount sd card fat partition 0 as root directory */
    if (dfs_mount("W25Q64", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("spi flash mount to / succesfull!\n");
    }
    else
    {
        rt_kprintf("spi flash mount to / failed!\n");
    }
    
    /* mount sd card fat partition 0 as root directory */
    if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == 0)
    {
        rt_kprintf("sd card mount to /sdcard succesfull!\n");        
    }
    else
    {
        rt_kprintf("sd card mount to /sdcard failed!\n");
    }
#endif /* RT_USING_DFS_ELMFAT */
        
#endif /* DFS */

		extern int phy_register_read(int reg);
		int value;
		while(1){
			value=phy_register_read(1);
			if((value&0x0004) == 0)
				;
				//HAL_GPIO_WritePin(GPIOG, LED14_Pin|CPU_RUN_Pin, GPIO_PIN_SET);
				//rt_kprintf("link down\n");
			else
				;
				//HAL_GPIO_WritePin(GPIOG, LED14_Pin|CPU_RUN_Pin, GPIO_PIN_RESET);
				//rt_kprintf("link up\n");
			rt_thread_delay(1000);
		}
}

/*
*******************LED指示灯信号**********************
*/
void rt_system_led_thread_entry(void* parameter)
{ 
	while(1)
	{
		//HAL_GPIO_WritePin(GPIOG, LED9_Pin|CPU_RUN_Pin, GPIO_PIN_SET);
		CPU_RUN_LED = ON;
		rt_thread_delay(100);
		//HAL_GPIO_WritePin(GPIOG, LED9_Pin|CPU_RUN_Pin, GPIO_PIN_RESET);
		CPU_RUN_LED = OFF;
		rt_thread_delay(100);
	}
}



/*
*******************按键处理**********************
*/
void rt_key_thread_entry(void* parameter)
{	
	int key_value;
	
	
	while(1)
	{
		key_value = KEY_Scan(1);
		switch(key_value)
		{
			case KEY0_PRES:                //back
				key_back_perss();
				//rt_kprintf("KEY0_PRES\n");
				break;
			case KEY1_PRES:                //enter
				key_enter_press();
				//rt_kprintf("KEY1_PRES\n");
				break;
			case KEY2_PRES:                //sub
				key_sub_press();
				//rt_kprintf("KEY2_PRES\n");
				break;
			case KEY3_PRES:                //add
				key_plus_press();
				//rt_kprintf("KEY3_PRES\n");
				break;
			case KEY4_PRES:                //down
				key_down_press();
				//rt_kprintf("KEY4_PRES\n");
				break;
			case KEY5_PRES:                //up
				key_up_press();
				//rt_kprintf("KEY5_PRES\n");
				break;
			default:
				break;	
		}
		
		rt_thread_delay(60);
	}
}

void alarm_log(void *parameter)
{
		int fd, i=1;
		char *str, buf[100];
		rt_uint32_t value;
		while(1)
		{
			if (rt_mb_recv(&mb_alarm, (rt_uint32_t *)&value, RT_WAITING_FOREVER)== RT_EOK)
			{
					time_t now;
					now = time(RT_NULL);
					str=ctime(&now);
					if(value==1){
						sprintf(buf, "%d.A fence zone alarmed at %s", i, str);
					}
					else if(value==2){
						sprintf(buf, "%d.B fence zone alarmed at %s", i, str);
					}
					else
						continue;
					
					i++;
					fd = open("/alarm.txt", O_WRONLY | O_CREAT | O_APPEND, 0);
					write(fd, buf, strlen(buf));
					close(fd);
			}
		}
}

int rt_application_init()
{
		extern void udpserv(void* paramemter);
								
		rt_mb_init(&mb_udp,
								"mbt_udp", /* name */
								&mb_udp_pool[0], /* mail mb_pool */
								sizeof(mb_udp_pool)/4, /*size*/
								RT_IPC_FLAG_FIFO);
								
		rt_mb_init(&mb_alarm,
								"mbt_alarm", /* name */
								&mb_alarm_pool[0], /* mail mb_pool */
								sizeof(mb_alarm_pool)/4, /*size*/
								RT_IPC_FLAG_FIFO);
	
    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3-4, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
		
		tid1 = rt_thread_create("system_run_led",
        rt_system_led_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3+2, 20);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
		
		keyid = rt_thread_create("key",
        rt_key_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3-3, 20);

    if (keyid != RT_NULL)
        rt_thread_startup(keyid);
		
		
		udp_server_id = rt_thread_create("udp_server",
        udpserv, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3-1, 20);

    if (udp_server_id != RT_NULL)
        rt_thread_startup(udp_server_id);
		
		alarm_log_id = rt_thread_create("alarm_log",
        alarm_log, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3+3, 20);

    if (alarm_log_id != RT_NULL)
        rt_thread_startup(alarm_log_id);

    return 0;
}
