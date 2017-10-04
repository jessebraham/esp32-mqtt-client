# TODO:
# Comment me

COMPONENT_ADD_INCLUDEDIRS := include


$(call compile_only_if,$(BLINK_GPIO),esp32-mqtt-client.o)
$(call compile_only_if,$(WIFI_SSID),esp32-mqtt-client.o)
$(call compile_only_if,$(WIFI_PASS),esp32-mqtt-client.o)

$(call compile_only_if,$(MQTT_BROKER),esp32-mqtt-client.o)
$(call compile_only_if,$(MQTT_PORT),esp32-mqtt-client.o)
$(call compile_only_if,$(MQTT_USER),esp32-mqtt-client.o)
$(call compile_only_if,$(MQTT_PASS),esp32-mqtt-client.o)


include $(IDF_PATH)/make/component_common.mk
