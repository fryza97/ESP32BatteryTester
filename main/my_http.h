#ifndef MY_HTTP_H
#define MY_HTTP_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>

esp_err_t hello_get_handler(httpd_req_t *req);
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err);
httpd_handle_t start_webserver(void);
esp_err_t stop_webserver(httpd_handle_t server);
void disconnect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

#endif /* MY_HTTP_H */