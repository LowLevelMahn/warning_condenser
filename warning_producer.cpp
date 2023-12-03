// clang++ -Wall -Wextra warning_producer.cpp
// g++ -Wall -Wextra warning_producer.cpp

static void unused1(){}
int used1(int a, unsigned int b, unsigned int c)
{ 
    int d;
    int e;
    return c < a ? a*2 : a > c ? a : d; 
}

int main()
{
  return used1(10,20,30);
}
