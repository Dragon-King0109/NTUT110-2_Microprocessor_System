#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 59
#define MODULE_NAME "LAB6demo5"

static int iCount = 0;
static char userChar[100];

static void demo_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "LAB6demo");
    printk("<1>%s: removed\n", MODULE_NAME);
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
    printk("Read: %s\n","Enter Read function");
    printk("device read\n");
    copy_from_user(userChar,buf,count);
    printk("Count: %d", count);
    printk("userChar(char): %s\n", userChar);
    printk("Read-Value: %s\n", userChar);
    return count;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{
    printk("Write: %s\n","Enter Write function");
    printk("device write\n");
    printk("%d\n",iCount);
    printk("W_buf_size: %d\n",(int)count);
    copy_from_user(userChar,buf,count);
    userChar[count - 1] = 0;
    printk("userChar(char): %s\n", userChar);
    iCount++;
    return count;
}

long drv_ioctl(struct file *filp,unsigned int cmd , unsigned long arg)
{
    printk("I/O Control: %s\n","Enter I/O Control function");
    printk("device ioctl\n");
    return 0;
}

static int drv_open(struct inode *inode , struct file *filp)
{
    printk("Open: %s\n","Enter Open function");
    printk("device open\n");
    return 0;
}

static int drv_release(struct inode *inode , struct file *filp)
{
    printk("Release: %s\n","Enter Release function");
    printk("device close\n");
    return 0;
}

struct file_operations drv_fops =
{
    read: drv_read,
    write: drv_write,
    unlocked_ioctl: drv_ioctl,
    open: drv_open,
    release: drv_release,
};

static int demo_init(void)
{
    if (register_chrdev(MAJOR_NUM, "LAB6demo", &drv_fops) < 0)
    {
        printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
        return (-EBUSY);
    }

    printk("<1>%s: started\n", MODULE_NAME);
    return 0;
}

module_init(demo_init);
module_exit(demo_exit);
