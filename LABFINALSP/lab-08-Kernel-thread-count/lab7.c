#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM to list all kernel threads (task->mm == NULL)");
MODULE_VERSION("1.0");

static int __init list_kernel_threads_init(void) {
    struct task_struct *task;
    int count = 0;

    printk(KERN_INFO "Listing kernel threads (task->mm == NULL):\n");

    for_each_process(task) {
        if (task->mm == NULL) {
            printk(KERN_INFO "PID: %d\tName: %s\n", task->pid, task->comm);
            count++;
        }
    }

    printk(KERN_INFO "Total number of kernel threads: %d\n", count);

    return 0;
}

static void __exit list_kernel_threads_exit(void) {
    printk(KERN_INFO "Kernel thread listing module unloaded.\n");
}

module_init(list_kernel_threads_init);
module_exit(list_kernel_threads_exit);
