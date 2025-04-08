#include "utils.hpp"

std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, std::unordered_map<int, std::pair<int, int>>> create_variables (int N, int M);

std::unordered_map<int, std::vector<int>> create_prefix (std::unordered_map<int, std::pair<int, int>> variables_);

std::vector<int> set_constraints ();

std::vector<std::vector<int>> define_winning_positions (int N, int M);

std::vector<std::vector<int>> create_clauses (int N, int M);