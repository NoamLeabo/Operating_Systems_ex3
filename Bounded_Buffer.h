#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>

using namespace std;

class Bounded_Buffer
{
private:
    vector<string> bounded_Buffer;
    int size;
    int index;
    sem_t space; 
    sem_t items; 
    pthread_mutex_t mutex;  

public:
    Bounded_Buffer(int size);
    void insert(string element);
    string remove();
    string getElementByIndex(int index);
    int getSize();
};

#endif // BOUNDED_BUFFER_H
