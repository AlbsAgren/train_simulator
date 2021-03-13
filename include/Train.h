/*
 * Train.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_TRAIN_H
#define DT060G_PROJECT_TRAIN_H

#include "MyTime.h"

#include <string>
#include <memory>
#include <vector>
#include <ostream>

// Forward declarations
class Station;
class Vehicle;

/**
 * Class for managing a single train
 */
class Train {
public:
    /**
     * Constructor
     *
     * @param trainNumber, the train number
     * @param departure, a Time object with the departure time
     * @param arrival, a Time object with the arrival time
     * @param topSpeed, train top speed
     * @param requiredVehicles, the types of vehicle required by the train
     * @param origin, a pointer to the origin station
     * @param destination, a pointer to the destination station
     */
    Train(const int &trainNumber, const Time &departure, const Time &arrival,
          const int &topSpeed, const std::vector<int> &requiredVehicles,
          Station *const origin, Station *const destination):
                                            mTrainNumber(trainNumber),
                                            mOrigDeparture(departure),
                                            mCurrentDeparture(departure),
                                            mOrigArrival(arrival),
                                            mCurrentArrival(arrival),
                                            mDelay(Time(0,0)),
                                            mTopSpeed(topSpeed),
                                            mSpeed(0),
                                            mRequiredVehicles(requiredVehicles),
                                            mOrigin(origin),
                                            mDestination(destination),
                                            mStatus("NOT ASSEMBLED"),
                                            mIgnore(false) { }

    // Default destructor
    ~Train() = default;

    /**
     * Function for setting train delay time
     *
     * @param delay, a Time object representing how delayed the train is
     */
    void setDelay(const Time &delay) { mDelay = delay; }

    /**
     * Function for setting train arrival time
     *
     * @param delay, a Time object with the arrival time
     */
    void setArrival(const Time &arrival) { mCurrentArrival = arrival; }

    /**
     * Function for setting train top speed
     *
     * @param topSpeed, the new top speed
     */
    void setTopSpeed(const double &topSpeed) { mTopSpeed = topSpeed; }

    /**
     * Function for setting train current speed
     *
     * @param speed, the new speed
     */
    void setSpeed(const double &speed) { mSpeed = speed; }

    /**
     * Function for setting train status
     *
     * @param status, the train status
     */
    void setStatus(const std::string &status) { mStatus = status; }

    /**
     * Function for setting train ignore flag to prevent log printouts
     *
     * @param ignore, whether to ignore the train
     */
    void setIgnore(const bool &ignore) { mIgnore = ignore; }

    /**
     * Function for setting train ignore flag to prevent log printouts
     *
     * @return, the train number
     */
    int getTrainNumber() const { return mTrainNumber; }

    /**
     * Function for getting train top speed
     *
     * @return, train top speed
     */
    double getTopSpeed() const { return mTopSpeed; }

    /**
     * Function for getting train current speed
     *
     * @return, train speed
     */
    double getSpeed() const { return mSpeed; }

    /**
     * Function for getting original departure time
     *
     * @return, the original departure time
     */
    Time getOrigDeparture() const { return mOrigDeparture; }

    /**
     * Function for getting current departure time
     *
     * @return, currently planned departure time
     */
    Time getCurrentDeparture() const { return mCurrentDeparture; }

    /**
     * Function for getting original arrival time
     *
     * @return, the original arrival time
     */
    Time getOrigArrival() const { return mOrigArrival; }

    /**
     * Function for getting current arrival time
     *
     * @return, currently planned arrival time
     */
    Time getCurrentArrival() const { return mCurrentArrival; }

    /**
     * Function for getting how delayed train actually is
     *
     * @return, a Time object representing how delayed train is
     */
    Time getDelay() const { return mDelay; }

    /**
     * Function for getting how delayed train was at departure
     *
     * @return, a Time object representing how delayed train was at departure
     */
    Time getDepartureDelay() const { return mDepartureDelay; }

    /**
     * Function for getting train ignore flag to prevent log printouts
     *
     * @return, a bool indicating if train should be ignored
     */
    bool getIgnore() const { return mIgnore; }

    /**
     * Function for getting how many vehicles are connected to the train
     *
     * @return, an int representing how many vehicles are connected to the train
     */
    int getNoOfVehicles() const { return mVehicles.size(); }

    /**
     * Function for getting which vehicle types must still be connected for
     * train to be complete
     *
     * @return, a vector with the type numbers of the required vehicles
     */
    std::vector<int> getRequiredVehicles() const { return mRequiredVehicles; }

    /**
     * Function for getting origin station of train
     *
     * @return, a pointer to the origin station
     */
    Station *getOrigin() const { return mOrigin; }

    /**
     * Function for getting destination station of train
     *
     * @return, a pointer to the destination station
     */
    Station *getDestination() const { return mDestination; }

    /**
     * Function for getting train status
     *
     * @return, the train status
     */
    std::string getStatus() const { return mStatus; }

    /**
     * Function for getting all currently connected vehicles
     *
     * @return, a vector of pointers to the connected vehicles
     */
    std::vector<Vehicle *> getVehicles() const { return mVehicles; }

    /**
     * Function for attaching additional vehicle to the train
     *
     * @param, a pointer to the vehicle to be attached
     */
    void attachVehicle(Vehicle *const vehicle);

    /**
     * Function for detaching the next vehicle from the train
     *
     * @param, a pointer to a pointer which will point to the detached
     * vehicle after the operation
     * @return, a bool indicating if the operation was successful
     */
    bool detachVehicle(Vehicle **vehicle);

    /**
     * Function for adding delay to the trian
     *
     * @param, a Time object with the amount of delay to be added
     */
    void addDelay(const Time &delay);

// Private data members
private:
    int mTrainNumber;

    double mTopSpeed, mSpeed;

    std::vector<int> mRequiredVehicles;

    std::vector<Vehicle *> mVehicles;

    Time mOrigDeparture, mCurrentDeparture, mOrigArrival, mCurrentArrival,
         mDelay, mDepartureDelay;

    Station *mOrigin, *mDestination;

    std::string mStatus;

    bool mIgnore;
};

/**
 * Overload of the << operator to allow easy printing of train info
 */
std::ostream &operator<<(std::ostream &os, const Train *const train);

#endif  // DT060G_PROJECT_TRAIN_H
