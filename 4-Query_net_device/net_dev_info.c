#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

MODULE_DESCRIPTION("Net Dev Info");
MODULE_AUTHOR("Yu-Ting");
MODULE_LICENSE("GPL");

static int __init info_init(void) {
	struct net_device* n = dev_get_by_name(&init_net, "eth0");

	if (n == NULL) {
		printk(KERN_ALERT "n is NULL");
	} else {
		printk(KERN_ALERT "eth0 name: %s\n", n->name);
	}

	printk(KERN_ALERT "info_init");

	return 0;
}

static void __exit info_exit(void) {
	printk(KERN_ALERT "info_exit");
}

module_init(info_init);
module_exit(info_exit);

