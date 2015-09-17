#ifndef wdt_H
#define wdt_H

#include "sam.h"
// watchdog operation modes
//#define ALWAYS_ON 1   //watch dog is always on
#define ONE_TIME_INTERRUPT 2   //watchdog generates an interrupt before reset
#define ONE_TIME 0    //watch dog is disabled after reset

//watchdog periods
#define WDT_8_MS		0x0ul 
#define WDT_16_MS		0x1ul
#define WDT_32_MS		0x2ul
#define WDT_64_MS		0x3ul
#define WDT_128_MS		0x4ul
#define WDT_256_MS		0x5ul
#define WDT_512_MS		0x6ul
#define WDT_1K_MS		0x7ul
#define WDT_2K_MS		0x8ul
#define WDT_4K_MS		0x9ul
#define WDT_8K_MS		0xAul
#define WDT_16K_MS		0xBul

typedef void (*voidFuncPtr)( void ) ;
static voidFuncPtr _callback2;

class wdt {
  public:
  
  
  wdt();  //constructor
  
  unsigned int wdt_period;
  
  /************************************************************************************************************************
*Description: Function responsible of WDT initialization
*Input Parameters: int mode  this parameter can be ONE_TIME (no interrupt) or ONE_TIME_INTERRUPT(early warning interrupt)
				   voidFuncPtr callback  pointer to interrupt function, Type NULL when unused
				   unsigned int wd_period  period expressed in clock cycles for watchdog
				   unsigned int int_period  period expressed in clock cycles for interrupt		
*Return Parameter: None
****************************************************************************************************************************/
void begin(int mode, voidFuncPtr callback, unsigned int wd_period, unsigned int int_period);
  
  
  /************************************************************************************************************************
*Description: This function enables watchdog
*Input Parameters: None	
*Return Parameter: None
****************************************************************************************************************************/
void enable(void);
  
  
  /************************************************************************************************************************
*Description: This function disables watchdog
*Input Parameters: None	
*Return Parameter: None
****************************************************************************************************************************/ 
void disable(void);
 
 
 
 /************************************************************************************************************************
*Description: This function sets period for watchdog
*Input Parameters: unsigned int period  this parameter express period in clock cycles
*Return Parameter: None
****************************************************************************************************************************/ 
void SetPeriod(unsigned int period);





/************************************************************************************************************************
*Description: This clear watchdog
*Input Parameters: None
*Return Parameter: None
****************************************************************************************************************************/
void reset(void);
  
  
  
};

#endif




















