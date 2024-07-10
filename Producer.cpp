#include <stdio.h>
#include <vector>
#include <iostream>
#include "Producer.h"

using namespace std;

// constructor
Producer::Producer(int bufferSize, int idP, int numOfArticals) : idP(idP), numOfArticals(numOfArticals)
{
    this->bBuffer = new Bounded_Buffer(bufferSize);
}

void Producer::PDelete()
{
    delete this->bBuffer;
}

// generator fo news
void Producer::generate()
{
    srand(time(NULL));
    for (int i = 0; i < this->numOfArticals; i++)
    {
        int randNum = rand() % 3;
        string newArt = this->articals[randNum];
        this->bBuffer->insert("producer " + std::to_string(this->idP) + " " + newArt + " " + std::to_string(this->counters[randNum]));
        this->counters[randNum]++;
    }
    // insert an empty termination message
    this->bBuffer->insert("DONE");
    return;
}

Bounded_Buffer *Producer::getBounded_Buffer()
{
    return this->bBuffer;
}
