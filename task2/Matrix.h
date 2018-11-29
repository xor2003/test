#ifndef __MY_MATRIX__
#define __MY_MATRIX__

//#include <string>
//#include <sstream>              //for std::istringstream
//#include <iterator>             //for std::istream_iterator
#include <vector>               //for std::vector
//#include <iostream>
#include <ostream>
//#include <iomanip>
//#include <algorithm>
//#include <cstdlib>

namespace My
{
  template <class T>
  class Matrix;
}

template <class T>  // print Matrix to ostream
std::ostream& operator<< (std::ostream& stream, const My::Matrix<T>& m)
{
    return m.toStream(stream);
}

namespace My
{

class Prototype
{
public:
    virtual Prototype* clone() = 0;
};

template <class T>
void operator<<(Matrix<T>& m, const std::vector<T>& row)
    {
        m.Insert_Row(row);
    }

template <class T> // value type
class Matrix:      // 2D Martix
	public Prototype
{
public:
    Matrix()
    {
    }

    Matrix(const Matrix<T>& other)
    {
	m_data = other.m_data;
    }

    virtual ~Matrix()
    {
    }

    friend void operator<<(Matrix& m, const std::vector<T>& row);

    void operator<<(const std::vector<T>& row);
    {
        if (row.size() != 0) m_data.push_back(row);
    }

    virtual const T& Get_Element(ptrdiff_t x,ptrdiff_t y) const
    {
        return m_data.at(y).at(x); // bounds checked. exception is generated in case of error
    }

    virtual T& Set_Element(ptrdiff_t x,ptrdiff_t y)
    {
        return m_data.at(y).at(x); // bounds checked. exception is generated in case of error
    }

    virtual std::size_t Get_Height() const
    {
        return m_data.size();
    }

    virtual std::size_t Get_Width() const
    {
        if (m_data.size()>0)  // if there are rows
        {
            return m_data[0].size(); // we can get column size
        }
        else
        {
            return 0;
        }
    }

    virtual std::ostream& toStream(std::ostream& stream) const // print Matrix to ostream
    {
        for(std::size_t y=0; y < Get_Height(); y++)
        {
            for(std::size_t x=0; x < Get_Width(); x++)
            {
                stream << Get_Element(x,y) << " ";
            }
            stream << std::endl;
        }
        return stream;
    }

    Matrix* clone() override
    {
	return new Matrix(*this);
    }

private:
    std::vector<std::vector<T> > m_data;
};



}

#endif
