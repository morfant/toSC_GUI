//
//  Osc.h
//  toSC
//
//  Created by giy on 2/26/14.
//
//

#pragma once
#include <iostream>
#include "ofxOsc.h"

class Osc{
protected:
    
    // OSC
    ofxOscSender    sender;
    const string    host = "localhost";
    const int       port = 57120;
    string          addrPattern;
    
    
public:
    
    Osc(string addrPattern);
    ~Osc();
    
    void    init();
    void    sendOSC(string cmd);    
    void    sendOSC(string destAddr, string cmd);
    
};
