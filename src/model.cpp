#include "model.hpp"


std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
          std::unordered_map<int, std::pair<int, int>>> create_variables (int N, int M)
{   
    /* "two-way" accessing */
    std::unordered_map<std::pair<int, int>, int, pair_hash> variables;
    std::unordered_map<int, std::pair<int, int>> variables_;
    
    int position_on_board, var_index = 0;
    std::vector<int> var;
    // std::cout << "N: " << N << " M: " << M << "\n";

    for (int t = 0; t < N*M; t++)
    {
        for (int k = 0; k < M*N; k++)
        {  
            variables[{t, k}] = var_index;
            std::pair<int, int> p = std::make_pair(t, k);
            variables_ [var_index++] = p;
        }
    }
    std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
              std::unordered_map<int, std::pair<int, int>>> p = std::make_pair(variables, variables_);

    return p;
}


std::unordered_map<int, std::vector<int>> create_prefix (std::unordered_map<int, std::pair<int, int>> variables_)
{
    std::unordered_map<int, std::vector<int>> prefix;

    for (const auto& [var_key, t_p] : variables_)
    {   
        prefix[t_p.first].push_back(var_key);
    }

    return prefix;
}


std::vector<std::vector<int>> define_winning_positions (int N, int M)
{
    std::vector<std::vector<int>> winning_moves;
    std::vector<int> r, c, d, d_;

    for (int i = 0; i < N; i++)
    {
        r = {}; c = {};
        for (int j = 0; j < M; j++)
        {
            r.push_back(N * i + j); // rows
            c.push_back(N * j + i); // columns

            if (i==j) 
            {
                d.push_back(N * i + j); // diagonal (main)
                d_.push_back(N * i + N - 1 - i); // ant. diagonal
            }
        }
        winning_moves.push_back(r);
        winning_moves.push_back(c);
    }

    winning_moves.push_back(d);
    winning_moves.push_back(d_);

    return winning_moves;
}


std::vector<std::vector<int>> create_clauses (int N, int M)
{
    std::vector<std::vector<int>> clauses;

    /* each cell is marked at most once (by any player) */
    for (int p = 0; p < N*M; p++)
    {   
        std::cout << "p: " << p << "\n";
        for (int t = 0; t < N * M; t++)
        {
            std::cout << "t: " << t << "\n";

            for (int t_ = t + 1; t_ < N * M; t_++)
            {
                std::cout << "t_: " << t_ << "\n";
            }
            std::cout << "\n";
        }
    }

    return clauses;
}
