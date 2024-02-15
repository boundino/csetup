#ifndef __XJJC_CSV_H_
#define __XJJC_CSV_H_

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
  private:
    std::string input_;
    int ni_, nj_, iheader_;
    xjjc::array2D<std::string> c_;
    std::vector<std::string> h_;
    std::vector<int> w_;
    void parse();
  };
}

void xjjc::csv::parse() {
  std::cout<<input_<<std::endl;
  std::ifstream filein(input_.c_str());
  ni_ = 0;
  for(std::string line; std::getline(filein, line);) {
    line = xjjc::str_trim( xjjc::str_erasestar(line, "#*") );
    if (line == "") continue;
    // std::cout<<line<<std::endl;
    auto nline = line;
    std::vector<std::string> vlines = xjjc::str_divide(nline, ",");
    nj_ = std::max((int)vlines.size(), nj_);
    w_.resize(nj_, 1);
    // std::cout<<vlines.size()<<std::endl;
    std::vector<std::string> il;
    for (int j=0; j<vlines.size(); j++) {
      auto ll = vlines[j];
      // std::cout<<j<<" "<<ll.length()<<" -> ";
      std::cout<<j<<" ";
      il.push_back(ll);
      w_[j] = std::max((int)ll.length(), w_[j]);
      // std::cout<<w_[j]<<" "<<ll<<" ";
      std::cout<<w_[j]<<" ";
      if (ni_ == iheader_) {
        h_.push_back(ll);
      }
      std::cout<<vlines[j]<<" ";
      std::cout<<"| ";
    }
    std::cout<<std::endl<<std::endl;
    c_.push_back(il);
    ni_++;
  }
}

void xjjc::csv::print() {
  for (int i=0; i<ni_ ; i++) {
    std::cout<<nj_<<" "<<c_[i][0]<<std::endl;
    for (int j=0; j<nj_; j++) {
      std::cout<<w_[j]<<" : ";
      std::string color = "\e[0m";
      if (i==iheader_) color = "\e[7m";
      if ((i > iheader_ && i%2==iheader_%2) || (iheader_<0 && i%2==0 )) color = "\e[40;37m";
      // std::cout << std::left << color << std::setw(w_[j]) << c_[i][j] << "\e[0m ";
      std::cout << std::left <<  std::setw(w_[j]) << c_[i][j] << "\e[0m ";
    }
    std::cout<<std::endl;
  }
}

#endif 
