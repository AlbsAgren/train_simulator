/*
 * Controller.cpp
 * Project
 * Albin Ågren
 */

#include "Controller.h"
#include "Vehicle.h"
#include "Station.h"
#include "Train.h"
#include "Simulation.h"
#include "Event.h"

#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <iostream>

Controller::Controller(Simulation *sim): mSim(sim), mLogLevel(off) {
    mLogFile.open("../resources/Project/Trainsim.log");

    // throw exception if file failed to open
    if(mLogFile.fail()) {
        throw std::runtime_error("logfile failed to open");
    }
}

std::string Controller::getLogLevelAsString() const {
    std::string logLevel;
    switch(mLogLevel) {
        case off:
            logLevel = "Off";
            break;
        case low:
            logLevel = "Low";
            break;
        case high:
            logLevel = "High";
            break;
        default:    // do nothing
            break;
    }
    return logLevel;
}

std::vector<std::string> Controller::getStationNames() const {
    std::vector<std::string> stationNames;

    // fill vector with station names
    for(const auto &station : mStations) {
        stationNames.push_back(station->getName());
    }
    return stationNames;
}

std::string Controller::getVehicleTypeNameByTypeNumber(const int &type) const {
    std::string typeName;
    switch(type) {
        case 0:
            typeName = "Coach";
            break;
        case 1:
            typeName = "Sleeper";
            break;
        case 2:
            typeName = "Open Wagon";
            break;
        case 3:
            typeName = "Covered Wagon";
            break;
        case 4:
            typeName = "Electric Locomotive";
            break;
        case 5:
            typeName = "Diesel Locomotive";
            break;
        default:    // do nothing
            break;
    }
    return typeName;
}

void Controller::loadStations() {
    std::ifstream inFile("../resources/Project/TrainStations.txt");

    // throw exception if file failed to open
    if(inFile.fail()) {
        throw std::runtime_error("station file failed to open");
    }

    std::string tmpStr;
    // read station name
    while(inFile >> tmpStr) {
        // make a new station
        std::unique_ptr<Station> newStation = std::make_unique<Station>(tmpStr);

        // get vehicle information
        std::getline(inFile, tmpStr);

        std::string vehicleStr;     // string to hold vehicle data
        // parse all vehicles
        while(!tmpStr.empty()) {
            // get substring representing single vehicle
            vehicleStr = tmpStr.substr(tmpStr.find('(') + 1,
                                       tmpStr.find(')') - 1);
            tmpStr = tmpStr.substr(tmpStr.find(')') + 1);

            // unique_ptr to hold new vehicle
            std::unique_ptr<Vehicle> newVehicle;

            int id, type, param0, param1;     // ints to hold vehicle paramers
            std::stringstream ss(vehicleStr);
            ss >> id >> type;   // use sstream to convert to ints

            // make the appropriate type of vehicle
            switch(type) {
                case 0: {
                    // read the params
                    ss >> param0 >> param1;
                    // make a new shared pointer and assign to newVehicle
                    newVehicle = std::make_unique<Coach>(id, param0, param1);
                    break;
                }
                case 1: {
                    ss >> param0;
                    newVehicle = std::make_unique<Sleeper>(id, param0);
                    break;
                }
                case 2: {
                    ss >> param0 >> param1;
                    newVehicle = std::make_unique<OpenWagon>(id, param0,
                                                             param1);
                    break;
                }
                case 3: {
                    ss >> param0;
                    newVehicle = std::make_unique<CoveredWagon>(id, param0);
                    break;
                }
                case 4: {
                    ss >> param0 >> param1;
                    newVehicle = std::make_unique<ElectricLocomotive>(id,
                                                                      param0,
                                                                      param1);
                    break;
                }
                case 5: {
                    ss >> param0 >> param1;
                    newVehicle = std::make_unique<DieselLocomotive>(id,
                                                                    param0,
                                                                    param1);
                    break;
                }
                default: {
                    // if type out of range, throw error
                    throw std::runtime_error("datafile corrupted");
                }
            }
            // add the new vehicle to the correct station
            newStation->attachVehicle(newVehicle.get());
            newVehicle->setStation(newStation.get());

            // log the event
            std::string event = "Connected to train pool at station " 
                              + newStation->getName();
            newVehicle->addHistory(event, Time(0, 0));

            // move pointer into member vector
            mVehicles.push_back(std::move(newVehicle));
        }
        // add station to Controller member vector
        mStations.push_back(std::move(newStation));
    }
    inFile.close();
}

void Controller::loadDistances() {
    std::ifstream inFile("../resources/Project/TrainMap.txt");

    // throw exception if file failed to open
    if(inFile.fail()) {
        throw std::runtime_error("map file failed to open");
    }

    // strings to hold station names
    Station *station0, *station1;
    std::string station0Name, station1Name;
    double distance;
    // get all distances
    while(inFile >> station0Name) {
        inFile >> station1Name;
        inFile >> distance;

        // set the distance for both station objects
        findStation(station0Name, &station0);
        station0->setDistance(station1Name, distance);
        findStation(station1Name, &station1);
        station1->setDistance(station0Name, distance);
    }
    inFile.close();
}

void Controller::loadTrains() {
    std::ifstream inFile("../resources/Project/Trains.txt");

    // throw exception if file failed to open
    if(inFile.fail()) {
        throw std::runtime_error("train file failed to open");
    }

    std::string tmpStr;
    // get line representing single train
    while(std::getline(inFile, tmpStr)) {
        std::stringstream ss(tmpStr);
        int id, topSpeed, type;
        std::string originName, destinationName;
        Time departure, arrival;

        // get id, origin, destination, departure time and arrival time
        ss >> id >> originName >> destinationName >> departure >> arrival
           >> topSpeed;

        // get the required vehicles
        std::vector<int> requiredVehicles;
        while(ss >> type) {
            requiredVehicles.push_back(type);
        }

        // get pointers to the origin and destination stations
        Station *origin, *destination;
        findStation(originName, &origin);
        findStation(destinationName, &destination);

        // make a new train object and assign a unique_ptr to it
        std::unique_ptr<Train> newTrain = std::make_unique<Train>(
                                                            id,
                                                            departure,
                                                            arrival,
                                                            topSpeed,
                                                            requiredVehicles,
                                                            origin,
                                                            destination);
        mTrains.push_back(std::move(newTrain));    // add train to member vector
    }

    inFile.close();
}

bool Controller::findStation(const std::string &name, Station **station) {
    // find station with matching name in member vector
    auto it = std::find_if(mStations.begin(), mStations.end(),
                           [name](std::unique_ptr<Station> &station) {
                            return station->getName() == name; });

    // if a matching station is found, assign it to the ptr and return true
    if(it != mStations.end()) {
        *station = (*it).get();
        return true;
    } else {
        return false;
    }
}

bool Controller::findTrain(const int &trainNumber, Train **train) {
    // find train with matching number in member vector
    auto it = std::find_if(mTrains.begin(), mTrains.end(),
                           [trainNumber](std::unique_ptr<Train> &train) {
                            return train->getTrainNumber() == trainNumber; });

    // if a matching train is found, assign it to the ptr and return true
    if(it != mTrains.end()) {
        *train = (*it).get();
        return true;
    } else {
        return false;
    }
}

bool Controller::findVehicle(const int &id, Vehicle **vehicle) {
    // find vehicle with matching number in member vector
    auto it = std::find_if(mVehicles.begin(), mVehicles.end(),
                           [id](std::unique_ptr<Vehicle> &vehicle) {
                            return vehicle->getId() == id; });

    // if a matching vehicle is found, assign it to the ptr and return true
    if(it != mVehicles.end()) {
        *vehicle = (*it).get();
        return true;
    } else {
        return false;
    }
}

void Controller::scheduleAssemblyEvents() {
    std::shared_ptr<Event> newEvent;

    // schedule assembly events for all trains
    for(const auto &train : mTrains) {
        Time eventTime = train->getCurrentDeparture() - Time(0, 30);
        newEvent = std::make_shared<AssemblyEvent>(eventTime, mSim,
                                                   this, train.get());;

        mSim->scheduleEvent(newEvent);
    }
}

bool Controller::attemptAssembly(Train *train) {
    bool complete = true;
    Station *station = train->getOrigin();
    Vehicle *vehicle;

    for(int type : train->getRequiredVehicles()) {
        // try to detatch a vehicle of the right type from station
        if(station->detachVehicle(type, &vehicle)) {
            // log event
            std::string event = "Disconnected from train pool at station "
                              + station->getName();
            vehicle->addHistory(event, mSim->getTime());

            // attach vehicle to train and log event
            train->attachVehicle(vehicle);
            event = "Connected to train " 
                  + std::to_string(train->getTrainNumber());
            vehicle->addHistory(event, mSim->getTime());

            // if a locomotive is slower than the train, adjust top speed
            if(vehicle->getType() > 3) {
                train->setTopSpeed(std::min(train->getTopSpeed(),
                                            vehicle->getTopSpeed()));
            }
        } else {
            complete = false;
        }
    }

    if(complete){
        train->setStatus("ASSEMBLED");
        // output log to console and log file
        std::stringstream ss;
        switch(mLogLevel) {
            case low:
                ss << mSim->getTime() << " " << train
                   << " is now assembled, arriving at the platform at "
                   << (mSim->getTime() + Time(0, 20)) << std::endl;

                // output to console and file
                std::cout << ss.str();
                mLogFile << ss.str();
                break;
            case high:
                ss << mSim->getTime() << " " << train
                   << " is now assembled, arriving at the platform at "
                   << (mSim->getTime() + Time(0, 20)) << std::endl
                   << "Connected vehicles: " << std::endl;

                // include individual vehicle info for high log level
                for(const Vehicle *const vehiclePtr : train->getVehicles()) {
                    ss << vehiclePtr->getInfo() << std::endl;

                    // print vehicle history
                    for(const std::string &event : vehiclePtr->getHistory()) {
                        ss << event << std::endl;
                    }
                }
                std::cout << ss.str();
                mLogFile << ss.str();
                break;
            case off:
                break;
        }
    // if assembly fail, set status to incomplete and log
    } else {
        train->setStatus("INCOMPLETE");
        train->addDelay(Time(0, 10));

        // log event
        std::stringstream ss;
        switch(mLogLevel) {
            case low:
                ss << mSim->getTime() << " " << train
                   << " is incomplete, next try at " 
                   << mSim->getTime() + Time(0, 10) << std::endl;
                std::cout << ss.str();
                mLogFile << ss.str();
                break;
            case high:
                ss << mSim->getTime() << " " << train
                   << " is incomplete, next try at " 
                   << mSim->getTime() + Time(0, 10) << std::endl
                   << "Missing vehicles: " << std::endl;
                // add the missing vehicle types
                for(const int &type : train->getRequiredVehicles()) {
                    ss << getVehicleTypeNameByTypeNumber(type) << std::endl;
                }
                std::cout << ss.str();
                mLogFile << ss.str();
                break;
            case off:
                break;
        }
    }
    return complete;    // indicate whether train fully equipped
}

void Controller::readyUp(Train *train) {
    train->setStatus("READY");

    // log event
    std::stringstream ss;
    switch(mLogLevel) {
        case low:
            ss << mSim->getTime() << " " << train
               << " is now at the platform, departing at "
               << train->getCurrentDeparture() << std::endl;

            // output to console and file
            std::cout << ss.str();
            mLogFile << ss.str();
            break;
        case high:
            ss << mSim->getTime() << " " << train
               << " is now at the platform, departing at "
               << train->getCurrentDeparture() << std::endl
               << "Connected vehicles: " << std::endl;

            // include individual vehicle info for high log level
            for(const Vehicle *vehiclePtr : train->getVehicles()) {
                ss << vehiclePtr->getInfo() << std::endl;

                // print vehicle history
                for(const std::string &event : vehiclePtr->getHistory()) {
                    ss << event << std::endl;
                }
            }
            std::cout << ss.str();
            mLogFile << ss.str();
            break;
        case off:
            break;
    }
}

void Controller::depart(Train *train) {
    train->setStatus("RUNNING");

    Time arrival, delay;

    // get the distance between origin and destination
    double distance = train->getOrigin()->
                        getDistance(train->getDestination()->getName());

    // calculate the required speed to arrive on time
    Time travelTime = train->getOrigArrival() - train->getCurrentDeparture();
    double requiredSpeed = distance / travelTime.getTimeAsDouble();

    // set train speed as required to stay on schedule, catch cases where train
    // is o far behind schedule its impossible to make it in time
    // (ie. required speed is < 0)
    if(requiredSpeed > 0 && requiredSpeed <= train->getTopSpeed()) {
        train->setSpeed(requiredSpeed);

    // attempt to compensate delays by raising speed
    } else {
        train->setSpeed(train->getTopSpeed());
        travelTime = distance / train->getTopSpeed();
    }

    // calculate new arrival and delay times
    arrival = train->getCurrentDeparture() + travelTime;
    delay = arrival - train->getOrigArrival();

    // set the new arrival and delay times
    train->setArrival(arrival);
    train->setDelay(delay);

    // log event
    std::stringstream ss;
    switch(mLogLevel) {
        case low:
            ss << mSim->getTime() << " " << train
               << " has left the platform, travelling at speed "
               << train->getSpeed() << " (" << train->getTopSpeed() << ")" 
               << std::endl;

            // output to console and file
            std::cout << ss.str();
            mLogFile << ss.str();
            break;
        case high:
            ss << mSim->getTime() << " " << train
               << " has left the platform, travelling at speed "
               << train->getSpeed() << " (" << train->getTopSpeed() << ")" 
               << std::endl << "Connected vehicles: " << std::endl;

            // include individual vehicle info for high log level
            for(const Vehicle *vehiclePtr : train->getVehicles()) {
                ss << vehiclePtr->getInfo() << std::endl;

                // print vehicle history
                for(const std::string &event : vehiclePtr->getHistory()) {
                    ss << event << std::endl;
                }
            }
            std::cout << ss.str();
            mLogFile << ss.str();
            break;
        case off:
            break;
    }
}

void Controller::arrive(Train *train) {
    train->setStatus("ARRIVED");

    // log event
    std::stringstream ss;
    switch(mLogLevel) {
        case low:
            // ignore trains outside of user specified time window
            if(!train->getIgnore()) {
                ss << mSim->getTime() << " " << train
                   << " has arrived at the platform, disassembly at "
                   << mSim->getTime() + Time(0, 20) << std::endl;

                // output to console and file
                mLogFile << ss.str();
                std::cout << ss.str();
            }
            break;
        case high:
            if(!train->getIgnore()) {
                ss << mSim->getTime() << " " << train
                   << " has arrived at the platform, disassembly at "
                   << mSim->getTime() + Time(0, 20) << std::endl
                   << "Connected vehicles: " << std::endl;

                // include individual vehicle info for high log level
                for(const Vehicle *vehiclePtr : train->getVehicles()) {
                    ss << vehiclePtr->getInfo() << std::endl;

                    // print vehicle history
                    for(const std::string &event : vehiclePtr->getHistory()) {
                        ss << event << std::endl;
                    }
                }
                if(mLogFile.is_open()) {
                    std::cout << ss.str();
                    mLogFile << ss.str();
                }
            }
            break;
        case off:
            break;
    }
}

void Controller::disassemble(Train *train) {
    train->setStatus("FINISHED");
    Station *station = train->getDestination();

    // detach the vehicles, add the event and store pointers in vector
    Vehicle *vehicle;
    std::vector<Vehicle *> vehicles;
    while(train->detachVehicle(&vehicle)) {
        // add event to vehicle history
        std::string event = "Disconnected from train " 
                          + std::to_string(train->getTrainNumber());
        vehicle->addHistory(event, mSim->getTime());

        station->attachVehicle(vehicle);
        event = "Connected to train pool at station " + station->getName();
        vehicle->addHistory(event, mSim->getTime());

        vehicles.push_back(vehicle);
    }

    // log event
    std::stringstream ss;
    switch(mLogLevel) {
        case low:
            if(!train->getIgnore()) {
                ss << mSim->getTime() << " " << train
                   << " has been disassembled" << std::endl;

                // output to console and file
                std::cout << ss.str();
                mLogFile << ss.str();
            }
        break;
        case high:
            if(!train->getIgnore()) {
                ss << mSim->getTime() << " " << train
                   << " has been disassembled." << std::endl
                   << "The train consisted of: " << std::endl;

                // include individual vehicle info for high log level
                for(const Vehicle *const vehiclePtr : vehicles) {
                    ss << vehiclePtr->getInfo() << std::endl;

                    // print vehicle history
                    for(const std::string &event : vehiclePtr->getHistory()) {
                        ss << event << std::endl;
                    }
                }
                std::cout << ss.str();
                mLogFile << ss.str();
            }
            break;
        case off:
            break;
    }
}

void Controller::ignoreDepartedTrains() {
    // set ignore flags for all departed trains
    for(auto &train : mTrains) {
        if(train->getCurrentDeparture() < mSim->getTime()) {
            train->setIgnore(true);
        }
    }
}

void Controller::printStatistics(const Time &endTime) const {
    // print on time, delayed and unfinished trains separately
    std::stringstream onTime, delayed, failed;
    Time departureDelay, arrivalDelay;

    // go through the trains and add them to the respecive sstream object
    for(const auto &train : mTrains) {
        // ignore trains out of time window
        if(train->getIgnore() || train->getOrigDeparture() > endTime) {
            ;   // null statment
        } else if(train->getStatus() == "FINISHED" &&
            train->getDelay() == Time(0, 0)) {
            onTime << train.get() << std::endl;

        } else if(train->getStatus() == "FINISHED" &&
                  train->getDelay() != Time(0, 0)) {
            delayed << train.get() << " Delay at departure: " 
                    << train->getDepartureDelay() << " Delay at arrival: "
                    << train->getDelay() << std::endl;

            departureDelay += train->getDepartureDelay();
            arrivalDelay += train->getDelay();
        } else {
            failed << train.get() << " never left the station" << std::endl;
        }
    }

    std::cout << "Trains on time:" << std::endl << onTime.str()
              << std::endl << "Delayed trains:" << std::endl << delayed.str()
              << std::endl << "Failed trains:" << std::endl << failed.str()
              << std::endl << "Total delay at departure: "
              << departureDelay << std::endl
              << "Total delay at arrival: " << arrivalDelay << std::endl;
}
