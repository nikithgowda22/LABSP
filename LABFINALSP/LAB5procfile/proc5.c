#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

#define PROC_FILENAME "task_details"

static struct proc_dir_entry *proc_file_entry;

static ssize_t proc_file_read(struct file *file, char __user *user_buffer, size_t count, loff_t *position) {
    struct task_struct *task;
    char buffer[1000];
    char *buf_ptr = buffer;
    int len = 0;

    for_each_process(task) {
      if( len < (sizeof(buffer) - 50)){
        len += snprintf(buf_ptr + len, sizeof(buffer) - len,
                        "PID: %d, Name: %s\n",
                        task->pid, task->comm);
    }}

    if (copy_to_user(user_buffer, buffer, len)) {
        return -EFAULT;
    }

    return len;
}

static const struct proc_ops proc_file_fops = {
    .proc_read = proc_file_read,
};

static int __init task_details_lkm_init(void) {
    proc_file_entry = proc_create(PROC_FILENAME, 0, NULL, &proc_file_fops);
    if (!proc_file_entry) {
        printk(KERN_ERR "Failed to create proc file\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Proc file created\n");
    return 0;
}

static void __exit task_details_lkm_exit(void) {
    if (proc_file_entry) {
        remove_proc_entry(PROC_FILENAME, NULL);
        printk(KERN_INFO "Proc file removed\n");
    }
}

module_init(task_details_lkm_init);
module_exit(task_details_lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM for printing task details in a proc file");

