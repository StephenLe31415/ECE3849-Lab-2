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

#include "button.h"
static constexpr uint32_t BUTTON_TICK_MS     = 20U;

// LED1: PN0 (D1 Green) - LED2: PN1 (D2 Blue)
#define LED1_PORT GPIO_PORTN_BASE
#define LED1_PIN  GPIO_PIN_0

#define LED2_PORT GPIO_PORTN_BASE
#define LED2_PIN  GPIO_PIN_1

/****** BUTTON ******/
void OnPlayPauseClick() {
    // Do something with the buzzer
    // gRunning = !gRunning;

}

void OnResetClick() {
    // Do something with the buzzer
    // global_timer = 0;
}

void buttonTask(void *pvParameters) {
    // Button Init
    Button btnPlayPause(S1);
    Button btnReset(S2);
    
    btnPlayPause.begin(); 
    btnPlayPause.setDebounceMs(30U);
//    btnPlayPause.setTickInterval(20U);
    
    btnReset.begin();
    btnReset.setDebounceMs(30U);
//    btnReset.setTickInterval(20U);

    btnPlayPause.attachClick(&OnPlayPauseClick);
    btnReset.attachClick(&OnResetClick);

    while(1) {
        btnPlayPause.tick();
        btnReset.tick();
        vTaskDelay(pdMS_TO_TICKS(BUTTON_TICK_MS));              // Wait 16ms
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
    xTaskCreate(buttonTask, "Button", 512, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}
