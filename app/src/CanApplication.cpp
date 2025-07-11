#include "CanApplication.hpp"

CanApplication::CanApplication(ICanInterface& canInterface)
    : canInterface_(canInterface)
    , ledState_(false)
{}

void CanApplication::Init() {
}

void CanApplication::Loop() {
    CanMessage rx;
    if (canInterface_.Receive(rx)) {
        OnReceive(rx);
    }

    CanMessage tx{};
    tx.id     = 0x123;
    tx.data[0]= 0xDE;
    tx.data[1]= 0xAD;
    tx.length = 2;
    canInterface_.Send(tx);
}

void CanApplication::OnReceive(const CanMessage& msg) {
    if (msg.id == 0x123) {
        ledState_ = !ledState_;
    }
}

bool CanApplication::GetLedState() const {
    return ledState_;
}
