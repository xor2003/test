/*
Build command: g++  _task2.cpp  -o _task2
*/

#include "Common.h"                   // for StringToType
#include "Matrix.h"                   // for operator<<, Matrix
#include "MatrixFixErrors.h"          // for MatrixFixErrors
#include "MatrixFromStreamInserter.h"  // for MatrixFromStreamInserter

#include <stdlib.h>                     // for exit
#include <iomanip>                      // for operator<<, setprecision
#include <iostream>                     // for ofstream, basic_ostream, etc
#include <fstream>                     // for ofstream, basic_ostream, etc
#include <string>                       // for char_traits, string


using namespace My;

int main (int argc, char *argv[])
{

    if (argc != 3)
    {
        std::cerr << argv[0] <<" <input.csv> <output.csv>" << std::endl;
        exit (1);
    }

    std::string input_file_name(argv[1]);
    std::string output_file_name(argv[2]);

    std::ifstream in;
    in.open (input_file_name, std::ifstream::in); // read input csv

    Matrix<double> input_matrix;
    std::string number_separators(", ");
    MatrixFromStreamInserter<double, StringToType<double> > ins;
	ins.run(in, number_separators, &input_matrix);  // put data to matrix

    in.close();

//    std::cout << std::setprecision(15) << input_matrix;

    Matrix<double>* output_matrix = nullptr;
    MatrixFixErrors<double> fix;
	fix.run(&input_matrix, output_matrix); // fix errors

//    std::cout << std::setprecision(15) << output_matrix;

    if (output_matrix)
    {
        std::ofstream out;
        out.open (output_file_name.c_str (), std::ofstream::out);
        out << std::setprecision(15);

        out << *output_matrix; // put data to output csv

        out.close();
    }

    return 0;
}
