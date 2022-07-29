/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#ifndef _QCOM_SYSTEM_HEAP_H
#define _QCOM_SYSTEM_HEAP_H

#include <linux/dma-heap.h>
#include <linux/err.h>
#include "qcom_dynamic_page_pool.h"

struct qcom_system_heap {
	struct device *dev;
	int uncached;
	struct dynamic_page_pool **pool_list;
	int vmid;
};

#ifdef CONFIG_QCOM_DMABUF_HEAPS_SYSTEM
int qcom_system_heap_create(char *name, bool uncached, int vmid);
struct page *qcom_sys_heap_alloc_largest_available(struct dynamic_page_pool **pools,
						   unsigned long size,
						   unsigned int max_order);
#else
struct page *qcom_sys_heap_alloc_largest_available(struct dynamic_page_pool **pools,
						   unsigned long size,
						   unsigned int max_order)
{
	return ERR_PTR(-EOPNOTSUPP);
}

static int qcom_system_heap_create(char *name, bool uncached, int vmid)
{
	return 1;
}
#endif

#endif /* _QCOM_SYSTEM_HEAP_H */
