#include <stdio.h>
#include <vector>
#include <iostream>
#include "Producer.h"

using namespace std;

// constructor
Producer::Producer(int bufferSize, int idP, int numOfArticals) : idP(idP), numOfArticals(numOfArticals)
{
    // create a new buffer
    this->bBuffer = new Bounded_Buffer(bufferSize);
}

void Producer::PDelete()
{
    // delete the buffer
    delete this->bBuffer;
}

// generator fo news
void Producer::generate()
{
    // generate random news
    srand(time(NULL));
    for (int i = 0; i < this->numOfArticals; i++)
    {
        // generate a random number
        int randNum = rand() % 3;
        // insert the article to the buffer
        string newArt = this->articals[randNum];
        // insert the article to the buffer
        this->bBuffer->insert("producer " + std::to_string(this->idP) + " " + newArt + " " + std::to_string(this->counters[randNum]));
        // increment the counter
        this->counters[randNum]++;
    }
    // insert an empty termination message
    this->bBuffer->insert("DONE");
    return;
}

Bounded_Buffer *Producer::getBounded_Buffer()
{
    // return the buffer
    return this->bBuffer;
}
