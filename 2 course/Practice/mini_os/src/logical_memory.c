//
// Logic memory management
// Developed by: Maxim Gavrilov, Yury Loshmanov, Alexey Pleshkov
//


#include "logical_memory.h"

void init_logical_memory() {
    register_interrupt_handler(0xE, &do_page_fault);
}
