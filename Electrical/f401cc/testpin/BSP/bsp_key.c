#include "bsp_key.h"
#include "stdbool.h"

//========================================================================
// ����: bsp_keyScan_20ms 
// ����: .
// ����: None.
// ����: None.
//========================================================================
bool key0Val=0;//����������1���ɿ���0
bool key0OneClicFlag=0;//����������־λ  ����ȡ��
bool key0TwoClicFlag=0;//����˫����־λ  ����ȡ��
bool key0LonClicFlag=0;//����������־λ  ����ȡ��
uint8_t clicTimeSpan_x20ms = 15;//˫��ʱ���� Ĭ��300ms
/*
void bsp_keyScan_20ms()
{
	static bool key0ValPrevious=0;
	static uint8_t clicCnt=0,timeOutCnt=0;
	
	if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin))
	{
		key0Val=1;
		if(key0ValPrevious != key0Val)//��������
		{
			clicCnt++;
			timeOutCnt=0;
			if(clicCnt == 1)//����
				key0OneClicFlag =~ key0OneClicFlag;
			else if(clicCnt == 2)//˫��
				key0TwoClicFlag =~ key0TwoClicFlag;
			else 
				key0TwoClicFlag =~ key0TwoClicFlag;//��������Ҳ��˫��
		}
		else
		{
			timeOutCnt++;
			if(timeOutCnt > clicTimeSpan_x20ms)
			{
				timeOutCnt = 0;
				clicCnt = 0;
			}
		}
		key0ValPrevious = key0Val;
	}
}
*/
