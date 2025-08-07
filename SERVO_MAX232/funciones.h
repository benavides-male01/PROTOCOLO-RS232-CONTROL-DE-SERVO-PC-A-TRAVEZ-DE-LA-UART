#ifndef FUNCIONES_H
#define FUNCIONES_H

extern uint8_t buffer[4];
extern uint8_t angulo;
extern uint8_t slice;
extern uint8_t chan;
extern uint16_t microSec;
extern uint8_t i;

void init(void);
void mover_servo(uint8_t valor);

#endif
