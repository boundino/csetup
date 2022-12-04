#include "include/compare.h"

#include <TCanvas.h>
#include <TH1D.h>
#include "xjjrootuti.h"
#include "xjjanauti.h"

int macro(std::string input="data/362294t.root::ht12f0vz-unw#TH1D,data/362294t.root::ht12f1vz-unw#TH1D")
{
  xjjroot::compare comp(input);
  auto ymax = xjjana::sethsmax(comp.vh);
  auto hempty = (TH1D*)comp.vh[0]->Clone("hempty");
  hempty->SetMinimum(0);
  hempty->SetMaximum(ymax*1.2);

  xjjroot::setgstyle(1);
  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw("AXIS");
  comp.draw();
  xjjroot::saveas(c, "figs/temp/barycentre-vz.png");

  return 0;
}

int main()
{
  return macro();
}
