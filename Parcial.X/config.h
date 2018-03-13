
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIG_H
#define	CONFIG_H

//#include <PIC18f4550.h>
#include "globalDefinitions.h"// include processor files - each processor file is guarded.  

void configBoard(void);
void wait_in_ms(int time_in_ms);
void wait_in_us(unsigned int microseconds);

#endif	/* CONFIG_H */

