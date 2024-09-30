#include"init.h"
#include "comm/boot_info.h"
#include "cpu/cpu.h"

//注释的是测试代码


//  int global_var =0x1234;
//  int global_var_zero;
//  static int static_global_var=0x2345;
//  static int stayic_global_var_zero;


//  const int const_int =0x33;
//  const char *str="abcdrfg";
void kernel_init(boot_info_t *boot_info){
    // int local_var;
    // static int static_local_var=0x33;
    // static int static_local_var_zero;
    cpu_init();


    }