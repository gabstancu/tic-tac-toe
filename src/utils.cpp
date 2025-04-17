#include "utils.hpp"

void write_QDIMACS (std::map<int, std::vector<int>> prefix,
                    std::unordered_map<std::pair<int, int>, int, pair_hash> variables, 
                    std::unordered_map<int, std::pair<int, int>> variables_, 
                    std::vector<std::vector<int>> clauses, 
                    const std::string filename
)
{
    std::ofstream file(filename);

    // write header
    std::string num_vars = std::to_string(variables.size());
    std::string num_clauses = std::to_string(clauses.size());
    std::string space = " ";
    std::string header = "p cnf" + space + num_vars + space + num_clauses + '\n';
    
    file << header;

    // write prefix
    // std::map<int, std::vector<int>> prefix_copy = prefix;
    auto last = std::prev(prefix.end());
    std::string line;

    for (auto it = prefix.begin(); it != prefix.end(); ++it)
    {
        file << ( (it->first % 2 == 0 ||it == last) ? "e " : "a " );

        for (int var : it->second)
        {
            file << var << " ";
        }
        file << "0\n";
    }

    // write clauses
    for (const auto& clause : clauses)
    {
        for (int literal : clause)
        {
            file << literal << " ";
        }
        file << "0\n";
    }

    file.close();

}

void write_variables (std::unordered_map<std::pair<int, int>, int, pair_hash> variables, 
                      const std::string filename)
{
    std::ofstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << " for writing.\n";
        return;
    }

    for (const auto& [key, val] : variables)
    {
        file << key.first << " " << key.second << " : " << val << '\n';
    }

    file.close();
    
}

void write_variables_ (std::unordered_map<int, std::pair<int, int>> variables_, 
                       const std::string filename)
{
    std::ofstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << " for writing.\n";
        return;
    }

    for (const auto& [key, val] : variables_)
    {
        file << key << " : " << val.first << " " << val.second << '\n';
    }

    file.close();
}


void write_winning_moves(std::vector<std::vector<int>> winning_cubes, 
                         const std::string filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << " for writing.\n";
        return;
    }

    for (const auto& winning_cube : winning_cubes)
    {
        for (int move : winning_cube)
        {
            file << move << " ";
        }
        file << '\n';
    }

    file.close();
}