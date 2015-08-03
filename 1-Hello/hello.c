#include <linux/kernel.h> /* pr_info 所需 include 檔案*/
#include <linux/init.h>
#include <linux/module.h> /* 所有 module 需要檔案*/
#include <linux/version.h>
 
MODULE_DESCRIPTION("Hello World !!");
MODULE_AUTHOR("Bo-Yi Wu <appleboy.tw AT gmail.com>");
MODULE_LICENSE("GPL");
 
static int __init hello_init(void)
{
    printk("Hello, world\n");
    
return 0;
}
 
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye\n");
}
 
module_init(hello_init);
module_exit(hello_exit);
