#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

extern "C" {
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "FreeRTOS.h"
#include "task.h"

#include "display/HAL_EK_TM4C1294XL_Crystalfontz128x128_ST7735.h"
#include "display/Crystalfontz128x128_ST7735.h"

}


#define DISPLAY_REFRESH_MS 16
#define TIMER_REFRESH_MS 1


tContext gContext;

volatile uint8_t hours = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;
volatile uint16_t milliseconds = 0;

volatile uint32_t gStopwatchMs = 0;

void displayTask(void* args) {
    while(1) {

        tRectangle background = {0, 0, 127, 127};
        GrContextForegroundSet(&gContext, ClrBlack);
        GrRectFill(&gContext, &background);

        char str[20];
        snprintf(str, sizeof(str), "%02u:%02u:%02u:%03u", hours, minutes, seconds, milliseconds);

        GrContextForegroundSet(&gContext, ClrYellow);
        GrStringDrawCentered(&gContext, str, -1, 64, 50, false);

        GrFlush(&gContext);

        vTaskDelay(pdMS_TO_TICKS(TIMER_REFRESH_MS));
    }
}

void timerTask(void* args) {
    while(1) {
        seconds = (gStopwatchMs / 1000U) % 60U;
        minutes = (gStopwatchMs / 60000U) % 60U;
        hours = gStopwatchMs / 3600000U;
        milliseconds = gStopwatchMs % 1000U;

        gStopwatchMs ++;

        vTaskDelay(pdMS_TO_TICKS(TIMER_REFRESH_MS));
    }
}

int main(void) {

    /* Disable interrupts during low-level setup */
    IntMasterDisable();
    FPUEnable();
    FPULazyStackingEnable();

    // Configure system clock to 120 MHz
    uint32_t sysClock = SysCtlClockFreqSet(
        SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480,
        120000000
    );

    //Initialize LCD
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    GrContextInit(&gContext, &g_sCrystalfontz128x128);
    GrContextFontSet(&gContext, &g_sFontFixed6x8);

    /* Now enable interrupts globally (FreeRTOS will manage nesting later) */
    IntMasterEnable();

    // Create tasks
    xTaskCreate(displayTask, "Display", 512, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(timerTask, "Timer", 512, NULL, tskIDLE_PRIORITY + 3, NULL);

    // Start scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}


//NOTE: PROBLEM during lab: stack size was too small on xTaskCreate
