#include <linux/device.h>

static int sb_match(struct device *dev, struct device_driver *drv)
{
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

int register_sb_driver(struct sb_device *drv)
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

static int __init sb_bus_init()
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
}

static void sb_bus_exit()
{
	bus_unregister(&sb_bus_type);
}

module_init(sb_bus_init);
module_exit(sb_bus_exit);
