#include "test_env.h"

#if defined(TARGET_LPC11U24)
#define P1_1    (1 <<  9) // p0.9
#define P1_2    (1 <<  8) // p0.8
#define PORT_1  Port0

#define P2_1    (1 << 24) // p1.24
#define P2_2    (1 << 25) // p1.25
#define PORT_2  Port1

#elif defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || defined(TARGET_LPC4088)
#define P1_1    (1 << 9)  // p0.9  -> p5
#define P1_2    (1 << 8)  // p0.8  -> p6
#define PORT_1  Port0

#define P2_1    (1 << 1)  // p2.1 -> p25
#define P2_2    (1 << 0)  // p2.0 -> p26
#define PORT_2  Port2

#elif defined(TARGET_KL25Z)
#define P1_1    (1 << 1) // PTA1
#define P1_2    (1 << 2) // PTA2
#define PORT_1  PortA

#define P2_1    (1 << 7) // PTC7
#define P2_2    (1 << 0) // PTC0
#define PORT_2  PortC
#endif

#define MASK_1   (P1_1 | P1_2)
#define MASK_2   (P2_1 | P2_2)

PortOut port_out(PORT_1, MASK_1);
PortIn  port_in (PORT_2, MASK_2);

int main() {
    port_out = MASK_1;
    wait(0.1);
    int value = port_in.read();
    if (value != MASK_2) {
        printf("[Test high] expected (0x%x) received (0x%x)\n", MASK_2, value);
        notify_completion(false);
    }
    
    port_out = 0;
    wait(0.1);
    value = port_in.read();
    if (value != 0) {
        printf("[Test low] expected (0x%x) received (0x%x)\n", 0, value);
        notify_completion(false);
    }
    
    notify_completion(true);
}
