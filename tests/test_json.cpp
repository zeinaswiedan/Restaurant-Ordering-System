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
