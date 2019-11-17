#include "sam.h"

void clockInit(void)
{
    SYSCTRL->OSC8M.bit.PRESC = 0;                          // no prescaler (is 8 on reset)
    SYSCTRL->OSC8M.reg |= 1 << SYSCTRL_OSC8M_ENABLE_Pos;   // enable source

    GCLK->GENDIV.bit.ID = 0x01;                            // select GCLK_GEN[1]
    GCLK->GENDIV.bit.DIV = 0;                              // no prescaler

    GCLK->GENCTRL.bit.ID = 0x01;                           // select GCLK_GEN[1]
    GCLK->GENCTRL.reg |= GCLK_GENCTRL_SRC_OSC8M;           // OSC8M source
    GCLK->GENCTRL.bit.GENEN = 1;                           // enable generator

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_SERCOM0_CORE;      // SERCOM0 peripheral channel
    GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_GEN_GCLK1;           // select source GCLK_GEN[1]
    GCLK->CLKCTRL.bit.CLKEN = 1;                           // enable generic clock

    PM->APBCSEL.bit.APBCDIV = 0;                           // no prescaler
    PM->APBCMASK.bit.SERCOM0_ = 1;                         // enable SERCOM0 interface
}


void setup() {
  // put your setup code here, to run once:
  clockInit();
}

void loop() {
  // put your main code here, to run repeatedly:

}
