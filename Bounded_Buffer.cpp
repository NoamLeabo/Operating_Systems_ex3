#include <stdio.h>
#include <vector>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include "Bounded_Buffer.h"

// constructor
Bounded_Buffer::Bounded_Buffer(int size) : size(size), index(0)
{
    this->bounded_Buffer = std::vector<string>(0);
    sem_init(&space, 0, size);  
    sem_init(&items, 0, 0);     
    pthread_mutex_init(&mutex, NULL); 
}

// add element to buffer
void Bounded_Buffer::insert(string element)
{
    sem_wait(&space);  
    pthread_mutex_lock(&mutex);  

    this->bounded_Buffer.push_back(element);

    pthread_mutex_unlock(&mutex);  
    sem_post(&items);
}

// remove element from buffer
string Bounded_Buffer::remove()
{
    sem_wait(&items); 
    pthread_mutex_lock(&mutex);  

    string front_of_buffer = this->bounded_Buffer.front();
    this->bounded_Buffer.erase(this->bounded_Buffer.begin());

    pthread_mutex_unlock(&mutex); 
    sem_post(&space);  

    return front_of_buffer;
}

// get element from buffer at index i
string Bounded_Buffer::getElementByIndex(int index)
{
    pthread_mutex_lock(&mutex);  

    if (index >= this->bounded_Buffer.size())
    {
        pthread_mutex_unlock(&mutex);  
        return "";
    }

    string element = this->bounded_Buffer.at(index);
    pthread_mutex_unlock(&mutex);  
    return element;
}

// get size of buffer
int Bounded_Buffer::getSize() {
    pthread_mutex_lock(&mutex);
    int size = this->bounded_Buffer.size();
    pthread_mutex_unlock(&mutex);
    return size;
}