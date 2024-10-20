#ifndef MY_ADC_H
#define MY_ADC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define ADC1_CH0     ADC_CHANNEL_4
#define ADC1_CH1     ADC_CHANNEL_5
#define ADC_ATTEN   ADC_ATTEN_DB_12

void adc_single_start(int *voltage);

#endif /* MY_ADC_H */