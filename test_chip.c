#include "simple_bus.h"

struct test_chip {
	char devname[32];
	struct sb_device sdev;
};

int chip_num = 4;

struct test_chip *chipdev;

static void chip_register_dev(struct test_chip *dev, int index)
{
	snprintf(dev->devname, sizeof(dev->devname), "chip%d", index);
	memcpy(dev->sdev.name, dev->devname, 32);
	dev_set_drvdata(&dev->sdev.dev, dev);
	register_sb_device(&dev->sdev);
}

int chip_init(void)
{
	int i;

	chipdev = kmalloc(chip_num * sizeof(struct test_chip), GFP_KERNEL);
	memset(chipdev, 0, chip_num * sizeof(struct test_chip));

	for (i = 0; i < chip_num; i++) {
		chip_register_dev(chipdev + i, i);
	}

	return 0;
}

void chip_cleanup(void)
{
	int i;
	for (i = 0; i < chip_num; i++) {
		unregister_sb_device(&chipdev[i].sdev);
	}
	kfree(chipdev);
}

module_init(chip_init);
module_exit(chip_cleanup);

MODULE_AUTHOR(CONFIG_MODULE_AUTHOR);
MODULE_VERSION(CONFIG_MODULE_VERSION);
MODULE_LICENSE(CONFIG_MODULE_LICENSE);
MODULE_DESCRIPTION(CONFIG_MODULE_DESCRIPTION);
