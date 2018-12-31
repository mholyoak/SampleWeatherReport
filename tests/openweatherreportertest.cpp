#include <boost/test/unit_test.hpp>

#include "../openweathermapreporter.h"
#include "restrequestermock.h"

#include <memory>
#include <iostream>

#define WEATHER_TEST_CASE(name) BOOST_FIXTURE_TEST_CASE(weather_test_##name, WeatherTestFixture)

// TODO Add common components to the WeatherTestFixture that are used for multiple tests
struct WeatherTestFixture
{
};


WEATHER_TEST_CASE(FindCity)
{
    std::cout << "Find City Test." << std::endl;

    std::string jsonStr("{\"message\":\"like\",\"cod\":\"200\",\"count\":1,\"list\":[{\"id\":5780993,\""
                        "name\":\"Salt Lake City\",\"coord\":{\"lat\":40.767,\"lon\":-111.8905},\""
                        "main\":{\"temp\":268.67,\"pressure\":1028,\"humidity\":74,\"temp_min\":267.15,\""
                        "temp_max\":269.25},\"dt\":1546112100,\"wind\":{\"speed\":1.05,\"deg\":239.001},\"sys\":{\""
                        "country\":\"US\"},\"rain\":null,\"snow\":null,\"clouds\":{\"all\":75},\"weather\":[{\""
                        "id\":803,\"main\":\"Clouds\",\"description\":\"broken clouds\",\"icon\":\"04d\"}]}]}");
    CRestResponse getRequest(true, 200, jsonStr);
    CRestResponse getBinaryRequest;
    std::shared_ptr<IRestRequester> restRequesterMock = std::make_shared<CRestRequesterMock>(getRequest, getBinaryRequest);

    COpenWeatherMapReporter openWeatherMapReporter(restRequesterMock);

    auto cityListResult = openWeatherMapReporter.FindCity("Salt Lake City");
    // Verify that the FindCity function returned the correct results based and the Mock JSON
    BOOST_CHECK_EQUAL(cityListResult.size(), 1);
    BOOST_CHECK_EQUAL(cityListResult[0], "Salt Lake City, US");
}

// TODO Add additional test cases
