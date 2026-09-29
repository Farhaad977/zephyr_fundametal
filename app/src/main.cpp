#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(main,LOG_LEVEL_INF);

const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(sled)); //Here the *dev will the address of the struct dev that gets created when we use DEVICE_DT_INST_DEFINE(...)
int main(void){

    if(!device_is_ready(dev)) 
    {
        return -1;        //Need to include the <zephyr/drivers/device.h> 
    }

    struct sensor_value val;         
    while(1)                           
    {
        sensor_sample_fetch(dev);                                       //Calling a Generic API where we pass in the custom
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        sensor_channel_get(dev, SENSOR_CHAN_ALL,&val);        //Calling a Generic API where we pass in the custom
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS); 
    }
    return 0;
}