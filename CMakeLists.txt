cmake_minimum_required(VERSION 3.16)

project(RestaurantOrderingSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find Qt correctly
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# ✅ Find JSON
find_package(nlohmann_json REQUIRED)

# ✅ Sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# ✅ Create executable FIRST
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RestaurantOrderingSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(RestaurantOrderingSystem
        ${PROJECT_SOURCES}
    )
endif()

# ✅ THEN link libraries
target_link_libraries(RestaurantOrderingSystem
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    nlohmann_json::nlohmann_json
)

# ✅ macOS bundle settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RestaurantOrderingSystem)
endif()

set_target_properties(RestaurantOrderingSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ✅ Install
include(GNUInstallDirs)
install(TARGETS RestaurantOrderingSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ✅ Required for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RestaurantOrderingSystem)
endif()

cmake_minimum_required(VERSION 3.10)
project(RestaurantOrderingSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(server server/server.cpp)
target_link_libraries(server ${Boost_LIBRARIES} )
add_executable(client server/client/client.cpp)
target_link_libraries(client ${Boost_LIBRARIES})


enable_testing()

add_executable(runTests
    tests/test_basic.cpp
    tests/test_json.cpp
    tests/test_network_mock.cpp
    tests/test_edge_cases.cpp
)

target_link_libraries(runTests
    gtest
    gtest_main
    gmock
    pthread
)

add_test(NAME runTests COMMAND runTests)
