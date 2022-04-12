#ifndef __XJJC_CONFIG_H_
#define __XJJC_CONFIG_H_

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "xjjcuti.h"

namespace xjjc
{
  class config
  {
  public:
    config(std::string input) : input_(input) { parse(); }
    std::string v(std::string key) { return value_[key]; }
    float vf(std::string key) { return atof(value_[key].c_str()); }
    int vi(std::string key) { return atoi(value_[key].c_str()); }
    void print();
  private:
    std::string input_;
    std::map<std::string, std::string> value_;
    void parse();
  };
}

void xjjc::config::parse()
{
  std::ifstream filein(input_.c_str());
  for(std::string line; std::getline(filein, line);)
    {
      if(!xjjc::str_contains(line, "=")) continue;
      line = xjjc::str_eraseall(line, " ");
      auto vline = xjjc::str_divide(line, "=");
      value_[vline[0]] = vline[1];
    }
}

void xjjc::config::print()
{
  for(auto& vv : value_)
      std::cout<<vv.first<<" ==> "<<vv.second<<std::endl;
}

#endif
