#ifndef BROOK
#define BROOK

#include <linux/notifier.h>

int register_notifier(struct notifier_block *nb);
int unregister_notifier(struct notifier_block *nb);

enum brook_msg {
	num1,
	num2,
	num3
};
#endif
