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
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  5
#define NO_GPIO     15

// On the LPC43xx the hardware pin name and the GPIO pin name are not the same.
// Encode SCU and GPIO offsets as a pin identifier
#define MBED_PIN(group, num, port, pin)  ((SCU_OFF(group,num) << 16) + GPIO_OFF(port,pin))

// Decode pin identifier into register, port and pin values
#define MBED_SCU_REG(MBED_PIN)   (LPC_SCU_BASE + (MBED_PIN >> 16))
#define MBED_GPIO_REG(MBED_PIN)  (LPC_GPIO_PORT_BASE + 0x2000 + ((MBED_PIN >> (PORT_SHIFT - 2)) & 0x0000003C))
#define MBED_GPIO_PORT(MBED_PIN) ((MBED_PIN >> PORT_SHIFT) & 0x0000000F)
#define MBED_GPIO_PIN(MBED_PIN)  (MBED_PIN & 0x0000001F)

typedef enum {
    // LPC43xx Pin Names
    // All pins defined. Package determines which are available.
    //          LBGA256  TFBGA180 TFBGA100 LQFP208  LQFP144
    // GPIO0    [15:0]   [15:0]   [15:6]   [15:0]   [15:0]
    //                            [4:0]
    // GPIO1    [15:0]   [15:0]   [15:0]   [15:0]   [15:0]
    // GPIO2    [15:0]   [15:0]            [15:0]   [15:0]
    // GPIO3    [15:0]   [15:0]   [7]      [15:0]   [15:0]
    //                            [5:3]
    //                            [1:0]
    // GPIO4    [15:0]   [15:0]            [15:0]   [11]
    // GPIO5    [26:0]   [26:0]   [11:0]   [25:0]   [18]
    //                                              [16:0]
    // GPIO6    [30:0]   [30:28]           [30:20]
    //                   [26:25]           [5:0]
    // GPIO7    [25:0]   [4:0]             [25:23]
    //                                     [21:17]
    //          ---      ---      ---      ---      ---
    // Total    164      117      49       131      83

    // Groups 0x00 - 0x0F : Digital pins
    // * Digital pins support up to 8 functions
    //   Use func=0 for GPIO0-GPIO4, func=4 for GPIO5-GPIO7
    // * High-drive pins default to 4 mA but can support 8, 14, 20 mA
    P0_0  = MBED_PIN(0x00, 0, 0, 0),    // GPIO0[0]
    P0_1  = MBED_PIN(0x00, 1, 0, 1),    // GPIO0[1]

    P1_0  = MBED_PIN(0x01, 0, 0, 4),    // GPIO0[4]
    P1_1  = MBED_PIN(0x01, 1, 0, 8),    // GPIO0[8]
    P1_2  = MBED_PIN(0x01, 2, 0, 9),    // GPIO0[9]
    P1_3  = MBED_PIN(0x01, 3, 0, 10),   // GPIO0[10]
    P1_4  = MBED_PIN(0x01, 4, 0, 11),   // GPIO0[11]
    P1_5  = MBED_PIN(0x01, 5, 1, 8),    // GPIO1[8]
    P1_6  = MBED_PIN(0x01, 6, 1, 9),    // GPIO1[9]
    P1_7  = MBED_PIN(0x01, 7, 1, 10),   // GPIO1[10]
    P1_8  = MBED_PIN(0x01, 8, 1, 1),    // GPIO1[1]
    P1_9  = MBED_PIN(0x01, 9, 1, 2),    // GPIO1[2]
    P1_10 = MBED_PIN(0x01, 10, 1, 3),   // GPIO1[3]
    P1_11 = MBED_PIN(0x01, 11, 1, 4),   // GPIO1[4]
    P1_12 = MBED_PIN(0x01, 12, 1, 5),   // GPIO1[5]
    P1_13 = MBED_PIN(0x01, 13, 1, 6),   // GPIO1[6]
    P1_14 = MBED_PIN(0x01, 14, 1, 7),   // GPIO1[7]
    P1_15 = MBED_PIN(0x01, 15, 0, 2),   // GPIO0[2]
    P1_16 = MBED_PIN(0x01, 16, 0, 3),   // GPIO0[3]
    P1_17 = MBED_PIN(0x01, 17, 0, 12),  // GPIO0[12] high-drive
    P1_18 = MBED_PIN(0x01, 18, 0, 13),  // GPIO0[13]
    P1_19 = MBED_PIN(0x01, 19, NO_GPIO, 0),
    P1_20 = MBED_PIN(0x01, 20, 0, 15),  // GPIO0[15]

    P2_0  = MBED_PIN(0x02, 0, 5, 0),    // GPIO5[0]
    P2_1  = MBED_PIN(0x02, 1, 5, 1),    // GPIO5[1]
    P2_2  = MBED_PIN(0x02, 2, 5, 2),    // GPIO5[2]
    P2_3  = MBED_PIN(0x02, 3, 5, 3),    // GPIO5[3]  high-drive
    P2_4  = MBED_PIN(0x02, 4, 5, 4),    // GPIO5[4]  high-drive
    P2_5  = MBED_PIN(0x02, 5, 5, 5),    // GPIO5[5]  high-drive
    P2_6  = MBED_PIN(0x02, 6, 5, 6),    // GPIO5[6]
    P2_7  = MBED_PIN(0x02, 7, 0, 7),    // GPIO0[7]
    P2_8  = MBED_PIN(0x02, 8, 5, 0),    // GPIO5[7]
    P2_9  = MBED_PIN(0x02, 9, 1, 10),   // GPIO1[10]
    P2_10 = MBED_PIN(0x02, 10, 0, 14),  // GPIO0[14]
    P2_11 = MBED_PIN(0x02, 11, 1, 11),  // GPIO1[11]
    P2_12 = MBED_PIN(0x02, 12, 1, 12),  // GPIO1[12]
    P2_13 = MBED_PIN(0x02, 13, 1, 13),  // GPIO1[13]

    P3_0  = MBED_PIN(0x03, 0, NO_GPIO, 0),
    P3_1  = MBED_PIN(0x03, 1, 5, 8),    // GPIO5[8]
    P3_2  = MBED_PIN(0x03, 2, 5, 9),    // GPIO5[9]
    P3_3  = MBED_PIN(0x03, 3, NO_GPIO, 0),
    P3_4  = MBED_PIN(0x03, 4, 1, 14),   // GPIO1[14]
    P3_5  = MBED_PIN(0x03, 5, 1, 15),   // GPIO1[15]
    P3_6  = MBED_PIN(0x03, 6, 0, 6),    // GPIO0[6]
    P3_7  = MBED_PIN(0x03, 7, 5, 10),   // GPIO5[10]
    P3_8  = MBED_PIN(0x03, 8, 5, 11),   // GPIO5[11]

    P4_0  = MBED_PIN(0x04, 0, 2, 0),    // GPIO2[0]
    P4_1  = MBED_PIN(0x04, 1, 2, 1),    // GPIO2[1]
    P4_2  = MBED_PIN(0x04, 2, 2, 2),    // GPIO2[2]
    P4_3  = MBED_PIN(0x04, 3, 2, 3),    // GPIO2[3]
    P4_4  = MBED_PIN(0x04, 4, 2, 4),    // GPIO2[4]
    P4_5  = MBED_PIN(0x04, 5, 2, 5),    // GPIO2[5]
    P4_6  = MBED_PIN(0x04, 6, 2, 6),    // GPIO2[6]
    P4_7  = MBED_PIN(0x04, 7, NO_GPIO, 0),
    P4_8  = MBED_PIN(0x04, 8, 5, 12),   // GPIO5[12]
    P4_9  = MBED_PIN(0x04, 9, 5, 13),   // GPIO5[13]
    P4_10 = MBED_PIN(0x04, 10, 5, 14),  // GPIO5[14]

    P5_0  = MBED_PIN(0x05, 0, 2, 0),    // GPIO2[9]
    P5_1  = MBED_PIN(0x05, 1, 2, 10),   // GPIO2[10]
    P5_2  = MBED_PIN(0x05, 2, 2, 11),   // GPIO2[11]
    P5_3  = MBED_PIN(0x05, 3, 2, 12),   // GPIO2[12]
    P5_4  = MBED_PIN(0x05, 4, 2, 13),   // GPIO2[13]
    P5_5  = MBED_PIN(0x05, 5, 2, 14),   // GPIO2[14]
    P5_6  = MBED_PIN(0x05, 6, 2, 15),   // GPIO2[15]
    P5_7  = MBED_PIN(0x05, 7, 2, 7),    // GPIO2[7]

    P6_0  = MBED_PIN(0x06, 0, NO_GPIO, 0),
    P6_1  = MBED_PIN(0x06, 1, 3, 0),    // GPIO3[0]
    P6_2  = MBED_PIN(0x06, 2, 3, 1),    // GPIO3[1]
    P6_3  = MBED_PIN(0x06, 3, 3, 2),    // GPIO3[2]
    P6_4  = MBED_PIN(0x06, 4, 3, 3),    // GPIO3[3]
    P6_5  = MBED_PIN(0x06, 5, 3, 4),    // GPIO3[4]
    P6_6  = MBED_PIN(0x06, 6, 0, 5),    // GPIO0[5]
    P6_7  = MBED_PIN(0x06, 7, 5, 15),   // GPIO5[15]
    P6_8  = MBED_PIN(0x06, 8, 5, 16),   // GPIO5[16]
    P6_9  = MBED_PIN(0x06, 9, 3, 5),    // GPIO3[5]
    P6_10 = MBED_PIN(0x06, 10, 3, 6),   // GPIO3[6]
    P6_11 = MBED_PIN(0x06, 11, 3, 7),   // GPIO3[7]
    P6_12 = MBED_PIN(0x06, 12, 2, 8),   // GPIO2[8]

    P7_0  = MBED_PIN(0x07, 0, 3, 8),    // GPIO3[8]
    P7_1  = MBED_PIN(0x07, 1, 3, 9),    // GPIO3[9]
    P7_2  = MBED_PIN(0x07, 2, 3, 10),   // GPIO3[10]
    P7_3  = MBED_PIN(0x07, 3, 3, 11),   // GPIO3[11]
    P7_4  = MBED_PIN(0x07, 4, 3, 12),   // GPIO3[12]
    P7_5  = MBED_PIN(0x07, 5, 3, 13),   // GPIO3[13]
    P7_6  = MBED_PIN(0x07, 6, 3, 14),   // GPIO3[14]
    P7_7  = MBED_PIN(0x07, 7, 3, 15),   // GPIO3[15]

    P8_0  = MBED_PIN(0x08, 8, 4, 0),    // GPIO4[0]  high-drive
    P8_1  = MBED_PIN(0x09, 0, 4, 1),    // GPIO4[1]  high-drive
    P8_2  = MBED_PIN(0x09, 1, 4, 2),    // GPIO4[2]  high-drive
    P8_3  = MBED_PIN(0x09, 2, 4, 3),    // GPIO4[3]
    P8_4  = MBED_PIN(0x08, 4, 4, 4),    // GPIO4[4]
    P8_5  = MBED_PIN(0x08, 5, 4, 5),    // GPIO4[5]
    P8_6  = MBED_PIN(0x08, 6, 4, 6),    // GPIO4[6]
    P8_7  = MBED_PIN(0x08, 7, 4, 7),    // GPIO4[7]
    P8_8  = MBED_PIN(0x08, 8, NO_GPIO, 0),

    P9_0  = MBED_PIN(0x09, 0, 4, 12),   // GPIO4[12]
    P9_1  = MBED_PIN(0x09, 1, 4, 13),   // GPIO4[13]
    P9_2  = MBED_PIN(0x09, 2, 4, 14),   // GPIO4[14]
    P9_3  = MBED_PIN(0x09, 3, 4, 15),   // GPIO4[15]
    P9_4  = MBED_PIN(0x09, 4, 5, 17),   // GPIO5[17]
    P9_5  = MBED_PIN(0x09, 5, 5, 18),   // GPIO5[18]
    P9_6  = MBED_PIN(0x09, 6, 4, 11),   // GPIO4[11]

    PA_0  = MBED_PIN(0x0A, 0, NO_GPIO, 0),
    PA_1  = MBED_PIN(0x0A, 1, 4, 8),    // GPIO4[8]  high-drive
    PA_2  = MBED_PIN(0x0A, 2, 4, 9),    // GPIO4[9]  high-drive
    PA_3  = MBED_PIN(0x0A, 3, 4, 10),   // GPIO4[10] high-drive
    PA_4  = MBED_PIN(0x0A, 4, 5, 19),   // GPIO5[19]

    PB_0   = MBED_PIN(0x0B, 0, 5, 20),  // GPIO5[20]
    PB_1   = MBED_PIN(0x0B, 1, 5, 21),  // GPIO5[21]
    PB_2   = MBED_PIN(0x0B, 2, 5, 22),  // GPIO5[22]
    PB_3   = MBED_PIN(0x0B, 3, 5, 23),  // GPIO5[23]
    PB_4   = MBED_PIN(0x0B, 4, 5, 24),  // GPIO5[24]
    PB_5   = MBED_PIN(0x0B, 5, 5, 25),  // GPIO5[25]
    PB_6   = MBED_PIN(0x0B, 6, 5, 26),  // GPIO5[26]

    PC_0   = MBED_PIN(0x0C, 0, NO_GPIO, 0),
    PC_1   = MBED_PIN(0x0C, 1, 6, 0),   // GPIO6[0]
    PC_2   = MBED_PIN(0x0C, 2, 6, 1),   // GPIO6[1]
    PC_3   = MBED_PIN(0x0C, 3, 6, 2),   // GPIO6[2]
    PC_4   = MBED_PIN(0x0C, 4, 6, 3),   // GPIO6[3]
    PC_5   = MBED_PIN(0x0C, 5, 6, 4),   // GPIO6[4]
    PC_6   = MBED_PIN(0x0C, 6, 6, 5),   // GPIO6[5]
    PC_7   = MBED_PIN(0x0C, 7, 6, 6),   // GPIO6[6]
    PC_8   = MBED_PIN(0x0C, 8, 6, 7),   // GPIO6[7]
    PC_9   = MBED_PIN(0x0C, 9, 6, 8),   // GPIO6[8]
    PC_10  = MBED_PIN(0x0C, 10, 6, 9),  // GPIO6[9]
    PC_11  = MBED_PIN(0x0C, 11, 6, 10), // GPIO6[10]
    PC_12  = MBED_PIN(0x0C, 12, 6, 11), // GPIO6[11]
    PC_13  = MBED_PIN(0x0C, 13, 6, 12), // GPIO6[12]
    PC_14  = MBED_PIN(0x0C, 14, 6, 13), // GPIO6[13]

    PD_0   = MBED_PIN(0x0D, 0, 6, 14),  // GPIO6[14]
    PD_1   = MBED_PIN(0x0D, 1, 6, 15),  // GPIO6[15]
    PD_2   = MBED_PIN(0x0D, 2, 6, 16),  // GPIO6[16]
    PD_3   = MBED_PIN(0x0D, 3, 6, 17),  // GPIO6[17]
    PD_4   = MBED_PIN(0x0D, 4, 6, 18),  // GPIO6[18]
    PD_5   = MBED_PIN(0x0D, 5, 6, 19),  // GPIO6[19]
    PD_6   = MBED_PIN(0x0D, 6, 6, 20),  // GPIO6[20]
    PD_7   = MBED_PIN(0x0D, 7, 6, 21),  // GPIO6[21]
    PD_8   = MBED_PIN(0x0D, 8, 6, 22),  // GPIO6[22]
    PD_9   = MBED_PIN(0x0D, 9, 6, 23),  // GPIO6[23]
    PD_10  = MBED_PIN(0x0D, 10, 6, 24), // GPIO6[24]
    PD_11  = MBED_PIN(0x0D, 11, 6, 25), // GPIO6[25]
    PD_12  = MBED_PIN(0x0D, 12, 6, 26), // GPIO6[26]
    PD_13  = MBED_PIN(0x0D, 13, 6, 27), // GPIO6[27]
    PD_14  = MBED_PIN(0x0D, 14, 6, 28), // GPIO6[28]
    PD_15  = MBED_PIN(0x0D, 15, 6, 29), // GPIO6[29]
    PD_16  = MBED_PIN(0x0D, 16, 6, 30), // GPIO6[30]

    PE_0   = MBED_PIN(0x0E, 0, 7, 0),   // GPIO7[0]
    PE_1   = MBED_PIN(0x0E, 1, 7, 1),   // GPIO7[1]
    PE_2   = MBED_PIN(0x0E, 2, 7, 2),   // GPIO7[2]
    PE_3   = MBED_PIN(0x0E, 3, 7, 3),   // GPIO7[3]
    PE_4   = MBED_PIN(0x0E, 4, 7, 4),   // GPIO7[4]
    PE_5   = MBED_PIN(0x0E, 5, 7, 5),   // GPIO7[5]
    PE_6   = MBED_PIN(0x0E, 6, 7, 6),   // GPIO7[6]
    PE_7   = MBED_PIN(0x0E, 7, 7, 7),   // GPIO7[7]
    PE_8   = MBED_PIN(0x0E, 8, 7, 8),   // GPIO7[8]
    PE_9   = MBED_PIN(0x0E, 9, 7, 9),   // GPIO7[9]
    PE_10  = MBED_PIN(0x0E, 10, 7, 10), // GPIO7[10]
    PE_11  = MBED_PIN(0x0E, 11, 7, 11), // GPIO7[11]
    PE_12  = MBED_PIN(0x0E, 12, 7, 12), // GPIO7[12]
    PE_13  = MBED_PIN(0x0E, 13, 7, 13), // GPIO7[13]
    PE_14  = MBED_PIN(0x0E, 14, 7, 14), // GPIO7[14]
    PE_15  = MBED_PIN(0x0E, 15, 7, 15), // GPIO7[15]

    PF_0   = MBED_PIN(0x0F, 0, NO_GPIO, 0),
    PF_1   = MBED_PIN(0x0F, 1, 7, 16),  // GPIO7[16]
    PF_2   = MBED_PIN(0x0F, 2, 7, 17),  // GPIO7[17]
    PF_3   = MBED_PIN(0x0F, 3, 7, 18),  // GPIO7[18]
    PF_4   = MBED_PIN(0x0F, 4, NO_GPIO, 0),
    PF_5   = MBED_PIN(0x0F, 5, 7, 19),  // GPIO7[19]
    PF_6   = MBED_PIN(0x0F, 6, 7, 20),  // GPIO7[20]
    PF_7   = MBED_PIN(0x0F, 7, 7, 21),  // GPIO7[21]
    PF_8   = MBED_PIN(0x0F, 8, 7, 22),  // GPIO7[22]
    PF_9   = MBED_PIN(0x0F, 9, 7, 23),  // GPIO7[23]
    PF_10  = MBED_PIN(0x0F, 10, 7, 24), // GPIO7[24]
    PF_11  = MBED_PIN(0x0F, 11, 7, 25), // GPIO7[25]

    // Map mbed pin names to LPC43xx board signals

    // Group 0x18 : CLKn pins
    SFP_CLK0  = MBED_PIN(0x18, 0, 0, 0),
    SFP_CLK1  = MBED_PIN(0x18, 1, 0, 0),
    SFP_CLK2  = MBED_PIN(0x18, 2, 0, 0),
    SFP_CLK3  = MBED_PIN(0x18, 3, 0, 0),
	
    // Group 0x19 : USB1, I2C0, ADC0, ADC1
    SFP_USB1  = MBED_PIN(0x19, 0, 0, 0),
    SFP_I2C0  = MBED_PIN(0x19, 1, 0, 0),
    SFP_AIO0  = MBED_PIN(0x19, 2, 0, 0), // ADC0 function select register
    SFP_AIO1  = MBED_PIN(0x19, 3, 0, 0), // ADC1 function select register
    SFP_AIO2  = MBED_PIN(0x19, 4, 0, 0), // Analog function select register

    SFP_EMCD  = MBED_PIN(0x1A, 0, 0, 0), // EMC clock delay register

    SFP_INS0  = MBED_PIN(0x1C, 0, 0, 0), // Interrupt select for pin interrupts 0 to 3
    SFP_INS1  = MBED_PIN(0x1C, 1, 0, 0), // Interrupt select for pin interrupts 4 to 7

#define MBED_ADC_NUM(MBED_PIN)   ((MBED_PIN >> 5) & 0x0000000F)
#define MBED_ADC_CHAN(MBED_PIN)  (MBED_PIN & 0x0000001F)

    // Use pseudo-pin ID also for ADCs, although with special handling
    SFP_ADC0_0 = MBED_PIN(0x19, 2, 0, 0), // ADC0_0
    SFP_ADC0_1 = MBED_PIN(0x19, 2, 0, 1), // ADC0_1
    SFP_ADC0_2 = MBED_PIN(0x19, 2, 0, 2), // ADC0_2
    SFP_ADC0_3 = MBED_PIN(0x19, 2, 0, 3), // ADC0_3
    SFP_ADC0_4 = MBED_PIN(0x19, 2, 0, 4), // ADC0_4
    SFP_ADC0_5 = MBED_PIN(0x19, 2, 0, 5), // ADC0_5
    SFP_ADC0_6 = MBED_PIN(0x19, 2, 0, 6), // ADC0_6

    SFP_ADC1_0 = MBED_PIN(0x19, 3, 1, 0), // ADC1_0
    SFP_ADC1_1 = MBED_PIN(0x19, 3, 1, 1), // ADC1_1
    SFP_ADC1_2 = MBED_PIN(0x19, 3, 1, 2), // ADC1_2
    SFP_ADC1_3 = MBED_PIN(0x19, 3, 1, 3), // ADC1_3
    SFP_ADC1_4 = MBED_PIN(0x19, 3, 1, 4), // ADC1_4
    SFP_ADC1_5 = MBED_PIN(0x19, 3, 1, 5), // ADC1_5
    SFP_ADC1_6 = MBED_PIN(0x19, 3, 1, 6), // ADC1_6
    SFP_ADC1_7 = MBED_PIN(0x19, 3, 1, 7), // ADC1_7

    // ---------- Micromint Bambino 200 ----------
    // LQFP144
    // NOTE: Pins marked (*) only available on 200E
    p5  = P1_2,   // SPI0 mosi
    p6  = P1_1,   // SPI0 miso
    p7  = P3_0,   // SPI0 sck
    p8  = P4_5,
    p9  = P6_4,   // Serial0 tx, I2C0 sda
    p10 = P6_5,   // Serial0 rx, I2C0 scl
    p11 = P1_4,   // SPI1 mosi (*)
    p12 = P1_3,   // SPI1 miso (*)
    p13 = PF_4,   // Serial1 tx, SPI1 sck (*)
    p14 = P1_14,  // Serial1 rx
    p15 = P4_3,   // ADC0
    p16 = P4_1,   // ADC1
    p17 = P7_4,   // ADC2
    p18 = SFP_ADC0_0, // ADC3, DAC0
    p19 = P7_5,   // ADC4
    p20 = P7_7,   // ADC5
    p21 = P4_0,   // PWM0
    p22 = P5_5,   // PWM1
    p23 = P5_7,   // PWM2
    p24 = P4_8,   // PWM3
    p25 = P4_9,   // PWM4
    p26 = P4_10,  // PWM5
    p27 = P2_4,   // I2C1 scl, Serial2 rx
    p28 = P2_3,   // I2C1 sda, Serial2 tx
    p29 = P3_2,   // CAN0 td
    p30 = P3_1,   // CAN0 rx

    // User interfaces: LEDs, buttons
    LED_YELLOW = P6_11,
    LED_GREEN = P2_5,
    LED_RED = LED_YELLOW,
    LED_BLUE = LED_GREEN,

    LED1 = LED_YELLOW,
    LED2 = LED_GREEN,
    LED3 = LED_GREEN,
    LED4 = LED_GREEN,

    BTN1 = P2_7,

    // Serial pins
    UART0_TX = P6_4,
    UART0_RX = P6_5,
    UART1_TX = P5_6,
    UART1_RX = P1_14,
    UART2_TX = P2_10,
    UART2_RX = P2_11,
    UART3_TX = P2_3,
    UART3_RX = P2_4,

    // Analog pins
    P_ADC0_0 = P4_3,
    P_ADC0_1 = P4_1,
    P_ADC1_0 = SFP_ADC0_0,
    P_ADC0_4 = P7_4,
    P_ADC0_3 = P7_5,
    P_ADC1_6 = P7_7,

    P_ADC0 = P_ADC0_0,
    P_ADC1 = P_ADC0_1,
    P_ADC2 = P_ADC1_0,
    P_ADC3 = P_ADC0_4,
    P_ADC4 = P_ADC0_3,
    P_ADC5 = P_ADC1_6,

    P_DAC0 = P4_4,

    // USB pins
    //P_USB0_TX = SFP_USB1,
    //P_USB0_RX = SFP_USB1,

    USBTX = UART0_TX,
    USBRX = UART0_RX,
    // ---------- End of Micromint Bambino 200 ----------

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    Repeater = 1,
    OpenDrain = 4
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
