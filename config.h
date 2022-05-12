#ifndef __XJJC_CONFIG_H_
#define __XJJC_CONFIG_H_

#include <fstream>
#include <iostream>
#include <iomanip>
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
    std::vector<float> vvf(std::string key);
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

std::vector<float> vvf(std::string key)
{
  auto vv = xjjc::str_divide(key, ",");
  std::vector<float> v_result;
  for(auto& iv : vv)
    v_result.push_back(atof(iv.c_str()));
  return v_result;
}

void xjjc::config::print()
{
  for(auto& vv : value_)
    std::cout<<std::left<<std::setw(40)<<vv.first<<" => "<<vv.second<<std::endl;
}

#endif
