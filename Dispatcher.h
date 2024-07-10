#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Producer.h"

using namespace std;

class Dispatcher
{
private:
    vector<Bounded_Buffer*> queues;
    int numOfBounded_Buffers = 0;
    int numOfTerminatedBuffers = 0;
    Bounded_Buffer* NEWS;
    Bounded_Buffer* SPORT;
    Bounded_Buffer* WEATHER;

    int extractType(string element);

public:
    Dispatcher();
    void addBounded_Bufer(Bounded_Buffer* bBuffer);
    void dispatch();
    void addSPORT(Bounded_Buffer* bBuffer);
    void addNEWS(Bounded_Buffer* bBuffer);
    void addWEATHER(Bounded_Buffer* bBuffer);
};

#endif // DISPATCHER_H