/*
 * Simulation.cpp
 * Project
 * Albin Ågren
 */

#include "Simulation.h"
#include "Event.h"

#include <queue>
#include <vector>
#include <memory>

void Simulation::scheduleEvent(const std::shared_ptr<Event> &event) {
    // add event to queue
    mEventQueue.push(event);
}

void Simulation::processNextEvent() {
    // get next event from queue and pop it
    std::shared_ptr<Event> nextEvent = mEventQueue.top();
    mEventQueue.pop();

    // set the time
    mCurrentTime = nextEvent->getTime();

    // process the event
    nextEvent->processEvent();
}

void Simulation::finishRunningTrains() {
    std::shared_ptr<Event> nextEvent;

    // pop all events, process those for departed trains
    while(!mEventQueue.empty()) {
        nextEvent = mEventQueue.top();
        // only process events for departed trains
        if(nextEvent->getType() > 2) {
            mCurrentTime = nextEvent->getTime();
            nextEvent->processEvent();
        }
        mEventQueue.pop();
    }
}
