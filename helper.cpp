#include "helper.h"
#include <regex>

using std::cin;
using std::string;
using std::vector;

Helper::Helper() {}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n"
              << std::endl;
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
            if (nb_dots > 1)
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

void Helper::splitString(string s, vector<string> &tokens, string delimeter)
{
    tokens.clear();
    char *_s = new char[s.length() + 1];
    strcpy(_s, s.c_str());

    char *pch;
    pch = strtok(_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok(NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;

    if (!std::getline(std::cin, input))
    {
        std::cout << "End-of-file condition encountered, terminating the program" << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    std::cout << std::endl;

    return input;
}

bool Helper::checkUserInputForRemoveItem(string userInput)
{
    std::regex pattern("^I\\d{4}$");

    while (userInput == "")
    {
        std::cout << "Please input a valid answer" << std::endl;
        userInput = Helper::readInput();
    }
    // Matching regex and is not eof
    if (std::regex_match(userInput, pattern) && !cin.eof())
    {
        // linked_list->remove_index(3);
        return true;
    }
    else
    {
        std::cout << "ID invalid or was not found" << std::endl;
    }

    return false;
}

string Helper::strip_spaces(string string)
{
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());

    return string;
}

bool Helper::isValidDenom(std::string userInput)
{
    int userInput_int = stoi(userInput);
    bool valid_denom = false;

    if (userInput_int == 10)
    {
        valid_denom = true;
    }
    else if (userInput_int == 20)
    {
        valid_denom = true;
    }
    else if (userInput_int == 50)
    {
        valid_denom = true;
    }
    else if (userInput_int == 100)
    {
        valid_denom = true;
    }
    else if (userInput_int == 200)
    {
        valid_denom = true;
    }
    else if (userInput_int == 500)
    {
        valid_denom = true;
    }
    else if (userInput_int == 1000)
    {
        valid_denom = true;
    }
    else
    {
        valid_denom = false;
    }

    return valid_denom;
}
