/*
 * UserInterface.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_USER_INTERFACE_H
#define DT060G_PROJECT_USER_INTERFACE_H

#include "MyTime.h"
#include "Controller.h"
#include "Simulation.h"

#include <string>
#include <memory>

/**
 * Class for providing user with control over the simulation
 * Owns the simulation and controller objects
 */
class UserInterface {
public:
    /**
     * Constructor, initializes time intervals to default values
     */
    UserInterface(): mStartTime(0, 0), mEndTime(23, 59), mInterval(0, 10) { }

    // Default destructor
    ~UserInterface() = default;

    /**
     * Function for getting user choice of menu option
     * 
     * @param numberOfOptions, int indicating the number of available options
     * @return, an int representing chosen option between 0 and numberOfOptions
     */
    int getMenuOption(int numberOfOptions = 1000);

    /**
     * Function for running the startup menu
     */
    void runStartMenu();

    /**
     * Function for running the main simulation menu
     */
    void runSimulationMenu();

    /**
     * Function for running the statistics menu
     */
    void runStatisticsMenu();

    /**
     * Function for running the train menu
     */
    void runTrainMenu();

    /**
     * Function for running the station menu
     */
    void runStationMenu();

    /**
     * Function for running the vehicle menu
     */
    void runVehicleMenu();

    /**
     * Function for preparing the simulation, loads data from file, schedules
     * initial events runs the simulation to the user specified start time
     *
     * @return, a bool indicating if setup was successful
     */
    bool performSetup();

    /**
     * Function for allowing user to change a time setting
     *
     * @return, a time object with the chosen new time
     */
    Time changeTimeSetting();

    /**
     * Function for running the simulation for one user specified interval
     */
    void runInterval();

    /**
     * Function for running the next event in the simulation queue
     */
    void runNextEvent();

    /**
     * Function for running the simulation to the chosen end time
     */
    void completeSimulation();

    /**
     * Function for changing the level of detail in the log entries
     */
    void changeLogLevel();

    /**
     * Function for printing end-of-simulation statistics
     */
    void printStatistics();

    /**
     * Function for letting user find a train by its train number
     * Prints train info upon successful find
     */
    void findTrainByNumber();

    /**
     * Function for letting user find a train through the id of a vehicle
     * connected to it. Prints train info upon successful find
     */
    void findTrainByVehicleId();

    /**
     * Function for printing all station names
     */
    void printStationNames();

    /**
     * Function for letting user find a station by its name
     * Prints vehicle pool info upon successful find
     */
    void findStationByName();

    /**
     * Function for letting user find a vehicle by its id
     * Prints vehicle info upon successful find
     */
    void findVehicleById();

// Private data members
private:
    Time mStartTime, mEndTime, mInterval;

    std::unique_ptr<Simulation> mSim;

    std::unique_ptr<Controller> mController;
};

#endif  // DT060G_PROJECT_USER_INTERFACE_H
