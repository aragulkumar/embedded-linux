#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/timer.h>

#define GPIO_BASE_PHYS  0xFE200000   // RPi4 GPIO base
#define GPIO_SIZE       0xB4

#define GPIO17          17

#define GPFSEL1_OFFSET  0x04
#define GPSET0_OFFSET   0x1C
#define GPCLR0_OFFSET   0x28

static void __iomem *gpio_base;
static struct timer_list blink_timer;
static int led_state = 0;

static void blink_led(struct timer_list *t)
{
    if (led_state) {
        iowrite32(1 << GPIO17, gpio_base + GPCLR0_OFFSET);
        led_state = 0;
    } else {
        iowrite32(1 << GPIO17, gpio_base + GPSET0_OFFSET);
        led_state = 1;
    }

    mod_timer(&blink_timer, jiffies + msecs_to_jiffies(500));
}

static int __init gpio_init(void)
{
    u32 val;

    pr_info("GPIO LED Driver loaded\n");

    gpio_base = ioremap(GPIO_BASE_PHYS, GPIO_SIZE);
    if (!gpio_base)
        return -ENOMEM;

    /* Configure GPIO17 as output */
    val = ioread32(gpio_base + GPFSEL1_OFFSET);
    val &= ~(7 << 21);     // clear bits
    val |=  (1 << 21);     // set output
    iowrite32(val, gpio_base + GPFSEL1_OFFSET);

    /* Setup timer */
    timer_setup(&blink_timer, blink_led, 0);
    mod_timer(&blink_timer, jiffies + msecs_to_jiffies(500));

    return 0;
}

static void __exit gpio_exit(void)
{
    del_timer_sync(&blink_timer);
    iowrite32(1 << GPIO17, gpio_base + GPCLR0_OFFSET);
    iounmap(gpio_base);
    pr_info("GPIO LED Driver removed\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abishek");
MODULE_DESCRIPTION("RPi4 GPIO LED Blink Driver (Timer based)");
