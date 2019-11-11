#ifndef PWM_H_
#define PWM_H_

#include "GPIO_Port.h"

class Pwm {
public:
    // We only support PWM for pins from 4 to 13.
	enum PIN_NUMBER {
		PIN_4  = 4,
		PIN_5  = 5,
		PIN_6  = 6,
		PIN_7  = 7,
		PIN_8  = 8,
		PIN_9  = 9,
		PIN_10 = 10,
		PIN_11 = 11,
		PIN_12 = 12,
		PIN_13 = 13,
	};

    enum PWM_FREQ {
        f_62503Hz = 0x01, 
        f_7812Hz  = 0x02,
        f_976Hz   = 0x03,
        f_244Hz   = 0x04,
        f_61Hz    = 0x05
    };

	enum TYPE_PWM {
		FAST = 0,
		PHASECORRECT = 1
	};

    Pwm(TYPE_PWM type, PIN_NUMBER pin, int dutyCycle, PWM_FREQ frequency);
    ~Pwm();

    bool updateDutyCycle(int newDutyCycle);
    bool updateFrequency(PWM_FREQ frequency);

private:
	uint8_t _pin;
	GPIO_PORT::GPIO_Port * _port;

    void setFastPwm();
    void setPhasePwm();
};


#endif /* PWM_H_ */
