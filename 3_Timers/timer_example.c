#include <linux/module.h>       // module_init, module_exit, MODULE_*
#include <linux/init.h>         // __init, __exit macros
#include <linux/kernel.h>       // printk, pr_info, ...
#include <linux/timer.h>

// Based on https://stackoverflow.com/questions/14953871/how-to-pass-custom-argument-to-linux-timers-function/
//
struct timer_with_data {
        struct timer_list timer;
        int               data;
};

// A timer is represented in the kernel as an instance of timer_list
//
static struct timer_list my_timer;
static struct timer_with_data my_timer_data ;

void my_timer_cb(struct timer_list *timer)
{
        pr_info("Timer cb: HZ = %d\n", HZ);
        pr_info("Timer cb: %s called (%ld) with argument %d.\n",
                __FUNCTION__, jiffies, timer->flags);
}

void my_timer_data_cb(struct timer_list *t) {
        struct timer_with_data *tmd = from_timer(&my_timer_data, t, timer);
        int data = tmd->data;
        pr_info("Timer data cb: received %d\n", data) ;
}

static void setup_my_timer(void)
{
        int retval;
        printk("Timer module loaded\n");
        
        // Initialize the timer with my_timer_cb callback and 0 as an arg.
        //
        timer_setup(&my_timer, my_timer_cb, 0);

        printk("Setup timer to fire in 3000ms (%ld)\n", jiffies);
        // mod_timer is equivalent to:
        // del_timer(timer);
        // timer->expires = expires;
        // add_timer(timer);    // FIRES the timer.
        retval = mod_timer(&my_timer, jiffies + msecs_to_jiffies(3000));
        if (retval) {
                pr_err("Timer firing failed\n");
        }
}

static void setup_my_timer_with_data(void)
{
        int retval = 0;

        my_timer_data.data = 2021;
        timer_setup(&(my_timer_data.timer), my_timer_data_cb, 0);
        retval = mod_timer(&(my_timer_data.timer),
                           jiffies + msecs_to_jiffies(3000));
        if (retval) {
                pr_err("Timer firing failed\n");
        }
}

static int __init my_init(void)
{

        setup_my_timer();
        setup_my_timer_with_data();

        return 0;
}

static void __exit my_exit(void)
{
        int retval;
        retval = del_timer_sync(&my_timer);
        if (retval) {
            printk("The timer is still in use...\n");
        }

        pr_info("Timer: module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Ángel Pérez <groverperezm-2000@hotmail.com>");
MODULE_DESCRIPTION("Standard timer example");
MODULE_LICENSE("GPL");
