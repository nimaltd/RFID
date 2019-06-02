#ifndef _RFID_H
#define _RFID_H

#include "usart.h"

//##########################################################
typedef struct
{
  uint32_t  Time;
  uint8_t   Tmp;
  uint8_t   Buff[16];
  uint8_t   Index;  
  uint32_t  NewCardCode;
  
}RFID_t;
//##########################################################
extern      RFID_t  RFID;
//##########################################################
void  RFID_Init(void);
void  RFID_CallBack(void);
void  RFID_Loop(void);
//##########################################################
void RFID_User_DetectNewCard(uint32_t CardCode);
//##########################################################

#endif
