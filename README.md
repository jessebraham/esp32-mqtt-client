# esp32-mqtt-client

A simple project to familiarize myself with the [Espressif IoT Development Framework](https://github.com/espressif/esp-idf/) and [MQTT](https://en.wikipedia.org/wiki/MQTT) via the [256dpi/esp-mqtt](https://github.com/256dpi/esp-mqtt) component.  

Connects to the configured wireless network and establishes a connection with the configured MQTT broker, illuminating a status LED on connection. Subscribe to a test topic, and continually publish to it.  


## Configuration

This project requires a number of configuration parameters to be set prior to building and flashing. This project assumes you have [ESP-IDF](https://github.com/espressif/esp-idf/) installed and configured as per the [instructions in their documentation](https://github.com/espressif/esp-idf/#setting-up-esp-idf).  

ESP-IDF uses [Kconfig](https://api.kde.org/frameworks/kconfig/html/index.html) for project configuration. To perform configuration, run `make menuconfig` from the project's root directory.  

### Wireless Network

The following parameters *must* be set in order to connect to the wireless network and in turn the MQTT broker.

| Parameter     | Description                                     |  
|:--------------|:------------------------------------------------|  
| **WIFI_SSID** | The SSID of the wireless network to connect to. |  
| **WIFI_PASS** | The passphrase to authenticate with.            |  

### MQTT

The following parameters are required for connecting to and interacting with the MQTT broker.

| Parameter       | Description                                    |  
|:----------------|:-----------------------------------------------|  
| **MQTT_BROKER** | The hostname of the MQTT Broker to connect to. |  
| **MQTT_PORT**   | The port that the MQTT Broker is running on.   |  
| **MQTT_USER**   | Username to authenticate with the MQTT Broker. |  
| **MQTT_PASS**   | Passphrase of the MQTT user.                   |  

### Miscellaneous

The `LED_GPIO` parameter is used to set the pin which drives the indicator LED. This LED is enabled when the device has established a connection with the MQTT broker, and disabled when the connection has been broken, or has yet to have been established.

| Parameter    | Description                                                          |  
|:-------------|:---------------------------------------------------------------------|  
| **LED_GPIO** | Set the GPIO pin for the LED, driven in an active-low configuration. |  


## Build, Flash and Monitor

When checking out the repository, be sure to use the `--recursive` flag to check out the MQTT component as well:  

```bash
$ git clone --recusive https://github.com/jessebraham/esp32-mqtt-client.git
```

To build and flash the application, run the following for the project's root directory:

```bash
$ # if you have not configured the project, now is the time to do so  
$ make menuconfig  
$ # substitute 5 for the number of cores in your system + 1, or exclude the flag
$ make -j5 flash
```

To view the status and output of the module, run:

```bash
$ make monitor
$ # use Ctrl + ] to exit monitor
```
