#include "stm32f10x.h"

/* Вариант 4: PA6 -> PA7 */
#define SW_PORT        GPIOA
#define SW_CR          CRL
#define SW_MODE_MASK   (GPIO_CRL_MODE6 | GPIO_CRL_CNF6)
#define SW_MODE_VALUE  (GPIO_CRL_CNF6_0)      /* MODE=00 input, CNF=01 floating input */
#define SW_IDR_BIT     GPIO_IDR_IDR6

#define LED_PORT       GPIOA
#define LED_CR         CRL
#define LED_MODE_MASK  (GPIO_CRL_MODE7 | GPIO_CRL_CNF7)
#define LED_MODE_VALUE (GPIO_CRL_MODE7_1)     /* MODE=10 output 2 MHz, CNF=00 push-pull */
#define LED_BS_BIT     GPIO_BSRR_BS7          /* set PA7 */
#define LED_BR_BIT     GPIO_BSRR_BR7          /* reset PA7 */

int main(void)
{
    /* Enable GPIOA clock. */
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

    /* PA6 input, PA7 output. */
    MODIFY_REG(SW_PORT->SW_CR, SW_MODE_MASK, SW_MODE_VALUE);
    MODIFY_REG(LED_PORT->LED_CR, LED_MODE_MASK, LED_MODE_VALUE);

    /* Initial state: LED off. */
    WRITE_REG(LED_PORT->BSRR, LED_BR_BIT);

    while (1)
    {
        if (READ_BIT(SW_PORT->IDR, SW_IDR_BIT) != 0U)
        {
            WRITE_REG(LED_PORT->BSRR, LED_BS_BIT); /* PA6 = 1 -> PA7 = 1 */
        }
        else
        {
            WRITE_REG(LED_PORT->BSRR, LED_BR_BIT); /* PA6 = 0 -> PA7 = 0 */
        }
    }
}