#include "simple_bus.h"

static int sb_match(struct device *dev, struct device_driver *drv)
{
	printk(KERN_INFO "dev name: %s, driver name: %s\n", dev_name(dev),
	       drv->name);
	return !strncmp(dev_name(dev), drv->name, strlen(drv->name));
}

struct bus_type sb_bus_type = {
	.name = "simple_bus",
	.match = sb_match,
};

static ssize_t version_show(struct bus_type *bus, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", "0.1");
}

static BUS_ATTR_RO(version);

static void sb_dev_release(struct device *dev)
{
}

int register_sb_device(struct sb_device *dev)
{
	dev->dev.bus = &sb_bus_type;
	dev->dev.release = sb_dev_release;
	dev_set_name(&dev->dev, dev->name);

	return device_register(&dev->dev);
}
EXPORT_SYMBOL(register_sb_device);

void unregister_sb_device(struct sb_device *dev)
{
	device_unregister(&dev->dev);
}
EXPORT_SYMBOL(unregister_sb_device);

static int sb_drv_probe(struct device *dev)
{
	printk(KERN_INFO "sb drv probe %s\n", dev_name(dev));
	return 0;
}

int register_sb_driver(struct sb_driver *drv)
{
	drv->driver.bus = &sb_bus_type;
	drv->driver.probe = sb_drv_probe;

	return driver_register(&drv->driver);
}
EXPORT_SYMBOL(register_sb_driver);

void unregister_sb_driver(struct sb_driver *drv)
{
	driver_unregister(&drv->driver);
}
EXPORT_SYMBOL(unregister_sb_driver);

static int __init sb_bus_init(void)
{
	int ret = bus_register(&sb_bus_type);

	if (ret) {
		printk(KERN_ERR "unable to register simple bus, return: %d\n",
		       ret);
		return ret;
	}

	if (bus_create_file(&sb_bus_type, &bus_attr_version)) {
		printk(KERN_ERR "unable to create version attribute\n", ret);
		return 0;
	}

	return 0;
}

static void sb_bus_exit(void)
{
	bus_unregister(&sb_bus_type);
}

module_init(sb_bus_init);
module_exit(sb_bus_exit);

MODULE_AUTHOR(CONFIG_MODULE_AUTHOR);
MODULE_VERSION(CONFIG_MODULE_VERSION);
MODULE_LICENSE(CONFIG_MODULE_LICENSE);
MODULE_DESCRIPTION(CONFIG_MODULE_DESCRIPTION);
