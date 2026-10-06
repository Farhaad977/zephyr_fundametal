#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

static int cmd_fetch_handler(const struct shell *sh,int argc,char **argv)
{
    const struct device *dev = shell_device_get_binding(argv[1]);
    shell_print(sh, "Sample Fetch API called");
    sensor_sample_fetch(dev);
    return 0;
}

static int cmd_get_handler(const struct shell *sh,int argc,char **argv)
{
    const struct device *dev = shell_device_get_binding(argv[1]);
    shell_print(sh, "Sample Channel Get API called");
    struct sensor_value val;
    sensor_channel_get(dev, SENSOR_CHAN_ALL, &val);
    return 0;
}

static int cmd_info_handler(const struct shell *sh,int argc,char **argv)
{
    const struct device *dev = shell_device_get_binding(argv[1]);
    shell_info(sh, "Device Name:%s\n", dev->name);
    shell_info(sh, "Initialized State:%d", dev->state->initialized);
    return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(sub_samp_driver,
SHELL_CMD_ARG(fetch, NULL, "Executes the Sensor Sample Fetch Function", cmd_fetch_handler, 2, 0), //We will pass command and Node Name/Label hence 2 arguments
SHELL_CMD_ARG(read, NULL, "Executes the Sensor Channel Get Function", cmd_get_handler, 2, 0),     //We will pass command and Node Name/Label hence 2 arguments                                                                                   
SHELL_CMD_ARG(info, NULL, "Display Device Name and Ready State", cmd_info_handler, 2, 0),       //We will pass command and Node Name/Label hence 2 arguments
SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_samp_driver, "Sensor Commands", NULL);