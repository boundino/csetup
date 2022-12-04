#ifndef __XJJROOT_COMPARE_H_
#define __XJJROOT_COMPARE_H_

#include <TFile.h>
#include <TColor.h>
#include <string>
#include <vector>

#include <TH1.h>
#include <TH2.h>

#include "xjjcuti.h"

namespace xjjroot
{
  enum Opt { name, type };
  std::vector<std::string> opt_default = {"", "TH1F"};

  class compare
  {
  public:
    compare(std::string input="inf::hist#,inf::hist#");
    std::vector<TH1*> vh;
    void setcolor(std::vector<Color_t> cc = {kBlack, kAzure-3, kRed-3, kGreen+2, kOrange-3, kBlue-5, kCyan-2, kMagenta-5, kYellow+2, kPink+2, kViolet+7})
    { for(int i=0; i<vh.size(); i++) { vh[i]->SetLineColor(cc[i]); vh[i]->SetMarkerColor(cc[i]); } }
    void draw(std::vector<const char*> dd = {"pe", "histe", "histe", "histe", "histe", "histe", "histe", "histe", "histe", "histe", "histe"});

  private:
    std::vector<std::vector<std::string>> opt;
  };
}

xjjroot::compare::compare(std::string input)
{
  auto inputs = xjjc::str_divide(input, ",");

  for(auto& ii : inputs)
    {
      auto thisopt = opt_default;
      auto pars = xjjc::str_divide(ii, "#");
      for(int i=0; i<pars.size(); i++)
        if(pars[i] != "") 
          thisopt[i] = pars[i];
      opt.push_back(thisopt);

      // pars[0]
      auto inputname = xjjc::str_divide(pars[0], "::");
      auto inf = TFile::Open(inputname[0].c_str());
      if(thisopt[type]=="TH1D")
        vh.push_back((TH1D*)inf->Get(inputname[1].c_str()));
      else if(thisopt[type]=="TH1F")
        vh.push_back((TH1F*)inf->Get(inputname[1].c_str())); 
      else if(thisopt[type]=="TH2D")
        vh.push_back((TH2D*)inf->Get(inputname[1].c_str()));
      else if(thisopt[type]=="TH2F")
        vh.push_back((TH2F*)inf->Get(inputname[1].c_str())); 
      auto hh = vh[vh.size()-1];
      hh->SetMarkerStyle(21);
      hh->SetMarkerSize(0.6);
      hh->SetLineWidth(1);
      setcolor();
    }
}

void xjjroot::compare::draw(std::vector<const char*> dd)
{
  for(int i=0; i<vh.size(); i++)
    vh[i]->Draw(Form("%s same", dd[i]));
}

#endif
