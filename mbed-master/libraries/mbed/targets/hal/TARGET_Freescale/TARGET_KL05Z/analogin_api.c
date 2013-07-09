/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "analogin_api.h"

#include "cmsis.h"
#include "pinmap.h"
#include "error.h"

static const PinMap PinMap_ADC[] = {
    /* A0-A5 pins */
    {PTA0,  ADC0_SE12, 0},
    {PTA8,  ADC0_SE3,  0},
    {PTA9,  ADC0_SE2,  0},
    {PTB8,  ADC0_SE11, 0},
    {PTB9,  ADC0_SE10, 0},
    {PTB13, ADC0_SE13, 0},
    /* Rest of pins ADC Mux */
    {PTB2, ADC0_SE4,  0},
    {PTB1, ADC0_SE5,  0},
    {PTB5, ADC0_SE1,  0},
    {PTA12, ADC0_SE0, 0},
    {PTB10, ADC0_SE9, 0},
    {PTB11, ADC0_SE8, 0},
    {PTB7, ADC0_SE7, 0},
    {PTB0, ADC0_SE6,  0},
    {NC,    NC,       0}
};

void analogin_init(analogin_t *obj, PinName pin) {
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    if (obj->adc == (uint32_t)NC) {
        error("ADC pin mapping failed");
    }

    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    uint32_t port = (uint32_t)pin >> PORT_SHIFT;
    SIM->SCGC5 |= 1 << (SIM_SCGC5_PORTA_SHIFT + port);

    ADC0->SC1[1] = ADC_SC1_ADCH(obj->adc);

    ADC0->CFG1 = ADC_CFG1_ADLPC_MASK    // Low-Power Configuration
               | ADC_CFG1_ADIV(3)       // Clock Divide Select: (Input Clock)/8
               | ADC_CFG1_ADLSMP_MASK   // Long Sample Time
               | ADC_CFG1_MODE(1)       // (12)bits Resolution
               | ADC_CFG1_ADICLK(1);    // Input Clock: (Bus Clock)/2

    ADC0->CFG2 = ADC_CFG2_MUXSEL_MASK   // ADxxb channels are selected
               | ADC_CFG2_ADACKEN_MASK  // Asynchronous Clock Output Enable
               | ADC_CFG2_ADHSC_MASK    // High-Speed Configuration
               | ADC_CFG2_ADLSTS(0);    // Long Sample Time Select

    ADC0->SC2 = ADC_SC2_REFSEL(0);      // Default Voltage Reference

    ADC0->SC3 = ADC_SC3_AVGE_MASK       // Hardware Average Enable
              | ADC_SC3_AVGS(0);        // 4 Samples Averaged

    pinmap_pinout(pin, PinMap_ADC);
}

uint16_t analogin_read_u16(analogin_t *obj) {
    // start conversion
    ADC0->SC1[0] = ADC_SC1_ADCH(obj->adc);

    // Wait Conversion Complete
    while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);

    // Return value (12bit)
    return (uint16_t)ADC0->R[0];
}

float analogin_read(analogin_t *obj) {
    uint16_t value = analogin_read_u16(obj);
    return (float)value * (1.0f / (float)0xFFFF);
}

