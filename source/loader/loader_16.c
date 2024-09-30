__asm__(".code16gcc");
#include"loader.h"

  boot_info_t boot_info;

static void show_msg(const char * msg){
    char c;
while((c=*msg++)!='\0'){
    asm(
    "mov $0xe, %%ah\n\t"
    "mov %[ch], %%al\n\t"
    "int $0x10"::[ch]"r"(c)
    );}
   


}

static void detect_memory(void){
uint32_t contID=0;
SMAP_entry_t smap_entry;
uint32_t signature, bytes;
show_msg("try to detect meomery");


boot_info.ram_region_count=0;
for(int i=0;i<BOOT_RAM_REGION_MAX;i++){
    SMAP_entry_t*entry=&smap_entry;

     __asm__ __volatile__(
            "int $0x15" 
            :"=a"(signature), "=c"(bytes), "=b"(contID)
            :"a"(0xE820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(entry)
        );
    if (signature != 0x534D4150 || bytes == 0){
            show_msg("fail in losder_16.c\r\n");

            return;
        }
    if(bytes>20&&(entry->ACPI & 0x0001==0)){


        continue;
    }


    if(entry->Type==1){

        boot_info.ram_region_cfg[boot_info.ram_region_count].start=entry->BaseL;
        
        boot_info.ram_region_cfg[boot_info.ram_region_count].size=entry->LengthL;

        boot_info.ram_region_count++;
    }
         
    if(contID==0){

        break;
    }





    }
    show_msg("ok");

}
//配置数组gdt表
//x86系统架构分段存储和分页存储，这里是用二维数组给的一种描述形式，通过gdt表访问内春
//gdt结构表分为三类基地址和界限和属性值
uint16_t gdt_table[][4]={


    {0,0,0,0},
    {0xFFFF,0X0000,0X9a00,0x00cf},
    {0xFFFF,0x0000,0x9200,0x00cf},
};




//关中断
static void enter_protect_mode(void){

    cli();
    
    uint8_t v=inb(0x92);
    outb(0x92,v|0x2);

    lgdt((uint32_t)gdt_table,sizeof(gdt_table));
    
    uint32_t cr0=read_cr0();
    
    write_cr0(cr0|(1<<0));

    far_jump(8, (uint32_t)protect_mode_entry);

}

void loader_entry(void){
show_msg(".....\n\r");
detect_memory();
enter_protect_mode();
for(;;){}


}