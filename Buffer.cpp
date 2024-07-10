#include <stdio.h>
#include <vector>
#include <iostream>
#include "Buffer.h"

// constructor
Buffer::Buffer() : index(0)
{
    this->buffer = std::vector<string>();
};

// add element to buffer
void Buffer::insert(string element)
{
    this->buffer.push_back(element);
    this->index++;
}

// remove element to buffer
string Buffer::remove()
{
    if (!this->buffer.empty())
    {
        string top_of_buffer = this->buffer.back();
        this->buffer.pop_back();
        this->index--;
        return top_of_buffer;
    }
    return "";
}

// get element from buffer at index i
string Buffer::getElementByIndex(int index)
{
    if (index > this->buffer.size() - 1)
    {
        return "";
    }

    return this->buffer.at(index);
}
