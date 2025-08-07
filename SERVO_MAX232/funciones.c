#include "hardware/gpio.h"
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "hardware.h"
#include "funciones.h"

uint8_t buffer[4], angulo, slice,chan;
uint16_t microSec;
uint8_t i = 0;  // Índice para ir guardando los caracteres que llegan en el buffer

void init() {
    stdio_init_all();

    // Inicialización del LED
    gpio_init(SERVO_PIN);
    gpio_set_dir(SERVO_PIN, GPIO_OUT);
    gpio_put(SERVO_PIN, false);
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

    // Configuración del PWM
    slice = pwm_gpio_to_slice_num(SERVO_PIN);
    chan = pwm_gpio_to_channel(SERVO_PIN);
    pwm_set_clkdiv_int_frac(slice, 125, 0);      // fCONT = fSYS / 125 = 125MHz / 125 = 1MHz (aprox)
    pwm_set_wrap(slice, 19999);                  // fPWM = fCONT / 19999 = 50Hz (aprox)
    pwm_set_enabled(slice, true);             // Habilita el PWM

    // Inicialización de la UART
    uart_init(UART_ID_1, BAUD_RATE);
    uart_init(UART_ID_0, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

}

void mover_servo(uint8_t valor){
    // Calcula los microsegundos correspondientes al ángulo
    // 500us = 0°, 2400us = 180°, proporcional entre esos valores
    microSec = 500 + (valor * (2400 - 500) / 180);

    // Muestra en consola (si tenés salida) para debug
    printf("Ángulo: %d, PWM: %dus\n", valor, microSec);

    // Actualiza el ciclo del PWM con el valor calculado
    pwm_set_chan_level(slice, chan, microSec);
}