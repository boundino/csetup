#ifndef __XJJROOT_PARAM__
#define __XJJROOT_PARAM__

#include <map>
#include <string>
#include <vector>
#include <TFile.h>
#include "xjjcuti.h"

namespace xjjroot
{
  class param
  {
  public:
    param() { ; }
    param(int isheavyion, float ptmin, float ptmax, float etamin, float etamax, float centmin, float centmax, int ismc, std::string obj="", std::string opt="");
    param(TFile* inf, std::string opt="");
    void write();
    float& operator[](std::string var) { return val_[var]; }
    bool ishi() { return (bool)ishi_; }
    bool ismc() { return (bool)ismc_; }
    void setishi(int ishi__) { ishi_ = ishi__; parsetag(); }
    void setismc(int ismc__) { ismc_ = ismc__; parsetag(); }
    std::string tag(std::string var = "") { return tag_[var]; }
    void print();
    void drawtex(float xleft=0.22, float ytop=0.88, float tsize=0.038, std::string exclude="");
  private:
    int ishi_, ismc_;
    std::map<std::string, float> val_;
    std::map<std::string, std::string> tag_;
    void parsetag();
    std::string opt_, obj_;

    std::vector<std::string> list_ = {
      "ptmin",
      "ptmax",
      "etamin",
      "etamax",
      "centmin",
      "centmax",
    };
  };
}

xjjroot::param::param(int isheavyion, float ptmin, float ptmax, float etamin, float etamax, float centmin, float centmax, int ismc, std::string obj, std::string opt) : 
  ishi_(isheavyion),
  ismc_(ismc),
  opt_(opt),
  obj_(obj)
{
  if(opt_!="Q") std::cout<<"\e[32;1m -- "<<__PRETTY_FUNCTION__<<"\e[0m"<<std::endl;
  ishi_ = isheavyion;
  ismc_ = ismc;
  val_["ptmin"] = ptmin;
  val_["ptmax"] = ptmax;
  val_["etamin"] = etamin;
  val_["etamax"] = etamax;
  val_["centmin"] = centmin;
  val_["centmax"] = centmax;

  parsetag();
  if(opt_!="Q") print();
}

xjjroot::param::param(TFile* inf, std::string opt) : opt_(opt)
{
  if(opt_!="Q") std::cout<<"\e[32;1m -- "<<__PRETTY_FUNCTION__<<"\e[0m"<<std::endl;
  TTree* p = (TTree*)inf->Get("param");
  p->SetBranchAddress("ishi", &ishi_);
  p->SetBranchAddress("ismc", &ismc_);
  p->SetBranchAddress("obj", &obj_);
  for(auto pp : list_) p->SetBranchAddress(pp.c_str(), &(val_[pp]));
  p->GetEntry(0);

  parsetag();
  if(opt_ != "Q") print();
}

void xjjroot::param::write()
{
  TTree* p = new TTree("param", "parameters");
  p->Branch("ishi", &ishi_);
  p->Branch("ismc", &ismc_);
  p->Branch("obj", &obj_);
  for(auto& v : val_) p->Branch(v.first.c_str(), &(v.second));
  p->Fill();
  p->Write();
}

void xjjroot::param::parsetag()
{
  tag_[""] = "";
  std::string tishi = (ishi_==0?"pp":(ishi_==1?"PbPb":""));
  tag_[""] += tishi;
  std::string tismc = (ismc_==0?"data":(ismc_==1?"MC":""));
  tag_[""] += ((tag_[""]==""?"":"_")+tismc);
  tag_[""] += ((tag_[""]==""?"":"_") + ("pt" + xjjc::number_remove_zero(val_["ptmin"]) + "-" + xjjc::number_remove_zero(val_["ptmax"])));
  tag_[""] += ("_eta" + xjjc::number_remove_zero(val_["etamin"]) + "-" + xjjc::number_remove_zero(val_["etamax"]));
  if(ishi_==1)
    tag_[""] += ("_cent" + xjjc::number_remove_zero(val_["centmin"]) + "-" + xjjc::number_remove_zero(val_["centmax"]));

  if(val_["ptmax"] < 999)
    tag_["pt"] = xjjc::number_remove_zero(val_["ptmin"]) + " < p_{T}" + (obj_==""?"":"^{"+obj_+"}") + " < " + xjjc::number_remove_zero(val_["ptmax"]) + " GeV/c";
  else
    tag_["pt"] = "p_{T}" + (obj_==""?"":"^{"+obj_+"}") + " > " + xjjc::number_remove_zero(val_["ptmin"]) + " GeV/c";

  if(val_["etamin"] > 0)
    tag_["eta"] = xjjc::number_remove_zero(val_["etamin"]) + " < |#eta" + (obj_==""?"":"^{"+obj_+"}") + "| < " + xjjc::number_remove_zero(val_["etamax"]);
  else
    tag_["eta"] = "|#eta" + (obj_==""?"":"^{"+obj_+"}") + "| < " + xjjc::number_remove_zero(val_["etamax"]);

  if(ishi_) tag_["cent"] = "Cent. " + xjjc::number_remove_zero(val_["centmin"]) + " - " + xjjc::number_remove_zero(val_["centmax"]) + "%";
  else tag_["cent"] = "";
  tag_["ishi"] = tishi;
  tag_["ismc"] = tismc;
}

void xjjroot::param::print()
{
  xjjc::prt_divider("\e[34m");
  for(auto& t : tag_)
    {
      std::cout << "\e[34m  " << t.second << "\e[0m" << std::endl;
      xjjc::prt_divider("\e[34m");
    }
}

void xjjroot::param::drawtex(float xleft, float ytop, float tsize, std::string exclude)
{
  std::vector<std::string> ex = xjjc::str_divide(exclude, ",");
  float ls = tsize*1.5;

  float ytop_ = ytop + ls;
  std::vector<std::string> info_left = {"pt", "eta", "cent"};
  for(auto& i : info_left)
    if(std::find(ex.begin(), ex.end(), i) == ex.end())
      { xjjroot::drawtex(xleft, ytop_-=ls, tag_[i].c_str(), tsize, 13); }

  std::vector<std::string> info_right = {""};
  ytop_ = ytop + ls;
  for(auto& i : info_right)
    if(std::find(ex.begin(), ex.end(), i) == ex.end())
      { xjjroot::drawtex(xleft+0.5, ytop_-=ls, tag_[i].c_str(), tsize, 13); }
}

#endif
