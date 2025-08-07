#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "funciones.h"
#include "hardware.h"
#include "stdlib.h"

uint8_t valor_MAX232;

int main(){
    init(); // Inicializa UART, PWM, GPIO según tu configuración (en la función init)
    while (1){
        // Verifica si llegó un nuevo byte por UART
        if (uart_is_readable(UART_ID_1)){
            valor_MAX232 = uart_getc(UART_ID_1); // Lee un carácter recibido por UART
            // Si el carácter recibido es ENTER
            if(valor_MAX232=='-'){
                printf("Se ajusto el ángulo a 0° porque se excede del margen de trabajo\n");
                buffer[0]= 0;
                i=3;
            }
            if ((valor_MAX232 == '\r' || valor_MAX232 == '\n')){
                // Solo procesamos si el buffer tiene datos (evita que se procese una línea vacía)
                if (i > 0){
                    buffer[i] = '\0'; // Finaliza la cadena de texto con null terminator

                    angulo = atoi(buffer); // Convierte el string recibido a un número entero

                    // Limita el valor del ángulo al rango válido de 0 a 180
                    if (angulo > 180){
                        printf("Se ajusto el ángulo a 180° porque se excede del margen de trabajo\n");
                        angulo = 180;
                    }
                    mover_servo(angulo);
                }
                // Reinicia el índice para poder recibir una nueva cadena
                i = 0;
            }
            // Si el carácter recibido es un número (0-9) y hay espacio en el buffer
            else if (i < 3 && valor_MAX232 >= '0' && valor_MAX232 <= '9'){
                buffer[i++] = valor_MAX232; // Lo guarda en el buffer y avanza el índice
            }
        }
    }
}
