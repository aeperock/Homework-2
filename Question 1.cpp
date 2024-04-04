#include <iostream>
#include <string>
#include <vector> // Include vector header
#include <memory>

// Abstract base class for Sensor
class Sensor {
public:
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
    virtual ~Sensor() {}
};

// Derived classes for different types of sensors
class TemperatureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
};

class PressureSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Pressure Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Pressure Sensor." << std::endl;
    }
};

class PositionSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Position Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Position Sensor." << std::endl;
    }
};

// Sensor Factory class
class SensorFactory {
public:
    static std::unique_ptr<Sensor> createSensor(const std::string& type) {
        if (type == "Temperature")
            return std::make_unique<TemperatureSensor>();
        else if (type == "Pressure")
            return std::make_unique<PressureSensor>();
        else if (type == "Position")
            return std::make_unique<PositionSensor>();
        else
            return nullptr;
    }
};

// Aerospace Control System class
class AerospaceControlSystem {
public:
    void addSensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));
    }

    void monitorAndAdjust() {
        for (const auto& sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }

private:
    std::vector<std::unique_ptr<Sensor>> sensors; // Corrected inclusion of vector
};

int main() {
    AerospaceControlSystem ctrlSys;

    // Adding sensors
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Position"));

    // Monitoring and adjusting
    ctrlSys.monitorAndAdjust();

    return 0;
}
