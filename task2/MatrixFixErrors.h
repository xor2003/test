#ifndef __MY_MATRIXFIXERRORS__
#define __MY_MATRIXFIXERRORS__

#include "Matrix.h"
#include <iostream>

namespace My
{

template <class T>  // Interpolate data errors
class MatrixFixErrors // TODO: May be optimized for low memory devices since only 3 rows required to process
{

public:
    MatrixFixErrors()
    {}

    virtual ~MatrixFixErrors()
    {}


    virtual void run(const Matrix<T>* input_matrix, Matrix<T>*& output_matrix)
    {
        output_matrix = const_cast< Matrix<T>* >(input_matrix)->clone();

        std::size_t matrix_height = input_matrix->Get_Height();
        std::size_t matrix_width =  input_matrix->Get_Width();

        if (matrix_height !=1 || matrix_width !=1) // cannot fix error values if matrix is 1x1.
        {
            for(std::size_t y=0; y < matrix_height; y++)
            {
                for(std::size_t x=0; x < matrix_width; x++)
                {
                    if (input_matrix->Get_Element(x,y) == 0) // if error value
                    {

//                        std::cout << "x=" << x << " y=" << y <<std::endl;
                        std::size_t valid_neighbors=0;
                        double sum=0; // Summ of the neighbours to get average value

                        try
                        {
                            sum += input_matrix->Get_Element(x-1,y); // trying get left neighbour
                            ++valid_neighbors;
//                            std::cout << "sum=" << sum << std::endl;
                        }
                        catch (...)
                        {}

                        try
                        {
                            sum += input_matrix->Get_Element(x,y-1); // trying get up neighbour
                            ++valid_neighbors;
//                            std::cout << "sum=" << sum << std::endl;
                        }
                        catch (...)
                        {}

                        try
                        {
                            sum += input_matrix->Get_Element(x+1,y); // trying get right neighbour
                            ++valid_neighbors;
//                            std::cout << "sum=" << sum << std::endl;
                        }
                        catch (...)
                        {}

                        try
                        {
                            sum += input_matrix->Get_Element(x,y+1); // trying get down neighbour
                            ++valid_neighbors;
//                            std::cout << "sum=" << sum << std::endl;
                        }
                        catch (...)
                        {}

                        output_matrix->Set_Element(x,y) = sum / valid_neighbors; // replace error value with average between neighbours
                    }
                }
//                std::cout << std::endl;
            }
        }

    }

};

}

#endif
