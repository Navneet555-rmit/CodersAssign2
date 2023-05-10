#include "helper.h"
#include "Node.h"

using std::string;
using std::vector;

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

void Helper::waitForEnter(){
    while (Helper::readInput() != ""){};
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;

    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1); 
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

void Helper::printInvalidPrice()
{
    std::cout << "Error: the price is not valid.\n";
}

void Helper::printCentsNotMultipleOf5()
{
    std::cout << "Error: the cents need to be a multiple of 5.\n";
}

void Helper::cancelAddTask()
{
    std::cout << "Cancelling \"add item\" at user's request.\n"; 
    std::cout << "The task Add Item failed to run successfully.\n";
}

void Helper::printLongInput()
{
    std::cout << "Error: line entered was too long. Please try again.\n";
}

vector<string> Helper::createVector(string id, string name, string desc, string price) {
    vector<string> data = {};
    data.push_back(id);
    data.push_back(name);
    data.push_back(desc);
    data.push_back(price);
    data.push_back(std::to_string(DEFAULT_STOCK_LEVEL));
    return data;
}
