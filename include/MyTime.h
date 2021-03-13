/*
 * MyTime.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_MYTIME_H
#define DT060G_PROJECT_MYTIME_H

#include <string>
#include <istream>
#include <ostream>

/**
 * Class for managing a duration in days, hours and minutes
 */
class Time {
public:
    /**
     * Default constructor
     */
    Time() = default;

    /**
     * Constructor for initializing all data members
     *
     * @param hours, the number of hours
     * @param minutes, the number of minutes
     */
    Time(const int &hours, const int &minutes);

    /**
     * Copy constructor
     *
     * @param time, a time object to be copied
     */
    Time(const Time &time);

    /**
     * Constructor for initalizing from time represented as a double
     *
     * @param timeAsDouble, a timestamp represented as a double
     */
    explicit Time(const double &timeAsDouble);

    /*
     * Overload of the assignment operator using a Time object
     */
    Time &operator=(const Time &time);

    /*
     * Overload of the assignment operator using a double (allows division)
     */
    Time &operator=(const double &timeAsDouble);

    /**
     * Function for setting hours
     *
     * @param hours, the number of hours
     */
    void setDay(const int &day) { mDay = day; }

    /**
     * Function for setting hours
     *
     * @param hours, the number of hours
     */
    void setHours(const int &hours) { mHours = hours; }

    /**
     * Function for setting minutes
     *
     * @param minutes, the number of minutes
     */
    void setMinutes(const int minutes) { mMinutes = minutes; }

    /**
     * Function for getting day
     *
     * @return, the day
     */
    int getDay() const { return mDay; }

    /**
     * Function for getting hours
     *
     * @return, the number of hours
     */
    int getHours() const { return mHours; }

    /**
     * Function for getting minutes
     *
     * @return, the number of minutes
     */
    int getMinutes() const { return mMinutes; }

    /**
     * Function for total in minutes time as an int
     *
     * @return, an int representing the total time in minutes
     */
    int getTotalTime() const;

    /**
     * Function for time in hours as a double
     *
     * @return, a double representing the total time in hours
     */
    double getTimeAsDouble() const;

    /**
     * Function for getting a formatted string of the stored time
     *
     * @return, a formatted string of the stored time
     */
    std::string getFormattedTime() const;

    /**
     * Overload of the + operator for adding two Time objects
     */
    Time operator+(const Time &time) const;

    /**
     * Overload of the + operator for subtracting two Time objects
     */
    Time operator-(const Time &time) const;

    /**
     * Overload of the < operator for comparing two Time objects
     */
    bool operator<(const Time &time) const;

    /**
     * Overload of the > operator for comparing two Time objects
     */
    bool operator>(const Time &time) const;

    /**
     * Overload of the == operator for comparing two Time objects
     */
    bool operator==(const Time &time) const;

    /**
     * Overload of the != operator for comparing two Time objects
     */
    bool operator!=(const Time &time) const;

    /**
     * Overload of the >= operator for comparing two Time objects
     */
    bool operator>=(const Time &time) const;

    /**
     * Overload of the prefix increment operator, increments 1 minute
     */
    Time &operator++();

    /**
     * Overload of the postfix increment operator, increments 1 minute
     */
    const Time operator++(int);

    /**
     * Overload of the += operator
     */
    Time &operator+=(const Time &time);

// Private data members
private:
    int mDay = 0, mHours = 0, mMinutes = 0;
};

/**
 * Overload of the << operator for outputting data to ostream object
 */
std::ostream &operator<<(std::ostream &os, const Time &time);

/**
 * Overload of the >> operator for reading data from istream object
 */
std::istream &operator>>(std::istream &is, Time &time);

#endif  // DT060G_PROJECT_MYTIME_H
