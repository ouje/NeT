/*
 * iSwitch.cc
 *
 *  Created on: 28. 9. 2015
 *      Author: xoujez03
 *
 *      Inspired by OMNeT++ User Manual Version 4.6
 *      This file is distributed WITHOUT ANY WARRANTY. See the file `license' for details on this and other legal matters.
 *
 *
 */

#define FSM_DEBUG
#include <string.h>
#include <omnetpp.h>

/*
 * Switch; see NED file for more info. This part is not fully complete.
 * SelfMessages have to be implemented. Also undisposed objects.
 * print-undisposed=false command is sets in omnetpp.ini to sweep them.
 */

class iSwitch: public cSimpleModule {
public:
    iSwitch();
    virtual ~iSwitch();
protected:
    cFSM fsm;
    enum {
        INIT = 0,
        ACTIVE = FSM_Steady(1),
        SEND = FSM_Transient(1),
        SEND2 = FSM_Transient(2),
    };

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    //messages
    //cMessage *selfMsg;
};

Define_Module(iSwitch);

iSwitch::iSwitch() {
}

iSwitch::~iSwitch() {
}
void iSwitch::initialize() {
    fsm.setName("fsm");
}

void iSwitch::handleMessage(cMessage *msg) {

    FSM_Switch(fsm)
    {

    case FSM_Enter(INIT):
        break;
    case FSM_Exit(INIT):
        FSM_Goto(fsm, ACTIVE);
        break;
    case FSM_Exit(ACTIVE):
        if (strcmp("Message-1", msg->getName()) == 0) {
            FSM_Goto(fsm, SEND);
        } else if (strcmp("Message-XY", msg->getName()) == 0) {
            FSM_Goto(fsm, SEND2);
        } else {
            error("ACTIVE STATE ERROR");
        }
        break;
    case FSM_Exit(SEND): {
        EV << "Received message" << msg->getName()
                  << ", sending it out to buffer\n";
        send(msg, "dim2ToClient2");

        FSM_Goto(fsm, ACTIVE);
        break;
    }
    case FSM_EnterExit(SEND2): {
        FSM_Goto(fsm, ACTIVE);
        break;
    }

    }
}

