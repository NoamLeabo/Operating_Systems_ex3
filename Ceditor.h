#ifndef CEDITOR_H
#define CEDITOR_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Bounded_Buffer.h"

using namespace std;

class Ceditor
{
private:
    Bounded_Buffer *forEdit;
    Bounded_Buffer *smanager;
    int idP;

public:
    Ceditor(int bufferSize, int idP);
    Bounded_Buffer *getBounded_Buffer();
    void addSmanager(Bounded_Buffer *bBuffer);
    void setBuffer(Bounded_Buffer *bBuffer);
    void edit();
};

#endif // CEDITOR_H
