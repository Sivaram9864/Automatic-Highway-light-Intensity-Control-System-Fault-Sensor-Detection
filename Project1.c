#include <stdio.h>

#define LDR_THRESHOLD 500

int read_LDR(void);
void light_ON(void);
void light_OFF(void);

int main(void)
{
    int ldr_value;

    while (1)
    {
        // Read value from LDR sensor
        ldr_value = read_LDR();

        // Check light intensity
        if (ldr_value < LDR_THRESHOLD)
        {
            light_ON();     // Dark -> Light ON
        }
        else
        {
            light_OFF();    // Bright -> Light OFF
        }
    }

    return 0;
}

// Function to read LDR sensor value
int read_LDR(void)
{
    int sensor_value;

    // Read ADC value from LDR
    // Hardware-specific ADC code goes here

    return sensor_value;
}

// Function to turn ON street light
void light_ON(void)
{
    // Set GPIO pin HIGH
}

// Function to turn OFF street light
void light_OFF(void)
{
    // Set GPIO pin LOW
}