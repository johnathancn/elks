/*
 * hello driver for ELKS kernel
 */

#include <linuxmt/kernel.h> /* printk() */
#include <linuxmt/fs.h>     /* file_operations struct */
#include <string.h>

#define HELLO_DEVICE_NAME       "hellodev"
#define HELLO_MAJOR     11

static char message[256];
char *msgptr = message;

static int hello_write(struct inode *inode, struct file *file, char* buf, int len)
{
    memcpy_fromfs(message,buf,len);
    printk("hellodev: hello_write() called\n");
    return 0;
}

static int hello_read(struct inode *inode, struct file *file, char* buf, int len)
{
    memcpy_tofs(buf, message, len);
    printk("hellodev: hello_read() called\n");
    return len;
}

static int hello_open(struct inode *inode, struct file *file)
{
    printk("hellodev: hello_open() called\n");
    return 0;
}

static void hello_release(struct inode *inode, struct file *file)
{
    printk("hellodev: hello_release() called\n");
    return;
}

static struct file_operations hello_fops = {
    NULL,                       /* lseek */
    hello_read,                 /* read */
    hello_write,                /* write */
    NULL,                       /* readdir */
    NULL,                       /* select */
    NULL,                       /* ioctl */
    hello_open,                 /* open */
    hello_release               /* release */
    
#ifdef BLOAT_FS
        ,
    NULL,                       /* fsync */
    NULL,                       /* check_media_type */
    NULL                        /* revalidate */
#endif
};

void hello_init(void)
{
        printk("hellodev: hello_init() called\n");

    /* register device */
    if (register_chrdev(HELLO_MAJOR, HELLO_DEVICE_NAME, &hello_fops))
        printk("hellodev: unable to register\n");
}
