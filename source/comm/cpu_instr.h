#ifndef CPU_INSIR_H
#define CPU_INSIR_H


#include"types.h"


//cli代码段
static inline void cli(void){

__asm__ __volatile__("cli");
}

// sti 代码段
static inline void sti(void){

__asm__ __volatile__("sti");
}

//
static inline uint8_t inb (uint16_t port ){
    uint8_t rv;
    __asm__ __volatile__("inb %[p], %[v]":[v]"=a"(rv): [p]"d"(port));
    return rv;

}

static inline uint16_t inw (uint16_t port ){
    uint16_t rv;
    __asm__ __volatile__("in %[p], %[v]":[v]"=a"(rv): [p]"d"(port));
    return rv;

}

static inline void outb(uint16_t port ,uint8_t date){
    __asm__ __volatile__("outb %[v], %[p]"::[p]"d"(port),[v]"a"(date));


}

//inter的手册代码加载的数据的地址和大小在哪里。
static inline  void lgdt(uint32_t start,uint32_t size){
    struct {

        uint16_t limit;
        uint16_t start15_0;
        uint16_t start31_16;

    }gdt;
    gdt.start31_16=start>>16;
    gdt.start15_0=start&0XFFFF;
    gdt.limit=size-1;
    {
        /* data */
    };
    
    __asm__ __volatile("lgdt %[g]"::[g]"m"(gdt));
} 



static inline uint16_t read_cr0(void){
    uint32_t cr0;
    __asm__ __volatile__("mov %%cr0, %[v]":[v]"=r"(cr0));
    return cr0;



}


static inline void write_cr0(uint32_t v){
      __asm__ __volatile__("mov %[v],%%cr0"::[v]"r"(v));

}
static inline void far_jump(uint16_t selector, uint32_t offset){
     
     
     uint32_t addr[]={offset,selector};

     __asm__ __volatile__("ljmpl *(%[a])"::[a]"r"(addr));





}
#endif