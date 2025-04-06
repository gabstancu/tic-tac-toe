#include "utils.hpp"

/* 
    Accepts as input the dimensions of the board: N x M
    Returns the variables of the problem

    var 0 -> move 0 position 1
    var 1 -> move 0 position 2
    var 2 -> move 0 position 3
    . 
    . 
    .  
    var N x M -> move k position l

    if move even: e player
    if move odd: a player
*/

std::unordered_map<int, std::vector<int>> create_variables (int N, int M);

std::unordered_map<int, int> create_prefix ();

std::vector<int> set_constraints ();

std::vector<std::vector<int>> create_clauses ();