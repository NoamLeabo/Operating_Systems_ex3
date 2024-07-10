#include <stdio.h>
#include <vector>
#include <iostream>
#include <semaphore.h>

using namespace std;

class Buffer
{
private:
    vector<string> buffer;
    int index;

public:
    Buffer();
    void insert(string element);
    string remove();
    string getElementByIndex(int index);
};
