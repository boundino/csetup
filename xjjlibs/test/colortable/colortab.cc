#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "xjjrootuti.h"

void colortab()
{
  int ncol = 0, nrow = 0;
  float width, height, dheight;

  std::vector<TString> colorlist_name = {"kGreen", "kOrange", "kRed", "kAzure", "kMagenta", "kCyan", "kYellow", "kBlue", "kPink", "kViolet"};
  std::vector<Color_t> colorlist_baseline = {kGreen, kOrange, kRed, kAzure, kMagenta, kCyan, kYellow, kBlue, kPink, kViolet};
  std::vector<std::vector<Color_t>> colorlist({xjjroot::colorlist_middle, xjjroot::colorlist_light, xjjroot::colorlist_dark});
  std::vector<std::string> colorlist_txt = {"colorlist_middle", "colorlist_light", "colorlist_dark"};
  width = 1./colorlist.size(); height = 1./colorlist[0].size(); dheight = height/5.; 
  TCanvas* c1 = new TCanvas("ccololist", "", 200*colorlist.size(), 100*colorlist[0].size());
  ncol = 0;
  for(auto& vc : colorlist)
    {
      nrow = 0;
      for(auto& cc : vc)
        {
          float x1 = width*ncol, y1 = 1-height*nrow, x2 = width*(ncol+1), y2 = 1-(height*(nrow+1)-dheight), y3 = 1-height*(nrow+1), yl = 1-(height*(nrow+1)-dheight/2.);
          xjjroot::drawbox(x1, y1, x2, y2, cc, 1., 1001, cc, 0, 0);
          xjjroot::drawbox(x1, y2, x2, y3, cc, 0.3, 1001, cc, 0, 0);
          xjjroot::drawline(x1, yl, x2, yl, cc, 2, 4);
          xjjroot::drawtex((x1+x2)/2., (y1+y2)/2., Form("%s%s%d", colorlist_name[nrow].Data(), (cc>colorlist_baseline[nrow]?"+":"-"), abs(cc-colorlist_baseline[nrow])), 0.04, 22, 62, 0);
          if(!nrow)
            xjjroot::drawtex((x1+x2)/2., y1, colorlist_txt[ncol].c_str(), 0.03, 23, 42, 0);
          if(!ncol) 
            xjjroot::drawtex(x1, y2, Form("[%d]", nrow), 0.022, 11, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c1->SaveAs("ccolorlist1.pdf");
  c1->SaveAs("ccolorlist1.png");

  std::vector<std::map<std::string, int>> mycolor({xjjroot::mycolor_middle, xjjroot::mycolor_light, xjjroot::mycolor_dark, xjjroot::mycolor_satmiddle, xjjroot::mycolor_satmiddle2});
  std::vector<std::string> mycolor_txt = {"mycolor_middle", "mycolor_light", "mycolor_dark", "mycolor_satmiddle", "mycolor_satmiddle2"};
  width = 1./mycolor.size(); height = 1./mycolor[0].size(); dheight = height/5.; 
  TCanvas* c2 = new TCanvas("cmycolor", "", 200*mycolor.size(), 100*mycolor[0].size());
  ncol = 0;
  for(auto& vc : mycolor)
    {
      nrow = 0;
      for(auto& cc : vc)
        {
          float x1 = width*ncol, y1 = 1-height*nrow, x2 = width*(ncol+1), y2 = 1-(height*(nrow+1)-dheight), y3 = 1-height*(nrow+1), yl = 1-(height*(nrow+1)-dheight/2.);
          xjjroot::drawbox(x1, y1, x2, y2, cc.second, 1., 1001, cc.second, 0, 0);
          xjjroot::drawbox(x1, y2, x2, y3, cc.second, 0.3, 1001, cc.second, 0, 0);
          xjjroot::drawline(x1, yl, x2, yl, cc.second, 2, 4);
          std::ostringstream oshex;
          TColor::SaveColor(oshex, cc.second);
          std::string strhex(oshex.str());
          auto pos1 = strhex.find("#"), pos2 = strhex.find("\"", pos1+1);
          std::string s(strhex, pos1+1, pos2-pos1-1);
          std::transform(s.begin(), s.end(), s.begin(),
                         [](unsigned char c){ return std::toupper(c); }
                         );
          xjjroot::drawtex((x1+x2)/2., (y1+y2)/2., s.c_str(), 0.05*(11*3)/(mycolor.size()*mycolor[0].size()), 22, 62, 0);
          if(!nrow)
            xjjroot::drawtex((x1+x2)/2., y1, mycolor_txt[ncol].c_str(), 0.02, 23, 42, 0);
          if(!ncol) 
            xjjroot::drawtex(x1, y2, Form("%s", cc.first.c_str()), 0.03*(11*3)/(mycolor.size()*mycolor[0].size()), 11, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c2->SaveAs("ccolorlist2.pdf");
  c2->SaveAs("ccolorlist2.png");

}

int main()
{
  colortab();
  return 0;
}
