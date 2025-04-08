#include "../include/model.hpp"

int main(){

    std::cout << "testing in main..." << "\n";
    int N = 3, M = 3;
    std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
              std::unordered_map<int, std::pair<int, int>>> p = create_variables (N, M);
    // printMapFlexible(p.first);

    std::unordered_map<int, std::vector<int>> prefix = create_prefix(p.second);
    // printMapOfVectors(prefix);

    std::vector<std::vector<int>> winning_moves = define_winning_positions(N, M);
    // print2DVector(winning_moves);

    std::vector<std::vector<int>> clauses = create_clauses(N, M);

    return 0;
}