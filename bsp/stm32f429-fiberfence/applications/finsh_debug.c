#include <rtthread.h>
#include "key_app.h"
#include <dfs_posix.h>
#include <string.h>

struct Params{
	rt_uint16_t alarm_A_th;
	rt_uint16_t alarm_B_th;
	rt_uint16_t power_th;
	rt_uint16_t alarm_interval;
	rt_uint16_t addr1;
	rt_uint16_t addr2;
	rt_uint16_t addr3;
	rt_uint16_t addr4;
	rt_uint16_t port;
};

enum KEY_VALUE
{
	KEY_UP=1,
	KEY_DOWN,
	KEY_PLUS,
	KEY_SUB,
	KEY_ENTER,
	KEY_RETURN
};

void key_test(enum KEY_VALUE value)
{
	switch(value)
	{
		case KEY_UP:
			key_up_press();
			break;
		case KEY_DOWN:
			key_down_press();
			break;
		case KEY_PLUS:
			key_plus_press();
			break;
		case KEY_SUB:
			key_sub_press();
			break;
		case KEY_ENTER:
			key_enter_press();
			break;
		case KEY_RETURN:
			key_back_perss();
			break;
		default:
			break;
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(key_test, key test. e.g: key_test(KEY_UP));
#endif

void list_all_param()
{
	rt_kprintf("--------Fiber Fence System Parameter List Tab-------\n");

	rt_kprintf("---------------------end----------------------------\n");
}

void sub_version()
{
	rt_kprintf("\n \\ | /\n");
	rt_kprintf("- RT -     Apollo Uart Project\n");
	rt_kprintf(" / | \\     %d.%d.%d build %s\n",
						 RT_VERSION, RT_SUBVERSION, RT_REVISION, __DATE__);
}

extern int AT24CXX_Write(rt_uint16_t addr,
                        void *buf,
                        size_t len);
extern int AT24CXX_Read(rt_uint16_t addr,
                        void *buf,
                        size_t len);

void save_parameter()
{
	struct Params P = {2200,
										2200,
										300,
										5,
										192,
										168,
										103,
										85,
										5900};
	AT24CXX_Write(0,(char *)&P, sizeof(struct Params));
}

void load_parameter()
{
	struct Params P;
	AT24CXX_Read(0,(char *)&P, sizeof(struct Params));
	rt_kprintf("%d.%d.%d.%d\n", P.addr1,P.addr2,P.addr3,P.addr4);
}

int get_line(int fd, char *buffer)
{
	int i=0, len;
	while(1){
		len = read(fd, &buffer[i], 1); 
		if(len<1)
			break;
		if(buffer[i]=='\n')
			break;
		i++;
	}
	buffer[i]='\0';
	return i;
}

void test_fgets()
{
	int fd, length;
	char buf[128];
	fd = open("/alarm.txt", O_RDONLY, 0); 
	if (fd < 0) 
	{ 
			rt_kprintf("check: open file for read failed\n"); 
			return; 
	} 
	do{
		length=get_line(fd, buf);
		rt_kprintf("%s(length:%d)\n", buf, length);
	}while(length!=0);
	close(fd);
	
}

void save_config()
{
	
}

void load_config()
{

}

void reset_config()
{

}
RTM_EXPORT(reset_config);

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_all_param, list all parameter);
FINSH_FUNCTION_EXPORT_ALIAS(list_all_param, lap, list all parameter);
FINSH_FUNCTION_EXPORT(sub_version,);
FINSH_FUNCTION_EXPORT(save_parameter,);
FINSH_FUNCTION_EXPORT(load_parameter,);
FINSH_FUNCTION_EXPORT(test_fgets,);
FINSH_FUNCTION_EXPORT(save_config,);
FINSH_FUNCTION_EXPORT(load_config,);
FINSH_FUNCTION_EXPORT_ALIAS(reset_config, reset,);
#endif
