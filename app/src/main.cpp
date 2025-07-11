#include "stm32f4xx_hal.h"
#include "CanInterfaceHAL.hpp"
#include "CanApplication.hpp"

extern "C" void SystemClock_Config();
extern "C" void MX_GPIO_Init();
extern "C" void MX_CAN1_Init();

CAN_HandleTypeDef hcan1;

int main() {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_CAN1_Init();
    HAL_CAN_Start(&hcan1);

    CanInterfaceHAL canHal;
    CanApplication  app(canHal);
    app.Init();

    while (true) {
        app.Loop();
        HAL_Delay(1000);
    }
}
