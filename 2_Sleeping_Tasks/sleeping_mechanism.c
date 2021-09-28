#include <linux/module.h>       // module_init, module_exit, MODULE_*
#include <linux/init.h>         // __init, __exit macros
#include <linux/sched.h>
#include <linux/delay.h>        // msleep
#include <linux/workqueue.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq);  // Static declare of wait queue.
static int condition = 0;
static struct work_struct wrk;          // work_queue

static void work_handler(struct work_struct *work)
{
    printk("Work handler: begin %s\n", __FUNCTION__);
    msleep(5000);
    printk("Work handler: wake up from waitqueue %s\n", __FUNCTION__);

    condition = 1;
    wake_up_interruptible(&my_wq);
}

static int __init my_init(void)
{
    printk("Wait queue example\n"); 
 
    INIT_WORK(&wrk, work_handler); 
    schedule_work(&wrk); 
 
    printk("Init: Going to sleep %s\n", __FUNCTION__); 
    wait_event_interruptible(my_wq, condition != 0); 
 
    pr_info("Init: woken up by the work job\n"); 
    return 0; 
}

void my_exit(void)
{
    printk("waitqueue example cleanup\n");
}


module_init(my_init);
module_exit(my_exit);
MODULE_DESCRIPTION("Moves job to waitqueue and is woken up by a worker in 5 secs");
MODULE_AUTHOR("Ángel Pérez <groverperezm-2000@hotmail.com>");
MODULE_LICENSE("GPL");
