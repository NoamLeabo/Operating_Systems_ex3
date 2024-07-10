#include <stdio.h>
#include <vector>
#include <iostream>
#include "Smanager.h"
#include "Bounded_Buffer.h"

using namespace std;

// constructor
Smanager::Smanager(){
    // create a new buffer
    this->bBuffer = new Bounded_Buffer(50);
}

void Smanager::print() {
    // print the articles
    while (1) {
        // remove the article
        std::string message = this->bBuffer->remove();
        // if the article is "DONE", increment the counter
        if (message == "DONE") {
            this->numOfDones++;
            // if the counter is 3, break
            if (this->numOfDones == 3) {
                break;
            }
        } 
        // else print the article
        else {
            std::cout << message << std::endl;
        }
    }
    // print "DONE" and finish
    std::cout << "DONE" << std::endl;
}

Bounded_Buffer *Smanager::getBounded_Buffer()
{
    // return the buffer
    return this->bBuffer;
}
