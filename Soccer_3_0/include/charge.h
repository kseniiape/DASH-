#pragma once

#include "Arduino.h"
#include "global.h"
#include "config.h"

void control_charge() {
    static int power = 1;
    int charge = analogRead(CHARGE_PIN);
    if (charge <= 600) {
        stop_motors = 1;
        power = 0;
    }
    else if (charge <= 800) {
        power = (power == 1? 0:1);
    }
    else {
        power = 1;
    }
    digitalWrite(CHARGE_LED_PIN,power);

}