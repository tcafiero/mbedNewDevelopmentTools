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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include "gpio_api.h"
#include "pinmap.h"

uint32_t gpio_set(PinName pin) {
    int f = 0;
    unsigned int port = (unsigned int)MBED_GPIO_PORT(pin);

    f = SCU_PINIO_FAST | ((port > 4) ? (4) : (0));
    pin_function(pin, f);

    return (1 << ((int)pin & 0x1F));
}

void gpio_init(gpio_t *obj, PinName pin, PinDirection direction) {
    if (pin == NC) return;
    
    obj->pin = pin;
    obj->mask = gpio_set(pin);

    LPC_GPIO_T *port_reg = (LPC_GPIO_T *) (LPC_GPIO_PORT_BASE);
    unsigned int port = (unsigned int)MBED_GPIO_PORT(pin);

    obj->reg_set = &port_reg->SET[port];
    obj->reg_clr = &port_reg->CLR[port];
    obj->reg_in  = &port_reg->PIN[port];
    obj->reg_dir = &port_reg->DIR[port];

    gpio_dir(obj, direction);
    switch (direction) {
        case PIN_OUTPUT: pin_mode(pin, PullNone); break;
        case PIN_INPUT : pin_mode(pin, PullDown); break;
    }
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    switch (direction) {
        case PIN_INPUT : *obj->reg_dir &= ~obj->mask; break;
        case PIN_OUTPUT: *obj->reg_dir |=  obj->mask; break;
    }
}
