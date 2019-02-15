R

TEST_F(OpenWeatherReportTest, FindCity)
{
    std::string jsonStr("{\"message\":\"like\",\"cod\":\"200\",\"count\":1,\"list\":[{\"id\":5780993,\""
                        "name\":\"Salt Lake City\",\"coord\":{\"lat\":40.767,\"lon\":-111.8905},\""
                        "main\":{\"temp\":268.67,\"pressure\":1028,\"humidity\":74,\"temp_min\":267.15,\""
                        "temp_max\":269.25},\"dt\":1546112100,\"wind\":{\"speed\":1.05,\"deg\":239.001},\"sys\":{\""
                        "country\":\"US\"},\"rain\":null,\"snow\":null,\"clouds\":{\"all\":75},\"weather\":[{\""
                        "id\":803,\"main\":\"Clouds\",\"description\":\"broken clouds\",\"icon\":\"04d\"}]}]}");
    CRestResponse getRequest(true, 200, jsonStr);

    EXPECT_CALL(*_restRequesterMock, GetRequest(_)).Times(1)
        .WillRepeatedly(Return(getRequest));

    COpenWeatherMapReporter openWeatherMapReporter(_restRequesterMock);

    auto cityListResult = openWeatherMapReporter.FindCity("Salt Lake City");

    // Verify that the FindCity function returned the correct results based and the Mock JSON
    EXPECT_EQ(cityListResult.size(), 1);
    EXPECT_EQ(cityListResult[0], "Salt Lake City, US");

}

