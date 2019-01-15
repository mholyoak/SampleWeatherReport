cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)

include_directories(.
        ../ThirdParty/googletest/googlemock/include/
        ../ThirdParty/googletest/googletest/include/
        ../ThirdParty/jsoncpp/include/)

# add the executable
add_executable (weatherGoogleTests
        ../openweathermapreporter.cpp
        ../restresponse.cpp
        ../locationweather.cpp
        GoogleTestMain.cpp
        ../ThirdParty/jsoncpp/dist/jsoncpp.cpp
        QPixmap.cpp OpenWeatherReportTests.cpp RestRequesterMock.h)

find_library(LIBGTEST_LIBRARY
        libgtestd.a
        PATHS
        ../cmake-build-debug/ThirdParty/googletest/googlemock/gtest/
        )

find_library(LIBGMOCK_LIBRARY
        libgmockd.a
        PATHS
        ../cmake-build-debug/ThirdParty/googletest/googlemock/
        )

# link GoogleTest with the test
target_link_libraries(weatherGoogleTests
#        ../cmake-build-debug/ThirdParty/googletest/googlemock/gtest/libgtestd.a)
        ${LIBGTEST_LIBRARY}
        ${LIBGMOCK_LIBRARY})
