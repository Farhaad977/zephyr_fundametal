add_subdirectory_ifdef(CONFIG_SAMP_DRIVER drivers/samp_driver)
if(CONFIG_SHELL)
    target_sources(app PRIVATE drivers/samp_driver/samp_driver_shell.c)
endif()