#include "MyTime.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

Time::Time(const int &hours, const int &minutes) {
    // add the arguments to the members
    mMinutes += minutes;
    mHours += hours;

    // increment day if hours > 23
    if(mHours > 23) {
        mHours -= 24;
        ++mDay;
    }

    // convert to proper units, eg if minutes now > 60
    mHours += mMinutes / 60;
    mMinutes %= 60;
}

Time::Time(const Time &time) {
    mMinutes = time.getMinutes();
    mHours = time.getHours();
    mDay = time.getDay();
}

Time::Time(const double &timeAsDouble) {
    double hours, minutes;

    // use modf to separate fractional and integer parts
    minutes = std::modf(timeAsDouble, &hours);

    // convert to integer member values
    mMinutes = static_cast<int>(minutes * 60);
    mHours = static_cast<int>(hours);
}

Time &Time::operator=(const Time &time) {
    mMinutes = time.getMinutes();
    mHours = time.getHours();
    mDay = time.getDay();

    return *this;
}

Time &Time::operator=(const double &timeAsDouble) {
    double hours, minutes;

    // use modf to separate fractional and integer parts
    minutes = std::modf(timeAsDouble, &hours);

    // convert to integer member values
    mMinutes = static_cast<int>(minutes * 60);
    mHours = static_cast<int>(hours);
    mDay = 0;

    while(mHours > 23) {
        mHours -= 24;
        ++mDay;
    }

    return *this;
}

std::string Time::getFormattedTime() const {
    std::stringstream ss;

    // format time as appropriate
    if(mDay != 0) {
        ss << std::setw(2) << std::setfill('0') << getDay() << ':'
           << std::setw(2) << std::setfill('0') << getHours() << ':'
           << std::setw(2) << std::setfill('0') << getMinutes();
    } else if(!getHours()) {
        ss << "00:"<< std::setw(2) << std::setfill('0') << getMinutes();
    } else {
        ss << std::setw(2) << std::setfill('0') << getHours() 
           << ':' << std::setw(2) << std::setfill('0') << getMinutes();
    }
    return ss.str();
}

int Time::getTotalTime() const {
    // sum all time as minutes
    int minutes = mMinutes;
    minutes += mHours * 60;
    minutes += mDay * 24 * 60;

    return minutes;
}

double Time::getTimeAsDouble() const {
    double timeDouble = mMinutes / 60.0;

    timeDouble += mHours;

    return timeDouble;
}

// TODO, REMOVE IF NOT NEEDED
Time Time::operator+(const Time &time) const {
    int minutes, hours;
    // get raw time in minutes
    int totalTime = getTotalTime() + time.getTotalTime();

    // convert to proper units
    hours = totalTime / 60;
    minutes = totalTime % 60;

    // create new time object and return it
    Time sum(hours, minutes);
    return sum;
}

// TODO, REMOVE IF NOT NEEDED
Time Time::operator-(const Time &time) const {
    int minutes, hours;
    // get raw time in minutes
    int totalTime = getTotalTime() - time.getTotalTime();

    // convert to proper units
    hours = totalTime / 60;
    minutes = totalTime % 60;

    // create new time object and return it
    Time difference(hours, minutes);
    return difference;
}


bool Time::operator<(const Time &time) const {
    // sum duration in minutes for both objects
    int lMinutes = getTotalTime();
    int rMinutes = time.getTotalTime();

    return lMinutes < rMinutes;
}

bool Time::operator>(const Time &time) const {
    // sum duration in minutes for both objects
    int lMinutes = getTotalTime();
    int rMinutes = time.getTotalTime();

    return lMinutes > rMinutes;
}

bool Time::operator==(const Time &time) const {
    // true if duration is exactly equal
    return(getTotalTime() == time.getTotalTime());
}

bool Time::operator!=(const Time &time) const {
    // true if duration is exactly equal
    return(getTotalTime() != time.getTotalTime());
}

bool Time::operator>=(const Time &time) const {
    // true if duration greater than or equal
    return(getTotalTime() >= time.getTotalTime());
}


Time &Time::operator++() {
    ++mMinutes;
    mHours += mMinutes / 60;
    mMinutes %= 60;

    while(mHours > 23) {
        mHours -= 24;
        ++mDay;
    }

    return *this;
}

const Time Time::operator++(int) {
    Time tmp = *this;
    ++*this;    // use the prefix operator to increment object
    return tmp;
}

Time &Time::operator+=(const Time &time) {
    mMinutes += time.getMinutes();
    mHours += time.getHours();
    mDay += time.getDay();

    mHours += mMinutes / 60;
    mMinutes %= 60;

    while(mHours > 23) {
        mHours -= 24;
        ++mDay;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Time &time) {
    // output class data to ostream object and return it
    os << time.getFormattedTime();
    return os;
}

std::istream &operator>>(std::istream &is, Time &time) {
    std::string tmpStr;

    // read the data
    std::getline(is, tmpStr, ':');

    // convert to int
    int hours = std::stoi(tmpStr);

    // save to object
    time.setHours(hours);

    // convert to minutes and save in object
    std::getline(is, tmpStr, ' ');

    int minutes = std::stoi(tmpStr);

    time.setMinutes(minutes);

    return is;
}
