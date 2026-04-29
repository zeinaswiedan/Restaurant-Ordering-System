#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(JsonEdgeCaseTest, InvalidJsonThrows) {
    std::string invalidMessage = R"({ "item": "Burger", )";

    EXPECT_THROW({
        json::parse(invalidMessage);
    }, json::parse_error);
}

// This test ensures the system can handle an empty JSON object
// without crashing or misbehaving.
TEST(JsonEdgeCaseTest, EmptyJson) {
    std::string message = "{}";
    auto j = nlohmann::json::parse(message);

    EXPECT_TRUE(j.empty());
}


// This test checks behavior when a required field is missing,
// ensuring the system does not assume all fields exist.
TEST(JsonEdgeCaseTest, MissingItemField) {
    std::string message = R"({"quantity":5})";
    auto j = nlohmann::json::parse(message);

    EXPECT_FALSE(j.contains("item"));
}


// This test ensures negative values are still parsed correctly,
// even though they may be invalid in real business logic.
TEST(JsonEdgeCaseTest, NegativeQuantity) {
    std::string message = R"({"item":"Burger","quantity":-5})";
    auto j = nlohmann::json::parse(message);

    EXPECT_LT(j["quantity"], 0);
}


// This test verifies correct handling of null values,
// which may occur in incomplete or corrupted data.
TEST(JsonEdgeCaseTest, NullField) {
    std::string message = R"({"item":null,"quantity":1})";
    auto j = nlohmann::json::parse(message);

    EXPECT_TRUE(j["item"].is_null());
}
