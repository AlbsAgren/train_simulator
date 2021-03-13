/*
 * Event.cpp
 * Project
 * Albin Ågren
 */

#include "Event.h"
#include "MyTime.h"
#include "Controller.h"
#include "Simulation.h"
#include "Train.h"

#include <memory>
#include <string>

void AssemblyEvent::processEvent() {
    Time nextEventTime;
    std::shared_ptr<Event> nextEvent;

    if(mController->attemptAssembly(mTrain)) {
        // schedule departure event 10 minutes in the future
        nextEventTime = mTrain->getCurrentDeparture() - Time(0, 10);
        nextEvent = std::make_shared<ReadyEvent>(nextEventTime,
                                                 mSim,
                                                 mController,
                                                 mTrain);
        mSim->scheduleEvent(nextEvent);

    // if assembly fails, schedule new attempt unless day has passed
    } else {
        // if incomplete, schedule new try in 10 minutes
        nextEventTime = mTime + Time(0, 10);

        // only schedule another try if still on day 0
        if(nextEventTime.getDay() == 0) {
            nextEvent = std::make_shared<AssemblyEvent>(nextEventTime,
                                                        mSim,
                                                        mController,
                                                        mTrain);

            mSim->scheduleEvent(nextEvent);
        }
    }
}

void ReadyEvent::processEvent() {
    mController->readyUp(mTrain);

    Time nextEventTime = mTrain->getCurrentDeparture();

    // create and schedule departure event
    std::shared_ptr<Event> nextEvent = std::make_shared<DepartureEvent>(
                                                                nextEventTime,
                                                                mSim,
                                                                mController,
                                                                mTrain);
    mSim->scheduleEvent(nextEvent);
}

void DepartureEvent::processEvent() {
    mController->depart(mTrain);

    // create and schedule upcoming arrival event
    Time nextEventTime = mTrain->getCurrentArrival();
    std::shared_ptr<Event> nextEvent = std::make_shared<ArrivalEvent>(
                                                                nextEventTime,
                                                                mSim,
                                                                mController,
                                                                mTrain);
    mSim->scheduleEvent(nextEvent);
}

void ArrivalEvent::processEvent() {
    mController->arrive(mTrain);

    // create and schedule upcoming disassembly event
    Time nextEventTime = mTime + Time(0, 20);
    std::shared_ptr<Event> nextEvent = std::make_shared<DisassemblyEvent>(
                                                                nextEventTime,
                                                                mSim,
                                                                mController,
                                                                mTrain);
    mSim->scheduleEvent(nextEvent);
}

void DisassemblyEvent::processEvent() {
    // disassemble the train
    mController->disassemble(mTrain);
}
