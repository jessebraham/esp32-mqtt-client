# TODO:
# Comment me

$(call compile_only_if,$(BLINK_GPIO),esp32-mqtt-client.o)
$(call compile_only_if,$(SSID),esp32-mqtt-client.o)
$(call compile_only_if,$(PASSPHRASE),esp32-mqtt-client.o)
