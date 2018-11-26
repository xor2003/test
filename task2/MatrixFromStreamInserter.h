#ifndef __MY_MATRIXFROMSTREAMINSERTER__
#define __MY_MATRIXFROMSTREAMINSERTER__

#include "Common.h"
#include "Matrix.h"

#include <string>
#include <iostream>
//#include <iterator>             //for std::istream_iterator


namespace My
{


template <class T>
class Matrix;

template <class T>
struct StringToType;



template <class T, typename F> // F used to convert element type
class MatrixFromStreamInserter // Get matrix values from file or stdin and convert from string to target value type
{
public:
    MatrixFromStreamInserter()
    {}

    virtual ~MatrixFromStreamInserter()
    {}


    virtual void run(std::istream& in, const std::string &delimiters, Matrix<T>* matrix)
    {

        std::string input_line;
        while (std::getline (in, input_line))
        {
            std::vector < std::string > fields;
            tokenize_string(input_line, delimiters,fields);
            std::vector < T > doubles(fields.size());

            try
            {
                std::transform(fields.begin(), fields.end(), doubles.begin(), F());
                matrix->Insert_Row(doubles);
            }
            catch (...)
            {
                std::cerr << "Error converting string to double in " << std::endl << "~" << input_line << "~" << std::endl;
            }
        }
    }

};

}

#endif
