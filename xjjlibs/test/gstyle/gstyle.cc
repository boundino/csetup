#include <TH2F.h>
#include <TCanvas.h>

#include "xjjrootuti.h"

void gstyle()
{
  TH2F* h = new TH2F("h", ";X Axis;Y Axis", 10, 0, 10, 10, 0, 10);
  xjjroot::sethempty(h);
  xjjroot::setgstyle();
  TCanvas* c = new TCanvas("c", "", 600, 600);
  c->Divide(2, 2);

  TPad* p0 = (TPad*)c->cd(1);
  h->Draw("AXIS");
  xjjroot::drawtex(0.57, 0.5, "xjjroot::setgstyle();", 0.06, 22, 62);

  TPad* p1 = (TPad*)c->cd(2);
  p1->SetTickx(1);
  p1->SetTicky(1);
  h->Draw("AXIS");
  xjjroot::drawtex(0.57, 0.5, "xjjroot::setgstyle(1);", 0.06, 22, 62);

  TPad* p2 = (TPad*)c->cd(3);
  p2->SetLineWidth(2);
  p2->SetFrameLineWidth(2);
  h->Draw("AXIS");
  xjjroot::drawtex(0.57, 0.5, "xjjroot::setgstyle(2);", 0.06, 22, 62);

  TPad* p3 = (TPad*)c->cd(4);
  p3->SetTickx(1);
  p3->SetTicky(1);
  p3->SetLineWidth(2);
  p3->SetFrameLineWidth(2);
  h->Draw("AXIS");
  xjjroot::drawtex(0.57, 0.5, "xjjroot::setgstyle(3);", 0.06, 22, 62);

  c->SaveAs("gstyle.pdf");
  c->SaveAs("gstyle.png");
}

int main()
{
  gstyle();
  return 0;
}
