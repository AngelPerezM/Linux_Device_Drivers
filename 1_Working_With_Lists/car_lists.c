#include <linux/init.h>         // __init, __exit macros
#include <linux/module.h>       // module_init, module_exit, MODULE_*
#include <linux/kernel.h>       // printk, pr_info
#include <linux/moduleparam.h>  // module_param, MODULE_PARM_*
#include <linux/list.h>
#include <linux/string.h>
#include <linux/slab.h>         // kmalloc()

struct car {
        int   n_doors;
        char  color [81];
        char  model [81];
        /* 
         * Now, with the `list` component, we can create list of `car`s
         */
        struct list_head list;
};

// Static method of initialization:
//
static LIST_HEAD(carlist);  // static list_head carlist = {.prev = carlist,
                            //                             .next = carlist}
struct car *redcar;
struct car *bluecar;
struct car *pinkcar;

static void fill_car_list (void)
{
        redcar  = kmalloc(sizeof(*redcar ), GFP_KERNEL);
        bluecar = kmalloc(sizeof(*bluecar), GFP_KERNEL);
        pinkcar = kmalloc(sizeof(*pinkcar), GFP_KERNEL);

        strcpy(redcar->color,  "Red");
        strcpy(bluecar->color, "Blue");
        strcpy(pinkcar->color, "Pink");
        
        // Dynamic method of initialization:
        INIT_LIST_HEAD(&(redcar->list));
        INIT_LIST_HEAD(&(bluecar->list));
        INIT_LIST_HEAD(&(pinkcar->list));

        // Can be used to implement a stack (LIFO):
        list_add(&(redcar->list), &carlist);
        list_add(&(bluecar->list), &carlist);
        
        // Can be used to implement a queue (FIFO):
        list_add_tail(&(pinkcar->list), &carlist);

        // | bluecar | redcar | pinkcar |
}

static void freeup_car_list (void)
{
        list_del(&redcar->list);
        list_del(&bluecar->list);
        list_del(&pinkcar->list);

        kfree(redcar); 
        kfree(bluecar); 
        kfree(pinkcar); 
}

static void traverse_car_list(void)
{
        struct car *c;
        int i = 0;

        list_for_each_entry(c, &carlist, list) {
                pr_info("Car %d: %s\n", i, c->color);
                i++;
        }
}

static int __init lists_init (void)
{       
        pr_info("Lists init function.\n"
                "Adding the elements to list\n");
        fill_car_list();
        traverse_car_list();

        return 0;
}

static void __exit lists_exit (void)
{
        pr_info("Destroyink list and freeing up allocated mem.\n");
        freeup_car_list();
}

module_init(lists_init);
module_exit(lists_exit);


MODULE_DESCRIPTION("Prints messages when the module is loaded and unloaded.");
MODULE_AUTHOR("Ángel Pérez <groverperezm-2000@hotmail.com>");
MODULE_LICENSE("GPL");
