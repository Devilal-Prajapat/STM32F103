1. Paste this in it.c
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

2. Paste this in main.c before main()

extern uint16_t rxindex;
extern uint8_t Rx_Buffer[256];
extern uint8_t Recv_Complete_F;

3. paste this in main.c before while()

UART_Init();
UART_Enable_Rx();
HAL_UART_Transmit(&huart1,(uint8_t *)"Hello world\n",12,100);
  
  4. paste this in main.c in while()
 if(Recv_Complete_F ==true)
 {
   if(strncmp((const char  *)&Rx_Buffer[0],"LED ON",6)==0)
   {
     HAL_UART_Transmit(&huart1,&Rx_Buffer[0],rxindex,100);
     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
   }
   else if(strncmp((const char  *)&Rx_Buffer[0],"LED OFF",7)==0)
   {
     HAL_UART_Transmit(&huart1,&Rx_Buffer[0],rxindex,100);
     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
   }
   else
   {
     HAL_UART_Transmit(&huart1,&Rx_Buffer[0],rxindex,100);
   }
   rxindex = 0;
   memset(Rx_Buffer,0x00,256);
   UART_Enable_Rx();
   Recv_Complete_F = false;
 }
 
 5. Initialize a led for debug (for ex PC13)
