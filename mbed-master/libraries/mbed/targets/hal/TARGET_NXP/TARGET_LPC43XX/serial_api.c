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
// math.h required for floating point operations for baud rate calculation
#include <math.h>
#include <string.h>

#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "error.h"

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/
static const PinMap PinMap_UART_TX[] = {
    {UART0_TX, UART_0, (SCU_PINIO_PULLDOWN | 2)},
    {UART1_TX, UART_1, (SCU_PINIO_PULLDOWN | 4)},
    {UART2_TX, UART_2, (SCU_PINIO_PULLDOWN | 2)},
    {UART3_TX, UART_3, (SCU_PINIO_PULLDOWN | 2)},
    {NC        , NC    , 0}
};

static const PinMap PinMap_UART_RX[] = {
    {UART0_RX, UART_0, (SCU_PINIO_PULLDOWN | 2)},
    {UART1_RX, UART_1, (SCU_PINIO_PULLDOWN | 1)},
    {UART2_RX, UART_2, (SCU_PINIO_PULLDOWN | 2)},
    {UART3_RX, UART_3, (SCU_PINIO_PULLDOWN | 2)},
    {NC        , NC    , 0}
};

#define UART_NUM    4

static uint32_t serial_irq_ids[UART_NUM] = {0};
static uart_irq_handler irq_handler;

int stdio_uart_inited = 0;
serial_t stdio_uart;

void serial_init(serial_t *obj, PinName tx, PinName rx) {
    int is_stdio_uart = 0;
    
    // determine the UART to use
    UARTName uart_tx = (UARTName)pinmap_peripheral(tx, PinMap_UART_TX);
    UARTName uart_rx = (UARTName)pinmap_peripheral(rx, PinMap_UART_RX);
    UARTName uart = (UARTName)pinmap_merge(uart_tx, uart_rx);
    if ((int)uart == NC) {
        error("Serial pinout mapping failed");
    }

    obj->uart = (LPC_USART_T *)uart;

    // enable fifos and default rx trigger level
    obj->uart->FCR = 1 << 0  // FIFO Enable - 0 = Disables, 1 = Enabled
                   | 0 << 1  // Rx Fifo Reset
                   | 0 << 2  // Tx Fifo Reset
                   | 0 << 6; // Rx irq trigger level - 0 = 1 char, 1 = 4 chars, 2 = 8 chars, 3 = 14 chars

    // disable irqs
    obj->uart->IER = 0 << 0  // Rx Data available irq enable
                   | 0 << 1  // Tx Fifo empty irq enable
                   | 0 << 2; // Rx Line Status irq enable
    
    // set default baud rate and format
    serial_baud  (obj, 9600);
    serial_format(obj, 8, ParityNone, 1);
    
    // pinout the chosen uart
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);
    
    // set rx/tx pins in PullUp mode
    pin_mode(tx, PullUp);
    pin_mode(rx, PullUp);
    
    switch (uart) {
        case UART_0: obj->index = 0; break;
        case UART_1: obj->index = 1; break;
        case UART_2: obj->index = 2; break;
#if (UART_NUM > 3)
        case UART_3: obj->index = 3; break;
#endif
#if (UART_NUM > 4)
        case UART_4: obj->index = 4; break;
#endif
    }
    
    is_stdio_uart = (uart == STDIO_UART) ? (1) : (0);
    
    if (is_stdio_uart) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
}

void serial_free(serial_t *obj) {
    serial_irq_ids[obj->index] = 0;
}

// serial_baud
// set the baud rate, taking in to account the current SystemFrequency
void serial_baud(serial_t *obj, int baudrate) {
    uint32_t PCLK = SystemCoreClock;

    // First we check to see if the basic divide with no DivAddVal/MulVal
    // ratio gives us an integer result. If it does, we set DivAddVal = 0,
    // MulVal = 1. Otherwise, we search the valid ratio value range to find
    // the closest match. This could be more elegant, using search methods
    // and/or lookup tables, but the brute force method is not that much
    // slower, and is more maintainable.
    uint16_t DL = PCLK / (16 * baudrate);

    uint8_t DivAddVal = 0;
    uint8_t MulVal = 1;
    int hit = 0;
    uint16_t dlv;
    uint8_t mv, dav;
    if ((PCLK % (16 * baudrate)) != 0) {     // Checking for zero remainder
        float err_best = (float) baudrate;
        uint16_t dlmax = DL;
        for ( dlv = (dlmax/2); (dlv <= dlmax) && !hit; dlv++) {
            for ( mv = 1; mv <= 15; mv++) {
                for ( dav = 1; dav < mv; dav++) {
                    float ratio = 1.0f + ((float) dav / (float) mv);
                    float calcbaud = (float)PCLK / (16.0f * (float) dlv * ratio);
                    float err = fabs(((float) baudrate - calcbaud) / (float) baudrate);
                    if (err < err_best) {
                        DL = dlv;
                        DivAddVal = dav;
                        MulVal = mv;
                        err_best = err;
                        if (err < 0.001f) {
                            hit = 1;
                        }
                    }
                }
            }
        }
    }
    
    // set LCR[DLAB] to enable writing to divider registers
    obj->uart->LCR |= (1 << 7);
    
    // set divider values
    obj->uart->DLM = (DL >> 8) & 0xFF;
    obj->uart->DLL = (DL >> 0) & 0xFF;
    obj->uart->FDR = (uint32_t) DivAddVal << 0
                   | (uint32_t) MulVal    << 4;
    
    // clear LCR[DLAB]
    obj->uart->LCR &= ~(1 << 7);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    // 0: 1 stop bits, 1: 2 stop bits
    if (stop_bits != 1 && stop_bits != 2) {
        error("Invalid stop bits specified");
    }
    stop_bits -= 1;
    
    // 0: 5 data bits ... 3: 8 data bits
    if (data_bits < 5 || data_bits > 8) {
        error("Invalid number of bits (%d) in serial format, should be 5..8", data_bits);
    }
    data_bits -= 5;

    int parity_enable, parity_select;
    switch (parity) {
        case ParityNone: parity_enable = 0; parity_select = 0; break;
        case ParityOdd : parity_enable = 1; parity_select = 0; break;
        case ParityEven: parity_enable = 1; parity_select = 1; break;
        case ParityForced1: parity_enable = 1; parity_select = 2; break;
        case ParityForced0: parity_enable = 1; parity_select = 3; break;
        default:
            error("Invalid serial parity setting");
            return;
    }
    
    obj->uart->LCR = data_bits            << 0
                   | stop_bits            << 2
                   | parity_enable        << 3
                   | parity_select        << 4;
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static inline void uart_irq(uint32_t iir, uint32_t index) {
    // [Chapter 14] LPC17xx UART0/2/3: UARTn Interrupt Handling
    SerialIrq irq_type;
    switch (iir) {
        case 1: irq_type = TxIrq; break;
        case 2: irq_type = RxIrq; break;
        default: return;
    }
    
    if (serial_irq_ids[index] != 0)
        irq_handler(serial_irq_ids[index], irq_type);
}

void uart0_irq() {uart_irq((LPC_USART0->IIR >> 1) & 0x7, 0);}
void uart1_irq() {uart_irq((LPC_UART1->IIR >> 1) & 0x7, 1);}
void uart2_irq() {uart_irq((LPC_USART2->IIR >> 1) & 0x7, 2);}
void uart3_irq() {uart_irq((LPC_USART3->IIR >> 1) & 0x7, 3);}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    serial_irq_ids[obj->index] = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable) {
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    switch ((int)obj->uart) {
        case UART_0: irq_n=USART0_IRQn; vector = (uint32_t)&uart0_irq; break;
        case UART_1: irq_n=UART1_IRQn; vector = (uint32_t)&uart1_irq; break;
        case UART_2: irq_n=USART2_IRQn; vector = (uint32_t)&uart2_irq; break;
        case UART_3: irq_n=USART3_IRQn; vector = (uint32_t)&uart3_irq; break;
    }
    
    if (enable) {
        obj->uart->IER |= 1 << irq;
        NVIC_SetVector(irq_n, vector);
        NVIC_EnableIRQ(irq_n);
    } else { // disable
        int all_disabled = 0;
        SerialIrq other_irq = (irq == RxIrq) ? (TxIrq) : (RxIrq);
        obj->uart->IER &= ~(1 << irq);
        all_disabled = (obj->uart->IER & (1 << other_irq)) == 0;
        if (all_disabled)
            NVIC_DisableIRQ(irq_n);
    }
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
int serial_getc(serial_t *obj) {
    while (!serial_readable(obj));
    return obj->uart->RBR;
}

void serial_putc(serial_t *obj, int c) {
    while (!serial_writable(obj));
    obj->uart->THR = c;
    
    uint32_t lsr = obj->uart->LSR;
    lsr = lsr;
    uint32_t thr = obj->uart->THR;
    thr = thr;
}

int serial_readable(serial_t *obj) {
    return obj->uart->LSR & 0x01;
}

int serial_writable(serial_t *obj) {
    return obj->uart->LSR & 0x20;
}

void serial_clear(serial_t *obj) {
    obj->uart->FCR = 1 << 1  // rx FIFO reset
                   | 1 << 2  // tx FIFO reset
                   | 0 << 6; // interrupt depth
}

void serial_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}
