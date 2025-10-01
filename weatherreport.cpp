#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };
    /// <summary>
    /// This is a stub for a weather sensor. For the sake of testing 
    /// we create a stub that generates weather data and allows us to
    /// test the other parts of this application in isolation
    /// without needing the actual Sensor during development    /// </summary>
    class SensorStub : public IWeatherSensor {
    public:
        int Humidity() const {
            return 72;
        }

        int Precipitation() const {
            return 70;
        }

        double TemperatureInC() const {
            return 26;
        }

        int WindSpeedKMPH() const {
            return 52;
        }
    };
    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        // precipitation < 20 is a sunny day
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    
    void TestRainy()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        assert(report.find("rain") != string::npos);    }
    
    // New sensor stub to expose the high precipitation bug
    class HighPrecipitationStub : public IWeatherSensor {
    public:
        int Humidity() const {
            return 85;
        }

        int Precipitation() const {
            return 70;  // High precipitation (>60)
        }

        double TemperatureInC() const {
            return 26;  // High temperature (>25)
        }

        int WindSpeedKMPH() const {
            return 30;  // Low wind speed (<50)
        }
    };

    void TestHighPrecipitation()
    {
        // This instance of stub needs to be different-
        // to give high precipitation (>60) and low wind-speed (<50)
        HighPrecipitationStub sensor;

        // strengthen the assert to expose the bug
        // (function returns Sunny day, it should predict rain)
        string report = Report(sensor);
        cout << "High precipitation report: " << report << endl;
        
        // With high precipitation (70) and low wind (<50), it should predict heavy rain
        // But due to the bug in the condition logic, it returns "Sunny Day"
        assert(report.find("rain") != string::npos);  // This will FAIL - exposing the bug!
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    cout << "All is well (maybe)\n";
}
