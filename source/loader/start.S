/**
 * 自己动手写操作系统
 *

 */

  	// 16位代码，务必加上
  	.code16
 	.text
	.global _start
	.extern loader_entry
_start:

	mov $0xe, %ah
	mov $' ', %al
	int $0x10 
	
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

	jmp  loader_entry
	
	.code32
	.text  
	.global protect_mode_entry
	.extern load_kernel
protect_mode_entry:
	mov $16, %ax
	mov %ax, %dx
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	jmp $8, $load_kernel
