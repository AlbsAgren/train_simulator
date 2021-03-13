/*
 * Vehicle.cpp
 * Project
 * Albin Ågren
 */

#include "Vehicle.h"
#include "MyTime.h"

#include <string>
#include <sstream>
#include <vector>

void Vehicle::addHistory(const std::string &event, const Time &time) {
    // create a string with the timestamp and the event description
    std::string tmpStr = time.getFormattedTime() + " " + event;
    mHistory.push_back(tmpStr);     // add event to member vector
}

std::string Coach::getInfo() const {
    std::stringstream ss;
    // use a stringstream object to format vehicle info
    ss << "[" << getTypeName() << "] id: " << getId() << ", seats: " << mSeats
       << ", internet: " << (mInternet ? "yes" : "no");

    return ss.str();    // return info as string
}

std::string Sleeper::getInfo() const {
    std::stringstream ss;
    ss << "[" << getTypeName() << "] id: " << getId() << ", beds: " << mBeds;

    return ss.str();
}

std::string OpenWagon::getInfo() const {
    std::stringstream ss;
    ss << "[" << getTypeName() << "] id: " << getId() << ", capacity: " << mCapacity
       << " tn, cargo area: " << mArea << " m2";

    return ss.str();
}

std::string CoveredWagon::getInfo() const {
    std::stringstream ss;
    ss << "[" << getTypeName() << "] id: " << getId() << ", volume: " << mVolume
       << " m3";

    return ss.str();
}

std::string ElectricLocomotive::getInfo() const {
    std::stringstream ss;
    ss << "[" << getTypeName() << "] id: " << getId() << ", top speed: " << mTopSpeed
       << " km/h, power: " << mPower << " kw";

    return ss.str();
}

std::string DieselLocomotive::getInfo() const {
    std::stringstream ss;
    ss << "[" << getTypeName() << "] id: " << getId() << ", top speed: " << mTopSpeed
       << " km/h, fuel consumption: " << mConsumption << " l/h";

    return ss.str();
}
