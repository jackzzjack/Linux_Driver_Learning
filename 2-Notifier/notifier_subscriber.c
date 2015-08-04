#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/notifier.h>

#include "notifier.h"

MODULE_LICENSE("GPL");

// 取得 notify 的內容
static int notify_sys(struct notifier_block *this, unsigned long code, void *data) {
	printk("I am subscriber, %s(): code=%ld, msg=\"%s\"\n", __FUNCTION__, code, (char*) data);

	return 0;
}

static struct notifier_block notifier = {
	.notifier_call = notify_sys,	// Function Pointer
};

static int __init init_modules(void) {
	register_jack_notifier(&notifier);

	return 0;
}

static void __exit exit_modules(void) {
	unregister_jack_notifier(&notifier);
}

module_init(init_modules);
module_exit(exit_modules);
