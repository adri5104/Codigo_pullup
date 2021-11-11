#include "Stepper.h"
#include <arduino.h>

Stepper::Stepper() {

    is_moving = false;
    px=0;

}

void Stepper::setPosition(float npx) {

    px = npx;

}

void Stepper::prepareMove(float newx) {

    obj = (newx - px) * STEPS_PER_MM;
    absobj = abs(obj);
    if (absobj) {
        is_moving = true;
        maxsteps = absobj;
        digitalWrite(dir_pin, obj > 0 ? HIGH : LOW);
        step_count = 0;
        prev_time = millis();
        setPosition(newx);
    }

}


void Stepper::move() {

    unsigned long curtime = millis();

    if (is_moving && (curtime - prev_time) >= millisbetweensteps) {
        prev_time = curtime;
        if (step_count<maxsteps) {
            digitalWrite(step_pin, HIGH);
            digitalWrite(step_pin, LOW);
            step_count++;
        }
    }

    is_moving = !(step_count >= maxsteps);

}

float Stepper::getPosition(){
    if(digitalRead(dir_pin)==HIGH){
      return (previa+step_count);
    }
    else{ return(previa-step_count);}
}