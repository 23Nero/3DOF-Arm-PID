#include "./../include/LeNguyenKhanhLam.h"

static char buff[BUFFER];
static volatile int stateStopBase = 0;
static volatile int tmp_homeBase = 0;
static volatile int tmp_homeLink1 = 0;
static volatile int tmp_homeLink2 = 0;

int main()
{
  sysInit();

  Kp1 = 24;
  Ki1 = 2.5;
  Kd1 = 0.5;

  setBase = 45;

 Kp2 = 60;
  Ki2 = 2.5;
  Kd2 = 0.5;

  setLink1 = 45;

  Kp3 = 60;
  Ki3 = 2.5;
  Kd3 = 0.5;

  setLink2 = -45;

  while (1)
  {

    if (stateHome)
    {
      TIM_SetDutyCycle(TIM2, CHANEL1, 200);
      GPIO_setPin(GPIO_C, 1);
      GPIO_resetPin(GPIO_C, 0);

      TIM_SetDutyCycle(TIM3, CHANEL2, 200);
      GPIO_setPin(GPIO_C, 3);
      GPIO_resetPin(GPIO_C, 2);

      TIM_SetDutyCycle(TIM3, CHANEL1, 200);
      GPIO_setPin(GPIO_A, 9);
      GPIO_resetPin(GPIO_A, 8);
    }
    if (tmp_homeBase && tmp_homeLink1 && tmp_homeLink2)
    {
      stateHome = 0;
      tmp_homeBase = tmp_homeLink1 = tmp_homeLink2 = 0;
      setBase = -30;
      setLink1 = 90;
      setLink2 = 90;
    }
  }
}

void USART2_IRQHandler(void)
{
  if (USART2->SR & USART_SR_RXNE)
  {
    USART_receiveString(USART2, buff, BUFFER);
    if (sscanf(buff, "Base: %lf", &setBase) == 1)
    {
      stateHome = 0;
      stateStopBase = 0;
      USART_sendString(USART2, "Success!");
    }
    else if (sscanf(buff, "Home: %d", &stateHome) == 1)
    {
    }
    else if (sscanf(buff, "Base: Kp-%lf Ki-%lf Kd-%lf", &Kp1, &Ki1, &Kd1) == 3)
    {
    }
  }
}
void EXTI15_10_IRQHandler(void)
{
  if (stateHome)
  {
    // Base
    if (GPIO_readPin(GPIO_C, 10))
    {
      pulseBase = 0;
      tmp_homeBase++;
      EXTI->PR |= (1 << 10);
    }
  }
}

void EXTI1_IRQHandler(void)
{
  // Link1
  if (stateHome)
  {
    if (GPIO_readPin(GPIO_B, 1))
    {
      pulseLink1 = 0;

      tmp_homeLink1++;
      EXTI->PR |= (1 << 1);
    }
  }
}
void EXTI2_IRQHandler(void)
{
  if (stateHome)
  {
    // Link2
    if (!GPIO_readPin(GPIO_B, 2))
    {
      pulseLink2 = 0;

      tmp_homeLink2++;
      EXTI->PR |= (1 << 2);
    }
  }
}

void TIM4_IRQHandler(void)
{
  if (!stateHome)
  {
    runBasePID();

    runLink1PID();

    runLink2PID();

    sendData();
  }
  TIM4->SR &= ~(1u << 0);
}

