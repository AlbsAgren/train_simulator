/*
 * Simulation.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_SIMULATION_H
#define DT060G_PROJECT_SIMULATION_H

#include "MyTime.h"
#include "Event.h"

#include <queue>
#include <vector>
#include <memory>

/**
 * Class for managing the simulation of events
 */
class Simulation {
public:
    /**
     * Constructor
     */
    Simulation(): mCurrentTime(Time(0, 0)), mEventQueue() { }

    // Default destructor
    ~Simulation() = default;

    /**
     * Function for setting simulation time
     *
     * @param time, a Time object representing current sim time
     */
    void setTime(const Time &time) { mCurrentTime = time; }

    /**
     * Function for getting simulation time
     *
     * @return, a Time object representing current sim time
     */
    Time getTime() const { return mCurrentTime; }

    /**
     * Function for getting time of next event
     *
     * @return, a Time object representing time of next event
     */
    Time getNextEventTime() const { return mEventQueue.top()->getTime(); }

    /**
     * Function for scheduling a new event
     *
     * @param event, a shared_ptr to an event object
     */
    void scheduleEvent(const std::shared_ptr<Event> &event);

    /**
     * Function for processing the next event in the queue
     */
    void processNextEvent();

    /**
     * Function for advancing the simulation until all departed trains
     * are disassembled
     */
    void finishRunningTrains();

    /**
     * Function for discerning if simulation is done
     *
     * @return, a bool indicating if simulation queue is empty
     */
    bool done() { return mEventQueue.empty(); }

// Private data members
private:
    Time mCurrentTime;

    std::priority_queue<std::shared_ptr<Event>,
                        std::vector<std::shared_ptr<Event>>,
                        EventComparison> mEventQueue;
};

#endif  // DT060G_PROJECT_SIMULATION_H
