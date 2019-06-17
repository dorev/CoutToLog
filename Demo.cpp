#include "CoutToLog.h"
#include <string>
#include <iostream>
int main()
{
  std::cout << "Type a few lines, then type exit" << std::endl;

  CoutToLog redirect1("test.log");
  CoutToLog redirect2("testERROR.log", std::cerr, std::ios::out | std::ios::app);

  // Input to console goes to log file  
  std::string input("");
  for(int i = 0; i < 3; ++i)
  {
    std::cin >> input;
    std::cout << input << std::endl;
    std::cin >> input;
    std::cerr << input << std::endl;
  }

  // Open log file
  system("notepad test.log");
  system("notepad testERROR.log");

  return 0;
}