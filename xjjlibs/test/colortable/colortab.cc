#include <TCanvas.h>
#include <vector>
#include <iostream>

#include "xjjrootuti.h"

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
          if(!ncol) xjjroot::drawtex(x1, y1, Form("%s", xjjroot::colorlist_name[nrow].Data()), 0.03, 13, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c1->SaveAs("colorchart/ccolorlist1.pdf");

  std::vector<std::map<std::string, int>> mycolor({xjjroot::mycolor_middle, xjjroot::mycolor_light, xjjroot::mycolor_dark});
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
          xjjroot::drawtex((x1+x2)/2., (y1+y2)/2., Form("%d", cc.second), 0.05, 22, 62, 0);
          if(!ncol) xjjroot::drawtex(x1, y1, Form("%s", cc.first.c_str()), 0.03, 13, 62, 0);
          nrow++;
        }
      ncol++;
    }
  c2->SaveAs("colorchart/ccolorlist2.pdf");

}

int main()
{
  colortab();
  return 0;
}
