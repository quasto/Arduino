
#include "wdt.h"

wdt::wdt()
{
	return;
}

void wdt::begin(int mode,voidFuncPtr callback, unsigned int wd_period, unsigned int int_period)
{
	/*if(mode == ONE_TIME)
	{*/
		PM->APBAMASK.reg |= PM_APBAMASK_WDT; //turn on clock for wdt
	
	//GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK4 | GCLK_CLKCTRL_ID( WDT_GCLK_ID )) ;
	GCLK->CLKCTRL.reg = (uint32_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK2 | (WDT_GCLK_ID << GCLK_CLKCTRL_ID_Pos)) ;
	while (GCLK->STATUS.bit.SYNCBUSY);
	
	GCLK->GENCTRL.reg = (GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSCULP32K | GCLK_GENCTRL_ID(2) | GCLK_GENCTRL_DIVSEL );
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
	
	GCLK->GENDIV.reg = GCLK_GENDIV_ID(2);
	GCLK->GENDIV.bit.DIV=4;
	while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
	
	
	WDT->CTRL.bit.ALWAYSON = 0;  //watchdog is not always on, then enable bit control the module
	WDT->CTRL.bit.WEN = 0; //watch dog in normal mode.
	
	while(WDT->STATUS.bit.SYNCBUSY); //wait for sync
	
	
	if(mode == ONE_TIME_INTERRUPT)
	{
		wdt_period = wd_period;
		if(int_period > wdt_period) return;
		else WDT->EWCTRL.bit.EWOFFSET = int_period; //setting early warning interrupt offset
		
		NVIC_DisableIRQ( WDT_IRQn  ) ;
		NVIC_ClearPendingIRQ( WDT_IRQn  ) ;
		NVIC_SetPriority( WDT_IRQn , 0 ) ;
		NVIC_EnableIRQ( WDT_IRQn  ) ;
		
		_callback2 = callback;
		WDT->INTENSET.bit.EW = 1; //early warning interrupt enabled
		
	}
	SetPeriod(wd_period);
	
}

void wdt::enable(void)
{
	if(WDT->CTRL.reg & WDT_CTRL_ENABLE)
	{
		return;
	}
	else
	{
		WDT->CTRL.reg = 0x1u<<1; //enable watchdog
	while(WDT->STATUS.bit.SYNCBUSY); //wait for sync
	}	
	
}


void wdt::disable(void)
{
	WDT->CTRL.reg = 0x0u<<1; //disable watchdog
	while(WDT->STATUS.bit.SYNCBUSY); //wait for sync
}


void wdt::SetPeriod(unsigned int period)
{
	if(WDT->CTRL.reg & WDT_CTRL_ENABLE)
	{
		WDT->CTRL.reg = ~WDT_CTRL_ENABLE;  //disable watchdog
	}
	
	if(period > 0x0B) period = WDT_16K_MS; 
	WDT->CONFIG.bit.PER = period; //16384 clock cycles (16.3 seconds) (default period)
	while(WDT->STATUS.bit.SYNCBUSY); //wait for sync
	wdt_period = period;
}

void wdt::reset(void)
{
	WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;
	while(WDT->STATUS.bit.SYNCBUSY); //wait for sync
}


void WDT_Handler( void )
{
  _callback2();
  WDT->INTFLAG.bit.EW = 1; //clearing interrupt flag
}
