/*
 * Controller.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_CONTROLLER_H
#define DT060G_PROJECT_CONTROLLER_H

#include "Train.h"
#include "Station.h"
#include "Vehicle.h"

#include <vector>
#include <memory>
#include <fstream>

// Forward declaration
class Simulation;

// Enum representing the different levels of log detail
enum LogLevel { off, low, high };

/**
 * Class for controlling the train system, owns all trains, vehicles
 * and stations
 */
class Controller {
public:
    /**
     * Constructor
     *
     * @param sim, a pointer to a Simulation object
     */
    explicit Controller(Simulation *sim);

    // Destructor
    ~Controller() { mLogFile.close(); }

    /**
     * Function for setting level of log detail
     *
     * @param logLevel, the desired log level
     */
    void setLogLevel(const LogLevel &logLevel) { mLogLevel = logLevel; }

    /**
     * Function for getting current log level
     *
     * @return, the current log level
     */
    LogLevel getLogLevel() const { return mLogLevel; }

    /**
     * Function for getting current log level as string
     *
     * @return, the current log level as string
     */
    std::string getLogLevelAsString() const;

    /**
     * Function for getting the names of all stations in the system
     *
     * @return, a vector of all station names
     */
    std::vector<std::string> getStationNames() const;

    /**
     * Function for getting a vehicle types name as string by its type number
     *
     * @param type, the type number
     * @return, the type name as a string
     */
    std::string getVehicleTypeNameByTypeNumber(const int &type) const;

    /**
     * Function for loading stations and their vehicle pool from file
     */
    void loadStations();

    /**
     * Function for loading station distances from file
     */
    void loadDistances();

    /**
     * Function for loading trains from file
     */
    void loadTrains();

    /**
     * Function for finding a station by name
     *
     * @param name, the station name
     * @param station, a pointer to a pointer to a station that will point to
     * the station object if one is found
     * @return, a bool indicating if the operation was successful
     */
    bool findStation(const std::string &name, Station **station);

    /**
     * Function for finding a train by train number
     *
     * @param trainNumber, the train number
     * @param train, a pointer to a pointer to a train that will point to
     * the train object if one is found
     * @return, a bool indicating if the operation was successful
     */
    bool findTrain(const int &trainNumber, Train **train);

    /**
     * Function for finding a vehicle by id
     *
     * @param id, the vehicle id
     * @param vehicle, a pointer to a pointer to a vehicle that will point to
     * the vehicle object if one is found
     * @return, a bool indicating if the operation was successful
     */
    bool findVehicle(const int &id, Vehicle **vehicle);

    /**
     * Function for scheduling the initial events for all trains, based on
     * their departure time
     */
    void scheduleAssemblyEvents();

    /**
     * Function for assembling train from available vehicles at origin station
     * as well as logging the event
     *
     * @param train, a pointer to the train to be assembled
     * @return, a bool indicating if train could be assembled
     */
    bool attemptAssembly(Train *train);

    /**
     * Function for changing train status to ready and logging the event
     *
     * @param train, a pointer to the train to be readied
     */
    void readyUp(Train *train);

    /**
     * Function for managing train departure, calculates train speed and
     * attempts to mitigate any delays, logs the event
     *
     * @param train, a pointer to the train to depart
     */
    void depart(Train *train);

    /**
     * Function for managing train arrival, changes train status and
     * logs the event
     *
     * @param train, a pointer to the train to arrive
     */
    void arrive(Train *train);

    /**
     * Function for managing train disassembly, transfers train vehicles
     * to the destination vehicle pool and logs the event
     *
     * @param train, a pointer to the train to disassemble
     */
    void disassemble(Train *train);

    /**
     * Function for setting ignore flag for already departed trains
     * Causes program not to log events for trains outside of user specified
     * simulation time window
     */
    void ignoreDepartedTrains();

    /**
     * Function for compiling and printing statistics from the trains in the
     * system
     *
     * @param endTime, the user specified end time of the simulation
     */
    void printStatistics(const Time &endTime) const;

// Private data members
private:
    Simulation *mSim;

    std::vector<std::unique_ptr<Vehicle>> mVehicles;

    std::vector<std::unique_ptr<Station>> mStations;

    std::vector<std::unique_ptr<Train>> mTrains;

    std::ofstream mLogFile;

    LogLevel mLogLevel;
};

#endif  // DT060G_PROJECT_CONTROLLER_H
