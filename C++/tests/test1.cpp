#include <iostream>
#include "test1.h"

int main()
{
  int lhv,rhv;
  std::cout << "enter left value:";
  std::cin  >> lhv;
  std::cout << "enter right value:";
  std::cin  >> rhv;


  std::cout << "result: " << calculator(lhv,rhv) << std::endl;

  return 0;
}