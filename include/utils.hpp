#include <stdio.h>
#include <iostream>
#include <set>
#include <cmath>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const 
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

template<typename K, typename V, typename Hash = std::hash<K>>
void printMapFlexible(const std::unordered_map<K, V, Hash>& map,
                      const std::string& player_flag = "") {
    for (const auto& [key, val] : map) {
        bool print = true;

        if constexpr (std::is_same<V, std::pair<int, int>>::value) {
            // Value is pair<int, int> → turn = val.first
            if (player_flag == "e") {
                print = (val.first % 2 == 0);
            } else if (player_flag == "a") {
                print = (val.first % 2 != 0);
            }

            if (print) {
                std::cout << "Key: " << key
                          << " -> Value: (" << val.first << ", " << val.second << ")\n";
            }

        } else if constexpr (std::is_same<K, std::pair<int, int>>::value && std::is_same<V, int>::value) {
            // Key is pair<int, int> → turn = key.first
            if (player_flag == "e") {
                print = (key.first % 2 == 0);
            } else if (player_flag == "a") {
                print = (key.first % 2 != 0);
            }

            if (print) {
                std::cout << "Key: (" << key.first << ", " << key.second
                          << ") -> Value: " << val << "\n";
            }

        } else {
            static_assert(std::is_same<V, void>::value,
                          "Unsupported map type for printMapFlexible.");
        }
    }
}


template<typename T>
void printVector(const std::vector<T>& vec, const std::string& label = "Vector") {
    std::cout << label << ": ";
    for (const T& val : vec) {
        std::cout << val << " ";
    }
    std::cout << '\n';
}


template<typename T>
void print2DVector(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) 
    {
        for (const T& val : row) 
        {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
}


template<typename T>
void printMapOfVectors(const std::unordered_map<int, std::vector<T>>& map) {
    for (const auto& [key, vec] : map) {
        std::cout << "Key: " << key << " -> Values: ";
        for (const T& val : vec) {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
}