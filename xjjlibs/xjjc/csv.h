#ifndef __XJJC_CSV_H_
#define __XJJC_CSV_H_

/*
  M-x set-buffer-file-coding-system RET unix RET
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "xjjcuti.h"

namespace xjjc {

  class csv {
  public:
    csv(std::string input, int iheader = -1) : input_(input), iheader_(iheader), ni_(0), nj_(0) { parse(); }
    void print();
    std::string at(int i, int j) { return c_[i][j]; }
    // std::string at(int i, std::string title);
  private:
    std::string input_;
    int ni_, nj_, iheader_;
    xjjc::array2D<std::string> c_;
    std::vector<std::string> h_;
    std::vector<int> w_;
    void parse();
    void print_div();
  };
}

void xjjc::csv::parse() {
  std::cout<<input_<<std::endl;
  std::ifstream filein(input_.c_str());
  ni_ = 0;
  for(std::string line; std::getline(filein, line);) {
    line = xjjc::str_trim( xjjc::str_erasestar(line, "#*") );
    if (line == "") continue;

    auto nline = line;
    std::vector<std::string> vlines = xjjc::str_divide(nline, ",");
    nj_ = std::max((int)vlines.size(), nj_);
    w_.resize(nj_, 1);
    c_.push_back(vlines);

    for (int j=0; j<vlines.size(); j++) {
      auto ll = vlines[j];
      w_[j] = std::max((int)ll.length(), w_[j]);
      if (ni_ == iheader_) {
        h_.push_back(ll);
      }
    }
    ni_++;
  }
}

void xjjc::csv::print() {
  for (int i=0; i<ni_ ; i++) {
    std::string color = "\e[0m";
    if (i==iheader_) color = "\e[48;5;248;38;5;232;1m";
    if ((i > iheader_ && i%2==iheader_%2) || (iheader_<0 && i%2==0 )) color = "\e[48;5;238m";
    print_div();
    std::cout << " " << color << "|";
    for (int j=0; j<nj_; j++) {
      std::cout << std::left << " "<< std::setw(w_[j]+1) << c_[i][j] << "|";
    }
    std::cout << "\e[0m" << std::endl;
  }
  print_div();
}

void xjjc::csv::print_div() {
  std::cout << " " << "\e[0m" << "+";
  for (int j=0; j<nj_; j++) {
    std::cout << std::left << "-"<< std::string(w_[j]+1, '-') << "+";
  }
  std::cout << "\e[0m" << std::endl;
}

#endif 
