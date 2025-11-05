#include <stdint.h>
#include <stdbool.h>

//extern "C" {
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "FreeRTOS.h"
#include "task.h"
//}

// LED1: PN0 (D1 Green) - LED2: PN1 (D2 Blue)
#define LED1_PORT GPIO_PORTN_BASE
#define LED1_PIN  GPIO_PIN_0

#define LED2_PORT GPIO_PORTN_BASE
#define LED2_PIN  GPIO_PIN_1

void LED1_Task(void *pvParameters) {
    while (1) {
        GPIOPinWrite(LED1_PORT, LED1_PIN, LED1_PIN);  // On
        vTaskDelay(pdMS_TO_TICKS(2000));
        GPIOPinWrite(LED1_PORT, LED1_PIN, 0);         // Off
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void LED2_Task(void *pvParameters) {
    while (1) {
        GPIOPinWrite(LED2_PORT, LED2_PIN, LED2_PIN);  // On
        vTaskDelay(pdMS_TO_TICKS(200));
        GPIOPinWrite(LED2_PORT, LED2_PIN, 0);         // Off
        vTaskDelay(pdMS_TO_TICKS(200));
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

    // Enable GPIO peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));

    //Initialize LCD
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    GrContextInit(&gContext, &g_sCrystalfontz128x128);
    GrContextFontSet(&gContext, &g_sFontFixed6x8);

    //Initialize

    /* Now enable interrupts globally (FreeRTOS will manage nesting later) */
    IntMasterEnable();

    // Create tasks
    xTaskCreate(LED1_Task, "LED1", 128, NULL, 1, NULL);
    xTaskCreate(LED2_Task, "LED2", 128, NULL, 1, NULL);

    // Start scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}
