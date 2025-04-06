#include "../include/model.hpp"

int main(){

    std::cout << "testing in main..." << "\n";
    
    std::unordered_map<int, std::vector<int>> variables;
    variables = create_variables (9, 9);
    


    return 0;
}