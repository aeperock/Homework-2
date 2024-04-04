#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

const int MAX_AIRCRAFT_IN_PATTERN = 3;

// Aircraft class
class Aircraft {
public:
    Aircraft(int id) : id(id) {}

    void approach() {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate landing process
    }

    int getId() const {
        return id;
    }

private:
    int id;
};

// Air Traffic Controller class
class AirTrafficController {
public:
    void processIncomingAircraft(Aircraft& aircraft) {
        std::lock_guard<std::mutex> lock(mutex);

        std::cout << "Aircraft " << aircraft.getId() << " is approaching." << std::endl;

        if (aircraftsInPattern < MAX_AIRCRAFT_IN_PATTERN) {
            if (!isTalking) {
                std::cout << "ATC is asleep. Aircraft " << aircraft.getId() << " wakes up ATC." << std::endl;
                isTalking = true;
            }
            std::cout << "Aircraft " << aircraft.getId() << " is cleared to land." << std::endl;
            ++aircraftsInPattern;
        } else {
            std::cout << "Traffic pattern is full. Aircraft " << aircraft.getId() << " needs to divert." << std::endl;
        }
    }

    void finishCommunication() {
        std::lock_guard<std::mutex> lock(mutex);
        isTalking = false;
        --aircraftsInPattern;
        std::cout << "ATC finishes communication. ATC falls asleep." << std::endl;
    }

private:
    std::mutex mutex;
    bool isTalking = false;
    int aircraftsInPattern = 0;
};

int main() {
    std::vector<Aircraft> aircrafts;
    AirTrafficController atc;

    // Create 10 aircraft
    for (int i = 1; i <= 10; ++i) {
        aircrafts.push_back(Aircraft(i));
    }

    // Simulate aircraft approaching
    for (auto& aircraft : aircrafts) {
        std::thread([&]() {
            atc.processIncomingAircraft(aircraft);
            aircraft.approach();
            atc.finishCommunication();
        }).detach();
    }

    // Wait for all threads to finish
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
