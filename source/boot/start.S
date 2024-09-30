/**
 * 自己动手写操作系统
 *

 */
	#include "boot.h"

  	// 16位代码，务必加上
  	.code16
 	.text
	.global _start
	.extern boot_entry
_start:
	mov $0, %ax
	mov %ax, %dx
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	mov $_start, %esp

	

	mov $0xe, %ah
	mov $'T', %al
	int $0x10 

	mov $0xe, %ah
	mov $'Y', %al
	int $0x10 

	mov $0xe, %ah
	mov $' ', %al
	int $0x10 

	mov $0xe, %ah
	mov $'i', %al
	int $0x10 

	mov $0xe, %ah
	mov $'s', %al
	int $0x10 
	                                                                                                                
	mov $0xe, %ah
	mov $' ', %al
	int $0x10 

	mov $0xe, %ah
	mov $'s', %al
	int $0x10 

	mov $0xe, %ah
	mov $'b', %al
	int $0x10 
read_loader:
	mov $0x8000, %bx
	mov $0x2, %ah
	mov $0x2, %cx
	mov $64, %al
	mov $0x0080, %dx
	int $0x13
	jc read_loader

	jmp  boot_entry
	
	jmp .
	// 引导结束段
	.section boot_end, "ax"
boot_sig: .byte 0x55, 0xaa
