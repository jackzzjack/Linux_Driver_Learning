#include <linux/kernel.h> /* pr_info 所需 include 檔案*/
#include <linux/init.h>
#include <linux/module.h> /* 所有 module 需要檔案*/
#include <linux/version.h>
#include <linux/netfilter_bridge.h>
#include <linux/random.h>
#include <linux/ip.h>
#include <linux/string.h>
#include <linux/time.h>

static unsigned int switch_hook_forward(
	unsigned int hook,
	struct sk_buff* skb,
	const struct net_device *dev_in,
	const struct net_device *dev_out,
	int (*okfn)(struct sk_buff *))
{
	unsigned int result = NF_DROP;
	//unsigned int result = NF_ACCEPT;
	return result;
}

static struct nf_hook_ops switch_hooks[] __read_mostly = {{
	.hook	= switch_hook_forward,
	.owner	= THIS_MODULE,
	.pf	= NFPROTO_BRIDGE,
	.hooknum= NF_BR_FORWARD,
	.priority = NF_BR_PRI_FILTER_BRIDGED,
}};
 
MODULE_DESCRIPTION("Switch Test");
MODULE_AUTHOR("Yu-Ting, Kao");
MODULE_LICENSE("GPL");
 
static int __init switch_init(void)
{
    printk("Switch init\n");
    
    if (nf_register_hooks(switch_hooks,
			ARRAY_SIZE(switch_hooks)) < 0) {
        printk("[switch] register hooks: failure.\n");
    } else {
        printk("[switch] register hooks: success.\n");
    }

    return 0;
}
 
static void __exit switch_exit(void)
{
    nf_register_hooks(switch_hooks,
			ARRAY_SIZE(switch_hooks));

    printk(KERN_INFO "Goodbye\n");
}
 
module_init(switch_init);
module_exit(switch_exit);
