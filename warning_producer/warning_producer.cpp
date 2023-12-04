// clang++ -Wall -Wextra warning_producer.cpp > warnings.txt 2>&1
// g++ -Wall -Wextra warning_producer.cpp > warnings.txt 2>&1
// MSVC cl, clang-cl, MinGW, Intel...

#include <vector>
#include <cassert>

static void unused1(){}
int used1(int a, unsigned int b, unsigned int c)
{ 
    std::vector<int> x;
    x.push_back(c);
    int d;
    int e;
    return c < a ? a*2 : a > c ? a : d; 
}

std::vector<int> nest_ranges(  )
{
    std::vector<int> distance( 10, 0 );
    std::vector<int> overlapping_ranges;
    size_t min_dist = 0;
    size_t otr = 0;
    overlapping_ranges.push_back( otr );
    return distance;
}

int main()
{
  return used1(10,20,30);
}

