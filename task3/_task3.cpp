/*
Build command: g++  _task2.cpp  -o _task2
*/

/*
#include "Common.h"                   // for StringToType
*/

#include <iostream>                     // for ofstream, basic_ostream, etc
#include <string>                       // for char_traits, string
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>

#include <cstddef>                      // for ptrdiff_t, size_t
#include <functional>                   // for less

namespace My
{

/*! ---------------------------------------------------------------------
//
//  Sorter class
//
//  \brief Sorts container V data according to the K keys container 
//         and store result to V result_data
//
// \param[in]  K keys, V data , F sorting function
//
// \param[out] V result_data
//
---------------------------------------------------------------------- */

template <class K, class V, typename F = std::less<ptrdiff_t> >
struct Sorter
{

 struct sort_proxy // sorting proxy class
 {

    typename K::const_iterator k; // iterator pointing to data container value
    typename V::const_iterator v; // iterator pointing to key container value

    sort_proxy() {}

    operator ptrdiff_t() //provides value for comparision
    {
        return *k;
    }
 };

    Sorter()
    {}

    void run (const K& keys, const V& data, V& result_data)
    {

        std::vector<sort_proxy > proxies(keys.size());

        {
 	 size_t proxy_i=0;
	 typename V::const_iterator v = data.begin(); // iterator to data container
         for (typename K::const_iterator k = keys.begin(); k != keys.end(); k++) // initialize sorting proxy container
         {
             proxies[proxy_i].k = k; // put key iterator to proxy container
             proxies[proxy_i].v = v; // put value iterator to proxy container
	     proxy_i++; // move proxy index
	     v++;  // move data iterator
         }
        }

        std::sort(proxies.begin(), proxies.end(), F()); // sorting proxy container

        result_data.resize(keys.size());
	typename V::iterator res_i = result_data.begin(); // result container iterator
        for (size_t j=0; j<proxies.size(); j++) // generating resulting data
        {
            *res_i = *(proxies[j].v); // move data to result container
	    res_i++;
        }
    }

};

}

using namespace My;

typedef std::list<std::string> data_type; // first container with data type
typedef std::list<ptrdiff_t> keys_type;   // second container with the key type

int main (int argc, char *argv[])
{

    data_type data = {{ "a", "b", "c" }}; // first container with data
    const keys_type keys = {{ 4, 7, 1 }}; // second container with the key

    data_type result_data;  // result container with data
    Sorter<keys_type, data_type> s;
    s.run(keys, data, result_data);

    // print result to screen
    std::copy(result_data.begin(), result_data.end(), std::ostream_iterator<std::string>( std::cout, " "));
    std::cout << std::endl;

    return 0;
}
