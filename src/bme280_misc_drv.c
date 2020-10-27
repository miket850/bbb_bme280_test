/* 
 * Company boilerplate license here 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>   
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/miscdevice.h>

#include "thirdparty/BME280_driver/bme280.h"

static struct miscdevice bme280_drv_dev; /* kernel device structure */
static char *bme280_name = "bme280_misc"; /* kernel device name string */

static struct bme280_dev bme280_dev_cfg; /* device structure from thirdparty BME280 driver */
static uint8_t bme280_dev_addr = BME280_I2C_ADDR_PRIM;

ssize_t bme280_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    
    ssize_t ret = 0;

    return ret;
}

int bme280_release(struct inode *inode, struct file *filp)
{
    printk(KERN_DEBUG "process %i (%s) released %s\n", current->pid, current->comm, bme280_name);
    return 0;
}


int bme280_open(struct inode *inode, struct file *filp)
{
    int8_t ret = BME280_OK;

    bme280_dev_cfg.intf_ptr = &bme280_dev_addr;

/*
    bme280_dev_cfg.intf = BME280_I2C_INTF;
    bme280_dev_cfg.read = user_i2c_read;
    bme280_dev_cfg.write = user_i2c_write;
    bme280_dev_cfg.delay_ms = user_delay_ms;

    ret = bme280_init(&bme280_dev_cfg);
*/

    if (ret != BME280_OK)
    {
	printk(KERN_WARNING "%s: failed to open, error code %d\n", bme280_name, ret);
	return ret;
    }
    printk(KERN_DEBUG "process %i (%s) success open minor(%u) file\n", current->pid, current->comm, iminor(inode));
   
    return 0;
}

struct file_operations bme280_fops = {
    .owner =    THIS_MODULE,
    .read =     bme280_read,
    .open =     bme280_open,
};

int bme280_init_module(void)
{
    int ret;
    bme280_drv_dev.minor = MISC_DYNAMIC_MINOR;
    bme280_drv_dev.name = bme280_name;
    bme280_drv_dev.fops = &bme280_fops;
    ret = misc_register(&bme280_drv_dev);

    if (ret)
    {
	printk(KERN_WARNING "%s: failed to install, error code %d\n", bme280_name, ret);
	return ret;
    }
    printk(KERN_INFO "%s: installed to minor number %i\n", bme280_name, bme280_drv_dev.minor);
    return 0;
}

void bme280_exit_module(void)
{
    misc_deregister(&bme280_drv_dev);
}

/* Register module install and uninstall functions */
module_init(bme280_init_module);
module_exit(bme280_exit_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Milieu Labs");

