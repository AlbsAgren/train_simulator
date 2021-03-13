/*
 * Event.h
 * Project
 * Albin Ågren
 */

#ifndef DT060G_PROJECT_EVENT_H
#define DT060G_PROJECT_EVENT_H

#include "MyTime.h"

#include <memory>

// Forward declarations
class Simulation;
class Controller;
class Train;

/**
 * Virtual base class representing simulation events
 */
class Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     */
    explicit Event(const Time &time): mTime(time) { }

    // Virtual destructor
    virtual ~Event() { }

    /**
     * Function for processing the event, pure virtual
     */
    virtual void processEvent() = 0;

    /**
     * Function for getting event type, pure virtual
     *
     * @return, an int representing the event type
     */
    virtual int getType() const = 0;

    /**
     * Function for getting event time
     *
     * @return, a Time object with the event time
     */
    Time getTime() const { return mTime; }

// Protected data members
protected:
    Time mTime;
};

// Class for compairing events by their time, for use with std::priority_queue
class EventComparison {
public:
    bool operator()(const std::shared_ptr<Event> &left,
                    const std::shared_ptr<Event> &right) {
        return left->getTime() > right->getTime();
    }
};

/**
 * Class representing train assembly
 */
class AssemblyEvent : public Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     * @param sim, a pointer to the simulation object
     * @param controller, a pointer to the controller object
     * @ train, a pointer to the train participating in the event
     */
    AssemblyEvent(const Time &time, Simulation *const sim,
                  Controller *const controller, Train *const train):
                                                     Event(time),
                                                     mSim(sim),
                                                     mController(controller),
                                                     mTrain(train) { }

    // Virtual destructor
    virtual ~AssemblyEvent() { }

    /**
     * Function for processing the event
     */
    void processEvent() override;

    /**
     * Function for getting event type
     *
     * @return, an int representing the event type
     */
    int getType() const override { return 0; }

// Private data members
private:
    Simulation *mSim;
    Controller *mController;
    Train *mTrain;
};

/**
 * Class representing the train arriving at the platform, ready to depart
 */
class ReadyEvent : public Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     * @param sim, a pointer to the simulation object
     * @param controller, a pointer to the controller object
     * @ train, a pointer to the train participating in the event
     */
    ReadyEvent(const Time time, Simulation *const sim,
               Controller *const controller, Train *const train):
                                                     Event(time),
                                                     mSim(sim),
                                                     mController(controller),
                                                     mTrain(train) { }

    // Virtual destructor
    virtual ~ReadyEvent() { }

    /**
     * Function for processing the event
     */
    void processEvent() override;

    /**
     * Function for getting event type
     *
     * @return, an int representing the event type
     */
    int getType() const override { return 1; }

// Private data members
private:
    Simulation *mSim;
    Controller *mController;
    Train *mTrain;
};

/**
 * Class representing train departure event
 */
class DepartureEvent : public Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     * @param sim, a pointer to the simulation object
     * @param controller, a pointer to the controller object
     * @ train, a pointer to the train participating in the event
     */
    DepartureEvent(const Time time, Simulation *const sim,
                   Controller *const controller, Train *const train):
                                                     Event(time),
                                                     mSim(sim),
                                                     mController(controller),
                                                     mTrain(train) { }

    // Virtual destructor
    virtual ~DepartureEvent() { }

    /**
     * Function for processing the event
     */
    void processEvent() override;

    /**
     * Function for getting event type
     *
     * @return, an int representing the event type
     */
    int getType() const override { return 2; }

// Private data members
private:
    Simulation *mSim;
    Controller *mController;
    Train *mTrain;
};

/**
 * Class representing train arrival at the destination
 */
class ArrivalEvent : public Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     * @param sim, a pointer to the simulation object
     * @param controller, a pointer to the controller object
     * @ train, a pointer to the train participating in the event
     */
    ArrivalEvent(const Time time, Simulation *const sim,
                 Controller *const controller, Train *const train):
                                                     Event(time),
                                                     mSim(sim),
                                                     mController(controller),
                                                     mTrain(train) { }

    // Virtual destructor
    virtual ~ArrivalEvent() { }

    /**
     * Function for processing the event
     */
    void processEvent() override;

    /**
     * Function for getting event type
     *
     * @return, an int representing the event type
     */
    int getType() const override { return 3; }

// Private data members
private:
    Simulation *mSim;
    Controller *mController;
    Train *mTrain;
};

/**
 * Class representing train disassembly event
 */
class DisassemblyEvent : public Event {
public:
    /**
     * Constructor
     *
     * @param time, the event time
     * @param sim, a pointer to the simulation object
     * @param controller, a pointer to the controller object
     * @ train, a pointer to the train participating in the event
     */
    DisassemblyEvent(const Time time, Simulation *const sim,
                     Controller *const controller, Train *const train):
                                                     Event(time),
                                                     mSim(sim),
                                                     mController(controller),
                                                     mTrain(train) { }

    // Virtual destructor
    virtual ~DisassemblyEvent() { }

    /**
     * Function for processing the event
     */
    void processEvent() override;

    /**
     * Function for getting event type
     *
     * @return, an int representing the event type
     */
    int getType() const override { return 4; }

// Private data members
private:
    Simulation *mSim;
    Controller *mController;
    Train *mTrain;
};

#endif  // DT060G_PROJECT_EVENT_H
