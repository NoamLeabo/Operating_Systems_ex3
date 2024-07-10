#include <stdio.h>
#include <vector>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include "Bounded_Buffer.h"

// constructor
Bounded_Buffer::Bounded_Buffer(int size) : size(size), index(0)
{
    // initialize semaphores and mutex
    this->bounded_Buffer = std::vector<string>(0);
    sem_init(&space, 0, size);  
    sem_init(&items, 0, 0);     
    pthread_mutex_init(&mutex, NULL); 
}

// add element to buffer
void Bounded_Buffer::insert(string element)
{
    // wait for a space to be available
    sem_wait(&space);  
    // lock the buffer
    pthread_mutex_lock(&mutex);

    // add element to buffer
    this->bounded_Buffer.push_back(element);

    // unlock all
    pthread_mutex_unlock(&mutex);  
    sem_post(&items);
}

// remove element from buffer
string Bounded_Buffer::remove()
{
    // wait for an item to be available
    sem_wait(&items); 
    // lock the buffer
    pthread_mutex_lock(&mutex);  

    // remove element from buffer
    string front_of_buffer = this->bounded_Buffer.front();
    this->bounded_Buffer.erase(this->bounded_Buffer.begin());

    // unlock all
    pthread_mutex_unlock(&mutex); 
    sem_post(&space);  

    return front_of_buffer;
}

// get size of buffer
int Bounded_Buffer::getSize() {
    // lock the buffer
    pthread_mutex_lock(&mutex);
    // get size of buffer
    int size = this->bounded_Buffer.size();
    // unlock the buffer
    pthread_mutex_unlock(&mutex);
    return size;
}

// check if buffer is empty
bool Bounded_Buffer::isEmpty() {
    // lock the buffer
    pthread_mutex_lock(&mutex);
    // check if buffer is empty
    bool empty = this->bounded_Buffer.empty();
    // unlock the buffer
    pthread_mutex_unlock(&mutex);
    return empty;
}