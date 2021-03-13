/*
 * Station.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_STATION_H
#define DT060G_PROJECT_STATION_H

#include <string>
#include <memory>
#include <vector>
#include <map>

// Forward declaration
class Vehicle;

/**
 * Class representing a single station
 */
class Station {
public:
    /**
     * Constructor
     *
     * @param name, the number of hours
     */
    explicit Station(const std::string &name): mName(name) { }

    // Default destructor
    ~Station() = default;

    /**
     * Function for setting the distance to another station
     *
     * @param stationName, the name of the other station
     * @param distance, a double with the distance to the other station
     */
    void setDistance(const std::string &stationName, const double &distance);

    /**
     * Function for getting station name
     *
     * @return, the station name
     */
    std::string getName() const { return mName; }

    /**
     * Function for getting station vehicle pool
     *
     * @return, a vector of pointers to the attached vehicles
     */
    std::vector<Vehicle *> getVehicles() const { return mVehicles; }

    /**
     * Function for getting distance to another station
     *
     * @param stationName, the name of the other station
     * @return, a double with the distance to the other station
     */
    double getDistance(const std::string &stationName) const
        { return mDistances.at(stationName); }

    /**
     * Function for attaching a vehicle to station pool
     *
     * @param vehicle, a pointer to the vehicle to be attached
     */
    void attachVehicle(Vehicle *const vehicle);

    /**
     * Function for detatching a vehicle of the specified type
     *
     * @param type, the type of the desired vehicle
     * @param vehicle, a pointer to a pointer in which to store the
     * detached vehicle
     * @return, a bool indicating if a vehicle of the speicfied type was found
     */
    bool detachVehicle(const int &type, Vehicle **vehicle);

// Private data members
private:
    std::string mName;

    std::vector<Vehicle *> mVehicles;

    std::map<std::string, double> mDistances;
};

#endif  // DT060G_PROJECT_STATION_H
