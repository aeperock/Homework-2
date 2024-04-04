#include <iostream>
#include <vector>

const int NUM_ROBOTS = 5;
const int TIME_TO_GRAB_TOOLS = 1;
const int TIME_TO_PERFORM_TASK = 5;

// Simulate a robot
class Robot {
public:
    Robot(int id) : id(id), timeTaken(0) {}

    void performTask() {
        std::cout << "Robot " << id << " is collecting data." << std::endl;

        // Time to grab tools
        timeTaken += TIME_TO_GRAB_TOOLS;

        std::cout << "Robot " << id << " acquired tools and starts performing a task." << std::endl;

        // Time to perform task
        timeTaken += TIME_TO_PERFORM_TASK;

        std::cout << "Robot " << id << " finished the task and returning the tools." << std::endl;
        
        // Return tools
        timeTaken += TIME_TO_GRAB_TOOLS;
    }

    int getTimeTaken() const {
        return timeTaken;
    }

private:
    int id;
    int timeTaken;
};

// Function to simulate the scenario
int simulateScenario() {
    std::vector<Robot> robots;

    // Initialize robots
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots.push_back(Robot(i));
    }

    int totalTime = 0;

    // Perform tasks
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots[i].performTask();
        std::cout << std::endl;
        
        // Update total time
        totalTime = std::max(totalTime, robots[i].getTimeTaken());
    }

    return totalTime;
}

int main() {
    int minTotalTime = simulateScenario();

    std::cout << "Duration: " << minTotalTime << " seconds" << std::endl;

    return 0;
}

