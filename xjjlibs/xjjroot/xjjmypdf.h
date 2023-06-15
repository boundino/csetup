#include <TCanvas.h>
#include <string>

#include "xjjrootuti.h"

/*
  xjjroot::mypdf pdf("output.pdf");
  // --> loop
  pdf.prepare();
  // draw
  pdf.write();
  // <--
  pdf.close();
*/
namespace xjjroot
{
  class mypdf
  {
  public:
    mypdf(std::string filename, std::string canvasname, int ww, int hh);
    mypdf(TCanvas* cc, std::string filename);
    void prepare() { fc->Clear(); fc->cd(); }
    void write(std::string pngname = "", std::string opt = "W");
    void close() { fc->Print(Form("%s]", ffname.c_str())); delete fc; }
    TCanvas* getc() { return fc; }
    std::string getfilename() { return ffname; }
  private:
    TCanvas* fc;
    std::string ffname;
  };
}

xjjroot::mypdf::mypdf(std::string filename, std::string canvasname,
                      int ww, int hh) : ffname(filename) {
  mkdir(ffname);
  fc = new TCanvas(canvasname.c_str(), "", ww, hh);
  fc->Print(Form("%s[", ffname.c_str()));
}

xjjroot::mypdf::mypdf(TCanvas* cc, std::string filename)
  : ffname(filename), fc(cc) {
  fc->Print(Form("%s[", ffname.c_str()));
}

void xjjroot::mypdf::write(std::string pngname, std::string opt) {
  if (pngname != "" && opt.find("W") != std::string::npos)
    drawcomment(pngname);
  fc->Print(Form("%s", ffname.c_str()));
  if (pngname != "") {
    mkdir(pngname);
    fc->SaveAs(pngname.c_str());
  }
}
