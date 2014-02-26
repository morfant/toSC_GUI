//
//  Osc.cpp
//  toSC
//
//  Created by giy on 2/26/14.
//
//

#include "Osc.h"

Osc::Osc(string addrP){
    addrPattern = addrP;
};

Osc::~Osc(){
}

void
Osc::init(){
    // open an outgoing connection to HOST:PORT
    sender.setup(host, port);
}



void
Osc::sendOSC(string cmd){
    ofxOscMessage m;
    m.setAddress(addrPattern);
    m.addStringArg(cmd);
    sender.sendMessage(m);
}

// ex : sendOSC('/test', "hello");
void
Osc::sendOSC(string destAddr, string cmd){
    ofxOscMessage m;
    m.setAddress(destAddr);
    m.addStringArg(cmd);
    sender.sendMessage(m);
}