#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>

class JSONParser {
public:
    JSONParser(const std::string& filename);
    ~JSONParser();

    // Function to parse JSON based on arguments
    void parse(const std::vector<std::string>& args);

private:
    std::string filename;
    nlohmann::json jsonData;
    std::mutex mutex; // Mutex to protect shared data

    // Function to parse JSON in a thread-safe manner
    void parseThreadSafe(const std::string& arg);

    // Helper functions for parsing logic
    int countNodes(const nlohmann::json& node);
    void displayTree(const nlohmann::json& node, const std::string& nodeName, int depth);
    void displayKeys(const nlohmann::json& node, int depth);
    void displayValues(const nlohmann::json& node, int depth);
    void prettyPrint(const nlohmann::json& node, int depth);
    void filterData(const nlohmann::json& node, const std::string& filterExpr);
    // Helper function for search
    void search(const nlohmann::json& node, const std::string& searchTerm, const std::string& currentPath = "");
    void extract(const nlohmann::json& node, const std::string& path, int depth);
    void saveToFile(const std::string& content, const std::string& fileName);
};

#endif // JSON_PARSER_H
