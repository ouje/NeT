/*
 * client1.cc
 *
 *  Created on: 27. 9. 2015
 *      Author: xoujez03
 *
 *      Inspired by OMNeT++ User Manual Version 4.6
 *      This file is distributed WITHOUT ANY WARRANTY. See the file `license' for details on this and other legal matters.
 *
 *
 */

#include <omnetpp.h>

/*  This client is a generator of messages.
 *  If the messages reach a number == "Initial", this scenario will be stopped by OMNeT++ function endSimulation().
 */

class client1: public cSimpleModule {
public:
    client1();
    virtual ~client1();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay();

private:

    long counter;
    int toplimit;

    //messages
    cMessage *initialMessage;  // holds pointer to the self-message

};

Define_Module(client1);  //generator of messages

client1::client1() {
    initialMessage = NULL;
}

client1::~client1() {
    cancelAndDelete(initialMessage);
}

void client1::initialize() {

    counter = 0;
    toplimit = par("limit");
    WATCH(counter);
    initialMessage = new cMessage("Initial");
    scheduleAt(simTime(), initialMessage);

}

void client1::handleMessage(cMessage *msg) {
    if (counter <= toplimit) {
        cMessage *sendMessage = new cMessage("Message-1");
        send(sendMessage, "tx");
        counter++;
        if (ev.isGUI()) {
            updateDisplay();
        }
        scheduleAt(simTime() + 1, initialMessage);
    } else
        endSimulation();

}

void client1::updateDisplay() {
    char buf[40];
    sprintf(buf, "sent: %ld", counter);
    getDisplayString().setTagArg("t", 0, buf);
}
