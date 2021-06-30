#include <TStyle.h>
#include <TH2F.h>
#include <TCanvas.h>
#include "xjjrootuti.h"

TH2F* makeh();

int frame()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetLineWidth(2); 
  gStyle->SetFrameLineWidth(2);

  TH2F* h; TCanvas* c; int i = 0;

  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->Draw();
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->GetXaxis()->SetLabelSize(0);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "h->GetXaxis()->SetLabelSize(0);", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->GetXaxis()->SetNdivisions(0);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "h->GetXaxis()->SetNdivisions(0);", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->Draw("X+");
  xjjroot::drawtex(0.55, 0.55, "h->Draw(\"X+\");", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  gStyle->SetPadTickX(2);
  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "gStyle->SetPadTickX(2);", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  gStyle->SetPadTickX(1);
  h = makeh(); c = new TCanvas("c", "", 600, 600);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "gStyle->SetPadTickX(1);", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(1);
  h = makeh(); c = new TCanvas("c", "", 600, 600);
  c->SetFrameLineWidth(0);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "#splitline{gStyle->SetPadTickY(1);}{c->SetFrameLineWidth(0);}", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(0);
  h = makeh(); c = new TCanvas("c", "", 600, 600);
  c->SetFrameLineWidth(0);
  h->Draw();
  xjjroot::drawtex(0.55, 0.55, "c->SetFrameLineWidth(0);", 0.04, 22, 62);
  c->SaveAs(Form("cframe%d.png", i));
  delete c; delete h; i++;

  return 0;
}



int main() { 
  return frame(); 
}

TH2F* makeh()
{
  TH2F* h = new TH2F("h", ";x;y", 10, 0, 10, 10, 0, 1.05);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleOffset(1.10);
  h->GetYaxis()->SetTitleOffset(1.30);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.045);
  h->GetYaxis()->SetLabelSize(0.045);
  h->SetStats(0);

  return h;
}
