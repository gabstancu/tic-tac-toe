#include "../include/model.hpp"

int main()
{

    int N = 3, M = 3;

    std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
              std::unordered_map<int, std::pair<int, int>>> p = create_variables (N, M);
    // printMapFlexible(p.first);

    std::map<int, std::vector<int>> prefix = create_prefix(p.second);
    // printMapOfVectors(prefix);

    std::vector<std::vector<int>> winning_positions = define_winning_positions(N, M);
    // print2DVector(winning_positions);

    std::vector<std::vector<int>> x_turns = generate_x_turns(N*M);
    // print2DVector(x_turns);

    std::vector<std::vector<int>> clauses = create_clauses(N, M, prefix, p.first, p.second, winning_positions, x_turns);
    // print2DVector(clauses);
    // printMapOfVectors(prefix);

    std::cout << "Num. of clauses: " << clauses.size() << "\n";

    write_QDIMACS(prefix, p.first, p.second, clauses, "../problem.txt");
    write_variables(p.first, "../variables.txt");
    write_variables_(p.second, "../variables_.txt");

    return 0;
}