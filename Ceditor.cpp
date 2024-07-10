#include <stdio.h>
#include <vector>
#include <iostream>
#include <thread>
#include "Ceditor.h"

using namespace std;

// constructor
Ceditor::Ceditor(int bufferSize, int idP) : idP(idP)
{
    this->forEdit = new Bounded_Buffer(bufferSize);
}

Bounded_Buffer *Ceditor::getBounded_Buffer()
{
    return this->forEdit;
}

void Ceditor::addSmanager(Bounded_Buffer *bBuffer)
{
    this->smanager = bBuffer;
}

void Ceditor::edit() {
    while (1) {
        std::string article = this->forEdit->remove();
        if (article == "DONE") {
            this->smanager->insert("DONE");
            break;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            this->smanager->insert(article);
        }
    }
}

void Ceditor::setBuffer(Bounded_Buffer *bBuffer)
{
    this->forEdit = bBuffer;
}