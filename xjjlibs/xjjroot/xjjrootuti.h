#ifndef _XJJROOT_UTI_H_
#define _XJJROOT_UTI_H_

/* xjjrootuti.h */

#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TArrow.h>
#include <TStyle.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TGaxis.h>
#include <TF1.h>
#include <TMath.h>
#include <TEfficiency.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TSystem.h>
#include <TFile.h>
#include <TEntryList.h>
#include <TTree.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TKey.h>
#include <TROOT.h>

#include <vector>
#include <iostream>
#include <iomanip>

#include "xjjcuti.h"

MAKE_HAS_METHOD(GetEntries);
MAKE_HAS_METHOD(numEntries);
MAKE_HAS_METHOD(GetN);
MAKE_HAS_METHOD(SetStats);

namespace xjjroot
{
  bool silence__ = false; void silence(bool s = true) { silence__ = s; }
  struct thgrstyle {
    Color_t mcolor=-1; Style_t mstyle=-1; Size_t msize=-1;
    Color_t lcolor=-1; Style_t lstyle=-1; Width_t lwidth=-1;
    Color_t fcolor=-1; Float_t falpha=-1; Style_t fstyle=-1;
    Float_t lalpha=-1; Float_t malpha=-1;
  };

  enum Gpreset { Standard, Colz };
  const float margin_pad_left = 0.18;
  const float margin_pad_right = 0.043;
  const float margin_pad_bottom = 0.145;
  const float margin_pad_top = 0.1;

  const std::vector<Color_t> colorlist_light  = { kGreen-8, kRed-9, kAzure-9, kOrange-4, kMagenta-8, kCyan-8, kYellow-6, kBlue-8, kPink+1, kViolet-9 };
  const std::vector<Color_t> colorlist_middle = { kGreen+2, kRed-3, kAzure-3, kOrange-3, kMagenta-5, kCyan-2, kYellow+2, kBlue-5, kPink+2, kViolet+7 };
  const std::vector<Color_t> colorlist_dark   = { kGreen+3, kRed+2, kAzure-6, kOrange+5, kMagenta-1, kCyan+3, kYellow+3, kBlue-1, kPink+3, kViolet+4 };
  // colorlist_bw
  // mycolor_satmiddle[cc], mycolor_light[cc], mycolor_middle[cc], mycolor_dark[cc]
  std::vector<std::string> cc = { "red", "azure", "green", "magenta", "orange", "olive", "pink", "cyan", "yellow", "blue", "violet" };
  Color_t color_alpha(Color_t color, double alpha);
  Color_t color_alpha_black(Color_t color, double alpha);
  Color_t color_blend(const std::vector<Color_t> colors, const std::vector<float> fracs);
  
  std::vector<Style_t> markerlist_solid = {21, 20, 34, 47, 33, 43, 22, 23};
  std::vector<Style_t> markerlist_open = {24, 25, 26, 27, 28, 30, 32, 42, 46, 44};

  namespace CMS {
    const char* internal = "#scale[1.2]{#bf{CMS}}#scale[0.4]{ }#scale[1.04]{#it{Internal}}";
    const char* simulation = "#scale[1.2]{#bf{CMS}}#scale[0.4]{ }#scale[1.04]{#it{Simulation}}";
    const char* preliminary = "#scale[1.2]{#bf{CMS}}#scale[0.4]{ }#scale[1.04]{#it{Preliminary}}";
    const char* cms = "#scale[1.3]{#bf{CMS}}";
    std::string snn = "#sqrt{s_{NN}}";
    std::string Dz = "D#scale[0.6]{#lower[-0.7]{0}}",
      Dzbar = "#bar{D}#scale[0.6]{#lower[-0.7]{0}}",
      DzDzbar = CMS::Dz + " (" + CMS::Dzbar + ")",
      DznDzbar = CMS::Dz + " +#scale[0.5]{ }" + CMS::Dzbar,
      DzDzbar2 = "#frac{" + DznDzbar + "}{2}"; // D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}"
  }
  
  void setgstyle(Int_t padtick=0, Width_t lwidth=2, Gpreset opt=Standard);
  void setcstyle(TCanvas* c, Int_t padtick=0, Gpreset opt=Standard);
  void adjust_margin(float tt=1, float rr=1, float bb=1, float ll=1);
  double scale_pad() { return std::sqrt(std::min(gPad->GetWNDC(), gPad->GetHNDC())); }
  float get_pad_center(char d = 'X'); // 'X' or 'Y'
  template <class T> void sethempty(T* hempty, Float_t xoffset=0, Float_t yoffset=0, Float_t xsize=1, Float_t ysize=1);
  template <class T> void setthgr(T* hempty, Float_t xoffset=0, Float_t yoffset=0);
  template <class T> void setthgrstyle(T* h, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1,
                                       Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1,
                                       Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1,
                                       Float_t lalpha=-1, Float_t malpha=-1);
  template <class T> void setthgrstyle(T* h, const thgrstyle& t);
  template <class T> void setmarkerstyle(T* h, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1, Float_t malpha=-1);
  template <class T> void setlinestyle(T* h, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1, Float_t lalpha=-1);
  template <class T> void settfstyle(T* h, Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1,
                                     Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1);
  void drawCMSleft(TString content=CMS::internal, Float_t xpos=0, Float_t ypos=0, Float_t tsize=0.04);
  void drawCMSright(TString content="PbPb (5.36 TeV)", Float_t xpos=0, Float_t ypos=0, Float_t tsize=0.04);
  void drawCMS(TString contentleft=CMS::internal, TString contentright="PbPb (5.36 TeV)", Float_t tsizef=1);
  void settex(TLatex* tex, Float_t tsize=0.04, Short_t align=12, Style_t font=42, Color_t color=kBlack, Float_t talpha=1, Float_t tangle=0);
  TLatex* drawtex(Double_t x, Double_t y, const char *text,
                  Float_t tsize=0.04, Short_t align=12, Style_t font=42, Color_t color=kBlack, Float_t talpha=1, Float_t tangle=0,
                  bool draw = true);
  TLatex* drawtexnum(Double_t x, Double_t y, const char *text,
                     Float_t tsize=0.04, Short_t align=12, Style_t font=42, Color_t color=kBlack, Float_t talpha=1, Float_t tangle=0,
                     bool draw = true);
  std::vector<TLatex*> drawtexgroup(Double_t x, Double_t y, std::vector<std::string> text, Float_t tsize=0.04, Short_t align=12, Style_t font=42, float lspacescale = 1.15,
                                    int ncol=1, Double_t colwid=0.2,
                                    std::vector<Color_t> color = {}); // colorlist_middle
  void drawtexgroup_wrap(Double_t x, Double_t y, std::vector<std::string> text, Float_t tsize=0.04, Short_t align=12, Style_t font=42, float lspacescale = 1.15, size_t nchar = 50);
  void movetex_n_draw(TLatex* tex, float x = -1, float y = -1, Short_t align = 0);
  void movetexgroup_n_draw(std::vector<TLatex*>& tex, float x = -1, float y = -1);
  void setleg(TLegend* leg, Float_t tsize=0.04);
  void setleg_n_draw(TLegend* leg, Float_t tsize=0.04);
  void moveleg_n_draw(TLegend* leg, float x1=-1, float y2=-1);
  TLegend* cloneleg_n_draw(const TLegend* leg, float x1=-1, float y2=-1);
  void autoleg_n_draw(TLegend* leg, float x1=-1, float y2=-1, float tsize=-1, float fline=1.1);
  void rewidthleg(TLegend* leg, int ncol);
  void addentrybystyle(TLegend* leg, std::string text, std::string opt,
                       Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1,
                       Color_t lcolor=-1, Style_t lstyle=-1, Width_t lwidth=-1,
                       Color_t fcolor=-1, Float_t falpha=-1, Style_t fstyle=-1,
                       Float_t lalpha=-1, Float_t malpha=-1);
  void addentrybystyle(TLegend* leg, std::string text, std::string opt, const thgrstyle& style);
  TLine* drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                  Color_t lcolor=kBlack, Style_t lstyle=1, Width_t lwidth=2, Float_t lalpha=1);
  TArrow* drawarrow(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                    Color_t lcolor=kBlack, Style_t lstyle=1, Width_t lwidth=2, Float_t lalpha=1,
                    Option_t* option = "|>", Float_t arrowsize=0.02);
  template<class T> TLine* drawline_vertical(Double_t x, T* hempty,
                                             Color_t lcolor=kBlack, Style_t lstyle=6, Width_t lwidth=1, Float_t lalpha=1);
  template<class T> TLine* drawline_horizon(Double_t y, T* hempty,
                                            Color_t lcolor=kBlack, Style_t lstyle=6, Width_t lwidth=1, Float_t lalpha=1);
  TBox* drawbox(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                Color_t fcolor=kGray, Float_t falpha=0.4, Style_t fstyle=1001,
                Color_t lcolor=0, Style_t lstyle=1, Width_t lwidth=0);
  TGaxis* drawaxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, 
                   Double_t wmin, Double_t wmax, 
                   Color_t lcolor=kBlack, Style_t lstyle=1, Width_t lwidth=1,
                   Option_t *chopt="", 
                   Float_t labelsize=gStyle->GetLabelSize("Y"), Style_t labelfont=gStyle->GetLabelFont("Y"),
                   Int_t ndiv=510, Double_t gridlength=0);
  void setaxisstyle(TAxis* axis, TGaxis* axis_mom);
  TGraph* drawpoint(Double_t x, Double_t y, Color_t mcolor=-1, Style_t mstyle=-1, Size_t msize=-1, std::string gopt="p same");

  template<class T> void print_obj(T* hh, int w=0);
  template<typename T> void print_tab(const std::vector<std::vector<T>>& vstrs, int8_t opt = 3);
  template<typename T1, typename T2> void print_tab(const std::map<T1, T2>& vstrs, int8_t opt = 3);
  template<typename T> void print_tab(const std::map<std::string, std::vector<T>>& vstrs, int8_t opt = 3);
  template<typename T> void print_vec_v(const std::vector<T>& vstrs, int8_t opt = 1);
  template<typename T> void print_vec_h(const std::vector<T>& vstrs, int8_t opt = 1);
  
  template<class T> void writehist(T* hh, int w=0) { if(!silence__) { print_obj(hh, w); } hh->Write(); }

  void print_gr(TGraph* gr);
  void print_th(TH1* h);
  
  void mkdir(std::string outputfile);
  void saveas(TCanvas* c, std::string outputfile, std::string opt="WT");
  TFile* newfile(std::string outputfile);
  void closefile(TFile*);
  void drawcomment(std::string comment, std::string opt="lb") {
    xjjroot::drawtex((opt.front()=='r'?1:0), (opt.back()=='t'?1:0), comment.c_str(), 0.024,
                     ((opt.front()=='r')*2+1)*10+((opt.back()=='t')*2+1), 42, kGray); }
  void writetex(std::string tr, std::string br, std::string str);
  std::string readtex(TTree* t, std::string br);

  std::vector<TPad*> twopads(TPad* c, TH1* hempty, TH1* hempty_ratio, float yupdiv = 1.9/3);
  // std::vector<TPad*> divide_canvas(TCanvas* c, int nx, int ny);
  std::vector<std::pair<TPad*, unsigned int>> divide_canvas(TCanvas* c, int nx, int ny);
}

/* ---------- */

void xjjroot::setgstyle(Int_t padtick/*=0*/, Width_t lwidth/*=2*/, Gpreset opt/*=Standard*/) {
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(4); // need to pair with Draw("e1")
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right * (opt==Colz?4:1));
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left * (opt==Colz?0.7:1));
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom);
  gStyle->SetTitleX(.0f);
  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(0);
  gStyle->SetLineWidth(1);
  gStyle->SetFrameLineWidth(1);
  if (padtick==1 || padtick==3) {
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
  }
  if (padtick==2 || padtick==3) { gStyle->SetLineWidth(lwidth); gStyle->SetFrameLineWidth(lwidth);}
}

void xjjroot::setcstyle(TCanvas* c, Int_t padtick/*=0*/, Gpreset opt/*=Standard*/) {
  c->SetRightMargin(xjjroot::margin_pad_right * (opt==Colz?4:1));
  c->SetLeftMargin(xjjroot::margin_pad_left * (opt==Colz?0.7:1));
  c->SetTopMargin(xjjroot::margin_pad_top);
  c->SetBottomMargin(xjjroot::margin_pad_bottom);
  if (padtick==1 || padtick==3) {
    c->SetTickx(1);
    c->SetTicky(1);
  }
}

void xjjroot::adjust_margin(float tt, float rr, float bb, float ll) {
  gStyle->SetPadRightMargin(xjjroot::margin_pad_right*rr);
  gStyle->SetPadLeftMargin(xjjroot::margin_pad_left*ll);
  gStyle->SetPadTopMargin(xjjroot::margin_pad_top*tt);
  gStyle->SetPadBottomMargin(xjjroot::margin_pad_bottom*bb);
}

float xjjroot::get_pad_center(char d) {
  float result = 0.5;
  if (std::tolower(d) == 'x') {
    result = gStyle->GetPadLeftMargin() + (1 -  gStyle->GetPadLeftMargin() -  gStyle->GetPadRightMargin()) / 2.;
  } else if (std::tolower(d) == 'y') {
    result = gStyle->GetPadBottomMargin() + (1 -  gStyle->GetPadBottomMargin() -  gStyle->GetPadTopMargin()) / 2.;
  }
  return result;
}

template <class T>
void xjjroot::sethempty(T* hempty, Float_t xoffset/*=0*/, Float_t yoffset/*=0*/, Float_t xsize/*=1*/, Float_t ysize/*=1*/) {
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.10+xoffset);
  hempty->GetYaxis()->SetTitleOffset(1.30+yoffset);
  hempty->GetXaxis()->SetTitleSize(0.05 * xsize);
  hempty->GetYaxis()->SetTitleSize(0.05 * ysize);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.045 * xsize);
  hempty->GetYaxis()->SetLabelSize(0.045 * ysize);
  if constexpr (has_method_SetStats<T>::value) {
    hempty->SetStats(0);
  }
}

template <class T>
void xjjroot::setthgr(T* hempty, Float_t xoffset/*=0*/, Float_t yoffset/*=0*/) {
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
void xjjroot::setthgrstyle(T* h, Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/,
                           Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/,
                           Color_t fcolor/*=-1*/, Float_t falpha/*=-1*/, Style_t fstyle/*=-1*/,
                           Float_t lalpha/*=-1*/, Float_t malpha/*=-1*/) {
  if(mcolor>=0) h->SetMarkerColor(mcolor);
  if(mstyle>=0) h->SetMarkerStyle(mstyle);
  if(msize>=0)  h->SetMarkerSize(msize);
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
  if(fcolor>=0) h->SetFillColor(fcolor);
  if(falpha>=0) h->SetFillColorAlpha(fcolor, falpha);
  if(fstyle>=0) h->SetFillStyle(fstyle);
  if(lalpha>=0) h->SetLineColorAlpha(lcolor, lalpha);
  if(malpha>=0) h->SetMarkerColorAlpha(mcolor, malpha);
}

template <class T>
void xjjroot::setthgrstyle(T* h, const thgrstyle& t) {
  setthgrstyle(h, t.mcolor, t.mstyle, t.msize,
               t.lcolor, t.lstyle, t.lwidth,
               t.fcolor, t.falpha, t.fstyle,
               t.lalpha, t.malpha);
}

template <class T>
void xjjroot::setmarkerstyle(T* h, Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/, Float_t malpha/*=-1*/) {
  if(mcolor>=0) h->SetMarkerColor(mcolor);
  if(mstyle>=0) h->SetMarkerStyle(mstyle);
  if(msize>=0)  h->SetMarkerSize(msize);
  if(malpha>=0) h->SetMarkerColorAlpha(mcolor, malpha);
}

template <class T>
void xjjroot::setlinestyle(T* h, Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/, Float_t lalpha/*=-1*/) {
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lalpha>=0) h->SetLineColorAlpha(lcolor, lalpha);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
}

template <class T>
void xjjroot::settfstyle(T* h, Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/,
                         Color_t fcolor/*=-1*/, Float_t falpha/*=-1*/, Style_t fstyle/*=-1*/) {
  h->SetNpx(1000);
  if(lcolor>=0) h->SetLineColor(lcolor);
  if(lstyle>=0) h->SetLineStyle(lstyle);
  if(lwidth>=0) h->SetLineWidth(lwidth);
  if(fcolor>=0) h->SetFillColor(fcolor);
  if(falpha>=0) h->SetFillColorAlpha(fcolor, falpha);
  if(fstyle>=0) h->SetFillStyle(fstyle);
}

void xjjroot::drawCMS(TString contentleft/*="#scale[1.25]{#bf{CMS}} #it{Internal}"*/,
                      TString contentright/*="PbPb #sqrt{s_{NN}} = 5.02 TeV"*/, Float_t tsizef/* = 1*/) {
  drawCMSleft(contentleft, 0, 0, 0.04*tsizef);
  drawCMSright(contentright, 0, 0, 0.04*tsizef);
}

void xjjroot::drawCMSleft(TString content/*="#scale[1.25]{#bf{CMS}} #it{Internal}"*/,
                          Float_t xpos/*=0*/, Float_t ypos/*=0*/, Float_t tsize/*=0.04*/) {
  auto* texCms = new TLatex(gStyle->GetPadLeftMargin()+xpos,(1-gStyle->GetPadTopMargin())+0.01+ypos, content.Data());
  texCms->SetNDC();
  texCms->SetTextAlign(11);
  texCms->SetTextSize(tsize);
  texCms->SetTextFont(42);
  texCms->Draw();
}

void xjjroot::drawCMSright(TString content/*="#sqrt{s_{NN}} = 5.02 TeV"*/,
                           Float_t xpos/*=0*/, Float_t ypos/*=0*/, Float_t tsize/*=0.04*/) {
  auto* texCol = new TLatex((1-gStyle->GetPadRightMargin())+xpos,(1-gStyle->GetPadTopMargin())+0.01+ypos, content.Data());
  texCol->SetNDC();
  texCol->SetTextAlign(31);
  texCol->SetTextSize(tsize);
  texCol->SetTextFont(42);
  texCol->Draw();
}

void xjjroot::settex(TLatex* tex, Float_t tsize/*=0.04*/, Short_t align/*=12*/,
                     Style_t font/*=42*/, Color_t color/*=kBlack*/, Float_t talpha/*=1*/, Float_t tangle/*=0*/) {
  tex->SetNDC();
  tex->SetTextFont(font);
  tex->SetTextAlign(align);
  tex->SetTextSize(tsize);
  tex->SetTextColor(color);
  tex->SetTextColorAlpha(color, talpha);
  tex->SetTextAngle(tangle);
}

TLatex* xjjroot::drawtex(Double_t x, Double_t y, const char* text,
                         Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/,
                         Color_t color/*=kBlack*/, Float_t talpha/*=1*/, Float_t tangle/*=0*/, 
                         bool draw/*=true*/) {
  auto* tex = new TLatex(x, y, text);
  xjjroot::settex(tex, tsize, align, font, color, talpha, tangle);
  if(draw) tex->Draw();
  return tex;
}

TLatex* xjjroot::drawtexnum(Double_t x, Double_t y, const char* text,
                            Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/,
                            Color_t color/*=kBlack*/, Float_t talpha/*=1*/, Float_t tangle/*=0*/,
                            bool draw/*=true*/) {
  auto* tex = new TLatex(x, y, text);
  xjjroot::settex(tex, tsize, align, font, color, talpha, tangle);
  tex->SetNDC(false);
  if(draw) tex->Draw();
  return tex;
}

std::vector<TLatex*> xjjroot::drawtexgroup(Double_t x, Double_t y, std::vector<std::string> text, Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/,
                                           float lspacescale/*=1.15*/,
                                           int ncol/*=1*/, Double_t colwid/*=0.2*/,
                                           std::vector<Color_t> color/*=std::vector<Color_t>(10, kBlack)*/) {
  double lspace = tsize * lspacescale;
  auto nrow = std::ceil(text.size()/ncol);
  
  Short_t horizontal = 1;
  if (align == 21 || align == 22 || align == 23) horizontal = 2;
  if (align == 31 || align == 32 || align == 33) horizontal = 3;
  Short_t vertical = 3;
  if (align == 11 || align == 21 || align == 31) vertical = 1;
  if (align == 12 || align == 22 || align == 32) vertical = 2;
  float y1 = y; // vertical = 3, top
  if (vertical == 1) y1 = y + lspace * (nrow-1); // vertical = 1, bottom
  if (vertical == 2) y1 = y + lspace*nrow/2. - tsize/2.; // vertical = 2, middle

  std::vector<TLatex*> vtex;
  for (unsigned t = 0; t < text.size(); t++) {
    auto icol = t%ncol, irow = t/ncol;
    double xx = x + colwid * icol; // horizontal = 1, left
    if (horizontal == 2) xx = x + colwid * (-(ncol-1)/2. + icol); // horizontal = 2, middle
    if (horizontal == 3) xx = x - colwid * icol; // horizontal = 3, right
    double yy = y1 - lspace*irow;
    constexpr unsigned fallback = kBlack;
    Color_t cc = t < color.size() ? color[t] : fallback;
    vtex.push_back(drawtex(xx, yy, text[t].c_str(), tsize, align, font, cc));
  }
  return vtex;
}

void xjjroot::drawtexgroup_wrap(Double_t x, Double_t y, std::vector<std::string> text, Float_t tsize/*=0.04*/, Short_t align/*=12*/, Style_t font/*=42*/,
                                float lspacescale/*=1.15*/, size_t nchar/*=50*/) {
  text = xjjc::str_wrap(text, nchar);
  drawtexgroup(x, y, text, tsize, align, font, lspacescale);
}

void xjjroot::movetex_n_draw(TLatex* tex, float x1/*=-1*/, float y2/*=-1*/, Short_t align/*=0*/) {
  if (align > 0)
    tex->SetTextAlign(align);
  if (x1 >= 0)
    tex->SetX(x1);
  if (y2 >= 0)
    tex->SetY(y2);
  tex->Draw();
}

// #include <algorithm>
#include <limits>

void xjjroot::movetexgroup_n_draw(std::vector<TLatex*>& gtex, float x, float y) {
  if (gtex.empty()) return;
  auto* first = gtex.front();
  if (!first) return;

  const Short_t align = first->GetTextAlign();
  const Short_t horizontal = align / 10;
  const Short_t vertical   = align % 10;

  double xmin =  std::numeric_limits<double>::max();
  double xmax = -std::numeric_limits<double>::max();
  double ymin =  std::numeric_limits<double>::max();
  double ymax = -std::numeric_limits<double>::max();

  for (const auto* tex : gtex) {
    if (!tex)
      continue;
    xmin = std::min(xmin, tex->GetX());
    xmax = std::max(xmax, tex->GetX());
    ymin = std::min(ymin, tex->GetY());
    ymax = std::max(ymax, tex->GetY());
  }

  // Determine the current group anchor from the text alignment.
  double oldx = xmin; // left aligned
  if (horizontal == 2)
    oldx = 0.5 * (xmin + xmax); // centered
  else if (horizontal == 3)
    oldx = xmax; // right aligned

  double oldy = ymin; // bottom aligned
  if (vertical == 2)
    oldy = 0.5 * (ymin + ymax); // vertically centered
  else if (vertical == 3)
    oldy = ymax; // top aligned

  const double dx = x - oldx;
  const double dy = y - oldy;

  for (auto* tex : gtex) {
    if (!tex) continue;
    if (x >= 0)
      tex->SetX(tex->GetX() + dx);
    if (y >= 0)
      tex->SetY(tex->GetY() + dy);
    tex->Draw();
  }
}

void xjjroot::setleg(TLegend* leg, Float_t tsize/*=0.04*/) {
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(tsize);
}

void xjjroot::setleg_n_draw(TLegend* leg, Float_t tsize/*=0.04*/) {
  xjjroot::setleg(leg, tsize);
  leg->Draw();
}

void xjjroot::moveleg_n_draw(TLegend* leg, float x1/*=-1*/, float y2/*=-1*/) {
  if (x1 < 0) x1 = leg->GetX1NDC();
  if (y2 < 0) y2 = leg->GetY2NDC();
  auto delta_x = leg->GetX2NDC() - leg->GetX1NDC();
  float x2 = x1 + delta_x;
  auto delta_y = leg->GetY2NDC() - leg->GetY1NDC();
  float y1 = y2 - delta_y;
  leg->SetX1NDC(x1);
  leg->SetY1NDC(y1);
  leg->SetX2NDC(x2);
  leg->SetY2NDC(y2);
  leg->Draw();
}

TLegend* xjjroot::cloneleg_n_draw(const TLegend* leg, float x1/*=-1*/, float y2/*=-1*/) {
  auto* leg2 = static_cast<TLegend*>(leg->Clone());
  moveleg_n_draw(leg2, x1, y2);
  return leg2;
}

void xjjroot::autoleg_n_draw(TLegend* leg, float x1/*=-1*/, float y2/*=-1*/, float tsize/*=-1*/, float fline/*=1.1*/) {
  if (x1 < 0) x1 = leg->GetX1NDC();
  if (y2 < 0) y2 = leg->GetY2NDC();
  if (tsize > 0) leg->SetTextSize(tsize);
  auto ncol = leg->GetNColumns();
  auto nent = leg->GetListOfPrimitives()->GetSize();
  int nrow = std::ceil(nent*1. / ncol);
  float delta_y = leg->GetTextSize() * fline * nrow;
  leg->SetY2NDC(y2);
  leg->SetY1NDC(y2 - delta_y);
  moveleg_n_draw(leg, x1, y2);
}

void xjjroot::rewidthleg(TLegend* leg, int ncol) {
  auto delta_x = leg->GetX2NDC() - leg->GetX1NDC();
  auto ncol_original = leg->GetNColumns();
  delta_x = delta_x / ncol_original * ncol;
  leg->SetNColumns(ncol);
  leg->SetX2NDC(leg->GetX1NDC() + delta_x);
}

void xjjroot::addentrybystyle(TLegend* leg, std::string text, std::string opt,
                              Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/,
                              Color_t lcolor/*=-1*/, Style_t lstyle/*=-1*/, Width_t lwidth/*=-1*/,
                              Color_t fcolor/*=-1*/, Float_t falpha/*=-1*/, Style_t fstyle/*=-1*/,
                              Float_t lalpha/*=-1*/, Float_t malpha/*=-1*/) {
  auto h = new TH1F(Form("dummyh_%s", xjjc::unique_str().c_str()), "", 1, 0, 1);
  setthgrstyle(h, mcolor, mstyle, msize,
               lcolor, lstyle, lwidth,
               fcolor, falpha, fstyle,
               lalpha, malpha);
  leg->AddEntry(h, text.c_str(), opt.c_str());
}

void xjjroot::addentrybystyle(TLegend* leg, std::string text, std::string opt, const thgrstyle& style) {
  auto h = new TH1F(Form("dummyh_%s", xjjc::unique_str().c_str()), "", 1, 0, 1);
  setthgrstyle(h, style);
  leg->AddEntry(h, text.c_str(), opt.c_str());
}

TLine* xjjroot::drawline(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                         Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=2*/, Float_t lalpha/*=1*/) {
  auto* l = new TLine(x1, y1, x2, y2);
  xjjroot::setlinestyle(l, lcolor, lstyle, lwidth, lalpha);
  l->Draw();
  return l;
}

TArrow* xjjroot::drawarrow(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                           Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=2*/, Float_t lalpha/*=1*/,
                           Option_t* option/*="|>"*/, Float_t arrowsize/*=0.02*/) {
  auto* l = new TArrow(x1, y1, x2, y2, arrowsize, option);
  xjjroot::setlinestyle(l, lcolor, lstyle, lwidth, lalpha);
  l->SetFillColor(lcolor);
  l->Draw();
  return l;
}

template<class T>
TLine* xjjroot::drawline_vertical(Double_t x, T* hempty,
                                  Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=2*/, Float_t lalpha/*=1*/) {
  auto line = drawline(x, hempty->GetYaxis()->GetXmin(), x, hempty->GetYaxis()->GetXmax(),
                       lcolor, lstyle, lwidth, lalpha);
  return line;
}

template<class T>
TLine* xjjroot::drawline_horizon(Double_t y, T* hempty,
                                 Color_t lcolor/*=kBlack*/, Style_t lstyle/*=1*/, Width_t lwidth/*=2*/, Float_t lalpha/*=1*/) {
  auto line = drawline(hempty->GetXaxis()->GetXmin(), y, hempty->GetXaxis()->GetXmax(), y,
                       lcolor, lstyle, lwidth, lalpha);
  return line;
}

TBox* xjjroot::drawbox(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
                       Color_t fcolor/*=kGray*/, Float_t falpha/*=0.4*/, Style_t fstyle/*=1001*/,
                       Color_t lcolor/*=0*/, Style_t lstyle/*=1*/, Width_t lwidth/*=0*/) {
  auto* b = new TBox(x1, y1, x2, y2);
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
                          Option_t *chopt/*=""*/, 
                          Float_t labelsize/*=gStyle->GetLabelSize("Y")*/, Style_t labelfont/*=gStyle->GetLabelFont("Y")*/, 
                          Int_t ndiv/*=510*/, Double_t gridlength/*=0*/) {
  auto* g = new TGaxis(xmin, ymin, xmax, ymax,
                       wmin, wmax, ndiv, chopt, gridlength);
  g->SetLabelColor(lcolor);
  g->SetLabelSize(labelsize);
  g->SetLabelFont(labelfont);
  g->SetTitleColor(lcolor);
  g->SetLineColor(lcolor);
  g->SetLineStyle(lstyle);
  g->SetLineWidth(lwidth);
  g->CenterTitle();
  g->Draw();
  return g;
}

void xjjroot::setaxisstyle(TAxis* axis, TGaxis* axis_mom) {
  axis->SetLabelFont(axis_mom->GetLabelFont());
  axis->SetLabelSize(axis_mom->GetLabelSize());
  axis->SetLabelOffset(axis_mom->GetLabelOffset());
  // axis->SetTitleFont(axis_mom->GetTitleFont()); // why no gettitlefont?
  axis->SetTitleSize(axis_mom->GetTitleSize());
  axis->SetTitleOffset(axis_mom->GetTitleOffset());
}


TGraph* xjjroot::drawpoint(Double_t x, Double_t y,
                           Color_t mcolor/*=-1*/, Style_t mstyle/*=-1*/, Size_t msize/*=-1*/,
                           std::string gopt/*="p same"*/) {
  double vx[] = {x}, vy[] = {y};
  auto* gr = new TGraph(1, vx, vy);
  setthgrstyle(gr, mcolor, mstyle, msize);
  if (!xjjc::str_contains(gopt, "off"))
    gr->Draw(gopt.c_str());
  return gr;
}

/* ----- */

template<class T> 
void xjjroot::print_obj(T* hh, int w) {
  if (!hh) { std::cout<<"error: bad object."<<std::endl; return; }
  std::cout<<std::left
           <<"\e[2m"<<Form("(%s)", hh->ClassName())<<"\e[0m "
           <<std::setw(w)<<"\e[0m"<<hh->GetName()<<"\e[0m";
  if constexpr (has_method_GetEntries<T>::value) {
    std::cout<<" \e[36;1m("<<hh->GetEntries()<<")\e[0m";
  } else if constexpr (has_method_GetN<T>::value) {
    std::cout<<" \e[36;1m("<<hh->GetN()<<")\e[0m";
  } else if constexpr (has_method_numEntries<T>::value) {
    std::cout<<" \e[36;1m("<<hh->numEntries()<<")\e[0m";
  }
  std::cout<<std::endl;
}

template<typename T>
void xjjroot::print_tab(const std::vector<std::vector<T>>& vstrs, int8_t opt) {
  std::vector<std::vector<std::string>> rs;
  for (const auto& h : vstrs) {
    std::vector<std::string> rss;
    for (const auto& hh : h)
      rss.push_back(hh->GetName());
    rs.push_back(rss);
  }
  xjjc::print_tab(rs, opt);
}

template<typename T1, typename T2>
void xjjroot::print_tab(const std::map<T1, T2>& vstrs, int8_t opt) {
  std::map<T1, std::string> rs;
  for (const auto& [key, h] : vstrs) {
    rs[key] = h->GetName(); //
  }
  xjjc::print_tab(rs, opt);
}

template<typename T>
void xjjroot::print_tab(const std::map<std::string, std::vector<T>>& vstrs, int8_t opt) {
  std::vector<std::vector<std::string>> rs;
  for (const auto& [key, h] : vstrs) {
    std::vector<std::string> rss;
    rss.push_back(key);
    for (const auto& hh : h)
      rss.push_back(hh->GetName());
    rs.push_back(rss);
  }
  xjjc::print_tab(rs, opt);
}

template<typename T>
void xjjroot::print_vec_v(const std::vector<T>& vstrs, int8_t opt) {
  std::vector<std::string> rs;
  for (const auto& h : vstrs) rs.push_back(h->GetName());
  xjjc::print_vec_v(rs, opt);
}

template<typename T>
void xjjroot::print_vec_h(const std::vector<T>& vstrs, int8_t opt) {
  std::vector<std::string> rs;
  for (const auto& h : vstrs) rs.push_back(h->GetName());
  xjjc::print_vec_h(rs, opt);
}

void xjjroot::print_gr(TGraph *gr) {
  std::vector<std::vector<std::string>> out;
  if (!gr) return;

  const auto n = gr->GetN();
  out.reserve(n+1);
  const auto* gre  = dynamic_cast<const TGraphErrors*>(gr);
  const auto* grae = dynamic_cast<const TGraphAsymmErrors*>(gr);

  if (grae) {
    out.push_back({ "X", "Y", "ErrorXlow", "ErrorXhigh", "ErrorYlow", "ErrorYhigh" });
  } else if (gre) {
    out.push_back({ "X", "Y", "ErrorX", "ErrorY" });
  } else {
    out.push_back({ "X", "Y" });
  }
    
  for (int i = 0; i < n; ++i) {
    double x, y;
    gr->GetPoint(i, x, y);

    if (grae) {
      out.push_back({
          xjjc::to_string(x),
          xjjc::to_string(y),
          xjjc::to_string(grae->GetErrorXlow(i)),
          xjjc::to_string(grae->GetErrorXhigh(i)),
          xjjc::to_string(grae->GetErrorYlow(i)),
          xjjc::to_string(grae->GetErrorYhigh(i))
        });
    } else if (gre) {
      out.push_back({
          xjjc::to_string(x),
          xjjc::to_string(y),
          xjjc::to_string(gre->GetErrorX(i)),
          xjjc::to_string(gre->GetErrorY(i))
        });
    } else {
      out.push_back({
          xjjc::to_string(x),
          xjjc::to_string(y)
        });
    }
  }

  print_obj(gr);
  xjjc::print_tab(out, 0);
}

void xjjroot::print_th(TH1 *h) {
  std::vector<std::vector<std::string>> out;
  if (!h) return;

  const auto n = h->GetEntries();
  out.reserve(n+1);
  out.push_back({ "Center", "LowEdge", "HighEdge", "Content", "Error" });
  
  for (int i = 0; i < n; ++i) {
    out.push_back({
        xjjc::to_string(h->GetBinCenter(i+1)),
        xjjc::to_string(h->GetBinLowEdge(i+1)),
        xjjc::to_string(h->GetBinLowEdge(i+1) + h->GetBinWidth(i+1)),
        xjjc::to_string(h->GetBinContent(i+1)),
        xjjc::to_string(h->GetBinError(i+1))
      });
  }

  print_obj(h);
  xjjc::print_tab(out, 0);
}

void xjjroot::mkdir(std::string outputfile) {
  if (outputfile.find("/") == std::string::npos) return;
  std::string dir("");
  size_t lastpos = 0;
  size_t pos = outputfile.find("/", 0);
  while (pos != std::string::npos) {
    std::string thistoken = outputfile.substr(lastpos, pos-lastpos);
    dir += (thistoken + "/");
    lastpos = pos+1;
    pos = outputfile.find("/", pos+1);
  }
  gSystem->Exec(Form("mkdir -p %s", dir.c_str()));
}

void xjjroot::saveas(TCanvas* c, std::string outputfile, std::string opt) {
  if (opt.find("T") != std::string::npos) {
    std::time_t t = std::time(0);
    std::string datetime(100,0);
    datetime.resize(std::strftime(&datetime[0], datetime.size(),
                                  "%b %d %a %-H:%M:%S %Z %Y", std::localtime(&t)));
    drawcomment(datetime, "rb");
  }
  if (opt.find("W") != std::string::npos)
    drawcomment(outputfile);
  
  mkdir(outputfile);
  std::cout<<"\e[1m";
  c->SaveAs(outputfile.c_str());
  std::cout<<"\e[0m";
}

TFile* xjjroot::newfile(std::string outputfile) {
  mkdir(outputfile);
  auto* outf = new TFile(outputfile.c_str(), "recreate");
  outf->cd();
  __XJJLOG << ">> "<<outputfile<<std::endl;
  return outf;
}

void xjjroot::closefile(TFile* outf) {
  __XJJLOG << ">> "<<outf->GetName()<<std::endl;
  outf->Close();
}

void xjjroot::writetex(std::string tr, std::string br, std::string str) {
  std::string s(str);
  auto* t = new TTree(tr.c_str(), "info");
  t->Branch(br.c_str(), &s);
  t->Fill();
  t->Write();
}

std::string xjjroot::readtex(TTree* t, std::string br) {
  std::string *s = 0;
  t->SetBranchAddress(br.c_str(), &s);
  t->GetEntry(0);
  std::string ss(*s);
  return ss;
}

std::vector<TPad*> xjjroot::twopads(TPad *c, TH1 *hempty, TH1 *hempty_ratio, float yupdiv/*= 1.9/3*/) {
  float ydowndiv = 1-yupdiv;

  xjjroot::setgstyle(1);
  // gStyle->SetLineWidth(2);

  sethempty(hempty, 0, 0.2);
  // sethempty(hempty, 0, 0.2, 1./yupdiv, 1./yupdiv);
  sethempty(hempty_ratio, -0.5, -0);
  hempty->GetXaxis()->SetNdivisions(510);
  hempty_ratio->GetXaxis()->SetNdivisions(510);
  hempty_ratio->GetYaxis()->SetNdivisions(505);

  hempty->GetYaxis()->SetTitleSize(hempty->GetYaxis()->GetTitleSize() * (1./yupdiv) * 0.9);
  hempty->GetXaxis()->SetTitleSize(hempty->GetXaxis()->GetTitleSize() * (1./yupdiv) * 0.9);
  hempty->GetYaxis()->SetLabelSize(hempty->GetYaxis()->GetLabelSize() * (1./yupdiv) * 0.9);
  hempty->GetXaxis()->SetLabelSize(hempty->GetXaxis()->GetLabelSize() * (1./yupdiv) * 0.9);
  hempty->GetYaxis()->SetTitleOffset(hempty->GetYaxis()->GetTitleOffset() * yupdiv);
  hempty->GetXaxis()->SetTitleOffset(hempty->GetXaxis()->GetTitleOffset() * yupdiv);
  // hempty_ratio->GetYaxis()->SetLabelOffset(hempty->GetYaxis()->GetLabelOffset() * yupdiv * (1+1.8));

  hempty_ratio->GetYaxis()->SetTitleSize(hempty->GetYaxis()->GetTitleSize() * (yupdiv / ydowndiv));
  hempty_ratio->GetXaxis()->SetTitleSize(hempty->GetXaxis()->GetTitleSize() * (yupdiv / ydowndiv));
  hempty_ratio->GetYaxis()->SetLabelSize(hempty->GetYaxis()->GetLabelSize() * (yupdiv / ydowndiv));
  hempty_ratio->GetXaxis()->SetLabelSize(hempty->GetXaxis()->GetLabelSize() * (yupdiv / ydowndiv));
  hempty_ratio->GetYaxis()->SetTitleOffset(hempty->GetYaxis()->GetTitleOffset() / (yupdiv / ydowndiv));
  hempty_ratio->GetXaxis()->SetTitleOffset(hempty->GetXaxis()->GetTitleOffset() / (yupdiv / ydowndiv) * (1+1.4));
  hempty_ratio->GetYaxis()->SetLabelOffset(hempty->GetYaxis()->GetLabelOffset() / (yupdiv / ydowndiv) * (1+1.8));
  hempty_ratio->GetXaxis()->SetLabelOffset(hempty->GetXaxis()->GetLabelOffset() / (yupdiv / ydowndiv));
  hempty_ratio->GetXaxis()->SetTickLength(hempty->GetXaxis()->GetTickLength() * (yupdiv / ydowndiv) );

  c->cd();
  auto* p1 = new TPad("p1", "", 0, ydowndiv, 1, 1);
  p1->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, 0, xjjroot::margin_pad_top);
  // p1->SetLogy();
  p1->Draw("axis");
  p1->cd();
  hempty->Draw("axis");
    
  c->cd();
  auto* p2 = new TPad("p2", "", 0, 0, 1, ydowndiv);
  p2->SetMargin(xjjroot::margin_pad_left, xjjroot::margin_pad_right, xjjroot::margin_pad_bottom * (yupdiv / ydowndiv) * 1.2, 0);
  p2->Draw("axis");
  p2->cd();
  hempty_ratio->Draw("axis");

  c->cd();
  std::vector<TPad*> pads = { p1, p2 };
  return pads;
}

std::vector<std::pair<TPad*, unsigned int>> xjjroot::divide_canvas(TCanvas* c, int nx, int ny) {
  // auto pads = xjjc::array2d<TPad*>(nx, ny);
  std::vector<std::pair<TPad*, unsigned int>> pads;
  float m_top = xjjroot::margin_pad_top/nx, m_bottom = xjjroot::margin_pad_bottom/ny, m_left = xjjroot::margin_pad_left/nx, m_right = xjjroot::margin_pad_right/ny;
  float fwidth = (1-m_left-m_right)/nx, fheight = (1-m_bottom-m_top)/ny;
  for (int j=0; j<ny; j++) {
    for (int i=nx-1; i>=0; i--) {
      c->cd();
      float px1 = i*fwidth, // left
        px2 = m_left + (i+1)*fwidth + m_right, // right
        py1 = 1 - (m_top + (j+1)*fheight + m_bottom), // bottom
        py2 = 1 - j*fheight; // top
      auto* pij = new TPad(Form("p-%d-%d", i, j), "", px1, py1, px2, py2);
      pij->SetMargin(m_left/(m_left+fwidth+m_right), m_right/(m_left+fwidth+m_right),
                     m_bottom/(m_top+fheight+m_bottom), m_top/(m_top+fheight+m_bottom));
      pij->SetFillStyle(4000);
      pij->Draw("axis");
      // pads[i][j] = pij;
      auto flag = ((i == 0) ? 1u : 0u) | ((j == ny-1) ? 2u : 0u);
      std::cout<<i<<" "<<j<<" => "<<flag<<" => "<<(flag & 2u)<<(flag & 1u)<<std::endl;
      pads.push_back({ pij, flag });
    }
  }
  return pads;
}

Color_t xjjroot::color_blend(const std::vector<Color_t> colors,
                             const std::vector<float> fracs) {
  if (colors.empty() || colors.size() != fracs.size())
    return kBlack;

  float sum = 0.;
  for (auto& fr : fracs)
    sum += fr;
  if (sum <= 0.)
    return kBlack;

  float r = 0.f, g = 0.f, b = 0.f;
  for (size_t i = 0; i < colors.size(); ++i) {
    TColor* c = gROOT->GetColor(colors[i]);
    if (!c) continue;

    float rr, gg, bb;
    c->GetRGB(rr, gg, bb);

    float w = fracs[i] / sum;

    r += w * rr;
    g += w * gg;
    b += w * bb;
  }
  return TColor::GetColor(r, g, b);
}

Color_t xjjroot::color_alpha(Color_t color, double alpha) {
  TColor *c = gROOT->GetColor(color);
  float r, g, b;
  c->GetRGB(r, g, b);
  r = alpha * r + (1-alpha);
  g = alpha * g + (1-alpha);
  b = alpha * b + (1-alpha);
  return TColor::GetColor(r, g, b);
}

Color_t xjjroot::color_alpha_black(Color_t color, double alpha) {
  TColor* c = gROOT->GetColor(color);
  float r, g, b;
  c->GetRGB(r, g, b);
  r *= alpha;
  g *= alpha;
  b *= alpha;
  return TColor::GetColor(r, g, b);
}

namespace xjjroot
{
  int dummy = (TColor::SetColorThreshold(0), 0);
  // TColor::GetColor (int), Color_t (short int)
  const std::vector<Color_t> colorlist_bw =
    { static_cast<Color_t>(TColor::GetColor("#000000")), static_cast<Color_t>(TColor::GetColor("#191919")), static_cast<Color_t>(TColor::GetColor("#323232")), static_cast<Color_t>(TColor::GetColor("#4c4c4c")),
      static_cast<Color_t>(TColor::GetColor("#5d5d5d")), static_cast<Color_t>(TColor::GetColor("#666666")), static_cast<Color_t>(TColor::GetColor("#7f7f7f")), static_cast<Color_t>(TColor::GetColor("#999999")),
      static_cast<Color_t>(TColor::GetColor("#b2b2b2")), static_cast<Color_t>(TColor::GetColor("#cccccc")), static_cast<Color_t>(TColor::GetColor("#d3d3d3")), static_cast<Color_t>(TColor::GetColor("#e2e2e2")) };
  const std::vector<Color_t> colorlist_wb(colorlist_bw.rbegin(), colorlist_bw.rend());
  
  std::map<std::string, Color_t> mycolor_middle =
    {
      {"green",     static_cast<Color_t>(TColor::GetColor("#02735E"))},
      {"orange",    static_cast<Color_t>(TColor::GetColor("#D95829"))},
      {"red",       static_cast<Color_t>(TColor::GetColor("#A6442E"))},
      {"azure",     static_cast<Color_t>(TColor::GetColor("#146EA6"))},
      {"magenta",   static_cast<Color_t>(TColor::GetColor("#A65579"))},
      {"olive",     static_cast<Color_t>(TColor::GetColor("#467325"))},
      {"cyan",      static_cast<Color_t>(TColor::GetColor("#458984"))},
      {"yellow",    static_cast<Color_t>(TColor::GetColor("#F2B445"))},
      {"blue",      static_cast<Color_t>(TColor::GetColor("#015AA6"))},
      {"pink",      static_cast<Color_t>(TColor::GetColor("#C07A97"))},
      {"violet",    static_cast<Color_t>(TColor::GetColor("#734886"))},
    };
  std::map<std::string, Color_t> mycolor_light =
    {
      {"green",     static_cast<Color_t>(TColor::GetColor("#A7C5A5"))},
      {"orange",    static_cast<Color_t>(TColor::GetColor("#DFB89D"))},
      {"red",       static_cast<Color_t>(TColor::GetColor("#D7ABAB"))},
      {"azure",     static_cast<Color_t>(TColor::GetColor("#96AECB"))},
      {"magenta",   static_cast<Color_t>(TColor::GetColor("#CCAABB"))},
      {"olive",     static_cast<Color_t>(TColor::GetColor("#95A273"))},
      {"cyan",      static_cast<Color_t>(TColor::GetColor("#8EBDC3"))},
      {"yellow",    static_cast<Color_t>(TColor::GetColor("#F3D391"))},
      {"blue",      static_cast<Color_t>(TColor::GetColor("#989FC6"))},
      {"pink",      static_cast<Color_t>(TColor::GetColor("#DDBFC6"))},
      {"violet",    static_cast<Color_t>(TColor::GetColor("#C4BFD0"))},
    };
  std::map<std::string, Color_t> mycolor_dark =
    {
      {"green",     static_cast<Color_t>(TColor::GetColor("#0E4037"))},
      {"orange",    static_cast<Color_t>(TColor::GetColor("#A65C41"))},
      {"red",       static_cast<Color_t>(TColor::GetColor("#752726"))},
      {"azure",     static_cast<Color_t>(TColor::GetColor("#255573"))},
      {"magenta",   static_cast<Color_t>(TColor::GetColor("#735160"))},
      {"olive",     static_cast<Color_t>(TColor::GetColor("#2E4021"))},
      {"cyan",      static_cast<Color_t>(TColor::GetColor("#3D5755"))},
      {"yellow",    static_cast<Color_t>(TColor::GetColor("#8C7C61"))},
      {"blue",      static_cast<Color_t>(TColor::GetColor("#184873"))},
      {"pink",      static_cast<Color_t>(TColor::GetColor("#8C767F"))},
      {"violet",    static_cast<Color_t>(TColor::GetColor("#4E3E54"))},
    };
  std::map<std::string, Color_t> mycolor_satmiddle =
    {
      {"green",     static_cast<Color_t>(TColor::GetColor("#5BB997"))},
      {"orange",    static_cast<Color_t>(TColor::GetColor("#D77D3C"))},
      {"red",       static_cast<Color_t>(TColor::GetColor("#CF5959"))},
      {"azure",     static_cast<Color_t>(TColor::GetColor("#2D6BB4"))},
      {"magenta",   static_cast<Color_t>(TColor::GetColor("#BD659F"))},
      {"olive",     static_cast<Color_t>(TColor::GetColor("#89AF4B"))},
      {"cyan",      static_cast<Color_t>(TColor::GetColor("#329FAE"))},
      {"yellow",    static_cast<Color_t>(TColor::GetColor("#EAAD31"))},
      {"blue",      static_cast<Color_t>(TColor::GetColor("#394CAC"))},
      {"pink",      static_cast<Color_t>(TColor::GetColor("#CF6E96"))},
      {"violet",    static_cast<Color_t>(TColor::GetColor("#7D64C4"))},
    };
  std::map<std::string, Color_t> mycolor_satmiddle2 =
    {
      {"green",     static_cast<Color_t>(TColor::GetColor("#2CE8A4"))},
      {"orange",    static_cast<Color_t>(TColor::GetColor("#F37920"))},
      {"red",       static_cast<Color_t>(TColor::GetColor("#F43434"))},
      {"azure",     static_cast<Color_t>(TColor::GetColor("#0B68D5"))},
      {"magenta",   static_cast<Color_t>(TColor::GetColor("#E93AAD"))},
      {"olive",     static_cast<Color_t>(TColor::GetColor("#95E119"))},
      {"cyan",      static_cast<Color_t>(TColor::GetColor("#16B4CA"))},
      {"yellow",    static_cast<Color_t>(TColor::GetColor("#FEB11B"))},
      {"blue",      static_cast<Color_t>(TColor::GetColor("#1734CF"))},
      {"pink",      static_cast<Color_t>(TColor::GetColor("#F54790"))},
      {"violet",    static_cast<Color_t>(TColor::GetColor("#6B3EEA"))},
    };
}

#endif
