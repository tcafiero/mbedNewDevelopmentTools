#include "test_env.h"

#if defined(TARGET_KL25Z)
AnalogIn in(PTC1);
AnalogOut out(PTE30);

#elif defined(TARGET_LPC4088)
AnalogIn in(p15); // p17 (p0.25) is connected to trimpot on OEM base board
AnalogOut out(p18);

#elif defined(TARGET_KL05Z)
AnalogIn in(PTB11);  // D9
AnalogOut out(PTB1); // D1

#else
AnalogIn in(p17);
AnalogOut out(p18);

#endif

#define ERROR_TOLLERANCE    0.05

int main() {
    bool check = true;

    for (float out_value=0.0; out_value<1.1; out_value+=0.1) {
        out.write(out_value);
        wait(0.1);

        float in_value = in.read();
        float diff = fabs(out_value - in_value);
        if (diff > ERROR_TOLLERANCE) {
            check = false;
            printf("ERROR (out:%.4f) - (in:%.4f) = (%.4f)"NL, out_value, in_value, diff);
        } else {
            printf("OK    (out:%.4f) - (in:%.4f) = (%.4f)"NL, out_value, in_value, diff);
        }
    }

    notify_completion(check);
}
