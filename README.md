# SampleWeatherReport
I've create a sample weather report application using Qt. I also created a test
application that runs a unit test for the COpenWeatherMapReporter class. The 
sample weather report app shows the weather for 3 cities. I also allows you to 
add a city and remove a city from the list. It also shows more detail weather 
for the cities. The application used curl for making REST API calls. It uses 
jsoncpp for parsing JSON. I used these for reuability and because I'm familiar 
with them. The licensing for both is MIT, so should be fine to use with a 
comercial application. These allow some of the code modules to be less Qt 
dependent and reusable. I could easily replace them with Qt components if 
there were a need. There are a few thing I would like to have done with more 
time. I'd have organized the files so Qt display files were in a sub-directory. 
The weather reporting modules were in another directory. The utilities were in 
another directory as well. The test application uses Boost Test. I would add 
more tests as well with additional time. It currently only has one test. It 
mocks QPixmap and the open weather map REST API. I would have addressed getting
updates to the weather report. I would make the updating of the list of cities 
more responsive. I'd create a easy way to deploy the applcation as it uses
Qt shared libraries which makes it a bit tricky to deploy. I'm sure I could 
come up with many more items as well.

## Build Application
#### Download and Install Qt at https://www.qt.io/download version 4.7.2 or later
#### Install CURL
* brew install curl
#### Clone jsoncpp to SampleWeatherReport/ThirdParty
* mkdir SampleWeatherReport/ThirdParty
* get clone https://github.com/open-source-parsers/jsoncpp.git
* python amalgamate.py
#### Build and Run Application
* Open Qt Creator
* open the SampleWeatherReport.pro file
* Click on the Run button (this builds and runs the application)

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

