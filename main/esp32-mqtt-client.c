#include <stdio.h>

#include "freertos/event_groups.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"


// Run 'make menuconfig' to define the following values.
#define BLINK_GPIO CONFIG_BLINK_GPIO
#define SSID       CONFIG_SSID
#define PASSPHRASE CONFIG_PASSPHRASE


static EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;


static void
initialise_wifi(void)
{
    // Disable wifi driver logging
    esp_log_level_set("wifi", ESP_LOG_NONE);

    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void
wifi_connect(void)
{
    wifi_config_t cfg = {
        .sta = {
            .ssid     = SSID,
            .password = PASSPHRASE,
        },
    };

    ESP_ERROR_CHECK( esp_wifi_disconnect() );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg) );
    ESP_ERROR_CHECK( esp_wifi_connect() );
}

static
esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }

    return ESP_OK;
}

void
print_ip_task(void *pv_param)
{
    printf("print_ip_task started\n");
    tcpip_adapter_ip_info_t ip_info;

    for ( ;; )
    {
        xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, true, true, portMAX_DELAY);
        ESP_ERROR_CHECK( tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info) );

        printf("IP:\t%s\n", ip4addr_ntoa(&ip_info.ip));
    }
}

void
app_main(void)
{
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_event_group = xEventGroupCreate();
    initialise_wifi();

    xTaskCreate(&print_ip_task, "print_ip_task", 2048, NULL, 5, NULL);
}
