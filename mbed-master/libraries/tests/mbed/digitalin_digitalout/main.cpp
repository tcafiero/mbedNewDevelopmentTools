#include "test_env.h"


#if defined(TARGET_KL25Z)
DigitalOut out(PTA1);
DigitalIn   in(PTC7);

#elif defined(TARGET_KL05Z)
DigitalOut out(PTB11);
DigitalIn   in(PTB1);

#else
DigitalOut out(p5);
DigitalIn   in(p25);

#endif

int main() {
    out = 0;
    wait(0.1);
    if (in != 0) {
        printf("ERROR: in != 0\n");
        notify_completion(false);
    }
    out = 1;
    wait(0.1);
    if (in != 1) {
        printf("ERROR: in != 1\n");
        notify_completion(false);
    }

    notify_completion(true);
}
