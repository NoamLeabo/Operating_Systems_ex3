#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <vector>

struct ProducerConfig {
    int id;
    int numProducts;
    int queueSize;
};

struct Config {
    std::vector<ProducerConfig> producers;
    int coEditorQueueSize;
};

Config readConfig(const std::string& filename);

#endif // CONFIG_READER_H
