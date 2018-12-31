cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

# add the executable
add_executable (weathertests
        maintest.cpp
        openweatherreportertest.cpp
        restrequestermock.cpp
        restrequestermock.h
        ../openweathermapreporter.cpp
        ../restresponse.cpp
        ../locationweather.cpp
        ../ThirdParty/jsoncpp/dist/jsoncpp.cpp QPixmap.cpp QPixmap)

# link boost with the test
target_link_libraries(weathertests
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
