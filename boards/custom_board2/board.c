#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/dt-bindings/clock/mcux_lpc_syscon_clock.h>
#include <stddef.h>
#include <stdarg.h>
#include <inttypes.h>
#include <zephyr/toolchain.h>

void board_early_init_hook(void)
{
	printk("Board Initialized\n");
}
