// https://www.geeksforgeeks.org/observer-pattern-c-design-patterns/
#include <iostream>
#include <set>
using namespace std;

// Observer Interface
struct Observer {
    virtual ~Observer() = default;
    virtual void update() = 0;
};

// DisplayElement Interface
struct DisplayElement {
    virtual ~DisplayElement() = default;
    virtual void display() = 0;
};

// Subject Interface
struct Subject {
    virtual ~Subject() = default;
    virtual void registerObservers(Observer*) = 0;
    virtual void removeObserver(Observer*) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Subject
struct WeatherData : Subject {
    void registerObservers(Observer* obs) { observers.insert(obs); }
    void removeObserver(Observer* obs) { observers.erase(obs); }
    void notifyObservers() {
        for (Observer* observer : observers)
            observer->update();
    }
    void measurementsChanged() { notifyObservers(); }

    void setMeasurements(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        measurementsChanged();
    }
    // getters
    float getTemperature() { return temperature;  }
    float getHumidity() { return humidity;  }
    float getPressure() { return pressure;  }

private:
    float temperature, humidity, pressure;
    set<Observer*> observers;
};

// Concrete Observer
struct CurrentConditionsDisplay : Observer, DisplayElement {
    CurrentConditionsDisplay() = default;
    CurrentConditionsDisplay(WeatherData* wd) {
        weatherData = wd;
        weatherData->registerObservers(this);
    }
    void update() override {
        temperature = weatherData->getTemperature();
        humidity = weatherData->getHumidity();
        display();
    }
    void display() override {
        cout << "Current conditions: Temperature " << temperature
            << "F degrees and " << humidity << "% humidity" << endl;
    }
private:
    float temperature, humidity, pressure;
    WeatherData* weatherData;
};


int main()
{
    WeatherData weatherData;    // Concrete Subject

    CurrentConditionsDisplay currentDisplay(&weatherData);
    weatherData.setMeasurements(80, 65, 30.4f);
    weatherData.setMeasurements(82, 70, 29.2f);
    weatherData.setMeasurements(78, 90, 29.2f);

    return 0;
}
