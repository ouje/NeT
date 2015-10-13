/*
 * buffer.cc
 *
 *  Created on: 29. 9. 2015
 *      Author: xoujez03
 *
 *      Inspired by OMNeT++ User Manual Version 4.6
 *      This file is distributed WITHOUT ANY WARRANTY. See the file `license' for details on this and other legal matters.
 *
 *
 */


#include <omnetpp.h>

/*
 * Buffer; see NED file for more info.
 *
 */

class buffer: public cSimpleModule {

    public:
    buffer();
    virtual ~buffer();
private:
    long counter;
    cStdDev countStat;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void endQueueAndSend(cMessage *msg);
    virtual void updateDisplay();                   // GUI buffer counter

    //messages
    cMessage *msgUnderService;
    cMessage *selfMsg;
    cQueue queue;                   //  Queue
    int sema;                       //  Client2 message confirmation
    int size;                       //  The limit of queue

    simsignal_t queuelenghtSignal = cComponent::registerSignal("gueuelenght");

};

Define_Module(buffer);

buffer::buffer() {
    msgUnderService = selfMsg = NULL;
}

buffer::~buffer() {
    delete msgUnderService;
    cancelAndDelete(selfMsg);

}

void buffer::initialize() {
    selfMsg = new cMessage("selfMessage");
    queue.setName("queue");
    sema = 1;
    counter = 0;
    size = par("sizeOfBuffer");
    WATCH(counter);
    countStat.setName("Buffer counter statistic");

}

void buffer::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage())
    {
        if (sema == 1) {
            endQueueAndSend(msgUnderService);
            sema = 0;
        } else {
            queue.insert(msgUnderService);
            msgUnderService = NULL;
        }

        if (queue.empty()) {

            msgUnderService = NULL; //we have empty queue and we will not send selfMessage scheduleAt(simTime() + 1, selfMsg);
        } else {
            msgUnderService = (cMessage *) queue.pop();
            emit(queuelenghtSignal, queue.length());
            scheduleAt(simTime() + 1, selfMsg);

        }
    } else if (!msgUnderService)  //if NOT msgServiced exists
    {
        if (msg->arrivedOn("portISwitch")) {
            msgUnderService = msg;
            scheduleAt(simTime(), selfMsg);

        } else {
            sema = 1;
            delete (msg);

        }

    } else {
        if (msg->arrivedOn("portISwitch")) {
            counter = queue.getLength();
            if (queue.length() < size) {
                queue.insert(msg);
            } else {
                send(msg, "toBucket");
            }

            if (ev.isGUI()) {
                updateDisplay();
            }
        } else {
            sema = 1;
            delete (msg);
        }

    }
}

void buffer::endQueueAndSend(cMessage *msg) {
    if (!msg->isSelfMessage())
        send(msg, "out");
}

void buffer::updateDisplay() {
    char buf[40];
    sprintf(buf, "In buffer is: %ld", counter);
    getDisplayString().setTagArg("t", 0, buf);
}

