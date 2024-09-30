
#include"loader.h"
#include <stddef.h>
#include "comm/elf.h"
#define SECTOR_SIZE 512
#define PORT_1F2 0x1F2
#define PORT_1F3 0x1F3
#define PORT_1F4 0x1F4
#define PORT_1F5 0x1F5
#define PORT_1F6 0x1F6
#define PORT_1F7 0x1F7
//读取磁盘扇区

static void read_disk(uint32_t sector, uint32_t sector_count, uint8_t *buf) {
    if (buf == NULL || sector_count == 0) return;

    outb(PORT_1F6, 0xE0);

    outb(PORT_1F2, sector_count >> 8);
    outb(PORT_1F3, sector >> 24);
    outb(PORT_1F4, 0);
    outb(PORT_1F5, 0);

    outb(PORT_1F2, sector_count);
    outb(PORT_1F3, sector);
    outb(PORT_1F4, sector >> 8);
    outb(PORT_1F5, sector >> 16);

    outb(PORT_1F7, 0x24);
    uint16_t *data_buf = (uint16_t *)buf;
    while (sector_count--) {
        while ((inb(PORT_1F7) & 0x88) != 0x08) {}

        for (int i = 0; i < SECTOR_SIZE / 2; i++) {
            *data_buf++ = inw(0x1F0);
        }
    }
}
//内存载入
static uint32_t reload_elf_file(uint8_t *file_buffer){
    Elf32_Ehdr *elf_hdr=(Elf32_Ehdr*)file_buffer;
    if((elf_hdr->e_ident[0]!=0x7F) || (elf_hdr->e_ident[1] !='E')
     ||(elf_hdr->e_ident[2]!='L')||(elf_hdr->e_ident[3]!='F')){




        return 0;
     }
     for(int i=0;i<elf_hdr->e_phnum;i++){

        Elf32_Phdr*phdr=(Elf32_Phdr*)(file_buffer+elf_hdr->e_phoff)+i;
        if(phdr->p_type!=PT_LOAD){


            continue;
        }
    uint8_t *src=file_buffer+phdr->p_offset;
    uint8_t *dest=(uint8_t*)phdr->p_paddr;
    for(int j=0;j<phdr->p_filesz;j++){




        *dest++=*src++;
    }

    dest=(uint8_t*)phdr->p_paddr+phdr->p_filesz;

    for(int j=0;j<phdr->p_memsz-phdr->p_filesz;j++){


        *dest++=0;
    }



     }
     return elf_hdr->e_entry;

}
static void dile(int code){



    for(;;){

    }
}
void load_kernel(void){

    read_disk(100 ,500 ,(uint8_t*)SYS_KERNEL_LOAD_ADDR); //这里500太小内核会不够
    uint32_t kernel_entry=reload_elf_file((uint8_t*)SYS_KERNEL_LOAD_ADDR);
    if (kernel_entry==0){



        dile(-1);
    }

    ((void(*)(boot_info_t*))kernel_entry)(& boot_info);



    // for(;;){


        
    // }
}