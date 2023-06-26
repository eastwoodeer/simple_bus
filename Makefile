MODULE_NAME		:= simple_bus
MODULE_LICENSE		:= GPL
MODULE_VERSION		:= 0.1
MODULE_AUTHOR		:= Chen Bin <chen.bin11@zte.com.cn>
MODULE_DESCRIPTION	:= simple bus test

ifneq ($(KERNELRELEASE),)
obj-m			:= $(MODULE_NAME).o

name-fix   = $(squote)$(quote)$(subst $(comma),_,$(subst -,_,$1))$(quote)$(squote)
ccflags-y += -DCONFIG_MODULE_AUTHOR=$(call name-fix,$(MODULE_AUTHOR))
ccflags-y += -DCONFIG_MODULE_VERSION=$(call name-fix,$(MODULE_VERSION))
ccflags-y += -DCONFIG_MODULE_DESCRIPTION=$(call name-fix,$(MODULE_DESCRIPTION))
ccflags-y += -DCONFIG_MODULE_LICENSE=$(call name-fix,$(MODULE_LICENSE))
else
PWD			:= $(shell pwd)
KERNEL_HEAD		:= $(shell uname -r)
KERNEL_DIR		:= /lib/modules/$(KERNEL_HEAD)/build

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

install:
	sudo insmod $(MODULE_NAME).ko

remove:
	sudo rmmod $(MODULE_NAME)

endif
