#ifndef __XJJC_SCONFIG_H_
#define __XJJC_SCONFIG_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "xjjcuti.h"

namespace xjjc
{
  class sconfig
  {
  public:
    sconfig(std::string input, std::string tok1=",", std::string tok2="#") : input_(input), t1_(tok1), t2_(tok2) { parse(); }
    int n() { return value.size(); }
    std::vector<std::vector<std::string>> value;
    void print();
  private:
    std::string input_, t1_, t2_;
    void parse();
  };
}

void xjjc::sconfig::parse()
{
  auto inputs = xjjc::str_divide(input_, t1_);
  for(int i=0; i<inputs.size(); i++)
    {
      auto params = xjjc::str_divide(inputs[i], t2_);
      value.push_back(params);
    }
  print();
}

void xjjc::sconfig::print()
{
  std::cout<<std::endl;
  for(auto& v : value)
    {
      std::cout<<"------"<<std::endl;
      for(auto& vv : v)
        std::cout<<std::left<<"  => "<<std::setw(40)<<vv<<std::endl;
    }
}

#endif
