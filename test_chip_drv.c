#include "simple_bus.h"

static struct sb_driver simple_bus_driver = {
	.driver = { .name = "chip" },
};

int test_chipdrv_init(void)
{
	return register_sb_driver(&simple_bus_driver);
}

void test_chipdrv_cleanup(void)
{
	unregister_sb_driver(&simple_bus_driver);
}

module_init(test_chipdrv_init);
module_exit(test_chipdrv_cleanup);

MODULE_AUTHOR(CONFIG_MODULE_AUTHOR);
MODULE_VERSION(CONFIG_MODULE_VERSION);
MODULE_LICENSE(CONFIG_MODULE_LICENSE);
MODULE_DESCRIPTION(CONFIG_MODULE_DESCRIPTION);
