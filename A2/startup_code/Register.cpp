#include "Register.h"

using std::cout;

Register::Register(){

}

Register::~Register(){
    
}

bool Register::LoadRegister(string file_name){
       std::string line;
        std::ifstream coins_file(file_name);
        if (!coins_file)
        {
            std::cout << file_name << " : " << "fail to open file" << std::endl;
            return false;
        }

        while (std::getline(coins_file, line))
        { 
            std::vector<std::string> tokens = {};
            Helper::splitString(line, tokens, ",");
            if (tokens.size()>=2){

                if (Helper::isNumber(tokens[0]) && Helper::isNumber(tokens[1])){
                    if (!this->InsertCash(std::stoi(tokens[0]),std::stoi(tokens[1]))){
                        return false;
                    }
                }else{
                    std::cout << file_name << " : " << "nots a number" << std::endl;
                    return false;
                }

            }else{
                std::cout << file_name << " : " << "tokens.size()!=2" << std::endl;
                return false;
            }
        }

        return true;
}

bool Register::InsertCash(int denomination,int amount){
    for (int i = 0; i < 8; i++) {
        if (denominators[i] == denomination){
            amounts[i] += amount;
            return true;
        }
    }
    return false;
}