/*
 * UserInterface.h
 * Project
 * Albin Ågren
 */

#include "UserInterface.h"
#include "MyTime.h"
#include "Simulation.h"
#include "Controller.h"

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <memory>

int UserInterface::getMenuOption(int numberOfOptions) {
    std::string userInput;
    int userChoice;
    bool invalid;

    // get user input
    std::getline(std::cin, userInput);

    // convert to int and confirm validity
    try {
        userChoice = std::stoi(userInput);
        invalid = false;
    } catch(const std::invalid_argument &) {
        invalid = true;
    } catch(const std::out_of_range &) {
        invalid = true;
    }

    // prompt user for new input if invalid
    while(invalid || userChoice < 0 || userChoice > numberOfOptions) {
        std::cout << "\nError, please enter a valid option (0-" 
                  << numberOfOptions << "):" << std::endl;
        invalid = false;
        // recursively call function to catch new invalid inputs
        userChoice = getMenuOption(numberOfOptions);
    }
    return userChoice;
}

void UserInterface::runStartMenu() {
        std::cout << "=== TrainSimulator 2000 ===";
        bool done = false;

        // print menu
        while(!done) {
        std::cout << std::endl << "Start Menu" << std::endl
                  << "1. Change start time [" << mStartTime.getFormattedTime()
                  << "]" << std::endl
                  << "2. Change end time [" << mEndTime.getFormattedTime()
                  << "]" << std::endl
                  << "3. Start simulation" << std::endl
                  << "0. Exit" << std::endl;

        // perform chosen action
        switch(getMenuOption(3)) {
            case 1:
                std::cout << "Changing start time" << std::endl;
                mStartTime = changeTimeSetting();
                // catch invalid time settings
                while(mStartTime > mEndTime) {
                    std::cout << "Start time can not be after end time, "
                              << "try again." << std::endl;
                    mStartTime = changeTimeSetting();
                }
                break;
            case 2:
                std::cout << "Changing end time" << std::endl;
                mEndTime = changeTimeSetting();
                while(mStartTime > mEndTime) {
                    std::cout << "Start time can not be after end time, "
                              << "try again." << std::endl;
                    mEndTime = changeTimeSetting();
                }
                break;
            case 3:
                runSimulationMenu();
                done = true;
                break;
            case 0:
                done = true;
        }
    }
}

void UserInterface::runSimulationMenu() {
    bool done = false;

    // catch errors in setup
    if(!performSetup()) {
        std::cout << "Setup failed, exiting program." << std::endl;
        done = true;
    }

    while(!done) {
        // go to statistics if simulation complete
        if(mSim->getTime() > mEndTime) {
            runStatisticsMenu();
            return;
        }

        std::cout << std::endl << "Simulation menu. Current time: ["
                  << mSim->getTime() << "]" << std::endl
                  << "1. Change interval [" << mInterval.getFormattedTime()
                  << "]" << std::endl
                  << "2. Run next interval" << std::endl
                  << "3. Next event" << std::endl
                  << "4. Complete simulation" << std::endl
                  << "5. Change log level ["
                  << mController->getLogLevelAsString()
                  << "]" << std::endl
                  << "6. Train menu" << std::endl
                  << "7. Station menu" << std::endl
                  << "8. Vehicle menu" << std::endl
                  << "0. Exit" << std::endl;

        switch(getMenuOption(8)) {
            case 1:
                std::cout << "Changing interval" << std::endl;
                mInterval = changeTimeSetting();
                break;
            case 2:
                runInterval();
                break;
            case 3:
                runNextEvent();
                break;
            case 4:
                completeSimulation();
                runStatisticsMenu();
                done = true;
                break;
            case 5:
                changeLogLevel();
                break;
            case 6:
                runTrainMenu();
                break;
            case 7:
                runStationMenu();
                break;
            case 8:
                runVehicleMenu();
                break;
            case 0:
                done = true;
        }
    }
}

void UserInterface::runStatisticsMenu() {
    bool done = false;

    while(!done) {
        std::cout << std::endl << "Statistics menu. Current time: ["
                  << mSim->getTime() << "]" << std::endl
                  << "1. Change log level ["
                  << mController->getLogLevelAsString()
                  << "]" << std::endl
                  << "2. Print statistics" << std::endl
                  << "3. Train menu" << std::endl
                  << "4. Station menu" << std::endl
                  << "5. Vehicle menu" << std::endl
                  << "0. Exit" << std::endl;

        switch(getMenuOption(5)) {
            case 1:
                changeLogLevel();
                break;
            case 2:
                printStatistics();
                break;
            case 3:
                runTrainMenu();
                break;
            case 4:
                runStationMenu();
                break;
            case 5:
                runVehicleMenu();
                break;
            case 0:
            default:
                done = true;
        }
    }
}

void UserInterface::runTrainMenu() {
    bool done = false;

    while(!done) {
        std::cout << std::endl << "Train menu" << std::endl
                  << "1. Search train by number" << std::endl
                  << "2. Search train by vehicle id" << std::endl
                  << "3. Change log level ["
                  << mController->getLogLevelAsString()
                  << "]" << std::endl
                  << "0. Return" << std::endl;

        switch(getMenuOption(3)) {
            case 1:
                findTrainByNumber();
                break;
            case 2:
                findTrainByVehicleId();
                break;
            case 3:
                changeLogLevel();
                break;
            case 0:
            default:
                done = true;
        }
    }
}

void UserInterface::runStationMenu() {
    bool done = false;

    while(!done) {
        std::cout << std::endl << "Station menu" << std::endl
                  << "1. Show station names" << std::endl
                  << "2. Find station by name" << std::endl
                  << "3. Change log level ["
                  << mController->getLogLevelAsString()
                  << "]" << std::endl
                  << "0. Return" << std::endl;

        switch(getMenuOption(3)) {
            case 1:
                printStationNames();
                break;
            case 2:
                findStationByName();
                break;
            case 3:
                changeLogLevel();
                break;
            case 0:
            default:
                done = true;
        }
    }
}

void UserInterface::runVehicleMenu() {
    bool done = false;

    while(!done) {
        std::cout << std::endl << "Vehicle menu" << std::endl
                  << "1. Find vehicle by id" << std::endl
                  << "2. Change log level ["
                  << mController->getLogLevelAsString()
                  << "]" << std::endl
                  << "0. Return" << std::endl;

        switch(getMenuOption(2)) {
            case 1:
                findVehicleById();
                break;
            case 2:
                changeLogLevel();
                break;
            case 0:
            default:
                done = true;
        }
    }
}

bool UserInterface::performSetup() {
    // unique_ptrs to manage the simulation objects
    mSim = std::make_unique<Simulation>();

    // try block for all operations that require a file to open
    try {
        // allocate a new controller object
        mController = std::make_unique<Controller>(mSim.get());

        // attempt to load the data from file
        mController->loadStations();
        mController->loadDistances();
        mController->loadTrains();
    } catch(std::runtime_error &re) {
        // print error message and return false
        std::cout << "Error: " << re.what() << std::endl;
        return false;
    }

    // have the controller schedule initial assembly events for all trains
    mController->scheduleAssemblyEvents();

    // run the sim quietly until the user defined start time
    while(mSim->getNextEventTime() < mStartTime) {
        mSim->processNextEvent();
    }

    // set ignore flag on departed train to prevent them from being logged
    mController->ignoreDepartedTrains();

    // set the sim time to the chosen start time
    mSim->setTime(mStartTime);

    // set the log level to low as default
    mController->setLogLevel(low);

    return true;
}

Time UserInterface::changeTimeSetting() {
    // get int for hour and minute
    std::cout << "Enter new hour:" << std::endl;
    int hour = getMenuOption(23);

    std::cout << std::endl << "Enter new minute:" << std::endl;
    int minute = getMenuOption(59);

    // return time object
    return Time(hour, minute);
}

void UserInterface::runInterval() {
    // process events set to happen within the set interval
    Time stopTime = mSim->getTime() + mInterval;

    // disallow intervals beyond the end time
    if(stopTime > mEndTime) {
        stopTime = mEndTime;
    }

    // process events within the interval
    while(!mSim->done() && mSim->getNextEventTime() < stopTime) {
        mSim->processNextEvent();
    }

    // set time time to stop time
    mSim->setTime(stopTime);

    // once the end is reached, finish events for all departed trains
   if(stopTime >= mEndTime) {
        mSim->finishRunningTrains();
    }
}

void UserInterface::runNextEvent() {
    mSim->processNextEvent();

    // once the end is reached, finish events for all departed trains
   if(mSim->getTime() >= mEndTime) {
        mSim->finishRunningTrains();
    }
}

void UserInterface::completeSimulation() {
    while(!mSim->done() && mSim->getNextEventTime() < mEndTime) {
        mSim->processNextEvent();
    }
    // ensure all departed trains are arrived and disassembled
    mSim->finishRunningTrains();
}

void UserInterface::changeLogLevel() {
    std::cout << "Change log level [" << mController->getLogLevelAsString()
              << "]" << std::endl
              << "1. Low" << std::endl << "2. High" << std::endl
              << "0. Return" << std::endl;

    switch(getMenuOption(2)) {
        case 1:
            mController->setLogLevel(low);
            break;
        case 2:
            mController->setLogLevel(high);
            break;
        default:    // do nothing
            break;
    }
}

void UserInterface::printStatistics() {
    mController->printStatistics(mEndTime);
}

void UserInterface::findTrainByNumber() {
    Train *train;

    // get user query
    std::cout << "Enter train number:" << std::endl;
    int trainNumber = getMenuOption();

    // attempt to find matching train
    if(mController->findTrain(trainNumber, &train)) {
        std::cout << "Train found:" << std::endl << train << std::endl;
        // print additional info if high log level
        if(mController->getLogLevel() == high) {
            std::cout << "Connected vehicles: " << train->getNoOfVehicles()
                      << std::endl;
            for(const Vehicle *vehiclePtr : train->getVehicles()) {
                std::cout << vehiclePtr->getInfo() << std::endl;

                // print vehicle history
                for(const std::string &event : vehiclePtr->getHistory()) {
                    std::cout << event << std::endl;
                }
            }
        }
    } else {
        std::cout << "Train not found, check train number." << std::endl;
    }
}

void UserInterface::findTrainByVehicleId() {
    Vehicle *vehicle;
    Train *train;

    std::cout << "Enter vehicle id:" << std::endl;
    int id = getMenuOption();

    if(mController->findVehicle(id, &vehicle)) {
        train = vehicle->getTrain();
        // train will be nulptr if vehicle not attached to a train
        if(train != nullptr) {
            std::cout << "Vehicle is attached to:" << std::endl
                      << train << std::endl;

            // print additional info if high log level
            if(mController->getLogLevel() == high) {
                std::cout << "Connected vehicles: "
                          << train->getNoOfVehicles() << std::endl;
                for(const Vehicle *vehiclePtr : train->getVehicles()) {
                    std::cout << vehiclePtr->getInfo() << std::endl;

                    // print vehicle history
                    for(const std::string &event : vehiclePtr->getHistory()) {
                        std::cout << event << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Vehicle is not connected to a train." << std::endl;
        }
    } else {
        std::cout << "Vehicle not found, check id." << std::endl;
    }
}

void UserInterface::printStationNames() {
    std::cout << std::endl << "Station Names:" << std::endl;
    for(const std::string &name : mController->getStationNames()) {
        std::cout << name << std::endl;
    }
}

void UserInterface::findStationByName() {
    std::string userInput;
    Station *station;

    std::cout << "Enter station name:" << std::endl;
    std::getline(std::cin, userInput);

    if(mController->findStation(userInput, &station)) {
        std::cout << station->getName() << std::endl << "Connected vehicles:"
                  << std::endl;

        for(const Vehicle *vehiclePtr : station->getVehicles()) {
            std::cout << vehiclePtr->getInfo() << std::endl;

            if(mController->getLogLevel() == high) {
                // print vehicle history
                for(const std::string &event : vehiclePtr->getHistory()) {
                    std::cout << event << std::endl;
                }
            }
        }
    } else {
        std::cout << "Station not found, check name." << std::endl;
    }
}

void UserInterface::findVehicleById() {
    Vehicle *vehicle;

    std::cout << "Enter vehicle id:" << std::endl;
    int id = getMenuOption();

    if(mController->findVehicle(id, &vehicle)) {
        std::cout << std::endl << vehicle->getInfo() << std::endl;

        // print last connected train or station
        if(vehicle->getTrain() != nullptr) {
            std::cout << "Last Connected to train: "
                      << vehicle->getTrain()->getTrainNumber() << std::endl;
        } else if(vehicle->getStation() != nullptr) {
            std::cout << "Last connected to station: "
                      << vehicle->getStation()->getName() << std::endl;
        }

        // print entire history if high log level
        if(mController->getLogLevel() == high) {
            std::cout << "Full history: " << std::endl;
            for(const std::string &event : vehicle->getHistory()) {
                std::cout << event << std::endl;
            }
        }
    } else {
        std::cout << "Vehicle not found, check id." << std::endl;
    }
}
