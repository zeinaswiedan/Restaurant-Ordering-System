#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::_;
using ::testing::Exactly;

class INetworkClient {
public:
    virtual ~INetworkClient() = default;
    virtual void sendMessage(const std::string& message) = 0;
};

class MockNetworkClient : public INetworkClient {
public:
    MOCK_METHOD(void, sendMessage, (const std::string& message), (override));
};

class OrderService {
public:
    explicit OrderService(INetworkClient& client) : client_(client) {}

    void placeOrder(const std::string& orderJson) {
        client_.sendMessage(orderJson);
    }

private:
    INetworkClient& client_;
};

TEST(NetworkTest, SendsOrderMessage) {
    MockNetworkClient mockClient;
    OrderService service(mockClient);

    std::string order = R"({"item":"Burger","quantity":1})";

    EXPECT_CALL(mockClient, sendMessage(order)).Times(Exactly(1));
    service.placeOrder(order);
}
// This test ensures that placing multiple orders
// triggers multiple network calls correctly.
TEST(NetworkTest, SendsMultipleOrders) {
    MockNetworkClient mockClient;
    OrderService service(mockClient);

    EXPECT_CALL(mockClient, sendMessage(_)).Times(2);

    service.placeOrder("order1");
    service.placeOrder("order2");
}


// This test verifies that empty orders are still sent,
// ensuring the system does not silently ignore input.
TEST(NetworkTest, SendsEmptyOrder) {
    MockNetworkClient mockClient;
    OrderService service(mockClient);

    EXPECT_CALL(mockClient, sendMessage("")).Times(1);

    service.placeOrder("");
}


// This test ensures no network call is made when no order is placed,
// verifying correct isolation of business logic.
TEST(NetworkTest, NoCallWhenNoOrder) {
    MockNetworkClient mockClient;
    OrderService service(mockClient);

    EXPECT_CALL(mockClient, sendMessage(_)).Times(0);
}


// This test checks that a specific message is sent exactly once,
// verifying correct request formatting.
TEST(NetworkTest, SendsSpecificMessage) {
    MockNetworkClient mockClient;
    OrderService service(mockClient);

    EXPECT_CALL(mockClient, sendMessage("test")).Times(1);
    service.placeOrder("test");
}
