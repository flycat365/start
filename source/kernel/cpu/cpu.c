#include"cpu/cpu.h"
#include "os_cfg.h"


static segment_desc_t gdt_table[GDT_TABLE_SIZE];

//selector
void segment_desc_set (int selector,uint32_t base,uint32_t limit, uint16_t attr){
    segment_desc_t *desc=gdt_table +selector/sizeof(segment_desc_t);
     desc->limit15_0=limit &0xFFFF;
     desc->base15_0=base & 0xFFFF;
     desc->base23_16=(base>>16)&0xFF;
     desc->attr =attr|(((limit>>16)&0xF)<<8);
     desc->base31_24=(base>>24)&0xFF;




}

void init_gdt(){
    for(int i=0;i<GDT_TABLE_SIZE;i++){
        segment_desc_set(i*sizeof(segment_desc_t),0,0,0);//左移三



    }


}
void   cpu_init(void){
    init_gdt();
    


}


