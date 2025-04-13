#include "model.hpp"


std::pair<std::unordered_map<std::pair<int, int>, int, pair_hash>, 
          std::unordered_map<int, std::pair<int, int>>> create_variables (int N, int M)
{   
    /* "two-way" accessing */
    std::unordered_map<std::pair<int, int>, int, pair_hash> variables;
    std::unordered_map<int, std::pair<int, int>> variables_;
    
    int var_index = 1;
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


std::map<int, std::vector<int>> create_prefix (std::unordered_map<int, std::pair<int, int>> variables_)
{
    std::map<int, std::vector<int>> prefix;

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



// Helper to check time spacing
bool is_spaced(const std::vector<int>& combo) {
    return (combo[1] - combo[0] >= 2) && (combo[2] - combo[1] >= 2);
}


// Main function: generates and returns all spaced 3-combinations
std::vector<std::vector<int>> generate_x_turns(int maxTurn) 
{
    std::vector<int> times;
    for (int i = 0; i < maxTurn; i+=2) times.push_back(i);

    std::vector<bool> bitmask(3, true);
    bitmask.resize(times.size(), false);

    std::vector<std::vector<int>> result;

    do 
    {
        std::vector<int> combo;
        for (size_t i = 0; i < times.size(); ++i)
            if (bitmask[i]) combo.push_back(times[i]);

        if (is_spaced(combo))
            result.push_back(combo);

    } 
    while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return result;
}



std::vector<std::vector<int>> create_clauses (int N, int M, 
                                              std::map<int, std::vector<int>>& prefix,
                                              std::unordered_map<std::pair<int, int>, int, pair_hash>& variables, 
                                              std::unordered_map<int, std::pair<int, int>>& variables_, 
                                              std::vector<std::vector<int>> winning_positions, 
                                              std::vector<std::vector<int>> x_turns)
{
    std::vector<std::vector<int>> clauses;
    std::vector<int> clause;

    /* each position is marked at most once (by any player) */
    for (int p = 0; p < N*M; p++)
    {   
        // std::cout << "p: " << p << "\n";
        for (int t = 0; t < N * M; t++)
        {
            clause.push_back(-(variables[{t, p}]));
            for (int t_ = t + 1; t_ < N * M; t_++)
            {
                int var_ = variables[{t_, p}];
                // printf("clause: -(%d %d) v -(%d %d)\n", t, p, t_, p);
                // printf("clause: -%d v -%d\n", variables[{t, p}], variables[{t_, p}]);
                clause.push_back(-(variables[{t_, p}]));
                clauses.push_back(clause);
                // printVector(clause);
                clause.pop_back();
            }
            // std::cout << "\n";
            clause = {};
        }
        clause = {};
    }

    clause = {};

    /* exactly one move has to be done per turn -> at least one move + at most one move */
    
    // at least one move per turn
    for (int t = 0; t < N*M; t++)
    {
        // std::cout << "turn " << t << "\n";
        for (int p = 0; p < N*M; p++)
        {
            // std::cout << t << " " << p << "\n";
            // std::cout << "variable index: " << variables[{t, p}] << "\n";
            clause.push_back(variables[{t, p}]);
        }
        // std::cout << "\n";
        // printVector(clause);
        clauses.push_back(clause);
        clause = {};
    }

    clause = {};
    
    // int ALARM = 0;
    // at most one move per turn
    // std::cout << "At most one move per turn..." << "\n";
    for (int t = 0; t < N*M; t++)
    {
        // std::cout << "turn " << t << "\n";
        for (int i = 0; i < N*M; i++)
        {
            for (int j = 0; j < N*M; j++)
            {
                if (i<j)
                {
                    // printf("clause: -(%d %d) v -(%d %d)\n", t, i, t, j);
                    // printf("clause: -%d v -%d\n", variables[{t, i}], variables[{t, j}]);
                    // ALARM++;
                    clause.push_back(-(variables[{t, i}]));
                    clause.push_back(-(variables[{t, j}]));
                    clauses.push_back(clause);
                    // printVector(clause);
                    clause = {};
                }
            }
        }
        // std::cout << "ALARM: " << ALARM << "\n";
        // ALARM = 0;
    }



    /* write winning strategies to "winning_moves.txt" */
    
    std::vector<std::vector<int>> winning_cubes = {};
    std::vector<int> winning_cube = {};

    for (std::vector<int> c : x_turns)
    {   
        for (std::vector<int> winning_placement : winning_positions)
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                // std::cout << c[i] << " " << winning_placement[i] << "\n";
                winning_cube.push_back(variables[{c[i], winning_placement[i]}]);
            }
            // printVector(winning_cube);
            winning_cubes.push_back(winning_cube);
            winning_cube = {};
            // std::cout << "\n";
        }
        // std::cout << "\n";
    }

    // print2DVector(winning_cubes);

    clause = {};

    /* set K as starting key for Tseitin variables (w) */
    int w_id = pow(N*M, 2) + 1;
    int w_num = 0;
    std::vector<int> tseitin_clause = {};
    // std::cout << "Tseitin variables starting from " << w_id << "\n";

    for (std::vector<int> winning_cube : winning_cubes)
    {   
        variables[{w_id, w_num}] = w_id;
        std::pair<int, int> p = std::make_pair(w_id, w_num);
        variables_[w_id] = p;

        /* -wi v x_{t, p} for every x_{t, p} in winning cube */
        clause.push_back(-w_id);
        for (int var : winning_cube)
        {
            // std::cout << var << " ";
            clause.push_back(var);
            
        }
        // std::cout << "\n";
        clauses.push_back(clause);

        clause = {};

        /* -x_{t1, p1} v -x_{t2, p2} v -x_{t3, p3} v wi */
        clause.push_back(w_id);
        for (int var : winning_cube)
        {
            // std::cout << var << " ";
            clause.push_back(-var);
            
        }

        clauses.push_back(clause);
        tseitin_clause.push_back(w_id);
        
        w_id++;
        w_num++;

        clause = {};
    }
    clauses.push_back(tseitin_clause);

    /* add variables to prefix (last block) */
    int prefix_id = N*M;
    prefix[prefix_id] = tseitin_clause;
    
    return clauses;
}
