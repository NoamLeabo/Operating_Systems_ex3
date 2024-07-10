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

// Func to read the configuration from a file
Config readConfig(const std::string& filename) {
    std::ifstream file(filename);
    Config config;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("PRODUCER") != std::string::npos) {
                // read producer ID
                ProducerConfig producer;
                producer.id = std::stoi(line.substr(line.find("PRODUCER") + 9));

                // read number of products
                // Read the next line
                std::getline(file, line); 
                producer.numProducts = std::stoi(line);

                // read queue size
                // read the next line
                std::getline(file, line);
                producer.queueSize = std::stoi(line.substr(line.find("=") + 2));

                // add producer to the list
                config.producers.push_back(producer);
            } else if (line.find("Co-Editor queue size") != std::string::npos) {
                // read co-editor queue size
                config.coEditorQueueSize = std::stoi(line.substr(line.find("=") + 2));
            }
        }
        file.close();
    } else {
        // failed to open the file
        std::cerr << "Failed to open file: " << filename << std::endl;
    }

    return config;
}