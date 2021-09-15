#include <linux/init.h>         // __init, __exit macros
#include <linux/module.h>       // module_init, module_exit, MODULE_*
#include <linux/kernel.h>       // printk, pr_info
#include <linux/moduleparam.h>  // module_param, MODULE_PARM_*

#define BUF_LEN (81)

/*
 * Module parameters:
 */
static char name [BUF_LEN];
static int  age;

// NOTE:  module_param_array    is used for pointers.
//        module_param          with charp type is for char pointers.
//        module_param_string   for character arrays you supply.
module_param_string(name, name, BUF_LEN, S_IRUGO|S_IWUSR);
module_param(age, int, S_IRUGO|S_IWUSR);

MODULE_PARM_DESC(name, "The name of the module executor");
MODULE_PARM_DESC(age, "The age of the module executor");

/*
 * __init places the code in the .init.text section of the kobject.
 * Take a look at `objdump -h helloworld.ko` output.
 */
static int __init helloworld_init (void)
{
        pr_info("Hello world!\n");
        printk(KERN_INFO "My name is %s and I am %d years old\n", name, age);
        return 0;
}

/*
 * __exit places the code in the .exit.text section.
 */
static void __exit helloworld_exit (void)
{
        pr_info("End of the world\n");
}

// indicates the function to be called when the module is loaded (insmod or
// modprobe)
module_init(helloworld_init);
// indicates the functino to be called when the module is unloaded (rmmod)
module_exit(helloworld_exit);


/*
 * The following values will be stored at the .modinfo section.
 * Dump the contents with `objdump helloworld.ko -d -j .modinfo`
 * or `modinfo helloworld.ko`.
 */
MODULE_DESCRIPTION("Prints messages when the module is loaded and unloaded.");
MODULE_AUTHOR("Ángel Pérez <groverperezm-2000@hotmail.com>");
MODULE_LICENSE("GPL");
