#pragma once

#include "ofMain.h"

#include "bug.hpp"

class Bug_leader : public Bug {
public:
    
    virtual void update();
    virtual void display();
    virtual void bear(Bug _child);
    
};

