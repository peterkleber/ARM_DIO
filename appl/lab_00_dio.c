/*
 * lab_03_spi.c
 *
 *  Created on: Aug 20, 2019
 *      Author: Muhammad.Elzeiny
 */

#include "../mcal/global_interrupt.h"
#include "../mcal/sys_ctr/SysCtr.h"
#include "../mcal/port_driver/port.h"
#include "../mcal/dio/dio.h"
#include "../mcal/mcu_hw.h"

#define LED_RED 0x02
#define LED_Blue 0x04
#define LED_Green 0x08

int main(void)
{
    unsigned int SW1_State = 1;
    unsigned int SW2_State = 1;

    SysCtr_init();
    PORT_init();


    while(1) {

       // SW2_State = (PORTF_REG.GPIODATA & 0x01);      /* read data from PORTF */
        SW2_State = Dio_ReadChannel(Dio_Channel_F0);
      //  SW1_State = (PORTF_REG.GPIODATA & 0x10);      /* read data from PORTF */
        SW1_State = Dio_ReadChannel(Dio_Channel_F4);

        if((SW1_State == 0)){
            PORTF_REG.GPIODATA |= LED_Blue;
        }
        else if((SW2_State == 0)){
            PORTF_REG.GPIODATA |= LED_Green;
        }
        else{
            PORTF_REG.GPIODATA &= ~(0x0E);
        }

    }

}


/*void main (void)
{
    SysCtr_init();
    PORT_init();

    Dio_WriteChannel(Dio_Channel_F1, STD_high);
    Dio_WriteChannel(Dio_Channel_F2, STD_high);
    Dio_WriteChannel(Dio_Channel_F3, STD_high);

    while(1)
    {


    }
     //return 0;
}
*/
// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1
