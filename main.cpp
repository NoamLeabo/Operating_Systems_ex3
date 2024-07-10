#include <iostream>
#include <pthread.h>
#include <vector>
#include "Producer.h"
#include "Dispatcher.h"
#include "Ceditor.h"
#include "Smanager.h"
#include "Config.h" 

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    // read the configuration from the command line argument
    Config config = readConfig(argv[1]);

    std::vector<Producer*> producers;
    for (const auto& producerConfig : config.producers) {
        // create a new Producer object with the specified configuration
        Producer* producer = new Producer(producerConfig.queueSize, producerConfig.id, producerConfig.numProducts);
        producers.push_back(producer);
    }

    // create the Dispatcher, Ceditor, and Smanager objects
    Dispatcher dispatcher;
    Ceditor sport(config.coEditorQueueSize, 1);
    Ceditor news(config.coEditorQueueSize, 2);
    Ceditor weather(config.coEditorQueueSize, 3);
    Smanager smanager;

    // add the bounded buffers to the dispatcher
    for (auto& producer : producers) {
        dispatcher.addBounded_Bufer(producer->getBounded_Buffer());
    }

    // add the co-editor bounded buffers to the dispatcher
    dispatcher.addNEWS(news.getBounded_Buffer());
    dispatcher.addSPORT(sport.getBounded_Buffer());
    dispatcher.addWEATHER(weather.getBounded_Buffer());

    // add the smanager bounded buffer to the co-editors
    sport.addSmanager(smanager.getBounded_Buffer());
    news.addSmanager(smanager.getBounded_Buffer());
    weather.addSmanager(smanager.getBounded_Buffer());

    pthread_t producer_threads[config.producers.size()];
    pthread_t dispatcher_thread_id;
    pthread_t ceditor_thread_ids[3];
    pthread_t smanager_thread_id;

    // create producer threads
    for (size_t i = 0; i < config.producers.size(); ++i) {
        pthread_create(&producer_threads[i], NULL, producer_thread, producers[i]);
    }

    // create dispatcher thread
    pthread_create(&dispatcher_thread_id, NULL, dispatcher_thread, &dispatcher);

    // create co-editor threads
    pthread_create(&ceditor_thread_ids[0], NULL, ceditor_thread, &sport);
    pthread_create(&ceditor_thread_ids[1], NULL, ceditor_thread, &news);
    pthread_create(&ceditor_thread_ids[2], NULL, ceditor_thread, &weather);

    // create smanager thread
    pthread_create(&smanager_thread_id, NULL, smanager_thread, &smanager);

    // join producer threads
    for (size_t i = 0; i < config.producers.size(); ++i) {
        pthread_join(producer_threads[i], NULL);
    }

    // join dispatcher thread
    pthread_join(dispatcher_thread_id, NULL);

    // join co-editor threads
    for (int i = 0; i < 3; i++) {
        pthread_join(ceditor_thread_ids[i], NULL);
    }

    // join smanager thread
    pthread_join(smanager_thread_id, NULL);

    // clean up producers to avoid memory leaks
    for (auto& producer : producers) {
        delete producer;
    }

    return 0;
}
