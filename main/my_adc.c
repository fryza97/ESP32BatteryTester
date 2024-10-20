#include "my_adc.h"

extern const char *TAG;

#define R1 10000 // 10kΩ
#define R2 2200  // 3.3kΩ
#define R_CONV 5545
#define VMAX 3300
#define DMAX 4095

#define ADC_TO_VOLTAGE(adc_val)             ((((uint32_t)(adc_val)) * VMAX) / DMAX)

//#define TRUE_VOLTAGE(adc1_val, adc2_val)    (DIVIDER_TO_VOLTAGE(adc1_val) - DIVIDER_TO_VOLTAGE(adc2_val))

static bool example_adc_calibration_init(adc_unit_t unit, adc_atten_t atten, adc_cali_handle_t *out_handle){
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        //ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        //ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        //ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
}

static void example_adc_calibration_deinit(adc_cali_handle_t handle){
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    //ESP_LOGI(TAG, "deregister %s calibration scheme", "Curve Fitting");
    ESP_ERROR_CHECK(adc_cali_delete_scheme_curve_fitting(handle));

#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    //ESP_LOGI(TAG, "deregister %s calibration scheme", "Line Fitting");
    ESP_ERROR_CHECK(adc_cali_delete_scheme_line_fitting(handle));
#endif
}

static int divider_conv(int voltage_adc){
    int voltage_divided = voltage_adc;
    
    voltage_divided *= R_CONV;
    voltage_divided /= 1000;

    return voltage_divided;
}


static void adc_init(adc_oneshot_unit_handle_t *adc1_handle, adc_oneshot_unit_init_cfg_t *init_config1, adc_oneshot_chan_cfg_t *config){
    ESP_ERROR_CHECK(adc_oneshot_new_unit(init_config1, adc1_handle));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(*adc1_handle, ADC1_CH0, config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(*adc1_handle, ADC1_CH1, config));
}

void adc_single_start(int *voltage){
    int adc_raw[2];

    adc_oneshot_unit_handle_t adc1_handle;

    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN,
    };

    adc_init(&adc1_handle, &init_config1, &config);

    adc_cali_handle_t adc1_cali_handle = NULL;
    bool do_calibration1 = example_adc_calibration_init(ADC_UNIT_1, ADC_ATTEN, &adc1_cali_handle);

    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC1_CH0, &adc_raw[0]));
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %4d ", ADC_UNIT_1 + 1, ADC1_CH0, adc_raw[0]);
    if (do_calibration1) {
        ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, adc_raw[0], &voltage[0]));
    }
    voltage[0] = divider_conv(voltage[0]);
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CH0, voltage[0]);
    vTaskDelay(pdMS_TO_TICKS(1000));

    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC1_CH1, &adc_raw[1]));
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %4d ", ADC_UNIT_1 + 1, ADC1_CH1, adc_raw[1]);
    if (do_calibration1) {
        ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc1_cali_handle, adc_raw[1], &voltage[1]));
    }
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CH1, voltage[1]);
    vTaskDelay(pdMS_TO_TICKS(1000));

    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc1_handle));
    if (do_calibration1) {
        example_adc_calibration_deinit(adc1_cali_handle);
    }
}