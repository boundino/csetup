#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "xjjrootuti.h"

std::vector<TString> colorlist_name = {"kGreen", "kOrange", "kRed", "kAzure", "kMagenta", "kCyan", "kYellow", "kBlue", "kPink", "kViolet"};
std::vector<Color_t> colorlist_baseline = {kGreen, kOrange, kRed, kAzure, kMagenta, kCyan, kYellow, kBlue, kPink, kViolet};
void colortab()
{
  int ncol = 0, nrow = 0;
  float width, height, dheight;

  std::vector<std::vector<Color_t>> colorlist({xjjroot::colorlist_middle, xjjroot::colorlist_light, xjjroot::colorlist_dark});
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
          xjjroot::drawtex((x1+x2)/2., (y1+y2)/2., Form("%d", cc), 0.05, 22, 62, 0);
          xjjroot::drawtex(x1, y1, Form("%s%s%d", colorlist_name[nrow].Data(), (cc>colorlist_baseline[nrow]?"+":"-"), abs(cc-colorlist_baseline[nrow])), 0.03, 13, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c1->SaveAs("colorchart/ccolorlist1.pdf");
  c1->SaveAs("colorchart/ccolorlist1.png");

  std::vector<std::map<std::string, int>> mycolor({xjjroot::mycolor_middle, xjjroot::mycolor_light, xjjroot::mycolor_dark, xjjroot::mycolor_satmiddle});
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
          xjjroot::drawtex((x1+x2)/2., (y1+y2)/2., std::string(strhex, pos1+1, pos2-pos1-1).c_str(), 0.05*(11*3)/(mycolor.size()*mycolor[0].size()), 22, 62, 0);
          if(!ncol) xjjroot::drawtex(x1, y1, Form("%s", cc.first.c_str()), 0.03*(11*3)/(mycolor.size()*mycolor[0].size()), 13, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c2->SaveAs("colorchart/ccolorlist2.pdf");
  c2->SaveAs("colorchart/ccolorlist2.png");

}

int main()
{
  colortab();
  return 0;
}
