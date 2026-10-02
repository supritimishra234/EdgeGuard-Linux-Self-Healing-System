#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define DEVICE_NAME "edgeguard"

static dev_t deviceNumber;
static struct cdev edgeguard_cdev;
static struct class *edgeguard_class;

static char message[256] = "EdgeGuard driver is running.\n";

static DEFINE_MUTEX(edgeguard_mutex);

static int edgeguard_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "EdgeGuard: device opened\n");
    return 0;
}

static int edgeguard_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "EdgeGuard: device closed\n");
    return 0;
}

static ssize_t edgeguard_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    int messageLength;

    if (*offset > 0)
        return 0;

    mutex_lock(&edgeguard_mutex);

    messageLength = strlen(message);

    if (length < messageLength)
    {
        mutex_unlock(&edgeguard_mutex);
        return -EINVAL;
    }

    if (copy_to_user(buffer, message, messageLength))
    {
        mutex_unlock(&edgeguard_mutex);
        return -EFAULT;
    }

    *offset = messageLength;

    mutex_unlock(&edgeguard_mutex);

    return messageLength;
}

static ssize_t edgeguard_write(
    struct file *file,
    const char __user *buffer,
    size_t length,
    loff_t *offset)
{
    size_t copyLength;

    copyLength = length;

    if (copyLength >= sizeof(message))
        copyLength = sizeof(message) - 1;

    mutex_lock(&edgeguard_mutex);

    memset(message, 0, sizeof(message));

    if (copy_from_user(message, buffer, copyLength))
    {
        mutex_unlock(&edgeguard_mutex);
        return -EFAULT;
    }

    message[copyLength] = '\0';

    mutex_unlock(&edgeguard_mutex);

    printk(KERN_INFO "EdgeGuard: message received from user space: %s\n",
           message);

    return copyLength;
}

static struct file_operations edgeguard_fops =
{
    .owner = THIS_MODULE,
    .open = edgeguard_open,
    .release = edgeguard_release,
    .read = edgeguard_read,
    .write = edgeguard_write
};

static int __init edgeguard_init(void)
{
    int result;

    printk(KERN_INFO "EdgeGuard: driver loading\n");

    result = alloc_chrdev_region(
        &deviceNumber,
        0,
        1,
        DEVICE_NAME);

    if (result < 0)
    {
        printk(KERN_ERR "EdgeGuard: failed to allocate device number\n");
        return result;
    }

    cdev_init(&edgeguard_cdev, &edgeguard_fops);

    result = cdev_add(
        &edgeguard_cdev,
        deviceNumber,
        1);

    if (result < 0)
    {
        unregister_chrdev_region(deviceNumber, 1);
        printk(KERN_ERR "EdgeGuard: failed to add character device\n");
        return result;
    }

    edgeguard_class = class_create(DEVICE_NAME);

    if (IS_ERR(edgeguard_class))
    {
        cdev_del(&edgeguard_cdev);
        unregister_chrdev_region(deviceNumber, 1);

        printk(KERN_ERR "EdgeGuard: failed to create device class\n");

        return PTR_ERR(edgeguard_class);
    }

    if (IS_ERR(device_create(
        edgeguard_class,
        NULL,
        deviceNumber,
        NULL,
        DEVICE_NAME)))
    {
        class_destroy(edgeguard_class);
        cdev_del(&edgeguard_cdev);
        unregister_chrdev_region(deviceNumber, 1);

        printk(KERN_ERR "EdgeGuard: failed to create device\n");

        return -1;
    }

    printk(KERN_INFO "EdgeGuard: driver loaded successfully\n");
    printk(KERN_INFO "EdgeGuard: device /dev/edgeguard created\n");

    return 0;
}

static void __exit edgeguard_exit(void)
{
    device_destroy(
        edgeguard_class,
        deviceNumber);

    class_destroy(edgeguard_class);

    cdev_del(&edgeguard_cdev);

    unregister_chrdev_region(
        deviceNumber,
        1);

    printk(KERN_INFO "EdgeGuard: driver unloaded\n");
}

module_init(edgeguard_init);
module_exit(edgeguard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Supriti Mishra");
MODULE_DESCRIPTION("EdgeGuard virtual character device driver");
MODULE_VERSION("1.0");