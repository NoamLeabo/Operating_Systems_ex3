#include <iostream>
#include <fstream>
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
Config readConfig(const std::string& filename) {
    std::ifstream file(filename);
    Config config;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("PRODUCER") != std::string::npos) {
                ProducerConfig producer;
                producer.id = std::stoi(line.substr(line.find("PRODUCER") + 9));
                std::getline(file, line); // Read the next line
                producer.numProducts = std::stoi(line);
                std::getline(file, line); // Read the next line
                producer.queueSize = std::stoi(line.substr(line.find("=") + 2));
                config.producers.push_back(producer);
            } else if (line.find("Co-Editor queue size") != std::string::npos) {
                config.coEditorQueueSize = std::stoi(line.substr(line.find("=") + 2));
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }

    return config;
}