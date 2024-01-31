# 🌈 JSON Parser Library

## Overview

The **JSON Parser Library** is a ⚡ fast and versatile C++ library designed for parsing and manipulating JSON data. Its multi-threaded capabilities make it efficient for handling large datasets, while the command-line interface (CLI) provides flexibility and ease of use.

## ✨ Features

- **Multi-threaded JSON Parsing:** Utilizes 🚀 multi-threading to efficiently parse large JSON files.
- **Command-Line Interface (CLI):** Offers a user-friendly CLI for performing various operations on JSON data.
- **Flexible JSON Tree Manipulation:** Functions for counting nodes, displaying trees, filtering data, searching, and more.
- **Dynamic Library:** Can be compiled as a shared library, making integration with other projects a breeze.

## 🚀 Getting Started

### Prerequisites

- CMake (Version >= 3.10)
- C++ Compiler (Supporting C++11)
- [nlohmann/json](https://github.com/nlohmann/json) (Fetched automatically during build)

### 🛠️ Build and Installation

```bash
mkdir build
cd build
cmake ..
make
```
## 🚀 Usage

### Example 1: Counting Nodes

```cpp
#include "json_parser.h"

int main() {
    JSONParser parser("example.json");
    parser.parse({ "-n" });  // Count nodes
    return 0;
}
```
### Example 2: Displaying Tree

```cpp
#include "json_parser.h"

int main() {
    JSONParser parser("example.json");
    parser.parse({ "-d=node_name" });  // Display tree for a specific node
    return 0;
}
```
### Example 3: Filtering Data

```cpp
#include "json_parser.h"

int main() {
    JSONParser parser("example.json");
    parser.parse({ "-f=filter_expr" });  // Filter data based on expression
    return 0;
}
```
## 🌐 Command-Line Interface (CLI)
The library comes with a CLI for easy interaction. For example:
```bash
./JSONParserLib -n -d=node_name -f=filter_expr
```
## 🤝 Contributing
- If you'd like to contribute to this project, please follow the Contributing Guidelines.
## 📄 License
This project is licensed under the MIT License.
## 🙌 Acknowledgments
- Special thanks to the contributors who made this project possible.
- Inspired by nlohmann/json library.
## 📧 Contact
For questions or support, please contact me
