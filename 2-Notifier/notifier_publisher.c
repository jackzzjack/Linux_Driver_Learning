#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

// 需要額外引入 slab.h (for kzalloc)
#include <linux/slab.h>

#include "notifier.h"

MODULE_LICENSE("GPL");

// 建立 Noifier List 的 Head
BLOCKING_NOTIFIER_HEAD(notifier_list);

// 訂閱 notifier_list 事件的 wrapper function
int register_notifier(struct notifier_block *nb) {
    return blocking_notifier_chain_register(&notifier_list, nb);
}
EXPORT_SYMBOL(register_notifier);

// 取消訂閱 notifier_list 事件的 wrapper function
int unregister_notifier(struct notifier_block *nb) {
    return blocking_notifier_chain_unregister(&notifier_list, nb);
}
EXPORT_SYMBOL(unregister_notifier);

// procfs 的 write function
static int write_proc(struct file *filp, const char __user *buf,
                               unsigned long count, void *data) {
    char *p = (char *) kzalloc(sizeof(char) * count, GFP_KERNEL);
    if (!p) {
        printk("no mem\n");
        return -ENOMEM;
    }
    if (copy_from_user(p, buf, count)) {
        printk("fault\n");
        return -EFAULT;
    }
    printk("%s(): msg=\"%s\"\n", __FUNCTION__, p);

    // 將事件 published 給 notifier_list 的 subscriber
    blocking_notifier_call_chain(&notifier_list, num1, (void*)p);
    kfree(p);
    return count;
}

static const struct file_operations test_fops = {
	.write = write_proc,
};

static int __init init_modules(void) {
    struct proc_dir_entry *ent;

/* create_proc_entry 在新版的 Kernel 已不被支援
 * 取而代之的是 proc_create，差異在再新增了第四個參數
 */
    ent = proc_create("notifier", S_IFREG | S_IWUSR, NULL, &test_fops);
    if (ent == NULL)
	return -ENOMEM;

    printk("Init notifier.");

    return 0;
}

static void __exit exit_modules(void) {
    remove_proc_entry("notifier", NULL);

    printk("Exit notifier.");
}

module_init(init_modules);
module_exit(exit_modules);
