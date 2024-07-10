#include <stdio.h>
#include <vector>
#include <iostream>
#include <thread>
#include "Ceditor.h"

using namespace std;

// constructor
Ceditor::Ceditor(int bufferSize, int idP) : idP(idP)
{
    // create a new buffer
    this->forEdit = new Bounded_Buffer(bufferSize);
}

Bounded_Buffer *Ceditor::getBounded_Buffer()
{
    // return the buffer
    return this->forEdit;
}

void Ceditor::addSmanager(Bounded_Buffer *bBuffer)
{
    // add the buffer
    this->smanager = bBuffer;
}

void Ceditor::edit()
{
    // "edit" the articles
    while (1)
    {
        // remove the article
        std::string article = this->forEdit->remove();
        // if the article is "DONE", insert it and break
        if (article == "DONE")
        {
            this->smanager->insert("DONE");
            break;
        }
        else
        {
            // "edit" the article
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // insert the article to the smanager
            this->smanager->insert(article);
        }
    }
}

void Ceditor::setBuffer(Bounded_Buffer *bBuffer)
{
    // set the buffer
    this->forEdit = bBuffer;
}