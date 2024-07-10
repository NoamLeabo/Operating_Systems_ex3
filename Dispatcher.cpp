#include <stdio.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Dispatcher.h"
#include <thread>
using namespace std;

//constructor
Dispatcher::Dispatcher(): queues(){}

//generator fo news
void Dispatcher::addBounded_Bufer(Bounded_Buffer* bBuffer) { 
    this->queues.push_back(bBuffer);  
    this->numOfBounded_Buffers = this->queues.size();
}

int Dispatcher::extractType(std::string element) {
    // Extracting the type (simplified)
    if (element.find("SPORTS") != std::string::npos) return 0;
    if (element.find("NEWS") != std::string::npos) return 1;
    if (element.find("WEATHER") != std::string::npos) return 2;
    return -1;
}

void Dispatcher::dispatch() {
    while (this->numOfTerminatedBuffers != this->numOfBounded_Buffers) {
        for (auto& bBuffer : this->queues) {
            std::string element = bBuffer->remove();
            if (element == "DONE") {
                this->numOfTerminatedBuffers++;
                continue;
            }

            switch (extractType(element)) {
                case 0: this->SPORT->insert(element); break;
                case 1: this->NEWS->insert(element); break;
                case 2: this->WEATHER->insert(element); break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    this->SPORT->insert("DONE");
    this->NEWS->insert("DONE");
    this->WEATHER->insert("DONE");
}

void Dispatcher::addSPORT(Bounded_Buffer* bBuffer) { this->SPORT = bBuffer; }
void Dispatcher::addNEWS(Bounded_Buffer* bBuffer) { this->NEWS = bBuffer; }
void Dispatcher::addWEATHER(Bounded_Buffer* bBuffer) { this->WEATHER = bBuffer; }
