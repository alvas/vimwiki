/*
 * hello.c
 * Copyright (C) 2021 qingyun <qingyun.oracle@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
    printk(KERN_ALERT "I bear a charmed life.\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Out, out, brief candle!\n");
}

module_init(hello_init);
module_exit(hello_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alvasli");
MODULE_DESCRIPTION("A Hello, World Module");

