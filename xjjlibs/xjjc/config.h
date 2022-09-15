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
    bool goodkey(std::string key) { return value_.find(key) != value_.end(); }
    std::string v(std::string key) { return goodkey(key)?value_[key]:""; }
    std::string operator[](std::string key) { return v(key); }
    float vf(std::string key) { return atof(v(key).c_str()); }
    int vi(std::string key) { return atoi(v(key).c_str()); }
    std::vector<std::string> vv(std::string key) { return str_divide(v(key), ","); }
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
      line = xjjc::str_replaceall(line, " =", "=");
      line = xjjc::str_replaceall(line, "= ", "=");
      auto vline = xjjc::str_divide(line, "=");
      value_[vline[0]] = vline[1];
    }
}

std::vector<float> xjjc::config::vvf(std::string key)
{
  std::vector<std::string> vv = str_divide(v(key), ",");
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
