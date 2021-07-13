#include "descriptor_tables.h"
#include "logical_memory.h"
#include "monitor.h"


struct multiboot;


int main(struct multiboot *mboot_ptr) {
    init_descriptor_tables();
    monitor_clear();


    initialise_paging();
    init_logical_memory();

    monitor_write("referencing \"c\" at uninitalised address: ");
    int* c = 0x10ffff;
// fault:        int* c = 0xc10ffff;
// non-fault:    int* c = 0xc100fff;
    monitor_write_hex(c);
    monitor_write("\n (page_fault expected)\n");
    
    *c = 11; 

    monitor_write("*c: ");
    monitor_write_dec(*c);
    monitor_write("\n");
   

    monitor_write("referencing \"d\" at impossible address: ");
    int* d = 0xffff10ffff;
    monitor_write_hex(d);
    monitor_write("\n (terminating page_fault expected)\n");
    
    *d = 11; 

    return 0;
}
