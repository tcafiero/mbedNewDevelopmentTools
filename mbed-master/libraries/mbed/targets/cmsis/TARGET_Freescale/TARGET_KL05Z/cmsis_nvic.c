/* mbed Microcontroller Library - cmsis_nvic for KL05Z
 * Copyright (c) 2011 ARM Limited. All rights reserved.
 *
 * CMSIS-style functionality to support dynamic vectors
 */
#include "cmsis_nvic.h"

#define NVIC_NUM_VECTORS (16 + 32)            // CORE + MCU Peripherals
#define NVIC_RAM_VECTOR_ADDRESS (0x1FFFFC00)  // Vectors positioned at start of RAM

void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector) {
    static volatile uint32_t *vectors = (uint32_t*)NVIC_RAM_VECTOR_ADDRESS;
    uint32_t i;

    // Copy and switch to dynamic vectors if the first time called
    if (SCB->VTOR != NVIC_RAM_VECTOR_ADDRESS) {
        uint32_t *old_vectors = (uint32_t*)SCB->VTOR;
        for (i=0; i<NVIC_NUM_VECTORS; i++) {
            vectors[i] = old_vectors[i];
        }
        SCB->VTOR = (uint32_t)vectors;
    }

    vectors[IRQn + 16] = vector;
}

uint32_t NVIC_GetVector(IRQn_Type IRQn) {
    uint32_t *vectors = (uint32_t*)SCB->VTOR;
    return vectors[IRQn + 16];
}
