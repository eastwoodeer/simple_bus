#ifndef SIMPLE_BUS_H
#define SIMPLE_BUS_H

#include <linux/device.h>
#include <linux/slab.h>

struct sb_device {
	char name[32];
	struct device dev;
};

struct sb_driver {
	struct device_driver driver;
};

int register_sb_device(struct sb_device *dev);
void unregister_sb_device(struct sb_device *dev);

int register_sb_driver(struct sb_driver *drv);
void unregister_sb_driver(struct sb_driver *drv);

#endif /* SIMPLE_BUS_H */
