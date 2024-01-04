#include "stdbool.h"


#include "user_main.h"

#include "bsp_led.h"


#include "bsp_uart.h"

#include "task.h"
#include "usart.h"
#include "XdriveCom.h"
#include "cubeMotion.h"
#include "OpiCom.h"
#include "zdt_motorCom.h"
/***************************************************/
/*********************TASK************************/
/***************************************************/
//========================================================================
// ����: basic  task
// ����: .
// ����: None.
// ����: None.
//========================================================================
	
void basicTask_entry()
{
	led_sta_update_20ms();	
}
/***************************************************/
/*********************��ʼ��************************/
/***************************************************/

void user_main()
{
	uart_init();
	roboInit();
}

void task1()
{
	if((serialActionStartFlag==0)&&(originMod==0))
	{
		static uint8_t cnt = 0;
		
		motorRcvStatusUpdate(cnt);
		cnt++;
		if(cnt>4)cnt=0;
	}
}
uint8_t deb1=0xFF;
void task2()
{
	if(deb1 == 0)
	{
		deb1 = 0xFF;
		zdt_motorEnanleCtl(3,zdt_disable);
	}	
	if(deb1 == 1)
	{
		deb1 = 0xFF;
		zdt_motorEnanleCtl(3,zdt_enable);
	}
	else if(deb1 == 2)
	{
		deb1 = 0xFF;
		zdt_motorTrackCtl(3,36000,511,506,10000);
	}
	else if(deb1 == 3)
	{
		deb1 = 0xFF;
		zdt_motorTrackCtl(3,-36000,511,506,10000);
	}	
	else if(deb1 == 4)
	{
		deb1 = 0xFF;
		zdt_motorTrackCtl(3,0,511,506,10000);
	}		
	else if(deb1 == 5)
	{
		deb1 = 0xFF;
		zdt_motorTrackCtl(3,0,511,506,10000);
	}		

	else if(deb1 == 7)
	{
		deb1 = 0xFF;
		zdt_readPos(3);
	}	
	else if(deb1 == 8)
	{
		deb1 = 0xFF;
		zdt_readSpeed(3);
	}	
	else if(deb1 == 9)
	{
		deb1 = 0xFF;
		motorStop(0);
	}
		else if(deb1 == 10)
	{
		deb1 = 0xFF;
		motorStop(1);
	}
	else if(deb1 == 11)
	{
		deb1 = 0xFF;
		motorCurrControl(0,-1000);
	}
		else if(deb1 == 12)
	{
		deb1 = 0xFF;
		motorCurrControl(1,-1000);
	}	
	else if(deb1 == 13)
	{
		deb1 = 0xFF;
		zdt_zeroPosSet(2,zdt_parmSave);
	}
	else if(deb1 == 14)
	{
		deb1 = 0xFF;
		zdt_zeroPosSet(3,zdt_parmSave);
	}	
	else if(deb1 == 15)
	{
		deb1 = 0xFF;
		zdt_zeroPosTrig(2);
	}
	else if(deb1 == 16)
	{
		deb1 = 0xFF;
		zdt_zeroPosTrig(3);
	}		
		else if(deb1 == 17)
	{
		deb1 = 0xFF;
		zdt_readEncoderVal(3);
	}
		else if(deb1 == 18)
	{
		deb1 = 0xFF;
		zdt_readEncoderVal(2);
	}
}
void task3()
{
	static uint8_t cnt;
	switch(cnt)
	{
		case 0:
			zdt_readEncoderVal(3);
			break;
		case 1:
			zdt_readPos(3);
			break;		
		case 2:
			zdt_readSpeed(3);
			break;			
	}
	cnt++;
	if(cnt > 2)cnt=0;
}
//========================================================================
//                         ���ر������� & �������
//========================================================================


static TASK_COMPONENTS Task_Comps[]=
{
//״̬  ����  ����  ����
	{0, 20, 20, basicTask_entry},				/* task 1 Period�� 2ms*/
	{0, 5, 5, serialActionTask},				/* task 2 Period�� 100ms �ɿ�����*/
	{0, 5, 5, OpiRcvTask},			/* task 3 Period�� 300ms ��ص�ѹ*/
//	{0, 100, 100, task1},					/* task 4 Period�� 500ms */
//	{0, 100, 100, task2},					/* task 5 Period�� 500ms */
//	{0, 5, 5, task3},					/* task 6 Period�� 500ms */
//	{0, 500, 500, task_D},					/* task 7 Period�� 500ms */
//	{0, 500, 500, task_E},					/* task 8 Period�� 500ms */

	/* Add new task here */
};

uint8_t Tasks_Max = sizeof(Task_Comps)/sizeof(Task_Comps[0]);

//========================================================================
// ����: Task_Handler_Callback
// ����: �����ǻص�����.
// ����: None.
// ����: None.
//========================================================================
void Task_Marks_Handler_Callback(void)
{
	uint8_t i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].TIMCount)    /* If the time is not 0 */
		{
			Task_Comps[i].TIMCount--;  /* Time counter decrement */
			if(Task_Comps[i].TIMCount == 0)  /* If time arrives */
			{
				/*Resume the timer value and try again */
				Task_Comps[i].TIMCount = Task_Comps[i].TRITime;  
				Task_Comps[i].Run = 1;    /* The task can be run */
			}
		}
	}
}

//========================================================================
// ����: Task_Pro_Handler_Callback
// ����: ������ص�����.
// ����: None.
// ����: None.
//========================================================================
void Task_Pro_Handler_Callback(void)
{
	uint8_t i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].Run) /* If task can be run */
		{
			Task_Comps[i].Run = 0;    /* Flag clear 0 */
			Task_Comps[i].TaskHook();  /* Run task */
		}
	}
}






