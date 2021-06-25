#ifndef _XJJANA_UTI_H_
#define _XJJANA_UTI_H_

/* xjjanauti.h */

#include <TTree.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TH1.h>
#include <TGaxis.h>
#include <TF1.h>
#include <TMath.h>
#include <TEfficiency.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TSystem.h>

#include <vector>
#include <iostream>
#include <iomanip>

#include "xjjrootuti.h"

namespace xjjana
{
  void dividebinwid(TH1* h);
  TH1* histMinusCorr(TH1* ha, TH1* hb, std::string name);
  void drawpull(TH1* h, TF1* f, Color_t color=0, float ymax=4);
  std::map<std::string, double> chi2test(TH1* h1, TH1* h2, const char* opt="UW");
  double gethminimum(TH1* h);
  double gethmaximum(TH1* h);
  double sethsmin(std::vector<TH1F*>& h, float factor);
  double sethsmax(std::vector<TH1F*>& h, float factor);
  void sethsminmax(std::vector<TH1F*>& h, float factor_min, float factor_max);

  TGraphErrors* shifthistcenter(TH1* hh, std::string name, int option=-1);
  TGraphAsymmErrors* shifthistcenter(TEfficiency* geff, std::string name, int option=-1);
  TGraphAsymmErrors* shifthistcenter(TH1* hh, std::string name, float offset, std::string option=""); // opt ["X0": zero x err]
  TGraphAsymmErrors* setwcenter(TH1F* h, std::vector<double>& xw, std::string name);
  std::vector<double> gethXaxis(TH1* h);

  void setbranchaddress(TTree* nt, const char* bname, void* addr);
  template <class T> T* copyobject(const T* obj, TString objname);
}

/* ---------- */

void xjjana::setbranchaddress(TTree* nt, const char* bname, void* addr)
{
  nt->SetBranchStatus(bname, 1);
  nt->SetBranchAddress(bname, addr);
}

void xjjana::dividebinwid(TH1* h)
{
  for(int i=0;i<h->GetNbinsX();i++)
    {
      Float_t val = h->GetBinContent(i+1)/h->GetBinWidth(i+1);
      Float_t valErr = h->GetBinError(i+1)/h->GetBinWidth(i+1);
      h->SetBinContent(i+1,val);
      h->SetBinError(i+1,valErr);
    }
}

TH1* xjjana::histMinusCorr(TH1* ha, TH1* hb, std::string name)
{
  TH1* hr = (TH1*)ha->Clone(name.c_str());
  for(int i=0;i<ha->GetNbinsX();i++)
    {
      hr->SetBinContent(i+1, ha->GetBinContent(i+1)-hb->GetBinContent(i+1));
      hr->SetBinError(i+1, TMath::Sqrt(TMath::Abs(ha->GetBinError(i+1)*ha->GetBinError(i+1) -
                                                  hb->GetBinError(i+1)*hb->GetBinError(i+1))));
    }
  return hr;
}

void xjjana::drawpull(TH1* h, TF1* f, Color_t color, float pullmax)
{
  Color_t tcolor = color?color:f->GetLineColor();
  int nbin = h->GetXaxis()->GetNbins();
  float binmin = h->GetXaxis()->GetXmin(), binmax = h->GetXaxis()->GetXmax();
  float yhmax = h->GetMaximum(), yhmin = h->GetMinimum();
  // float yhmax = h->GetYaxis()->GetXmax();
  for(int bb=0; bb<nbin; bb++)
    {
      float realval = h->GetBinError(bb+1)==0?0:(h->GetBinContent(bb+1)-f->Eval(h->GetBinCenter(bb+1)))/h->GetBinError(bb+1);
      // float fillval = ((realval+pullmax)/(pullmax*2))*yhmax;
      float fillval = ((realval+pullmax)/(pullmax*2))*(yhmax-yhmin)+yhmin;
      xjjroot::drawbox(h->GetBinCenter(bb+1)-h->GetBinWidth(bb+1)/2., (yhmax-yhmin)/2.+yhmin, h->GetBinCenter(bb+1)+h->GetBinWidth(bb+1)/2., fillval, tcolor, 0.1, 1001);
    }
  xjjroot::drawline(binmin, (yhmax-yhmin)/2.+yhmin, binmax, (yhmax-yhmin)/2.+yhmin, kGray, 2, gStyle->GetLineWidth(), 0.5);
  xjjroot::drawaxis(binmax, yhmin, binmax, yhmax, -pullmax, pullmax, tcolor, 1, gStyle->GetLineWidth(), "+L", h->GetYaxis()->GetLabelSize()*0.9);
  xjjroot::drawtex(0.93, 0.55, "Pull", 0.04, 33, 62, tcolor);
}

std::map<std::string, double> xjjana::chi2test(TH1* h1, TH1* h2, const char* opt)
{
  // double res[n];
  std::cout<<"## Chi2 Test ("<<h1->GetName()<<", "<<h2->GetName()<<")"<<std::endl;
  double pvalue = h1->Chi2Test(h2, opt);
  double chi2 = h1->Chi2Test(h2, Form("%s CHI2", opt));
  double chi2ndf = h1->Chi2Test(h2, Form("%s CHI2/NDF P", opt));
  double ndf = chi2 / chi2ndf;
  std::map<std::string, double> result;
  result["chi2ndf"] = chi2ndf;
  result["pvalue"] = pvalue;
  result["chi2"] = chi2;
  result["ndf"] = ndf;
  result["chi2prob"] = TMath::Prob(chi2, ndf);
  return result;
}

double xjjana::gethminimum(TH1* h)
{
  double ymin = 1.e+10;
  for(int i=0; i<h->GetXaxis()->GetNbins(); i++)
    ymin = std::min(ymin, h->GetBinContent(i+1));
  return ymin;
}

double xjjana::gethmaximum(TH1* h)
{
  double ymax = -1.e+10;
  for(int i=0; i<h->GetXaxis()->GetNbins(); i++)
    ymax = std::max(ymax, h->GetBinContent(i+1));
  return ymax;
}

double xjjana::sethsmin(std::vector<TH1F*>& h, float factor)
{
  double ymin = 1.e+10;
  for(auto& hh : h) ymin = std::min(ymin, gethminimum(hh));
  for(auto& hh : h) hh->SetMinimum(ymin * factor);
  return ymin;
}

double xjjana::sethsmax(std::vector<TH1F*>& h, float factor)
{
  double ymax = -1.e+10;
  for(auto& hh : h) ymax = std::max(ymax, gethmaximum(hh));
  for(auto& hh : h) hh->SetMaximum(ymax * factor);
  return ymax;
}

void xjjana::sethsminmax(std::vector<TH1F*>& h, float factor_min, float factor_max)
{
  double ymax = -1.e+10, ymin = 1.e+10;
  for(auto& hh : h)
    {
      ymin = std::min(ymin, gethminimum(hh));
      ymax = std::max(ymax, gethmaximum(hh));
    }
  for(auto& hh : h)
    {
      hh->SetMinimum(ymin * factor_min);
      hh->SetMaximum(ymax * factor_max);
    }
}

TGraphErrors* xjjana::shifthistcenter(TH1* hh, std::string name, int option)
{
  int n = hh->GetNbinsX();
  std::vector<double> xx, yy, xxerr, yyerr;
  for(int i=0; i<n; i++)
    {
      yy.push_back(hh->GetBinContent(i+1));
      yyerr.push_back(hh->GetBinError(i+1));
      if(option == 0) xxerr.push_back(hh->GetBinWidth(i+1)/2.);
      else xxerr.push_back(0);
      if(option < 0) xx.push_back(hh->GetBinCenter(i+1) - hh->GetBinWidth(i+1)/2.);
      else if(option > 0) xx.push_back(hh->GetBinCenter(i+1) + hh->GetBinWidth(i+1)/2.);
      else xx.push_back(hh->GetBinCenter(i+1));
    }
  TGraphErrors* gr = new TGraphErrors(n, xx.data(), yy.data(), xxerr.data(), yyerr.data()); gr->SetName(name.c_str());
  return gr;
}

TGraphAsymmErrors* xjjana::shifthistcenter(TH1* hh, std::string name, float offset, std::string option)
{
  int n = hh->GetNbinsX();
  std::vector<double> xx, yy, xxel, xxeh, yyerr;
  for(int i=0; i<n; i++)
    {
      yy.push_back(hh->GetBinContent(i+1));
      xx.push_back(hh->GetBinCenter(i+1) + offset);
      if(option.find("Y0") != std::string::npos)
        yyerr.push_back(0);
      else
        yyerr.push_back(hh->GetBinError(i+1));
      if(option.find("X0") != std::string::npos)
        {
          xxel.push_back(0);
          xxeh.push_back(0);
        }
      else
        {
          xxel.push_back(std::max(hh->GetBinWidth(i+1)/2. + offset, (double)0));
          xxeh.push_back(std::max(hh->GetBinWidth(i+1)/2. - offset, (double)0));
        }
    }
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(n, xx.data(), yy.data(), xxel.data(), xxeh.data(), yyerr.data(), yyerr.data()); gr->SetName(name.c_str());
  return gr;
}

TGraphAsymmErrors* xjjana::shifthistcenter(TEfficiency* geff, std::string name, int option)
{
  TH1* hclone = geff->GetCopyTotalHisto();
  int n = hclone->GetNbinsX();
  std::vector<double> xx, yy, xxel, xxeh, yyel, yyeh;
  for(int i=0; i<n; i++)
    {
      if(option < 0) xx.push_back(hclone->GetBinCenter(i+1) - hclone->GetBinWidth(i+1)/2.);
      else if(option > 0) xx.push_back(hclone->GetBinCenter(i+1) + hclone->GetBinWidth(i+1)/2.);
      else xx.push_back(hclone->GetBinCenter(i+1));
      if(option == 0) { xxel.push_back(hclone->GetBinWidth(i+1)/2.); xxeh.push_back(hclone->GetBinWidth(i+1)/2.); }
      else { xxel.push_back(0); xxeh.push_back(0); }
      yy.push_back(geff->GetEfficiency(i+1));
      yyel.push_back(geff->GetEfficiencyErrorLow(i+1));
      yyeh.push_back(geff->GetEfficiencyErrorUp(i+1));
    }
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(n, xx.data(), yy.data(), xxel.data(), xxeh.data(), yyel.data(), yyeh.data()); gr->SetName(name.c_str());
  return gr;
}

TGraphAsymmErrors* xjjana::setwcenter(TH1F* h, std::vector<double>& xw, std::string name)
{
  int n = h->GetXaxis()->GetNbins();
  std::vector<double> y(n), xel(n), xeh(n), ye(n);
  for(int i=0; i<n; i++)
    {
      xel[i] = xw[i] - (h->GetBinCenter(i+1)-h->GetBinWidth(i+1)/2.);
      xeh[i] = (h->GetBinCenter(i+1)+h->GetBinWidth(i+1)/2.) - xw[i];
      y[i] = h->GetBinContent(i+1);
      ye[i] = h->GetBinError(i+1);
    }
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(n, xw.data(), y.data(), xel.data(), xeh.data(), ye.data(), ye.data());
  gr->SetName(name.c_str());
  return gr;
}

std::vector<double> xjjana::gethXaxis(TH1* h)
{
  const double* vx = h->GetXaxis()->GetXbins()->GetArray();
  int nx = h->GetXaxis()->GetNbins();
  std::vector<double> vvx({vx, vx+nx});
  vvx.push_back(h->GetXaxis()->GetXmax());
  return vvx;
}

template <class T>
T* xjjana::copyobject(const T* obj, TString objname)
{
  T* newobj = new T(*obj);
  newobj->SetName(objname);
  return newobj;
}

#endif
