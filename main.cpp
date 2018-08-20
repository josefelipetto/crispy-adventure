/**
    main.cpp
    Purpose: Analyze computer performance on calculating PI number.

    @author José Henrique Felipetto
    @version 1.0 20/08/2018
*/

#include <cstdint>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

/**
    Get the number of clocks on the moment that is called

    @return the number of clocks on the moment
*/
uint64_t rdtscp(){
    unsigned int lo,hi;
    asm	volatile ("rdtscp":"=a"	(lo),"=d"(hi));
    return	((uint64_t)hi	<<	32)	|	lo;
}


int main()
{

    auto t0 = steady_clock::now();
    auto r0 = rdtscp();

    long long clock = 0;

    long double aux = 0;

    long double exp = 1;
    
    for(size_t i = 0; i < 1e9; i++ )
    {
        aux += ( exp / ( (2*i+2)*(2*i+3)*(2*i+4) ));

        exp = - exp;
    }

    long double pi = 3 + 4 * aux;

    auto dc = rdtscp() - r0;

    auto d = steady_clock::now() - t0;

    cout << "Pi : " << pi << endl;

    cout << "Clock :" << dc << endl;

    cout << "Time:" << duration_cast<milliseconds>(d).count() << " ms" << endl;

    return 0;
}
