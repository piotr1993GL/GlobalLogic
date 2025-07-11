#pragma once

#include "CanInterface.hpp"
#include "stm32f4xx_hal.h"

class CanInterfaceHAL : public ICanInterface {
public:
    bool Send(const CanMessage& msg) override;
    bool Receive(CanMessage& msg) override;
};
