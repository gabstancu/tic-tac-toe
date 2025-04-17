#include "utils.hpp"

std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
                             std::unordered_map<int, std::pair<int, int>>> create_variables (int N, int M);


std::map<int, std::vector<int>> create_prefix (std::unordered_map<int, std::pair<int, int>> variables_);


std::vector<std::vector<int>> define_winning_positions (int N, int M);


std::vector<std::vector<int>> create_clauses (int N, int M, 
                                              std::map<int, std::vector<int>>& prefix,
                                              std::unordered_map<std::pair<int, int>, int, pair_hash>& variables, 
                                              std::unordered_map<int, std::pair<int, int>>& variables_, 
                                              std::vector<std::vector<int>> winning_positions,
                                              std::vector<std::vector<int>> x_turns);


bool is_spaced(const std::vector<int>& combo);


std::vector<std::vector<int>> generate_x_turns(int maxTurn);
