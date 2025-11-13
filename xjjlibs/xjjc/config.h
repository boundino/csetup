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
    config(const std::string& input, const std::string& escape="%%")
      : input_(std::move(input)), escape_(std::move(escape)) { parse(); print(); }
    bool has(const std::string& key) const { return value_.find(key) != value_.end(); }
    // get single value
    template <typename T = std::string> T get(const std::string& key) const { return str_convert<T>(v(key)); }
    std::string operator[](const std::string& key) const { return get(key); }
    // get vector
    template <typename T> std::vector<T> get_vec(const std::string& key) const { return str_convert_vector<T>(v(key)); }
    // service
    void print(const std::string& div2 = ",") const;
  private:
    std::map<std::string, std::string> value_;
    std::string input_, escape_;
    // start from string
    std::string v(const std::string& key) const { return has(key) ? value_.at(key) : ""; }
    void parse();
  };
}

void xjjc::config::parse() {
  std::ifstream filein(input_.c_str());
  std::string line_now, key_now;
  for (std::string line; std::getline(filein, line);) {
    line = xjjc::str_trim( xjjc::str_erasestar(line, "#*") );
    if (line == "") continue;

    bool endp = line[line.length()-1] != '\\';
    if (!endp) line.pop_back();
      
    auto content = line;
    if (xjjc::str_contains(line, "=")) {
      auto vline = xjjc::str_divide_trim(line, "=");
      key_now = vline[0];
      content = vline[1];
    }
    line_now += xjjc::str_trim(content);

    if (endp) {
      line_now = xjjc::str_replaceall(line_now, escape_, "#");
      value_[key_now] = line_now;
      key_now.clear();
      line_now.clear();
    }
  }
}

void xjjc::config::print(const std::string& div2) const {
  auto maxk = std::string("").length();
  for (auto& iv : value_) {
    maxk = std::max(maxk, iv.first.length());
  }
  for (auto& iv : value_) {
    std::cout << std::left << " \e[4;3m" << std::setw(maxk) << iv.first << "\e[0m"
              << "\e[2m => \e[0m";
    auto vl2 = str_divide_trim(iv.second, div2);
    auto first = true;
    for (auto & i2 : vl2) {
      if (!first)
        std::cout << std::left << std::setw(maxk+5) << " ";
      first = false;
      std::cout << str_trim(i2) << "\e[0m"
                << std::endl;
    }
  }
}

#endif
