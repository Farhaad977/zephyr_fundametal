#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "samp_driver.h"

#define DT_DRV_COMPAT samp_driver      //So that the DEVICE_* and DT_* macros know which compatible="..." we are using 

LOG_MODULE_REGISTER(samp_driver,LOG_LEVEL_INF); //We register 1 time for entire module.

struct my_config{
    struct gpio_dt_spec led;
};

struct my_data{
    uint32_t val;
};

void change_param(const struct device *dev, int32_t val)    //API to read the changed Mutable Data value
{
    struct my_data *dat = dev->data;
    dat->val = val;
    LOG_INF("Data Value:%d",dat->val);
}

void read_param(const struct device *dev)           //API to read the Mutable Data value
{
    struct my_data *dat = dev->data;
    LOG_INF("Data Value:%d",dat->val);
}

static int sens_samp_fetch_myimpl(const struct device *dev,enum sensor_channel chan){           //Our own function 
    LOG_INF("Sensor Fetch from Channel %d",chan);                                      //where we typecast the dev->config and dev->data
    struct my_data *dat = dev->data;                                                       //setting the gpio pin as HIGH
    const struct my_config *conf = dev->config;                                             //writing that value in the dev->data value data member 
    gpio_pin_set_dt(&conf->led, 1);
    dat->val = 1;
    return 0;
}

static int sens_channel_get_myimpl(const struct device *dev,enum sensor_channel chan,struct sensor_value *val){         //Our own function 
    LOG_INF("Sensor Get from Channel %d",chan);                                                                    //where we typecast the dev->config and dev->data
    struct my_data *dat= dev->data;                                                                                    //setting the gpio pin as HIGH                                                                                       
    val->val1 = dat->val;                                                                                              //writing that value in the dev->data value data member

    const struct my_config *conf = dev->config;
    gpio_pin_set_dt(&conf->led, 0);
    dat->val = 0;
    return 0;
}

static DEVICE_API(sensor, custom)={
    .sample_fetch = sens_samp_fetch_myimpl,
    .channel_get = sens_channel_get_myimpl
};

static int init_func(const struct device *dev){
    LOG_INF("Device Initialized");
    const struct my_config *conf = dev->config;
    if(!gpio_is_ready_dt(&conf->led)) return -ENODEV;
    gpio_pin_configure_dt(&conf->led, GPIO_OUTPUT_INACTIVE);
    return 0;
}

//Below we have created a Macro to automate instanciating of instances which includes(the data struct(mutable), config struct(constant))

#define SAMPLE_DRIVER(inst)     \
    static struct my_data data_##inst;  \
    static const struct my_config config_##inst={    \
        .led = GPIO_DT_SPEC_INST_GET(inst, gpios), \
    };                                                  \
    DEVICE_DT_INST_DEFINE(inst,init_func,NULL,&data_##inst,&config_##inst,POST_KERNEL,10,&custom);  \

DT_INST_FOREACH_STATUS_OKAY(SAMPLE_DRIVER);