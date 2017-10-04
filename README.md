# esp32-mqtt-client

A very simple project to introduce myself to the [Espressif IoT Framework](https://github.com/espressif/esp-idf/) and [MQTT](https://en.wikipedia.org/wiki/MQTT) using the [256dpi/esp-mqtt](https://github.com/256dpi/esp-mqtt) component.


## Configuration

A number of configuration parameters are required to build and run this project successfully. This project assumes you have the Espressif IoT Framework installed and configured as per the instructions in their documentation.

To configure the required parameters, run `make menuconfig`.

### Wireless Network Configuration

The following configuration is required for the Wirless Network connection:

**WIFI_SSID** - The SSID of the wireless network to connect to.  
**WIFI_PASS** - The passphrase to authenticate with.

### MQTT Configuration

The following configuration is required for the MQTT Broker connection:

**MQTT_BROKER** - The hostname of the MQTT Broker to connect to.  
**MQTT_PORT** - The port that the MQTT Broker is running on.  
**MQTT_USER** - Username to authenticate with the MQTT Broker.  
**MQTT_PASS** - Passphrase of the MQTT user.  
