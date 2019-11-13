/*
 * dio.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Muhammad.Elzeiny
 */

#include "../../utils/Bit_Math.h"
#include "../../utils/STD_Types.h"
#include "../mcu_hw.h"
/* include the header file that contains register definitions */

#include "dio.h"

STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    /* Return the Input Channel Value */

    switch(PortId){
    case Dio_Port_A :
        if ((PORTA_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
          return STD_high ;
      }
      else{
          return STD_low ;
      }
        break;
    case Dio_Port_B :
        if ((PORTB_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
            return STD_high ;
        }
        else{
            return STD_low ;
        }
        break;
    case Dio_Port_C :
        if ((PORTC_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
            return STD_high ;
        }
        else{
            return STD_low ;
        }
        break;
    case Dio_Port_D :
        if ((PORTD_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
            return STD_high ;
        }
        else{
            return STD_low ;
        }
        break;
    case Dio_Port_E :
        if ((PORTE_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
            return STD_high ;
        }
        else{
            return STD_low ;
        }
        break;
    case Dio_Port_F :
      //  if (PORTF_REG.GPIODATA & (1<<ChannelPos) == STD_high) {
        if ((PORTF_REG.GPIODATA>>ChannelPos) & (1u) == STD_high) {
            return STD_high ;
        }
        else{
            return STD_low ;
        }
        break;
    }

}
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    /* Write the input value in the corresponding ChannelId */

    switch(PortId){
    case Dio_Port_A :
        if(Level == STD_high){
            PORTA_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTA_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;
    case Dio_Port_B :
        if(Level == STD_high){
            PORTB_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTB_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;
    case Dio_Port_C :
        if(Level == STD_high){
            PORTC_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTC_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;
    case Dio_Port_D :
        if(Level == STD_high){
            PORTD_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTD_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;
    case Dio_Port_E :
        if(Level == STD_high){
            PORTE_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTE_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;
    case Dio_Port_F :
        if(Level == STD_high){
            PORTF_REG.GPIODATA |= (1<<ChannelPos) ;
        }
        else{
            PORTF_REG.GPIODATA &= ~(1<<ChannelPos) ;
        }
        break;

    }
}
uint8 Dio_ReadPort(Dio_PortType PortId )
{
    uint8 ret;

    switch(PortId){
    case Dio_Port_A :
        ret = PORTA_REG.GPIODATA ;
        break;
    case Dio_Port_B :
        ret = PORTB_REG.GPIODATA ;
            break;
    case Dio_Port_C :
        ret = PORTC_REG.GPIODATA ;
            break;
    case Dio_Port_D :
        ret = PORTD_REG.GPIODATA ;
            break;
    case Dio_Port_E :
        ret = PORTE_REG.GPIODATA ;
            break;
    case Dio_Port_F :
        ret = PORTF_REG.GPIODATA ;
            break;
    }

    /* Return the Port Value*/

    return ret;
}
void Dio_WritePort( Dio_PortType PortId, uint8 value)
{
    /* Write the input value in the corresponding PortId */
    uint32 PORT_HIGH = 0xFFFFFFFF ;
    uint32 PORT_LOW = 0x00000000 ;

    switch(PortId){
    case Dio_Port_A :
        if(value == STD_high){
            PORTA_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTA_REG.GPIODATA = PORT_LOW ;
        }
        break;
    case Dio_Port_B :
        if(value == STD_high){
            PORTB_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTB_REG.GPIODATA = PORT_LOW ;
        }
        break;
    case Dio_Port_C :
        if(value == STD_high){
            PORTC_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTC_REG.GPIODATA = PORT_LOW ;
        }
        break;
    case Dio_Port_D :
        if(value == STD_high){
            PORTD_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTD_REG.GPIODATA = PORT_LOW ;
        }
        break;
    case Dio_Port_E :
        if(value == STD_high){
            PORTE_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTE_REG.GPIODATA = PORT_LOW ;
        }
        break;
    case Dio_Port_F :
        if(value == STD_high){
            PORTF_REG.GPIODATA = PORT_HIGH ;
        }
        else{
            PORTF_REG.GPIODATA = PORT_LOW ;
        }
        break;
    }

}
void Dio_FlipChannel( Dio_ChannelType ChannelId)
{
    /* toggle the corresponding ChannelId */

    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    switch(PortId){
    case Dio_Port_A :
        PORTA_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;
    case Dio_Port_B :
        PORTB_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;
    case Dio_Port_C :
        PORTC_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;
    case Dio_Port_D :
        PORTD_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;
    case Dio_Port_E :
        PORTE_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;
    case Dio_Port_F :
        PORTF_REG.GPIODATA ^= (1<<ChannelPos) ;
        break;

    }


}
void Dio_FlipPort(Dio_PortType PortId)
{
    /* toggle the port value */
        uint32 PORT_HIGH = 0xFFFFFFFF ;

    switch(PortId){
    case Dio_Port_A :
        PORTA_REG.GPIODATA ^= PORT_HIGH ;
        break;
    case Dio_Port_B :
        PORTB_REG.GPIODATA ^= PORT_HIGH ;
        break;
    case Dio_Port_C :
        PORTC_REG.GPIODATA ^= PORT_HIGH ;
        break;
    case Dio_Port_D :
        PORTD_REG.GPIODATA ^= PORT_HIGH ;
        break;
    case Dio_Port_E :
        PORTE_REG.GPIODATA ^= PORT_HIGH ;
        break;
    case Dio_Port_F :
        PORTF_REG.GPIODATA ^= PORT_HIGH ;
        break;
    }

}



