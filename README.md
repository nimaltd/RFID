# RFID EM-18,EM-19 module Library for STM32 HAL
#### I use Stm32f103c8 and Keil Compiler and Stm32CubeMX wizard.
 <br />
Please Do This ...
<br />
<br />
1) Config your usart and enable RX interrupt (9600,1,1) on CubeMX.
<br />
2) Select "General peripheral Initalizion as a pair of '.c/.h' file per peripheral" on project settings.
<br />
3) Config your RFID_Config.h file.
<br />
4) Add RFID_CallBack() on usart interrupt routin. 
<br />
5) Call  RFID_Init().
<br />
6) Put RFID_Loop() in your main or a task.
<br />

```
#include "RFID.h"
.
.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART2)
  {
    RFID_CallBack();    
  }  
}
.
.
int main()
{
  .
  .
  RFID_Init();
  .
  .
  while(1)
  {
    .
    .
    RFID_Loop();
    .
    . 
  }

```
