#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(JsonEdgeCaseTest, InvalidJsonThrows) {
    std::string invalidMessage = R"({ "item": "Burger", )";

    EXPECT_THROW({
        json::parse(invalidMessage);
    }, json::parse_error);
}
