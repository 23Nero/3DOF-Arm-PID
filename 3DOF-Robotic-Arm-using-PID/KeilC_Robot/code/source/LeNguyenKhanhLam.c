#include "./../include/LeNguyenKhanhLam.h"

volatile int stateHome = 0;

void sysInit(void)
{
  enaleClockModule();
  configGPIO();
  configTim();
  configUsart();
  configSysTickInt(NULL);
}

void enaleClockModule(void)
{
  /* Enable clock */
  RCC->AHB1ENR |= (1 << 0);  // Port A
  RCC->AHB1ENR |= (1 << 1);  // Port B
  RCC->AHB1ENR |= (1 << 2);  // Port C
  RCC->AHB1ENR |= (1 << 7);  // Port H
  RCC->APB1ENR |= (1 << 17); // USART2
  RCC->APB1ENR |= (1 << 0);  // TIM2
  RCC->APB1ENR |= (1 << 1);  // TIM3
  RCC->APB1ENR |= (1 << 2);  // TIM4
  RCC->APB2ENR |= SYSCFGEN;  // Exti
}

void configTim(void)
{
  TIM_Stop(TIM2);
  TIM_Stop(TIM3);
  TIM_Stop(TIM4);
  /* Set timer2 channel 1 - PA0 */
  GPIO_setMode(GPIO_A, 0, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 0, AF1);

  TIM_Config(TIM2, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

  TIM_ConfigOutputCompare(TIM2, CHANEL1, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM2, CHANEL1, ACTIVE_HIGH);

  /* Set timer2 channel 2 - PA1 */
  GPIO_setMode(GPIO_A, 7, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 7, AF2);

  TIM_ConfigOutputCompare(TIM3, CHANEL2, TIM_OCMODE2_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL2, ACTIVE_HIGH);

  /* Set timer3 channel 1 - PA6 */
  GPIO_setMode(GPIO_A, 6, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 6, AF2);

  TIM_Config(TIM3, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

  TIM_ConfigOutputCompare(TIM3, CHANEL1, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL1, ACTIVE_HIGH);

  TIM_Start(TIM2);
  TIM_Start(TIM3);
  TIM_Start(TIM5);

  TIM_Config(TIM4, 1600, 1000, TIM_MODE_BASIC);
  /*Enable interrupt TIM4*/
  TIM4->DIER |= (1 << 0);
  /*Enable IRQ tim4*/
  NVIC->ISER[0] |= (1 << 30);
  TIM_Start(TIM4);
}

void configGPIO(void)
{
  /* Set PB8 input */
  GPIO_setMode(GPIO_B, 8, INPUT);
  GPIO_setPullUpDown(GPIO_B, 8, PULL_UP);

  /* Enable interrupt EXTI8_9 */
  NVIC->ISER[0] |= (1 << 23);

  /* Select PORTB for EXTI8 */
  SYSCFG->EXTICR3 |= (1 << 0);
  /* Unmask EXTI8 */
  EXTI->IMR |= (1 << 8);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 8);

  /* Set PB9 input */
  GPIO_setMode(GPIO_B, 9, INPUT);
  GPIO_setPullUpDown(GPIO_B, 9, PULL_UP);

  GPIO_setMode(GPIO_C, 1, OUTPUT);
  GPIO_setMode(GPIO_C, 0, OUTPUT);

  GPIO_setMode(GPIO_C, 10, INPUT);
  GPIO_setPullUpDown(GPIO_C, 10, PULL_UP);
  /* Enable interrupt EXTI10_15 */
  NVIC->ISER[1] |= (1 << 8);

  /* Select PORTC for EXTI10 */
  SYSCFG->EXTICR3 |= (2 << 8);
  /* Unmask EXTI10 */
  EXTI->IMR |= (1 << 10);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 10);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  /* Set PC4 input */
  GPIO_setMode(GPIO_C, 4, INPUT);
  GPIO_setPullUpDown(GPIO_C, 4, PULL_DOWN);

  /* Enable interrupt EXTI4 */
  NVIC->ISER[0] |= (1 << 10);

  /* Select PORTC for EXTI4 */
  SYSCFG->EXTICR2 |= (2 << 0);
  /* Unmask EXTI4 */
  EXTI->IMR |= (1 << 4);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 4);

  /* Set PB13 input */
  GPIO_setMode(GPIO_B, 13, INPUT);
  GPIO_setPullUpDown(GPIO_B, 13, PULL_UP);

  GPIO_setMode(GPIO_C, 2, OUTPUT);
  GPIO_setMode(GPIO_C, 3, OUTPUT);

  GPIO_setMode(GPIO_B, 1, INPUT);
  GPIO_setPullUpDown(GPIO_B, 1, PULL_UP);

  /* Enable interrupt EXTI1 */
  NVIC->ISER[0] |= (1 << 1);

  /* Select PORH for EXTI0 */
  SYSCFG->EXTICR1 |= (1 << 4);
  /* Unmask EXTI1 */
  EXTI->IMR |= (1 << 1);
  /* Rising or Falling */
  EXTI->FTSR |= (1 << 1);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  /* Set PB3 input */
  GPIO_setMode(GPIO_B, 3, INPUT);
  GPIO_setPullUpDown(GPIO_B, 3, PULL_UP);

  /* Enable interrupt EXT3 */
  NVIC->ISER[0] |= (1 << 9);

  /* Select PORTB for EXTI3 */
  SYSCFG->EXTICR1 |= (1 << 12);
  /* Unmask EXTI4 */
  EXTI->IMR |= (1 << 3);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 3);

  GPIO_setMode(GPIO_B, 5, INPUT);
  GPIO_setPullUpDown(GPIO_B, 5, PULL_UP);

  GPIO_setMode(GPIO_A, 8, OUTPUT);
  GPIO_setMode(GPIO_A, 9, OUTPUT);

  GPIO_setMode(GPIO_B, 2, INPUT);
  GPIO_setPullUpDown(GPIO_B, 2, PULL_UP);

  /* Enable interrupt EXTI2 */
  NVIC->ISER[0] |= (1 << 8);
  /* Select PORTB for EXT2 */
  SYSCFG->EXTICR1 |= (1 << 8);
  /* Unmask EXTI1 */
  EXTI->IMR |= (1 << 2);
  /* Rising or Falling */
  EXTI->FTSR |= (1 << 2);
}

void configUsart(void)
{
  // Configure Usart2
  NVIC->ISER[1] |= (1 << 6);
  GPIO_setMode(GPIO_A, 2, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 2, AF7);

  GPIO_setMode(GPIO_A, 3, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 3, AF7);

  uart_set_baudrate(USART2, SYSTEM_CORE_CLOCK, 115200);

  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 2);
  USART2->CR1 |= USART_CR1_RXNEIE;
  USART2->CR1 |= (1 << 13);
}

void runBasePID(void)
{
  posBase = ((pulseBase * 360) / 11300);
  Ea = setBase - posBase;
  alpha1 = 2 * T * Kp1 + Ki1 * T * T + 2 * Kd1;
  beta1 = T * T * Ki1 - 4 * Kd1 - 2 * T * Kp1;
  gama1 = 2 * Kd1;
  outputBase = (alpha1 * Ea + beta1 * E1 + gama1 * E2 + 2 * T * lastoutputBase) / (2 * T);
  lastoutputBase = outputBase;
  E2 = E1;
  E1 = Ea;

  if (outputBase > 255)
  {
    outputBase = 255;
  }
  else if (outputBase < -255)
  {
    outputBase = -255;
  }
  if (outputBase > 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)outputBase);
    GPIO_setPin(GPIO_C, 1);
    GPIO_resetPin(GPIO_C, 0);
  }
  else if (outputBase < 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)-outputBase);
    GPIO_setPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
  else
  {
    GPIO_resetPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
}

void runLink1PID(void)
{
  posLink1 = ((pulseLink1 * 360) / 11300);
  Eb = setLink1 - posLink1;
  alpha2 = 2 * T * Kp2 + Ki2 * T * T + 2 * Kd2;
  beta2 = T * T * Ki2 - 4 * Kd2 - 2 * T * Kp2;
  gama2 = 2 * Kd2;
  outputLink1 = (alpha2 * Eb + beta2 * E3 + gama2 * E4 + 2 * T * lastoutputLink1) / (2 * T);
  lastoutputLink1 = outputLink1;
  E4 = E3;
  E3 = Eb;

  if (outputLink1 > 255)
  {
    outputLink1 = 255;
  }
  else if (outputLink1 < -255)
  {
    outputLink1 = -255;
  }
  if (outputLink1 > 0)
  {
    TIM_SetDutyCycle(TIM3, CHANEL2, (uint16_t)outputLink1);
    GPIO_setPin(GPIO_C, 2);
    GPIO_resetPin(GPIO_C, 3);
  }
  else if (outputLink1 < 0)
  {
    TIM_SetDutyCycle(TIM3, CHANEL2, (uint16_t)-outputLink1);
    GPIO_setPin(GPIO_C, 3);
    GPIO_resetPin(GPIO_C, 2);
  }
  else
  {
    GPIO_resetPin(GPIO_C, 2);
    GPIO_resetPin(GPIO_C, 3);
  }
}

void EXTI9_5_IRQHandler(void)
{
  if (GPIO_readPin(GPIO_B, 9))
    pulseBase--;
  else
    pulseBase++;

  EXTI->PR |= (1 << 8);
}

void EXTI4_IRQHandler(void)
{
  if (GPIO_readPin(GPIO_B, 13))
  {
    pulseLink1--;
  }
  else
    pulseLink1++;

  EXTI->PR |= (1 << 4);
}

void EXTI3_IRQHandler(void)
{
  if (GPIO_readPin(GPIO_B, 5))
  {
    pulseLink2--;
  }
  else
    pulseLink2++;

  EXTI->PR |= (1 << 3);
}

void runLink2PID(void)
{
  posLink2 = ((pulseLink2 * 360) / 7450);
  Ec = setLink2 - posLink2;
  alpha3 = 2 * T * Kp3 + Ki3 * T * T + 2 * Kd3;
  beta3 = T * T * Ki3 - 4 * Kd3 - 2 * T * Kp3;
  gama3 = 2 * Kd3;
  outputLink2 = (alpha3 * Ec + beta3 * E5 + gama3 * E6 + 2 * T * lastoutputLink2) / (2 * T);
  lastoutputLink2 = outputLink2;
  E6 = E5;
  E5 = Ec;

  if (outputLink2 > 255)
  {
    outputLink2 = 255;
  }
  else if (outputLink2 < -255)
  {
    outputLink2 = -255;
  }
  if (outputLink2 > 0)
  {
    TIM_SetDutyCycle(TIM3, CHANEL1, (uint16_t)outputLink2);
    GPIO_setPin(GPIO_A, 8);
    GPIO_resetPin(GPIO_A, 9);
  }
  else if (outputLink2 < 0)
  {
    TIM_SetDutyCycle(TIM3, CHANEL1, (uint16_t)-outputLink2);
    GPIO_setPin(GPIO_A, 9);
    GPIO_resetPin(GPIO_A, 8);
  }
  else
  {
    GPIO_resetPin(GPIO_A, 8);
    GPIO_resetPin(GPIO_A, 9);
  }
}

void sendData(void)
{
  char buffer[33];
  sprintf(buffer, "%d", pulseBase);
  USART_sendString(USART2, buffer);
  USART_sendString(USART2, "\n");
}
