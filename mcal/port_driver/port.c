
/*
 * port.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Mustafa Sayed
 */
#define MAX_NUM_OF_CH_IN_PORT       8

#include "../../utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include "../../config/port_cfg.h"
#include "../mcu_hw.h"
#include "port_types.h"
#include "port.h"

extern Port_CfgType PortCfgArr[];

void PORT_init(void)
{
    uint8 i;
    Port_IdType PortId;
    Port_ChIdType ChId;
    volatile PORT_RegType* PORT_Addr;
    for (i = 0; i < PORT_NUM_OF_ACTIVATED_CH; ++i)
    {
      /*  PortId = i/ MAX_NUM_OF_CH_IN_PORT;
        ChId = i % MAX_NUM_OF_CH_IN_PORT;*/

        PortId = PortCfgArr[i].Channel / 8;
                ChId = PortCfgArr[i].Channel % 8;

        switch (PortId)
        {
        case Port_Id_A:
            PORT_Addr = &PORTA_REG;
            break;
        case Port_Id_B:
            PORT_Addr = &PORTB_REG;
            break;
        case Port_Id_C:
            PORT_Addr = &PORTC_REG;
            break;
        case Port_Id_D:
            /* Assign PORTD address to PORT_Addr variable */
            PORT_Addr = &PORTD_REG;
            break;
        case Port_Id_E:
            PORT_Addr = &PORTE_REG;
            break;
        case Port_Id_F:
            PORT_Addr = &PORTF_REG;
            break;
        }

        //Unlock Ports
        switch(PortCfgArr[i].Channel){
        case Port_Channel_F0 :

            PORTF_REG.GPIOLOCK = 0x4C4F434B; /* unlock commit register */
            PORTF_REG.GPIOCR = 0x01; /* make PORTF0 configurable */
            break;

        }

        /* set channel direction */
        if(PortCfgArr[i].Dir == port_Dir_Output )
        {
            // CLR_BIT(PORT_Addr->GPIODIR, );
           // PORT_Addr->GPIODIR = 0xFFFFFFFF;
            PORT_Addr->GPIODIR |= (1<<ChId) ;
        }
        else
        {
            PORT_Addr->GPIODIR &= ~(1<<ChId) ;
            //PORT_Addr->GPIODIR = 0x00000000;
        }


        /* set channel mode */
        if(PortCfgArr[i].Mode == PORT_MODE_PIN_X_DIO){
            PORT_Addr->GPIOAFSEL &= ~(1<<ChId) ;
        }
        else{

        }

        /* set Interrupt configuration */

        if(PortCfgArr[i].Interrupt == Port_IntDisable)
        {
            CLR_BIT(PORT_Addr->GPIOIM, ChId);
        }
        else
        {
            CLR_BIT(PORT_Addr->GPIOIM, ChId); //disable interrupts

            PORT_Addr->GPIOIS &= ~(1<<ChId) ;//The edge on the corresponding pin is detected
            PORT_Addr->GPIORIS &= ~(1<<ChId) ;//An interrupt condition has not occurred on the corresponding pin

            switch(PortCfgArr[i].Interrupt){
            case Port_IntBothEdges :
                PORT_Addr->GPIOIBE |= (1<<ChId) ;//Both edges on the corresponding pin trigger an interrupt.
                break;
            case Port_IntFallingEdge :
                PORT_Addr->GPIOIBE &= ~(1<<ChId) ;//Interrupt generation is controlled by the GPIO Interrupt Event (GPIOIEV) register
                PORT_Addr->GPIOIEV &= ~(1<<ChId) ;//A falling edge or a Low level on the corresponding pin triggers an interrupt

                           break;
            case Port_IntRisingEdge :
                PORT_Addr->GPIOIBE &= ~(1<<ChId) ;//Interrupt generation is controlled by the GPIO Interrupt Event (GPIOIEV) register
                PORT_Addr->GPIOIEV |= (1<<ChId) ;//A rising edge or a High level on the corresponding pin triggers an interrupt
                           break;

            }

            PORT_Addr->GPIOIM |= (1<<ChId) ;//enable interrupts
        }

        /* set Internal Attachment configuration */
        PORT_Addr->GPIOCR |= (1<<ChId) ;//The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits can be written
        switch(PortCfgArr[i].AttachedRes){
        case Port_InternalAttach_NA :
        break;
        case Port_InternalAttach_PullUpRes :

        PORT_Addr->GPIOPUR |= (1<<ChId) ;

        break;
        case Port_InternalAttach_PullDownRes :

        PORT_Addr->GPIOPDR |= (1<<ChId) ;

        break;
        case Port_InternalAttach_OpenDrain :

        PORT_Addr->GPIOODR |= (1<<ChId) ;

        break;

        }

        /* set current strength configuration */

        switch(PortCfgArr[i].CurrentDrive){

        case Port_CurrDrive_2mA :

        PORT_Addr->GPIODR2R |= (1<<ChId) ;

        break;
        case Port_CurrDrive_4mA :

        PORT_Addr->GPIODR4R |= (1<<ChId) ;

        break;
        case Port_CurrDrive_8mA :

        PORT_Addr->GPIODR8R |= (1<<ChId) ;

        break;

        }


        /*Check if analog functionality is required*/
        if(PortCfgArr[i].Mode != Port_Mode_AIN )
        {
            /* enable digital and disable ADC  */
            PORT_Addr->GPIODEN |= (1<<ChId) ;

        }
        else
        {
            /* disable digital and enable ADC */
            PORT_Addr->GPIOAMSEL |= (1<<ChId) ;

        }

    //    PORT_Addr->GPIOCR &= ~(1<<ChId) ;//The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or GPIODEN bits cannot be written.
    }
}
