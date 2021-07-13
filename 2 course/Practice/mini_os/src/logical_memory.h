//
// Logical memory management
// Developed by: Maxim Gavrilov, Yury Loshmanov, Alexey Pleshkov
//


#include "isr.h"


void do_page_fault(registers_t regs);
void init_logical_memory();
