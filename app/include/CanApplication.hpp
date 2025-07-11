#pragma once

#include "CanInterface.hpp"

class CanApplication {
public:
    explicit CanApplication(ICanInterface& canInterface);

    void Init();
    void Loop();
    void OnReceive(const CanMessage& msg);
    bool GetLedState() const;

private:
    ICanInterface& canInterface_;
    bool           ledState_;
};
