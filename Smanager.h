#ifndef SMANAGER_H
#define SMANAGER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Bounded_Buffer.h"

using namespace std;

class Smanager
{
private:
    Bounded_Buffer *bBuffer;
    int numOfDones = 0;

public:
    Smanager();
    void print();
    Bounded_Buffer *getBounded_Buffer();
};

#endif // SMANAGER_H
