#ifndef _XJJROOT_UTI_H_
#define _XJJROOT_UTI_H_

/* xjjrootuti.h */

#include <TTree.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TH1.h>
#include <TGaxis.h>
#include <TMath.h>
#include <TEfficiency.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TSystem.h>

#include <vector>

namespace xjjroot
{
  const float margin_pad_left = 0.18;
  const float margin_pad_right = 0.043;
  const float margin_pad_bottom = 0.145;
  const float margin_pad_top = 0.1;

  std::vector<Color_t> colorlist_light  = {kGreen-8, kOrange-4, kRed-9, kAzure-9, kMagenta-8, kCyan-8, kYellow-6, kBlue-8, kPink+1, kViolet-9};
  std::vector<Color_t> colorlist_middle = {kGreen+2, kOrange-3, kRed-3, kAzure-3, kMagenta-5, kCyan-2, kYellow+2, kBlue-5, kPink+2, kViolet+7};
  std::vector<Color_t> colorlist_dark   = {kGreen+3, kOrange+5, kRed+2, kAzure-6, kMagenta-1, kCyan+3, kYellow+3, kBlue-1, kPink+3, kViolet+4};

  void setgstyle(Int_t padtick=0, Width_t lwidth=2);
  template <class T> void sethempty(T* hempty, Float_t xoffset=0, Float_t yoffset=0, Float_t xsize=0.05, Float_t ysize=0.05);
  template <class T> void setthgr(T* hempty, Float_t xoffset=0, Float_t yoffset=0);
  template <class T> void setthgrstyle(T* h, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1, Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1);
  template <class T> void setlinestyle(T* h, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1, Float_t lalpha=-1);
  template <class T> void settfstyle(T* h, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1, Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1);
  template <class T> void setmarkerstyle(T* h, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1);
  void drawCMSleft(TString content="#scale[1.25]{#bf{CMS}} #it{Preliminary}", Float_t xpos=0, Float_t ypos=0);
  void drawCMSright(TString content="PbPb #sqrt{s_{NN}} = 5.02 TeV", Float_t xpos=0, Float_t ypos=0);
  void drawCMS(TString contentleft="#scale[1.25]{#bf{CMS}} #it{Preliminary}", TString contentright="PbPb #sqrt{s_{NN}} = 5.02 TeV");
  void settex(TLatex* tex, Float_t tsize=0.04, Short_t align=12, Style_t font=42, Color_t color=kBlack);
  TLatex* drawtex(Double_t x, Double_t y, const char *text, Float_t tsize=0.04, Short_t align=12, Style_t font=42, Color_t color=kBlack);
  void drawtexgroup(Double_t x, Double_t y, std::vector<std::string> text, int ncol=1, Double_t colwid=0.2, Float_t tsize=0.04, Short_t align=12, Style_t font=42, std::vector<Color_t> color=colorlist_middle);
  void setleg(TLegend* leg, Float_t tsize=0.04);
  void setlegndraw(TLegend* leg, Float_t tsize=0.04);
  TLine* drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t lcolor=kBlack, Style_t lstyle=1, Width_t lwidth=2, Float_t lalpha=1);
  TBox* drawbox(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t fcolor=kGray, Float_t falpha=0.4, Style_t fstyle=1001, Color_t lcolor=0, Style_t lstyle=1, Width_t lwidth=0);
  TGaxis* drawaxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, 
                   Double_t wmin, Double_t wmax, 
                   Color_t lcolor=kBlack, Style_t lstyle=1, Width_t lwidth=1,
                   Option_t *chopt="", Int_t ndiv=510, Double_t gridlength=0);

  void dividebinwid(TH1* h);
  TH1* histMinusCorr(TH1* ha, TH1* hb, std::string name);
  TGraphErrors* shifthistcenter(TH1* hh, std::string name, int option=-1);
  TGraphAsymmErrors* shifthistcenter(TEfficiency* geff, std::string name, int option=-1);

  void mkdir(std::string outputfile);

  void setbranchaddress(TTree* nt, const char* bname, void* addr);
  template <class T> T* copyobject(const T* obj, TString objname);
}

/* ---------- */

void xjjroot::setgstyle(Int_t padtick/*=0*/, Width_t lwidth/*=2*/)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left);
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom);
  gStyle->SetTitleX(.0f);
  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(0);
  gStyle->SetLineWidth(1);
  gStyle->SetFrameLineWidth(1);
  if(padtick==1 || padtick==3)
    {
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
    }
  if(padtick==2 || padtick==3) { gStyle->SetLineWidth(lwidth); gStyle->SetFrameLineWidth(lwidth);}
}

template <class T>
void xjjroot::sethempty(T* hempty, Float_t xoffset/*=0*/, Float_t yoffset/*=0*/, Float_t xsize/*=0.05*/, Float_t ysize/*=0.05*/)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.10+xoffset);
  hempty->GetYaxis()->SetTitleOffset(1.30+yoffset);
  hempty->GetXaxis()->SetTitleSize(xsize);
  hempty->GetYaxis()->SetTitleSize(ysize);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.045);
  hempty->GetYaxis()->SetLabelSize(0.045);
  hempty->SetStats(0);
}

template <class T>
void xjjroot::setthgr(T* hempty, Float_t xoffset/*=0*/, Float_t yoffset/*=0*/)
{
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.10+xoffset);
  hempty->GetYaxis()->SetTitleOffset(1.30+yoffset);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.045);
  hempty->GetYaxis()->SetLabelSize(0.045);
  hempty->SetStats(0);
  hempty->SetMarkerStyle(20);
  hempty->SetMarkerSize(1.1);
  hempty->SetMarkerColor(kBlack);
  hempty->SetLineColor(kBlack);
}

template <class T>
void xjjroot::setthgrstyle(T* h, Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/, Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/, Color_t fcolor/*=-1*/, Float_t falpha/*=-1*/, Style_t fstyle/*=-1*/)
{
  if(mcolor>=0) h->SetMarkerColor(mcolor);
  if(mstyle>=0) h->SetMarkerStyle(mstyle);
  if(msize>=0)  h->SetMarkerSize(msize);
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
  if(fcolor>=0) h->SetFillColor(fcolor);
  if(falpha>=0) h->SetFillColorAlpha(fcolor, falpha);
  if(fstyle>=0) h->SetFillStyle(fstyle);
}

template <class T>
void xjjroot::setlinestyle(T* h, Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/, Float_t lalpha/*=-1*/)
{
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lalpha>=0) h->SetLineColorAlpha(lcolor, lalpha);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
}

template <class T>
void xjjroot::settfstyle(T* h, Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/, Color_t fcolor/*=-1*/, Float_t falpha/*=-1*/, Style_t fstyle/*=-1*/)
{
  h->SetNpx(1000);
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
  if(fcolor>=0) h->SetFillColor(fcolor);
  if(falpha>=0) h->SetFillColorAlpha(fcolor, falpha);
  if(fstyle>=0) h->SetFillStyle(fstyle);
}

template <class T>
void xjjroot::setmarkerstyle(T* h, Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/)
{
  if(mcolor>=0) h->SetMarkerColor(mcolor);
  if(mstyle>=0) h->SetMarkerStyle(mstyle);
  if(msize>=0)  h->SetMarkerSize(msize);
}

void xjjroot::drawCMS(TString contentleft/*="#scale[1.25]{#bf{CMS}} #it{Preliminary}"*/, TString contentright/*="PbPb #sqrt{s_{NN}} = 5.02 TeV"*/)
{
  drawCMSleft(contentleft);
  drawCMSright(contentright);
}

void xjjroot::drawCMSleft(TString content/*="#scale[1.25]{#bf{CMS}} #it{Preliminary}"*/, Float_t xpos/*=0*/, Float_t ypos/*=0*/)
{
  if(content=="" || content=="Preliminary") content = "#scale[1.25]{#bf{CMS}} #it{Preliminary}";
  if(content=="Simulation") content = "#scale[1.25]{#bf{CMS}} #it{Simulation}";
  TLatex* texCms = new TLatex(gStyle->GetPadLeftMargin()+xpos,(1-gStyle->GetPadTopMargin())*1.02+ypos, content.Data());
  texCms->SetNDC();
  texCms->SetTextAlign(11);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
}

void xjjroot::drawCMSright(TString content/*="PbPb #sqrt{s_{NN}} = 5.02 TeV"*/, Float_t xpos/*=0*/, Float_t ypos/*=0*/)
{
  TLatex* texCol = new TLatex((1-gStyle->GetPadRightMargin())+xpos,(1-gStyle->GetPadTopMargin())*1.02+ypos, content.Data());
  texCol->SetNDC();
  texCol->SetTextAlign(31);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();
}

void xjjroot::settex(TLatex* tex, Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/, Color_t color/*=kBlack*/)
{
  tex->SetNDC();
  tex->SetTextFont(font);
  tex->SetTextAlign(align);
  tex->SetTextSize(tsize);
  tex->SetTextColor(color);
}

TLatex* xjjroot::drawtex(Double_t x, Double_t y, const char* text, Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/, Color_t color/*=kBlack*/)
{
  TLatex* tex = new TLatex(x, y, text);
  xjjroot::settex(tex, tsize, align, font, color);
  tex->Draw();
}

void xjjroot::drawtexgroup(Double_t x, Double_t y, std::vector<std::string> text, int ncol/*=1*/, Double_t colwid/*=0.2*/, Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/, std::vector<Color_t> color/*=std::vector<Color_t>()*/)
{
  double lspace = tsize+0.005;
  bool left = true, top = true;
  if(align == 31 || align == 33) left = false;
  if(align == 11 || align == 31) top = false;
  for(int t=0; t<text.size(); t++)
    {
      double xx = x + colwid*(t%ncol);
      if(!left) xx = x - colwid*(t%ncol);
      double yy = y - lspace*(t/ncol);
      if(!top) yy = y + lspace*(t/ncol);
      Color_t cc = t<color.size()?color[t]:kBlack;
      drawtex(xx, yy, text[t].c_str(), tsize, align, font, cc);
    }
}

void xjjroot::setleg(TLegend* leg, Float_t tsize/*=0.04*/)
{
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(tsize);
}

void xjjroot::setlegndraw(TLegend* leg, Float_t tsize/*=0.04*/)
{
  xjjroot::setleg(leg, tsize);
  leg->Draw();
}

TLine* xjjroot::drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=2*/, Float_t lalpha/*=1*/)
{
  TLine* l = new TLine(x1, y1, x2, y2);
  xjjroot::setlinestyle(l, lcolor, lstyle, lwidth, lalpha);
  l->Draw();
  return l;
}

TBox* xjjroot::drawbox(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Color_t fcolor/*=kGray*/, Float_t falpha/*=0.4*/, Style_t fstyle/*=1001*/, Color_t lcolor/*=0*/, Style_t lstyle/*=1*/, Width_t lwidth/*=0*/)
{
  TBox* b = new TBox(x1, y1, x2, y2);
  b->SetFillColor(fcolor);
  b->SetFillColorAlpha(fcolor, falpha);
  b->SetFillStyle(fstyle);
  b->SetLineColor(lcolor);
  b->SetLineStyle(lstyle);
  b->SetLineWidth(lwidth);
  b->Draw();
  return b;
}

TGaxis* xjjroot::drawaxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, 
                          Double_t wmin, Double_t wmax, 
                          Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=1*/,
                          Option_t *chopt/*=""*/, Int_t ndiv/*=510*/, Double_t gridlength/*=0*/)
{
  TGaxis* g = new TGaxis(xmin, ymin, xmax, ymax,
                         wmin, wmax, ndiv, chopt, gridlength);
  g->SetLabelColor(lcolor);
  g->SetTitleColor(lcolor);
  g->SetLineColor(lcolor);
  g->SetLineStyle(lstyle);
  g->SetLineWidth(lwidth);
  g->Draw();
  return g;
}

/* ----- */

void xjjroot::setbranchaddress(TTree* nt, const char* bname, void* addr)
{
  nt->SetBranchStatus(bname, 1);
  nt->SetBranchAddress(bname, addr);
}

template <class T>
T* xjjroot::copyobject(const T* obj, TString objname)
{
  T* newobj = new T(*obj);
  newobj->SetName(objname);
  return newobj;
}

void xjjroot::dividebinwid(TH1* h)
{
  for(int i=0;i<h->GetNbinsX();i++)
    {
      Float_t val = h->GetBinContent(i+1)/h->GetBinWidth(i+1);
      Float_t valErr = h->GetBinError(i+1)/h->GetBinWidth(i+1);
      h->SetBinContent(i+1,val);
      h->SetBinError(i+1,valErr);
    }
}

TH1* xjjroot::histMinusCorr(TH1* ha, TH1* hb, std::string name)
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

TGraphErrors* xjjroot::shifthistcenter(TH1* hh, std::string name, int option)
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

TGraphAsymmErrors* xjjroot::shifthistcenter(TEfficiency* geff, std::string name, int option)
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

void xjjroot::mkdir(std::string outputfile)
{
  if(outputfile.find("/")==std::string::npos) return;
  std::string dir("");
  size_t lastpos = 0;
  size_t pos = outputfile.find("/", 0);
  while(pos != std::string::npos)
    {
      std::string thistoken = outputfile.substr(lastpos, pos-lastpos);
      dir += (thistoken + "/");
      lastpos = pos+1;
      pos = outputfile.find("/", pos+1);
    }
  gSystem->Exec(Form("mkdir -p %s", dir.c_str()));
}

namespace xjjroot
{
  int dummy = (TColor::SetColorThreshold(0), 0);
  std::map<std::string, int> mycolor_middle = {
    std::pair<std::string, int>("greenblue", TColor::GetColor("#6CA892")),
    std::pair<std::string, int>("orange", TColor::GetColor("#C67D4B")),
    std::pair<std::string, int>("red", TColor::GetColor("#BA6E6E")),
    std::pair<std::string, int>("azure", TColor::GetColor("#4B6D97")),
    std::pair<std::string, int>("magenta", TColor::GetColor("#AA7799")),
    std::pair<std::string, int>("green", TColor::GetColor("#839169")),
    std::pair<std::string, int>("cyan", TColor::GetColor("#44929b")),
    std::pair<std::string, int>("yellow", TColor::GetColor("#EAAD31")),
    std::pair<std::string, int>("blue", TColor::GetColor("#4C599C")),
    std::pair<std::string, int>("pink", TColor::GetColor("#C07A97")),
    std::pair<std::string, int>("violet", TColor::GetColor("#8473B3")),
  };
  std::map<std::string, int> mycolor_light = {
    std::pair<std::string, int>("greenblue", TColor::GetColor("#A7C5A5")),
    std::pair<std::string, int>("orange", TColor::GetColor("#DFB89D")),
    std::pair<std::string, int>("red", TColor::GetColor("#D7ABAB")),
    std::pair<std::string, int>("azure", TColor::GetColor("#96AECB")),
    std::pair<std::string, int>("magenta", TColor::GetColor("#CCAABB")),
    std::pair<std::string, int>("green", TColor::GetColor("#95A273")),
    std::pair<std::string, int>("cyan", TColor::GetColor("#8EBDC3")),
    std::pair<std::string, int>("yellow", TColor::GetColor("#F3D391")),
    std::pair<std::string, int>("blue", TColor::GetColor("#989FC6")),
    std::pair<std::string, int>("pink", TColor::GetColor("#DDBFC6")),
    std::pair<std::string, int>("violet", TColor::GetColor("#C4BFD0")),
  };
  std::map<std::string, int> mycolor_dark = {
    std::pair<std::string, int>("greenblue", TColor::GetColor("#406457")),
    std::pair<std::string, int>("orange", TColor::GetColor("#8A5734")),
    std::pair<std::string, int>("red", TColor::GetColor("#863F3F")),
    std::pair<std::string, int>("azure", TColor::GetColor("#324864")),
    std::pair<std::string, int>("magenta", TColor::GetColor("#754966")),
    std::pair<std::string, int>("green", TColor::GetColor("#6D7850")),
    std::pair<std::string, int>("cyan", TColor::GetColor("#2D6066")),
    std::pair<std::string, int>("yellow", TColor::GetColor("#BB8413")),
    std::pair<std::string, int>("blue", TColor::GetColor("#2D365E")),
    std::pair<std::string, int>("pink", TColor::GetColor("#926678")),
    std::pair<std::string, int>("violet", TColor::GetColor("#5E4D8D")),
  };
}

#endif
