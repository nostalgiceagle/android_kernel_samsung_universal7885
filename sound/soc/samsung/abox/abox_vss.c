/* sound/soc/samsung/abox/abox_vss.c
 *
 * ALSA SoC Audio Layer - Samsung Abox VSS driver
 *
 * Copyright (c) 2016 Samsung Electronics Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/* #define DEBUG */
#include <linux/device.h>
#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/shm_ipc.h>
#include <linux/io.h>

#include "abox.h"

#include <linux/stub_logs.h>

#define VSS_MAGIC_OFFSET (0x600000)

static int samsung_abox_vss_probe(struct platform_device *pdev)
{
	if (IS_ENABLED(CONFIG_SHM_IPC)) {
		void __iomem *magic_addr = phys_to_virt(shm_get_phys_base() +
				shm_get_cp_size() + VSS_MAGIC_OFFSET);

		dev_dbg(&pdev->dev, "%s\n", __func__);
		writel(0, magic_addr);
	} else
		dev_info(&pdev->dev, "%s(shm is disabled)\n", __func__);

	return 0;
}

static int samsung_abox_vss_remove(struct platform_device *pdev)
{
	dev_dbg(&pdev->dev, "%s\n", __func__);
	return 0;
}

static const struct of_device_id samsung_abox_vss_match[] = {
	{
		.compatible = "samsung,abox-vss",
	},
	{},
};
MODULE_DEVICE_TABLE(of, samsung_abox_vss_match);

static struct platform_driver samsung_abox_vss_driver = {
	.probe  = samsung_abox_vss_probe,
	.remove = samsung_abox_vss_remove,
	.driver = {
		.name = "samsung-abox-vss",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(samsung_abox_vss_match),
	},
};

module_platform_driver(samsung_abox_vss_driver);

MODULE_AUTHOR("Gyeongtaek Lee, <gt82.lee@samsung.com>");
MODULE_DESCRIPTION("Samsung ASoC A-Box VSS Driver");
MODULE_ALIAS("platform:samsung-abox-vss");
MODULE_LICENSE("GPL");
