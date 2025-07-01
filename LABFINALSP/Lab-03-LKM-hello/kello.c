//-----------------------------------------------------------------
//	kello.c
//
//	This kernel module outputs a brief message to the console.
//
//		compile using: $ mmake hello 
//		install using: $ /sbin/insmod hello.ko
//
//-----------------------------------------------------------------
// hello_lkm.c
#include <linux/module.h>    // Needed by all modules
#include <linux/kernel.h>    // Needed for KERN_INFO
#include <linux/init.h>      // Needed for the macros

static int __init hello_init(void) {
    printk(KERN_INFO "\n   Hello, everybody! \n\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "\n   Goodbye now... \n\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Hello World LKM");

module_init(hello_init);
module_exit(hello_exit);

// #include <linux/module.h>		// for printk()

// int init( void )
// {
// 	printk( "\n   Kello, everybody! \n\n" );

// 	return	0;
// }

// void exit( void )
// {
// 	printk( "\n   Goodbye now... \n\n" );
// }

// MODULE_LICENSE("GPL");
// module_init(init);
// module_exit(exit);

