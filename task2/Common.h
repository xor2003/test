#ifndef __MY_COMMON__
#define __MY_COMMON__

//#include <utility>
#include <string>
//#include <sstream>              //for std::istringstream
//#include <iterator>             //for std::istream_iterator
#include <vector>               //for std::vector
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <cstdlib>
#include <algorithm>

namespace My
{

// split string to vector of strings
void tokenize_string(const std::string &original_string, const std::string &delimiters, std::vector<std::string> & tokens)
{
    tokens.clear();
    if (original_string.empty()) return;

    std::size_t pos_start = original_string.find_first_not_of(delimiters);
    std::size_t pos_end   = original_string.find_first_of(delimiters, pos_start);

    while (std::string::npos != pos_start/* && std::string::npos != pos_end*/)
    {
        if (pos_end != pos_start)
        {
//                std::cout << "~" << pos_start << ","<<pos_end<< " "<< original_string.substr(pos_start, pos_end - pos_start) << "~" << std::endl;
            tokens.push_back(original_string.substr(pos_start, pos_end - pos_start));
        }

        pos_start = original_string.find_first_not_of(delimiters, pos_end);
        pos_end   = original_string.find_first_of(delimiters, pos_start);
    }
}

template <class T>
struct StringToType;

template <> // convert string to double
struct StringToType<double> : std::unary_function<const std::string&, double>
{
    double operator()(const std::string& s) const
    {
        return std::stod(s);
    }
};


}

#endif
