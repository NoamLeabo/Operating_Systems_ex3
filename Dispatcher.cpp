#include <stdio.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Dispatcher.h"
#include <thread>
using namespace std;

// constructor
Dispatcher::Dispatcher() : queues() {}

// generator for news
void Dispatcher::addBounded_Bufer(Bounded_Buffer *bBuffer)
{
    this->queues.push_back(bBuffer);
    this->numOfBounded_Buffers = this->queues.size();
}

// extract the type from the element
int Dispatcher::extractType(std::string element)
{
    // extracting the type
    if (element.find("SPORTS") != std::string::npos)
        return 0;
    if (element.find("NEWS") != std::string::npos)
        return 1;
    if (element.find("WEATHER") != std::string::npos)
        return 2;
    return -1;
}

// dispatch the elements to the corresponding buffers
void Dispatcher::dispatch()
{
    // dispatch the elements to the corresponding buffers
    while (this->numOfTerminatedBuffers != this->numOfBounded_Buffers)
    {
        // iterate through the buffers
        for (auto &bBuffer : this->queues)
        {
            // if the buffer is empty, continue
            if (bBuffer->isEmpty())
            {
                continue;
            }

            // remove the element
            std::string element = bBuffer->remove();
            // if the element is "DONE", increment the number of terminated buffers
            if (element == "DONE")
            {
                this->numOfTerminatedBuffers++;
                continue;
            }
            // insert the element to the corresponding buffer
            switch (extractType(element))
            {
            case 0:
                this->SPORT->insert(element);
                break;
            case 1:
                this->NEWS->insert(element);
                break;
            case 2:
                this->WEATHER->insert(element);
                break;
            }
        }
        // sleep for 100 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // insert "DONE" to the buffers
    this->SPORT->insert("DONE");
    this->NEWS->insert("DONE");
    this->WEATHER->insert("DONE");
}

// add SPORT buffer
void Dispatcher::addSPORT(Bounded_Buffer *bBuffer) { this->SPORT = bBuffer; }

// add NEWS buffer
void Dispatcher::addNEWS(Bounded_Buffer *bBuffer) { this->NEWS = bBuffer; }

// add WEATHER buffer
void Dispatcher::addWEATHER(Bounded_Buffer *bBuffer) { this->WEATHER = bBuffer; }
