#pragma once

#include <cstdint>

struct CanMessage {
    uint16_t id;
    uint8_t  data[8];
    uint8_t  length;
};

class ICanInterface {
public:
    virtual ~ICanInterface() = default;
    virtual bool Send(const CanMessage& msg)   = 0;
    virtual bool Receive(CanMessage& msg)      = 0;
};

