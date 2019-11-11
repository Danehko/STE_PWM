#include "Pwm.h"
#include "GPIO.h"
#include <util/delay.h>

void fade(Pwm * p);

int main() {
    Pwm p(Pwm::FAST, Pwm::PIN_13, 1, Pwm::f_976Hz);

    for(;;) {

        p.updateFrequency(Pwm::f_976Hz);
        fade(&p);

        p.updateFrequency(Pwm::f_62503Hz);
        fade(&p);
    }

    return 0;
}

void fade(Pwm * p) {
    unsigned char i=0;
     //Fade up
     for(i=1; i<100;i++){
         p->updateDutyCycle(i);
         _delay_ms(30);
     }

     //Fade down
     for(i=100; i>1;i--){
         p->updateDutyCycle(i);
         _delay_ms(30);
     }
}
