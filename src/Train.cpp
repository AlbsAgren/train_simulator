/*
 * Train.cpp
 * Project
 * Albin Ågren
 */

#include "Train.h"
#include "Vehicle.h"
#include "Station.h"

#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include <algorithm>

void Train::addDelay(const Time &delay) {
    // add the delay to departure and arrival times
    mCurrentDeparture += delay;
    mCurrentArrival += delay;
    mDelay += delay;
    mDepartureDelay += delay;
}

void Train::attachVehicle(Vehicle *vehicle) { 
    // remove one of the vehicle's type from the list of needed vehicles
    mRequiredVehicles.erase(std::find(mRequiredVehicles.begin(),
                                      mRequiredVehicles.end(),
                                      vehicle->getType()));

    vehicle->setTrain(this);    // point vehicle train pointer to this train

    // add the new vehicle to the train
    mVehicles.push_back(vehicle);
}

bool Train::detachVehicle(Vehicle **vehicle) {
    // remove a vehicle and return true unless vector empty
    if(!mVehicles.empty()) {
        *vehicle = mVehicles.front();
        (*vehicle)->setTrain(nullptr);  // remove vehicle pointer to train
        mVehicles.erase(mVehicles.begin());
        return true;
    } else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const Train *const train) {
    os << "Train " << train->getTrainNumber()
       << " (" << train->getStatus() << ") from " 
       << train->getOrigin()->getName() << " "
       << train->getOrigDeparture() << " (" 
       << train->getCurrentDeparture() << ") to " 
       << train->getDestination()->getName() << " "
       << train->getOrigArrival() << " ("
       << train->getCurrentArrival() << ") delay (" 
       << train->getDelay() << ") speed = " << train->getSpeed()
       << " km/h";

    return os;
}
