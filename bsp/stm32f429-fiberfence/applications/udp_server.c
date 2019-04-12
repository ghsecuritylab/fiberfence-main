/*
 * 代码清单：UDP服务端，接收和处理上位机发送的命令
 */
#include <rtthread.h>
#include <stdio.h>
#include <lwip/sockets.h> /* 使用BSD socket，需要包含sockets.h头文件 */
#include <lwip/netdb.h>

#include "drv_gpio.h"

#define MAX_DATA_LEN 512
#define BASE_PACK_LEN 10

//查询命令
#define CMD_EXIT        0x100f
#define CMD_CPU_USAGE   0x1001
#define CMD_OPTIC_POWER 0x1002
#define CMD_ALARM_COUNT 0x1003

//控制命令
#define CMD_DAC_GAIN_A        0x2001
#define CMD_DAC_GAIN_B        0x2002
#define CMD_ADC_SAMPLE_FRQ    0x2003
#define CMD_ALARM_THRESHOLD_A 0x2004
#define CMD_ALARM_THRESHOLD_B 0x2005
#define CMD_POWER_THRESHOLD   0x2006
#define CMD_ALARM_INTERVAL    0x2007

//响应命令
#define CMD_RESPONSE_OK        0x0000
#define CMD_RESPONSE_UNKNOW    0x1111
#define CMD_RESPONSE_MAGIC_ERR 0x2222

#define CMD_HEARTBEAT   0x3001    //心跳包
#define CMD_ALARM       0x3002  	//报警包
#define CMD_POWER_LOWER 0x3003    //光功率故障

static rt_uint16_t device_online_flags[8]={10};

static rt_timer_t heartbeat_check_timer;

extern float get_cpu(void);
extern int set_dac(rt_uint16_t value, rt_uint16_t chip_id);

typedef struct {
    uint16_t magic;
    uint16_t cmd;
    uint16_t device_id;
    uint16_t zone_id;
		uint16_t power_flag1;
		uint16_t power_flag2;
    char data[MAX_DATA_LEN];
} Cmd_Data;

void red_led_control(int pin, rt_bool_t value){
		switch(pin){
					case 0:
						RED_LED1=value;
						break;
					case 1:
						RED_LED2=value;
						break;
					case 2:
						RED_LED3=value;
						break;
					case 3:
						RED_LED4=value;
						break;
					case 4:
						RED_LED5=value;
						break;
					case 5:
						RED_LED6=value;
						break;
					case 6:
						RED_LED7=value;
						break;
					case 7:
						RED_LED8=value;
						break;
					case 8:
						RED_LED9=value;
						break;
					case 9:
						RED_LED10=value;
						break;
					case 10:
						RED_LED11=value;
						break;
					case 11:
						RED_LED12=value;
						break;
					case 12:
						RED_LED13=value;
						break;
					case 13:
						RED_LED14=value;
						break;
					case 14:
						RED_LED15=value;
						break;
					case 15:
						RED_LED16=value;
						break;
					default:
						break;
				}
}

void green_led_control(int pin, rt_bool_t value){
		switch(pin){
					case 0:
						GREEN_LED1=value;
						break;
					case 1:
						GREEN_LED2=value;
						break;
					case 2:
						GREEN_LED3=value;
						break;
					case 3:
						GREEN_LED4=value;
						break;
					case 4:
						GREEN_LED5=value;
						break;
					case 5:
						GREEN_LED6=value;
						break;
					case 6:
						GREEN_LED7=value;
						break;
					case 7:
						GREEN_LED8=value;
						break;
					case 8:
						GREEN_LED9=value;
						break;
					case 9:
						GREEN_LED10=value;
						break;
					case 10:
						GREEN_LED11=value;
						break;
					case 11:
						GREEN_LED12=value;
						break;
					case 12:
						GREEN_LED13=value;
						break;
					case 13:
						GREEN_LED14=value;
						break;
					case 14:
						GREEN_LED15=value;
						break;
					case 15:
						GREEN_LED16=value;
						break;
					default:
						break;
				}
}

void switch_control(int pin, rt_bool_t value){
		switch(pin){
					case 0:
						SWITCH1=value;
						break;
					case 1:
						SWITCH2=value;
						break;
					case 2:
						SWITCH3=value;
						break;
					case 3:
						SWITCH4=value;
						break;
					case 4:
						SWITCH5=value;
						break;
					case 5:
						SWITCH6=value;
						break;
					case 6:
						SWITCH7=value;
						break;
					case 7:
						SWITCH8=value;
						break;
					case 8:
						SWITCH9=value;
						break;
					case 9:
						SWITCH10=value;
						break;
					case 10:
						SWITCH11=value;
						break;
					case 11:
						SWITCH12=value;
						break;
					case 12:
						SWITCH13=value;
						break;
					case 13:
						SWITCH14=value;
						break;
					case 14:
						SWITCH15=value;
						break;
					case 15:
						SWITCH16=value;
						break;
					default:
						break;
				}
}

/*********************************************************
* 函数名：heartbeat_check
* 
* 功  能：检查各设备心跳
*********************************************************/
static void heartbeat_check(void *parameter){
		int i=0;
		for(i=0;i<8;i++){
			if(device_online_flags[i]>0){
				device_online_flags[i]--;
				green_led_control(2*i, ON);
				green_led_control(2*i+1, ON);
			}
			else{
				green_led_control(2*i, OFF);
				green_led_control(2*i+1, OFF);
				device_online_flags[i]=0;
			}
		}
}

void response(int sock, int cmd, struct sockaddr *client_addr, int addr_len)
{
//	struct Cmd_Data r;
//	r.magic = 0x1234;
//	r.cmd = cmd;
//	sendto(sock, (char *)&r, BASE_PACK_LEN+2, 0, client_addr, addr_len);
}

/*********************************************************
* 函数名：cmd_process
* 
* 功  能：处理接收到的命令
*********************************************************/
extern TIM_HandleTypeDef htim10;
void cmd_process(int sock, Cmd_Data *cd, struct sockaddr *client_addr, int addr_len)
{
		int zone_id = 2*cd->device_id+cd->zone_id;
		switch(cd->cmd){
			//心跳信号
			case CMD_HEARTBEAT:{
				device_online_flags[cd->device_id]=10;
			}
			//报警信号
			case CMD_ALARM:{
				red_led_control(zone_id, ON);
				switch_control(zone_id, ON);
				HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1); //开启蜂鸣器
				break;
			}
			//光功率过低故障
			case CMD_POWER_LOWER:{
				green_led_control(zone_id, OFF);
				HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1); //开启蜂鸣器
				break;
			}
			default:
				break;
		}
}

/*********************************************************
* 函数名：udpserv
* 
* 功  能：udp服务，接收各室外机上传的报警，并处理报警信息
*********************************************************/
void udpserv(void* paramemter)
{
    int sock;
    int bytes_read;
    char *recv_data;
		Cmd_Data *cmd_data_t;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;

    /* 分配接收用的数据缓冲 */
    recv_data = rt_malloc(1024);
    if (recv_data == RT_NULL)
    {
        /* 分配内存失败，返回 */
        rt_kprintf("No memory\n");
        return;
    }

    /* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        rt_kprintf("Socket error\n");

        /* 释放接收用的数据缓冲 */
        rt_free(recv_data);
        return;
    }

    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* 绑定socket到服务端地址 */
    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr))
            == -1)
    {
        /* 绑定地址失败 */
        rt_kprintf("Bind error\n");

        /* 释放接收用的数据缓冲 */
        rt_free(recv_data);
        return;
    }

    addr_len = sizeof(struct sockaddr);
    rt_kprintf("UDPServer Waiting for client on port 5000...\n");

		heartbeat_check_timer = rt_timer_create("heartbeat_check_timer", heartbeat_check,
                             RT_NULL, 1000,
                             RT_TIMER_FLAG_PERIODIC);
		
		if (heartbeat_check_timer != RT_NULL) rt_timer_start(heartbeat_check_timer);
		
    while (1)
    {
        /* 从sock中收取最大1024字节数据 */
        bytes_read = recvfrom(sock, recv_data, 1024, 0,
                              (struct sockaddr *) &client_addr, &addr_len);			
			
				if(bytes_read <=0 )
				{
						rt_kprintf("recive error\n");
						continue;
				}

				cmd_data_t=(Cmd_Data *)recv_data;
				
				/* 校验帧头 */
				if(cmd_data_t->magic!=0x1234)
				{
						rt_kprintf("magic error\n");
						continue;
				}
				/* 处理接收到命令 */
				cmd_process(sock, cmd_data_t, (struct sockaddr *) &client_addr, addr_len);
    }
		
		lwip_close(sock);
		rt_free(recv_data);

    return;
}

/*********************************************************
* 函数名：udp_send_data
* 
* 功  能：udp数据发送，将报警信息汇总上报到监控中心
*********************************************************/
void udp_send_data(char *send_data, int len)
{
    int sock, port=8089;
    struct hostent *host;
    struct sockaddr_in server_addr;
		char *tmp;
	
		tmp=rt_malloc(2004);

    host = (struct hostent *) gethostbyname("192.168.1.255");

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        rt_kprintf("Socket error\n");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *) host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
		

		sendto(sock, send_data, len, 0,
					 (struct sockaddr *) &server_addr, sizeof(struct sockaddr));

		
    lwip_close(sock);
		rt_free(tmp);
}

void EXTI3_IRQHandler(void)
{
		rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
		rt_interrupt_leave();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		int i;
		if(GPIO_Pin == GPIO_PIN_3)
		{
			for(i=0; i<16; i++){
				red_led_control(i, OFF);
				switch_control(i, OFF);
			}
			HAL_TIM_PWM_Stop(&htim10,TIM_CHANNEL_1); //关闭蜂鸣器
		}
}
