#include <stdio.h>
#include <vector>
#include <iostream>
#include "Smanager.h"
#include "Bounded_Buffer.h"

using namespace std;

// constructor
Smanager::Smanager(){
    this->bBuffer = new Bounded_Buffer(50);
}

void Smanager::print() {
    while (1) {
        std::string message = this->bBuffer->remove();
        if (message == "DONE") {
            this->numOfDones++;
            if (this->numOfDones == 3) {
                break;
            }
        } else {
            std::cout << message << std::endl;
        }
    }
    std::cout << "DONE" << std::endl;
}

Bounded_Buffer *Smanager::getBounded_Buffer()
{
    return this->bBuffer;
}
