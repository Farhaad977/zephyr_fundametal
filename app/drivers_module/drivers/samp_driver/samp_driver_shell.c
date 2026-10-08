#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "samp_driver.h"
#include "stdlib.h"

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

static int cmd_chngparam_handler(const struct shell *sh,int argc,char **argv)
{
    const struct device *dev = shell_device_get_binding(argv[1]);
    if(argc !=3)
    {
        shell_error(sh, "Usage: sensor set <node> <value 0-1000>");
        return -EINVAL;
    }

    char *end;
    long val = strtol(argv[2], &end, 10);
     if (end == argv[2] || *end != '\0') {
        shell_error(sh, "Invalid number: %s", argv[2]);
        return -EINVAL;
    }
    if (val < 0 || val > 1000) {
        shell_error(sh, "Value %ld out of range (0-1000)", val);
        return -ERANGE;
    }

    if (dev == NULL) {
        shell_error(sh, "Device %s not found", argv[1]);
        return -ENODEV;
    }

    change_param(dev, (int32_t)val);
    shell_print(sh, "Value set to %ld", val);
    return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(sub_samp_driver,
SHELL_CMD_ARG(fetch, NULL, "Executes the Sensor Sample Fetch Function", cmd_fetch_handler, 2, 0), //Will pass command and Node Name hence 2 arguments
SHELL_CMD_ARG(read, NULL, "Executes the Sensor Channel Get Function", cmd_get_handler, 2, 0),     //Will pass command and Node Name hence 2 arguments                                                                                   
SHELL_CMD_ARG(info, NULL, "Display Device Name and Ready State", cmd_info_handler, 2, 0),       //Will pass command and Node Name hence 2 arguments
SHELL_CMD_ARG(set, NULL, "Change Parameter Extension API",cmd_chngparam_handler , 3, 0),    //Will pass command and Node Name and value hence 3 arguments

SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_samp_driver, "Sensor Commands", NULL);