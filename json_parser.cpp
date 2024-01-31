#include "json_parser.h"

JSONParser::JSONParser(const std::string& filename) : filename(filename) {
    // Read JSON data from file
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> jsonData;
        file.close();
    }
}

JSONParser::~JSONParser() {
    // Destructor
}

void JSONParser::parse(const std::vector<std::string>& args) {
    std::vector<std::thread> threads;

    // Launch threads for parsing based on arguments
    for (const auto& arg : args) {
        threads.emplace_back(&JSONParser::parseThreadSafe, this, arg);
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }
}

void JSONParser::parseThreadSafe(const std::string& arg) {
    std::lock_guard<std::mutex> lock(mutex); // Lock to ensure thread safety

    // Additional parsing logic based on arguments
    if (arg == "-n" || arg == "--node-count") {
        int nodeCount = countNodes(jsonData);
        std::cout << "Number of nodes: " << nodeCount << std::endl;
    } else if (arg.substr(0, 3) == "-d=" || arg.substr(0, 10) == "--display=") {
        std::string nodeName = arg.substr(arg.find('=') + 1);
        std::cout << "Displaying tree for node: " << nodeName << std::endl;
        displayTree(jsonData, nodeName, 0);
    } else if (arg == "-h" || arg == "--help") {
        std::cout << "Available arguments:\n"
                  << "-n, --node-count: Count the number of nodes in the JSON tree.\n"
                  << "-d=<nodeName>, --display=<nodeName>: Display the entire tree starting from the specified node.\n"
                  << "-f=<filterExpr>, --filter=<filterExpr>: Filter the JSON data based on a specified expression.\n"
                  << "-s=<searchTerm>, --search=<searchTerm>: Search for a specific term in the JSON data.\n"
                  << "-k, --keys: Display only the keys (field names) in the JSON data.\n"
                  << "-v, --values: Display only the values in the JSON data.\n"
                  << "-p, --pretty-print: Output the JSON data in a formatted, human-readable way.\n"
                  << "-e=<path>, --extract=<path>: Extract and display a specific path or value from the JSON data.\n"
                  << "-o=<outputFile>, --output-file=<outputFile>: Save the results to a file instead of printing them to the console.\n"
                  << std::endl;
    } else if (arg.substr(0, 3) == "-f=" || arg.substr(0, 9) == "--filter=") {
        std::string filterExpr = arg.substr(arg.find('=') + 1);
        filterData(jsonData, filterExpr);
    } else if (arg.substr(0, 3) == "-s=" || arg.substr(0, 9) == "--search=") {
        std::string searchTerm = arg.substr(arg.find('=') + 1);
        search(jsonData, searchTerm);
    } else if (arg == "-k" || arg == "--keys") {
        displayKeys(jsonData, 0);
    } else if (arg == "-v" || arg == "--values") {
        displayValues(jsonData, 0);
    } else if (arg == "-p" || arg == "--pretty-print") {
        prettyPrint(jsonData, 0);
    } else if (arg.substr(0, 3) == "-e=" || arg.substr(0, 10) == "--extract=") {
        std::string extractPath = arg.substr(arg.find('=') + 1);
        extract(jsonData, extractPath, 0);
    } else if (arg.substr(0, 3) == "-o=" || arg.substr(0, 13) == "--output-file=") {
        std::string outputFile = arg.substr(arg.find('=') + 1);
        std::string content;
        prettyPrint(jsonData, 0); // Example: Pretty-print the JSON data before saving
        saveToFile(content, outputFile);
    } else {
        std::cerr << "Unknown argument: " << arg << std::endl;
    }
}

int JSONParser::countNodes(const nlohmann::json& node) {
    int count = 1; // Count the current node

    if (node.is_object()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            count += countNodes(it.value());
        }
    } else if (node.is_array()) {
        for (const auto& element : node) {
            count += countNodes(element);
        }
    }

    return count;
}

void JSONParser::displayTree(const nlohmann::json& node, const std::string& nodeName, int depth) {
    if (node.is_object()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::string currentName = it.key();
            const nlohmann::json& currentValue = it.value();

            if (currentName == nodeName) {
                // Display the entire tree starting from the specified node
                std::cout << std::string(depth * 2, ' ') << currentName << ": " << currentValue << std::endl;
            }

            displayTree(currentValue, nodeName, depth + 1);
        }
    } else if (node.is_array()) {
        for (size_t i = 0; i < node.size(); ++i) {
            std::string currentName = std::to_string(i);
            const nlohmann::json& currentValue = node[i];

            if (currentName == nodeName) {
                // Display the entire tree starting from the specified node
                std::cout << std::string(depth * 2, ' ') << currentName << ": " << currentValue << std::endl;
            }

            displayTree(currentValue, nodeName, depth + 1);
        }
    }
}

void JSONParser::displayKeys(const nlohmann::json& node, int depth) {
    if (node.is_object()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::string currentName = it.key();
            std::cout << std::string(depth * 2, ' ') << currentName << std::endl;
            displayKeys(it.value(), depth + 1);
        }
    } else if (node.is_array()) {
        for (size_t i = 0; i < node.size(); ++i) {
            std::string currentName = std::to_string(i);
            std::cout << std::string(depth * 2, ' ') << currentName << std::endl;
            displayKeys(node[i], depth + 1);
        }
    }
}

void JSONParser::displayValues(const nlohmann::json& node, int depth) {
    if (node.is_object()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            displayValues(it.value(), depth + 1);
        }
    } else if (node.is_array()) {
        for (size_t i = 0; i < node.size(); ++i) {
            displayValues(node[i], depth + 1);
        }
    } else {
        std::cout << std::string(depth * 2, ' ') << node << std::endl;
    }
}

void JSONParser::prettyPrint(const nlohmann::json& node, int depth) {
    std::cout << node.dump(2) << std::endl;
}

void JSONParser::filterData(const nlohmann::json& node, const std::string& filterExpr) {
    // Add your filter logic here
    // For simplicity, this example just prints the filtered data
    try {
        auto result = node[filterExpr];
        std::cout << "Filtered Data:\n" << result.dump(2) << std::endl;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Error filtering data with expression " << filterExpr << ": " << e.what() << std::endl;
    }
}

void JSONParser::search(const nlohmann::json& node, const std::string& searchTerm, const std::string& currentPath) {
    // Add your search logic here
    // For simplicity, this example just prints the paths where the term is found

    std::cout << "Search results for term '" << searchTerm << "':\n";

    if (node.is_object()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::string newPath = currentPath + "/" + it.key();
            search(it.value(), searchTerm, newPath);
        }
    } else if (node.is_array()) {
        for (size_t i = 0; i < node.size(); ++i) {
            std::string newPath = currentPath + "/" + std::to_string(i);
            search(node[i], searchTerm, newPath);
        }
    } else {
        if (node == searchTerm) {
            std::cout << "Found at path: " << currentPath << std::endl;
        }
    }
}


void JSONParser::extract(const nlohmann::json& node, const std::string& path, int depth) {
    // Add your extraction logic here
    // For simplicity, this example just prints the extracted data
    try {
        auto result = node[path];
        std::cout << "Extracted Data:\n" << result.dump(2) << std::endl;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Error extracting data from path " << path << ": " << e.what() << std::endl;
    }
}

void JSONParser::saveToFile(const std::string& content, const std::string& fileName) {
    // Add logic to save content to the specified file
    // For simplicity, this example just prints a message
    std::cout << "Results saved to file: " << fileName << std::endl;
}
