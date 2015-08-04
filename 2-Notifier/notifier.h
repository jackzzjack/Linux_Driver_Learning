#ifndef BROOK
#define BROOK

#include <linux/notifier.h>

// register 和 unregister 都利用 wrapper function
int register_jack_notifier(struct notifier_block *nb);
int unregister_jack_notifier(struct notifier_block *nb);

enum brook_msg {
	num1,
	num2,
	num3
};

#endif
