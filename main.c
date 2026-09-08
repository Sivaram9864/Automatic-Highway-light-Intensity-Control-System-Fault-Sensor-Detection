#include <stdint.h>
#include <stdbool.h>

/* Temperature limits */
#define TEMP_WARNING_LEVEL    70
#define TEMP_CRITICAL_LEVEL   85
#define TEMP_NORMAL_LEVEL  80

/* System states */
typedef enum
{
    SYSTEM_NORMAL,
    SYSTEM_WARNING,
    SYSTEM_CRITICAL
} SystemState_t;

/* Global variables */
static SystemState_t systemState = SYSTEM_NORMAL;
static int16_t currentTemperature = 0;
static bool motorShutdown=false;


/*----------------------------------------------------------
 * Hardware functions
 * These functions are already implemented elsewhere.
 *----------------------------------------------------------*/

int16_t Sensor_ReadTemperature(void)
{
    /* Simulates reading temperature from sensor */
    return 65;
}

void LED_Green_On(void)
{
    /* Hardware implementation */
}

void LED_Green_Off(void)
{
    /* Hardware implementation */
}

void LED_Red_On(void)
{
    /* Hardware implementation */
}

void LED_Red_Off(void)
{
    /* Hardware implementation */
}

void Buzzer_On(void)
{
    /* Hardware implementation */
}

void Buzzer_Off(void)
{
    /* Hardware implementation */
}

void Motor_On(void)
{
    /* Hardware implementation */
}

void Motor_Off(void)
{
    /* Hardware implementation */
}


/*----------------------------------------------------------
 * Temperature monitoring
 *----------------------------------------------------------*/

void Temperature_Update(void)
{
    currentTemperature = Sensor_ReadTemperature();

    if (currentTemperature >= TEMP_CRITICAL_LEVEL)
    {
        systemState = SYSTEM_CRITICAL;
    }
    else if (currentTemperature >= TEMP_WARNING_LEVEL)
    {
        systemState = SYSTEM_WARNING;
    }
    else
    {
        systemState = SYSTEM_NORMAL;
    }

    if(motorShutdown==true && currentTemperature<TEMP_NORMAL_LEVEL){
        motorShutdown=false;
    }
}


/*----------------------------------------------------------
 * System status handling
 *----------------------------------------------------------*/

void System_StatusUpdate(void)
{
    switch (systemState)
    {
        case SYSTEM_NORMAL:

            LED_Green_On();
            LED_Red_Off();
            Buzzer_Off();
            if(motorShutdown==true)
            {
                Motor_Off();
            }
            else{
                Motor_On();
            }

            break;


        case SYSTEM_WARNING:

            LED_Green_Off();
            LED_Red_On();
            Buzzer_Off();
            if (motorShutdown == true)
            {
                Motor_Off();
            }
            else
            {
                Motor_On();
            }

            break;


        case SYSTEM_CRITICAL:

            LED_Green_Off();
            LED_Red_On();
            Buzzer_On();
            Motor_Off();
            motorShutdown=true;

            break;


        default:

            LED_Green_Off();
            LED_Red_Off();
            Buzzer_Off();
            Motor_Off();

            break;
    }
}


/*----------------------------------------------------------
 * Main application
 *----------------------------------------------------------*/

int main(void)
{
    /* Hardware initialization would happen here */

    while (1)
    {
        Temperature_Update();

        System_StatusUpdate();

        /* Other application tasks */

    }

    return 0;
}