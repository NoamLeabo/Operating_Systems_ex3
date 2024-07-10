#include <iostream>
#include <pthread.h>
#include <vector>
#include "Producer.h"
#include "Dispatcher.h"
#include "Ceditor.h"
#include "Smanager.h"

#define NUM_PRODUCERS 3
#define NUM_ARTICLES 3
#define BUFFER_SIZE 1

void* producer_thread(void* arg) {
    Producer* producer = (Producer*)arg;
    producer->generate();
    pthread_exit(NULL);
}

void* dispatcher_thread(void* arg) {
    Dispatcher* dispatcher = (Dispatcher*)arg;
    dispatcher->dispatch();
    pthread_exit(NULL);
}

void* ceditor_thread(void* arg) {
    Ceditor* ceditor = (Ceditor*)arg;
    ceditor->edit();
    pthread_exit(NULL);
}

void* smanager_thread(void* arg) {
    Smanager* smanager = (Smanager*)arg;
    smanager->print();
    pthread_exit(NULL);
}

int main() {
    Producer p1(BUFFER_SIZE, 1, NUM_ARTICLES);
    Producer p2(BUFFER_SIZE, 2, NUM_ARTICLES);
    Producer p3(BUFFER_SIZE, 3, NUM_ARTICLES);

    Dispatcher dispatcher;
    Ceditor sport(BUFFER_SIZE, 1);
    Ceditor news(BUFFER_SIZE, 2);
    Ceditor weather(BUFFER_SIZE, 3);
    Smanager smanager;

    dispatcher.addNEWS(news.getBounded_Buffer());
    dispatcher.addSPORT(sport.getBounded_Buffer());
    dispatcher.addWEATHER(weather.getBounded_Buffer());

    dispatcher.addBounded_Bufer(p1.getBounded_Buffer());
    dispatcher.addBounded_Bufer(p2.getBounded_Buffer());
    dispatcher.addBounded_Bufer(p3.getBounded_Buffer());

    sport.addSmanager(smanager.getBounded_Buffer());
    news.addSmanager(smanager.getBounded_Buffer());
    weather.addSmanager(smanager.getBounded_Buffer());

    
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t dispatcher_thread_id;
    pthread_t ceditor_thread_ids[3];
    pthread_t smanager_thread_id;

    // Create producer threads
    pthread_create(&producer_threads[0], NULL, producer_thread, &p1);
    pthread_create(&producer_threads[1], NULL, producer_thread, &p2);
    pthread_create(&producer_threads[2], NULL, producer_thread, &p3);

    // Create dispatcher thread
    pthread_create(&dispatcher_thread_id, NULL, dispatcher_thread, &dispatcher);

    // Create ceditor threads
    pthread_create(&ceditor_thread_ids[0], NULL, ceditor_thread, &sport);
    pthread_create(&ceditor_thread_ids[1], NULL, ceditor_thread, &news);
    pthread_create(&ceditor_thread_ids[2], NULL, ceditor_thread, &weather);

    // Create smanager thread
    pthread_create(&smanager_thread_id, NULL, smanager_thread, &smanager);

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    // Join dispatcher thread
    pthread_join(dispatcher_thread_id, NULL);

    // Join ceditor threads
    for (int i = 0; i < 3; i++) {
        pthread_join(ceditor_thread_ids[i], NULL);
    }

    // Join smanager thread
    pthread_join(smanager_thread_id, NULL);

    return 0;
}
