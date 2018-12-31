# SampleWeatherReport

## Build Application
#### Download and Install Qt at https://www.qt.io/download version 4.7.2 or later
#### Install CURL
* brew install curl
#### Clone jsoncpp to SampleWeatherReport/ThirdParty
* mkdir SampleWeatherReport/ThirdParty
* get clone https://github.com/open-source-parsers/jsoncpp.git
* python amalgamate.py

## Build Test Application
#### Install cmake
* brew install cmake
#### Install Boost
* brew install boost
#### Run cmake and build
* mkdir SampleWeatherReport/tests/build
* cd SampleWeatherReport/test/build
* cmake ../.
* make
#### Run Unit tests
* ./weathertests

