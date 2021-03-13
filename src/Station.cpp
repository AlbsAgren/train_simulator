/*
 * Train.cpp
 * Project
 * Albin Ågren
 */

#include "Station.h"
#include "Vehicle.h"

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

void Station::setDistance(const std::string &stationName, const double &distance) {
    // insert a key-value pair representing the distance to another station
    mDistances.insert(std::pair<std::string, double>(stationName, distance));
}

void Station::attachVehicle(Vehicle *const vehicle) {
    // add vehicle to vector and set vehicle station member pointer
    mVehicles.push_back(vehicle);
    vehicle->setStation(this);
}

bool Station::detachVehicle(const int &type, Vehicle **vehicle) {
    // use find_if with lambda to find vehicles of matching type
    auto it = std::find_if(mVehicles.begin(), mVehicles.end(), 
                           [type](Vehicle *vehicle)
                                { return vehicle->getType() == type; });

    // if vehicle found, remove it from the member vector and return true
    if(it != mVehicles.end()) {
        *vehicle = *it;
        (*it)->setStation(nullptr);     // unset the vehicle station pointer
        mVehicles.erase(it);
        return true;
    } else {
        return false;
    }
}
