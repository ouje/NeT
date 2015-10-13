/*
 * bucket.cc
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

/*
 * Bucket; see NED file for more info.
 */

class bucket: public cSimpleModule {
private:
    long counter;
protected:

    virtual void handleMessage(cMessage *msg);
    virtual void initialize();
    virtual void updateDisplay();
};

Define_Module(bucket);

void bucket::initialize() {
    counter = 0;
    WATCH(counter);

}

void bucket::handleMessage(cMessage *msg) {
    counter++;
    delete msg;
    if (ev.isGUI()) {
        updateDisplay();
    }

}

void bucket::updateDisplay() {
    char buf[40];
    sprintf(buf, "In bucket is: %ld", counter);
    getDisplayString().setTagArg("t", 0, buf);
}
