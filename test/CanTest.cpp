#include <gtest/gtest.h>
#include "CanApplication.hpp"

class MockCanInterface : public ICanInterface {
public:
    CanMessage lastSent{};
    CanMessage toReceive{};
    bool       hasMessage = false;

    bool Send(const CanMessage& msg) override {
        lastSent = msg;
        return true;
    }

    bool Receive(CanMessage& msg) override {
        if (hasMessage) {
            msg         = toReceive;
            hasMessage = false;
            return true;
        }
        return false;
    }
};

TEST(CanApplicationTest, ShouldSendMessageEveryLoop) {
    MockCanInterface mock;
    CanApplication   app(mock);

    app.Loop();

    EXPECT_EQ(mock.lastSent.id,     0x123);
    EXPECT_EQ(mock.lastSent.length, 2);
    EXPECT_EQ(mock.lastSent.data[0], 0xDE);
    EXPECT_EQ(mock.lastSent.data[1], 0xAD);
}

TEST(CanApplicationTest, ShouldToggleLedOnReceive) {
    MockCanInterface mock;
    CanApplication   app(mock);

    EXPECT_FALSE(app.GetLedState());

    mock.toReceive.id       = 0x123;
    mock.toReceive.data[0]  = 0xFF;
    mock.toReceive.length   = 1;
    mock.hasMessage         = true;

    app.Loop();
    EXPECT_TRUE(app.GetLedState());

    mock.toReceive.id  = 0x123;
    mock.hasMessage    = true;

    app.Loop();
    EXPECT_FALSE(app.GetLedState());
}
