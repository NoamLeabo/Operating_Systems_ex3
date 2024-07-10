#ifndef PRODUCER_H
#define PRODUCER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Bounded_Buffer.h"

using namespace std;

class Producer
{
private:
    Bounded_Buffer *bBuffer;
    string articals[3] = {"SPORTS", "NEWS", "WEATHER"};
    int idP;
    int counters[3] = {0, 0, 0};
    int numOfArticals;

public:
    Producer(int bufferSize, int idP, int numOfArticals);
    void generate();
    Bounded_Buffer *getBounded_Buffer();
    void PDelete();
};

#endif // PRODUCER_H
