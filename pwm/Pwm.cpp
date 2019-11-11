#include "Pwm.h"
#include <avr/pgmspace.h>

Pwm::Pwm(TYPE_PWM type, PIN_NUMBER pin, int dutyCycle, PWM_FREQ frequency) {
    if (pin < 4 || pin > 13) {
        // If the choosen pin is not valid, pwm will use pin 13
        pin = PIN_13; 
    }

	_pin = pgm_read_byte(GPIO_PORT::id_to_bit+pin);
	_port = GPIO_PORT::AllPorts[pgm_read_byte(GPIO_PORT::id_to_port+pin)];
	_port->dir(_pin, 1);

    if (!updateDutyCycle(dutyCycle)) {
        // If the duty cycle value is not valid, dety cycle will be setted to zero.
        updateDutyCycle(0);
    }

    // Always set OC0A to be cleared and set OC0A at bottom
    TCCR0A = (1<<COM0A1);
    if (type == PHASECORRECT) {
        setPhasePwm();
    } else {
        // The default pwm type is FAST, if the choosen value is not valid,
        // the PWM will be configured as FAST.
        setFastPwm();
    }

    if (!updateFrequency(frequency)) {
        // If the choosen frequency is not supported the frequency will fall to its default value.
        // Frequency defaults to 976 Hz
        updateFrequency(f_976Hz);
    }
}

Pwm::~Pwm() {}

void Pwm::setFastPwm() {
    TCCR0A |= ((1<<WGM01)|(1<<WGM00)); 
}

void Pwm::setPhasePwm() {
    TCCR0A |= ((0<<WGM01)|(1<<WGM00)); 
}

bool Pwm::updateDutyCycle(int dutyCycle) {
    // OCR0 is what controls the duty cycle
    // OCR0 = 45% of 255 = 114.75 = 115
    if (dutyCycle < 100 && dutyCycle > 0) {
        OCR0A = dutyCycle * 255/100;
        return true;
    } else {
        OCR0A = 0;
        return false;
    }
}

bool Pwm::updateFrequency(PWM_FREQ frequency) {
    if (frequency > 0x05 || frequency < 0x01) {
        return false;
    }
    // Prescaler config
    TCCR0B = frequency;
    return true;
}
