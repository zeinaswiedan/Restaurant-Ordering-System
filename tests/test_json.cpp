#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(JsonTest, ParseValidOrder) {
    std::string message = R"({
        "item": "Burger",
        "quantity": 2,
        "price": 50
    })";

    json j = json::parse(message);

    EXPECT_EQ(j["item"], "Burger");
    EXPECT_EQ(j["quantity"], 2);
    EXPECT_EQ(j["price"], 50);
}

TEST(JsonTest, MissingField) {
    std::string message = R"({
        "item": "Pizza"
    })";

    json j = json::parse(message);

    EXPECT_TRUE(j.contains("item"));
    EXPECT_FALSE(j.contains("quantity"));
}
// This test ensures that a normal JSON order message
// is parsed correctly and fields are accessible.
TEST(JsonTest, ParseDifferentItem) {
    std::string message = R"({"item":"Pizza","quantity":3})";
    auto j = nlohmann::json::parse(message);

    EXPECT_EQ(j["item"], "Pizza");
    EXPECT_EQ(j["quantity"], 3);
}


// This test checks that quantity = 0 is handled correctly,
// since zero is a valid edge value in orders.
TEST(JsonTest, QuantityIsZero) {
    std::string message = R"({"item":"Burger","quantity":0})";
    auto j = nlohmann::json::parse(message);

    EXPECT_EQ(j["quantity"], 0);
}


// This test ensures large order quantities are still parsed correctly,
// simulating bulk orders in the system.
TEST(JsonTest, LargeQuantity) {
    std::string message = R"({"item":"Fries","quantity":100})";
    auto j = nlohmann::json::parse(message);

    EXPECT_EQ(j["quantity"], 100);
}
