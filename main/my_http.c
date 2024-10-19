#include "my_http.h"
#include "web.c"

extern const char *TAG;
extern float adc_voltage;
char temp[450];

/* An HTTP GET handler */
esp_err_t voltage_handler(httpd_req_t *req){
    esp_err_t error;
    
    ESP_LOGI(TAG, "Voltage measurement completed!");

    sprintf(temp, "%s %5.2f %s", web_string1, adc_voltage, web_string2);

    req->user_ctx = (void*) temp;
    const char *response = (const char *) req->user_ctx;
    error = httpd_resp_send(req, response, strlen(response));
    if(error != ESP_OK){
        ESP_LOGI(TAG, "Error %d while sending Response", error);
    }
    else ESP_LOGI(TAG, "Response sent Successfully");
    return error;
}

httpd_uri_t voltage = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = voltage_handler,
    .user_ctx  = "Voltage measurement:"
};

esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err){
    /* For any other URI send 404 and close socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}

httpd_handle_t start_webserver(void){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &voltage);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

esp_err_t stop_webserver(httpd_handle_t server){
    // Stop the httpd server
    return httpd_stop(server);
}

void disconnect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        if (stop_webserver(*server) == ESP_OK) {
            *server = NULL;
        } else {
            ESP_LOGE(TAG, "Failed to stop http server");
        }
    }
}

void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}