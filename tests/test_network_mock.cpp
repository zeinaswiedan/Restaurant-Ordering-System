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
