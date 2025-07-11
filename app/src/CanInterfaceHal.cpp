#include "CanInterfaceHAL.hpp"
#include <algorithm>  // std::copy

extern CAN_HandleTypeDef hcan1;

bool CanInterfaceHAL::Send(const CanMessage& msg) {
    CAN_TxHeaderTypeDef header{};
    header.StdId = msg.id;
    header.IDE   = CAN_ID_STD;
    header.RTR   = CAN_RTR_DATA;
    header.DLC   = msg.length;

    uint32_t mailbox;
    return (HAL_CAN_AddTxMessage(&hcan1, &header, 
                 const_cast<uint8_t*>(msg.data), &mailbox) == HAL_OK);
}

bool CanInterfaceHAL::Receive(CanMessage& msg) {
    CAN_RxHeaderTypeDef header{};
    uint8_t data[8];
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &header, data) != HAL_OK) {
        return false;
    }

    msg.id     = header.StdId;
    msg.length = header.DLC;
    std::copy(data, data + header.DLC, msg.data);
    return true;
}
