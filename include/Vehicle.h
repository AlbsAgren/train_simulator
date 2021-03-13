/*
 * Vehicle.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_VEHICLE_H
#define DT060G_PROJECT_VEHICLE_H

#include "MyTime.h"
#include "Train.h"
#include "Station.h"

#include <vector>
#include <memory>
#include <string>

/**
 * Virtual base class for representing vehicles
 */
class Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     */
    explicit Vehicle(const int &id): mId(id), mTrain(nullptr),
                                     mStation(nullptr) { }

    // Virtual destructor
    virtual ~Vehicle() { }

    /**
     * Function for setting which train vehicle is attached to
     *
     * @param train, a pointer to a train
     */
    void setTrain(Train *const train) { mTrain = train; }

    /**
     * Function for setting which station vehicle is attached to
     *
     * @param station, a pointer to a station
     */
    void setStation(Station *const station) { mStation = station; }

    /**
     * Function for getting vehicle id
     *
     * @return, vehicle id
     */
    int getId() const { return mId; }

    /**
     * Function for getting vehicle history
     *
     * @return, a vector of strings recording all vehicle events
     */
    std::vector<std::string> getHistory() const { return mHistory; }

    /**
     * Function for getting the train to which vehicle is attached
     *
     * @return, a pointer to the train to which the vehicle is attached
     * or a nullptr if vehicle is not attached to a train
     */
    Train *getTrain() const { return mTrain; }

    /**
     * Function for getting the station to which vehicle is attached
     *
     * @return, a pointer to the station to which the vehicle is attached
     * or a nullptr if vehicle is not attached to a station pool
     */
    Station *getStation() const { return mStation; }

    /**
     * Function for getting vehicle type, pure virtual
     *
     * @return, an int representing vehicle type
     */
    virtual int getType() const = 0;

    /**
     * Function for getting vehicle type name, pure virtual
     *
     * @return, an string describing vehicle type
     */
    virtual std::string getTypeName() const = 0;

    /**
     * Function for getting vehicle info, pure virtual
     *
     * @return, a string with vehicle info
     */
    virtual std::string getInfo() const = 0;

    /**
     * Function for getting number of seats
     *
     * @return, an int representing the number of seats
     */
    virtual int getNoOfSeats() const { return 0; }

    /**
     * Function for determining if vehicle has internet
     *
     * @return, a bool indicating if vehicle has internet
     */
    virtual bool hasInternet() const { return false; }

    /**
     * Function for getting number of beds
     *
     * @return, an int representing the number of beds
     */
    virtual int getNoOfBeds() const { return 0; }

    /**
     * Function for getting cargo capacity
     *
     * @return, an int representing the capacity in tons
     */
    virtual int getCargoCapacity() const { return 0; }

    /**
     * Function for getting cargo area
     *
     * @return, an int representing the area in m2
     */
    virtual int getCargoArea() const { return 0; }

    /**
     * Function for getting cargo volume
     *
     * @return, an int representing the volume in m3
     */
    virtual int getCargoVolume() const { return 0; }

    /**
     * Function for getting top speed
     *
     * @return, a double representing the top speed in km/h
     */
    virtual double getTopSpeed() const { return 0; }

    /**
     * Function for getting vehicle power
     *
     * @return, an int representing the power in kw
     */
    virtual int getPower() const { return 0; }

    /**
     * Function for getting vehicle fuel consumption
     *
     * @return, an int representing the power in l/km
     */
    virtual int getFuelConsumption() const { return 0; }

    /**
     * Function for adding a new event to vehicle history
     *
     * @param event, a sting describing the event
     * @param time, a Time object with the event time
     */
    void addHistory(const std::string &event, const Time &time);

// Private data members
private:
    int mId;

    std::vector<std::string> mHistory;

    Train *mTrain;
    Station *mStation;
};

/**
 * Class representing a coach vehicle
 */
class Coach : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param seats, the number of seats
     * @param internet, a bool indicating if vehicle has internet
     */
    Coach(const int &id, const int &seats, const bool &internet):
                                                     Vehicle(id),
                                                     mSeats(seats),
                                                     mInternet(internet) { }

    // Virtual destructor
    virtual ~Coach() { }

    /**
     * Function for getting vehicle type
     *
     * @return, an int representing vehicle type
     */
    int getType() const override { return 0; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Coach"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting number of seats
     *
     * @return, an int representing the number of seats
     */
    int getNoOfSeats() const override { return mSeats; }

    /**
     * Function for determining if vehicle has internet
     *
     * @return, a bool indicating if vehicle has internet
     */
    bool hasInternet() const override { return mInternet; }

// Private data members
private:
    int mSeats;
    bool mInternet;
};

/**
 * Class representing a sleeper vehicle
 */
class Sleeper : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param beds, the number of beds
     */
    Sleeper(const int &id, const int &beds): Vehicle(id), mBeds(beds) { }

    // Virtual destructor
    virtual ~Sleeper() { }

    /**
     * Function for getting vehicle type
     *
     * @return, an int representing vehicle type
     */
    int getType() const override { return 1; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Sleeper"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting number of beds
     *
     * @return, an int representing the number of beds
     */
    int getNoOfBeds() const override { return mBeds; }

// Private data members
private:
    int mBeds;
};

/**
 * Class representing an open cargo wagon vehicle
 */
class OpenWagon : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param capacity, the capacity in tons
     * @param area, the cargo area in m2
     */
    OpenWagon(const int &id, const int &capacity, const int &area):
                                                        Vehicle(id),
                                                        mCapacity(capacity),
                                                        mArea(area) { }

    // Virtual destructor
    virtual ~OpenWagon() { }

    /**
     * Function for getting vehicle type
     *
     * @return, an int representing vehicle type
     */
    int getType() const override { return 2; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Open Wagon"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting cargo capacity
     *
     * @return, an int representing the capacity in tons
     */
    int getCargoCapacity() const override { return mCapacity; }

    /**
     * Function for getting cargo area
     *
     * @return, an int representing the area in m2
     */
    int getCargoArea() const override { return mArea; }

// Private data members
private:
    int mCapacity, mArea;
};

/**
 * Class representing a covered wagon vehicle
 */
class CoveredWagon : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param volume, the cargo volume in m3
     */
    CoveredWagon(const int &id, const int &volume): Vehicle(id),
                                                    mVolume(volume) { }

    // Virtual destructor
    virtual ~CoveredWagon() { }

    /**
     * Function for getting vehicle type
     *
     * @return, an int representing vehicle type
     */
    int getType() const override { return 3; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Covered Wagon"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting cargo volume
     *
     * @return, an int representing the volume in m3
     */
    int getCargoVolume() const override { return mVolume; }

// Private data members
private:
    int mVolume;
};

/**
 * Class representing an electric locomotive vehicle
 */
class ElectricLocomotive : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param topSpeed, vehicle top speed in km/h
     * @param power, the power in kw
     */
    ElectricLocomotive(const int &id, const double &topSpeed,
                       const int &power):               Vehicle(id),
                                                        mTopSpeed(topSpeed),
                                                        mPower(power) { }

    // Virtual destructor
    virtual ~ElectricLocomotive() { }

    /**
     * Function for getting vehicle type
     *
     * @return, an int representing vehicle type
     */
    int getType() const override { return 4; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Electric Locomotive"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting top speed
     *
     * @return, a double representing the top speed in km/h
     */
    double getTopSpeed() const override { return mTopSpeed; }

    /**
     * Function for getting vehicle power
     *
     * @return, an int representing the power in kw
     */
    int getPower() const override { return mPower; }

// Private data members
private:
    double mTopSpeed;
    int mPower;
};

/**
 * Class representing a diesel locomotive vehicle
 */
class DieselLocomotive : public Vehicle {
public:
    /**
     * Constructor
     *
     * @param id, the vehicle id
     * @param topSpeed, vehicle top speed in km/h
     * @param consumption, the consumption in l/h
     */
    DieselLocomotive(const int &id, const double &topSpeed, 
                     const int &consumption): Vehicle(id),
                                              mTopSpeed(topSpeed),
                                              mConsumption(consumption) { }

    // Virtual destructor
    virtual ~DieselLocomotive() { }

    /**
     * Function for getting vehicle type
     *
     * @return, a double representing vehicle type
     */
    int getType() const override { return 5; }

    /**
     * Function for getting vehicle type name
     *
     * @return, an string describing vehicle type
     */
    std::string getTypeName() const override { return "Diesel Locomotive"; }

    /**
     * Function for getting vehicle info
     *
     * @return, a string with vehicle info
     */
    std::string getInfo() const override;

    /**
     * Function for getting top speed
     *
     * @return, an int representing the top speed in km/h
     */
    double getTopSpeed() const override { return mTopSpeed; }

    /**
     * Function for getting vehicle fuel consumption
     *
     * @return, an int representing the power in l/h
     */
    int getFuelConsumption() const override { return mConsumption; }

// Private data members
private:
    double mTopSpeed;
    int mConsumption;
};

#endif  // DT060G_PROJECT_VEHICLE_H
