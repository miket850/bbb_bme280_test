#
# Company boilerplate headers here.
#

# std=c99 to allow for mixed declarations and code for thirdparty BME280 driver code
# Define 32bit for beaglebone black (and to try to suppress floating point operations).
#ccflags-y += -std=c99 -DBME280_32BIT_ENABLE 

# the kernel headers are installed.
ifneq ($(KERNELRELEASE),)
	obj-m := bme280_misc.o
	bme280_misc-objs := bme280_misc_drv.o thirdparty/BME280_driver/bme280.o 

else
	KERN_DIR ?= /usr/src/linux-headers-$(shell uname -r)/
	PWD := $(shell pwd)

# Build the module in-tree
default:
	$(info $$KERN_DIR is [${KERN_DIR}])
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules

endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

