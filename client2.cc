/*
 * client2.cc
 *
 *  Created on: 28. 9. 2015
 *      Author: xoujez03
 *
 *      Inspired by OMNeT++ User Manual Version 4.6
 *      This file is distributed WITHOUT ANY WARRANTY. See the file `license' for details on this and other legal matters.
 *
 *
 */

#include <omnetpp.h>

/*
 * Client2; This module consumes messages from Client1 and sends the "Continue" message confirmation to the switch module.
 *
 */

class client2: public cSimpleModule {
public:
    client2();
    virtual ~client2();
private:
    cMessage *endServiceMsg;
    cMessage *selfMsg;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

Define_Module(client2);

client2::client2() {
    selfMsg = NULL;
}

client2::~client2() {
    cancelAndDelete(selfMsg);
}

void client2::initialize() {

}

void client2::handleMessage(cMessage *msg) {
    delete msg;
    endServiceMsg = new cMessage("Continue");
    send(endServiceMsg, "tx");
    endServiceMsg = NULL;

}

