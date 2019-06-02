
#include "RFID.h"
#include "RFID_Config.h"
#include <string.h>
#include <stdlib.h>

//###################################################################################
RFID_t  RFID;
//###################################################################################
void  RFID_Init(void)
{
  RFID.Index=0;
  RFID.Time = 0;
  memset(RFID.Buff,0,sizeof(RFID.Buff));
  HAL_UART_Receive_IT(&_RFID_USART,&RFID.Tmp,1);  
}
//###################################################################################
void  RFID_CallBack(void)
{
  RFID.Time = HAL_GetTick();
  if(RFID.Index<sizeof(RFID.Buff)-2)
  {
    RFID.Buff[RFID.Index] = RFID.Tmp;
    RFID.Index++;        
  }  
  HAL_UART_Receive_IT(&_RFID_USART,&RFID.Tmp,1);  
}
//###################################################################################
void  RFID_Loop(void)
{
  if((RFID.Index>0) && (HAL_GetTick()-RFID.Time>50))
  {
    if(RFID.Index==12)
		{			
			uint32_t Code;
			char str[10];
			uint8_t xorData=0;			
			for(uint8_t i=0;i<10;i+=2)
			{
				memset(str,0,sizeof(str));
				memcpy(str,&RFID.Buff[i],2);
				xorData = xorData^strtoul(str,NULL,16);
			}			
			memset(str,0,sizeof(str));
			memcpy(str,&RFID.Buff[10],2);
			if(xorData==strtoul(str,NULL,16))
			{
				memset(str,0,sizeof(str));
				memcpy(str,&RFID.Buff[2],8);
				Code = strtoul(str,NULL,16);		
				RFID.NewCardCode = Code;
        RFID_User_DetectNewCard(RFID.NewCardCode);
			}        
    }    
    memset(RFID.Buff,0,sizeof(RFID.Buff));
    RFID.Index=0;    
  }  
}
//###################################################################################
