/*Calculo de Capacitor, resistencia y el consumo en watts para conectar leds en AC*/

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

#define VOLTAJE_PUENTE_DIODOS    1.5
#define AMPERAJE_MAX_LED              1.0

//FUNCIONES
// Función para calcular la reactancia capacitiva
float calcular_reactancia_capacitiva(float voltaje, int num_leds, float voltaje_led, float corriente_led, int num_series_leds) {
    return (voltaje - VOLTAJE_PUENTE_DIODOS - (num_leds * voltaje_led)) / (corriente_led * num_series_leds);
}

// Función para calcular el valor del capacitor
float calcular_capacitor(float reactancia_capacitiva, float frecuencia) {
    float resultado1 = 2*M_PI;
    float resultado2 = frecuencia * reactancia_capacitiva;
    return (1/(resultado1*resultado2));
}

// Función para calcular la resistencia
float calcular_resistencia(float voltaje_pico, int num_leds, float voltaje_led) {
    return ((voltaje_pico - VOLTAJE_PUENTE_DIODOS - (num_leds * voltaje_led))/AMPERAJE_MAX_LED ); 
}

// Función para calcular la potencia disipada en la resistencia
float calcular_potencia(float corriente_led, int num_series_leds, float resistencia) {
    return pow((corriente_led * num_series_leds), 2) * resistencia;
}


int main(void) {
    int voltac, hz, numleds, numSled;
    float watts, vpico, vled, iled, capacitor, resistencia, Xc;

    printf("\n\nCalculadora de componentes para circuito de LEDs\n");

    // Solicitar datos al usuario con validación básica
    do {
        printf("\nIngrese el voltaje AC (115V o 230V): ");
        if (scanf("%d", &voltac) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin);
        } else if (voltac != 115 && voltac != 230) {
            printf("Error: El voltaje debe ser 115V o 230V.\n");
        }
    } while (voltac != 115 && voltac != 230);

do {
        printf("\nIngrese la frecuencia en Hz (50 o 60): ");
        if (scanf("%d", &hz) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin); // Limpiar el buffer de entrada
        } else if (hz != 50 && hz != 60) {
            printf("Error: La frecuencia debe ser 50Hz o 60Hz.\n");
        }
    } while (hz != 50 && hz != 60);

int entrada1; // Variable auxiliar para almacenar la entrada del usuario

    do {
        printf("\nNúmero de LEDs en serie: ");
        if (scanf("%d", &entrada1) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin); // Limpiar el buffer de entrada
        } else if (entrada1 <= 0) {
            printf("Error: Ingrese un número positivo.\n");
        } else {
            // Si la entrada es válida, asigna el valor a numleds
            numleds = entrada1;
            break; // Sale del bucle
        }
    } while (1); // Bucle infinito que se rompe cuando la entrada es válida

int entrada2; // Variable auxiliar para almacenar la entrada del usuario

    do {
        printf("\nNúmero de series a implementar: ");
        if (scanf("%d", &entrada2) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin); // Limpiar el buffer de entrada
        } else if (entrada2 <= 0) {
            printf("Error: Ingrese un número positivo.\n");
        } else {
            // Si la entrada es válida, asigna el valor a numleds
            numSled = entrada2;
            break; // Sale del bucle
        }
    } while (1); // Bucle infinito que se rompe cuando la entrada es válida

do {
        printf("\nVoltaje del LED (incluya decimales si es necesario): ");
        if (scanf("%f", &vled) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin); // Limpiar el buffer de entrada
        } else if (vled <= 0) {
            printf("Error: Ingrese un valor positivo.\n");
        }
    } while (vled <= 0);

float entrada3; // Variable auxiliar para almacenar la entrada del usuario

    do {
        printf("\nCorriente que desea para el LED (en miliamperes, entre 0.001 y 0.999): ");
        if (scanf("%f", &entrada3) != 1) {
            printf("Error: Ingrese un valor numérico válido.\n");
            fflush(stdin); // Limpiar el buffer de entrada
        } else if (entrada3 < 0.001 || entrada3 > 0.999) {
            printf("Error: El valor debe estar entre 0.001 y 0.999 mA.\n");
        } else {
            // Si la entrada es válida, asigna el valor a ampled
            iled = entrada3;
            break; // Sale del bucle
        }
    } while (1); // Bucle infinito que se rompe cuando la entrada es válida

// Cálculos
    Xc = calcular_reactancia_capacitiva(voltac, numleds, vled, iled, numSled);
    vpico = voltac * sqrt(2);
    capacitor = calcular_capacitor(Xc, hz);
    resistencia = calcular_resistencia(vpico, numleds, vled);
    watts = calcular_potencia(iled, numSled, resistencia);

    // Mostrar resultados
    printf("\nReactancia capacitiva: %.3f ohms\n", Xc);
    printf("\nCapacitor: %.10f uF\n", capacitor);
    printf("\nResistencia: %.3f ohms\n", resistencia);
    printf("\nPotencia disipada en la resistencia: %.3f watts\n\n", watts);

return 0;

}
