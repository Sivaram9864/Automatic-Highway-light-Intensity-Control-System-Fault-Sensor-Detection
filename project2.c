#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN     PB5
#define LDR_CHANNEL 0

void ADC_Init(void)
{
    ADMUX = (1 << REFS0);  // AVCC as reference voltage
    ADCSRA = (1 << ADEN)  // Enable ADC
           | (1 << ADPS2)
           | (1 << ADPS1)
           | (1 << ADPS0); // Prescaler = 128
}

uint16_t ADC_Read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    ADCSRA |= (1 << ADSC);  // Start conversion

    while (ADCSRA & (1 << ADSC))
    {
        // Wait for conversion
    }

    return ADC;
}

int main(void)
{
    uint16_t ldr_value;

    // Configure LED pin as output
    DDRB |= (1 << LED_PIN);

    // Initialize ADC
    ADC_Init();

    while (1)
    {
        ldr_value = ADC_Read(LDR_CHANNEL);

        /*
         * ADC value:
         * 0    -> minimum voltage
         * 1023 -> maximum voltage
         */

        if (ldr_value < 500)
        {
            // Dark condition
            PORTB |= (1 << LED_PIN);
        }
        else
        {
            // Daylight condition
            PORTB &= ~(1 << LED_PIN);
        }

        _delay_ms(500);
    }

    return 0;
}