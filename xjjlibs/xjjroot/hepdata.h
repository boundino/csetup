/*
  qualifiers:
  - {name: RE, value: PB PB --> D0 --> K + PI}
  - {name: SQRT(S), units: GEV, value: 5020}
  - {name: $|$RAPIDITY(D)$|$, value: $<$ 1}
  - {name: CENTRALITY, units: $\%$, value: 0.0 - 100.0}
  - {name: GLOBAL UNCERTAINTY (TAA and LUMI), units: $\%$, value: -4.6 +4.1}
*/

#include <ostream>
#include <iostream>
#include <vector>
#include <string>
#include "TH1F.h"
#include <TGraphErrors.h>

namespace xjjroot {
  struct hep_nuv {
    std::string name;
    std::string units;
    std::string value;
  };
  hep_nuv make_hep_nuv(std::vector<std::string> v) {
    hep_nuv h = {v[0], v[1], v[2]};
    return h;
  }
  std::string print_hep_nuv(hep_nuv v, bool print = false) {
    std::string r = "{name: " + v.name;
    if (v.units != "")
      r += (", units: " + v.units);
    if (v.value != "")
      r += (", value: " + v.value);
    r += "}";
    if (print)
      std::cout<<r<<std::endl;
    return r;
  }

  //
  class hepdata {
  public:
    hepdata(TH1* _hstat, TGraphErrors* _hsyst,
            std::vector<std::string> _x_header, std::vector<std::string> _y_header) : hstat(_hstat), hsyst(_hsyst), x_header(make_hep_nuv(_x_header)), y_header(make_hep_nuv(_y_header)) { ; }
    // std::vector<std::string> _x_header, std::vector<std::string> _y_header);
    void set_qualifiers(std::vector<hep_nuv> _qualifiers) { qualifiers = _qualifiers; }
    void print_qualifiers() {
      for (auto& q : qualifiers)
        print_hep_nuv(q, true);
    }
    void print(std::ostream& out, float range_l = 99, float range_h = -99);
    
  private:
    TH1* hstat;
    TGraphErrors* hsyst;
    hep_nuv x_header, y_header;
    std::vector<hep_nuv> qualifiers;

  };
}

void xjjroot::hepdata::print(std::ostream &out, float range_l, float range_h) {
  out << "independent_variables:" << std::endl;
  out << "- header: " << print_hep_nuv(x_header) << std::endl;
  out << "  values:" << std::endl;

  for (int i=0; i<hstat->GetNbinsX(); i++) {
    if (hstat->GetBinCenter(i+1) < range_l || hstat->GetBinCenter(i+1) > range_h) continue;
    out << "  - {low: " << Form("%.1f", hstat->GetBinCenter(i+1) - hstat->GetBinWidth(i+1)/2.)
        << ", high: " << Form("%.1f", hstat->GetBinCenter(i+1) + hstat->GetBinWidth(i+1)/2.)
        << "}" << std::endl;
  }

  out << "dependent_variables:" << std::endl;
  out << "- header: " << print_hep_nuv(x_header) << std::endl;
  out << "  qualifiers:" << std::endl;
  for (auto& q : qualifiers) {
    out << "  - " << print_hep_nuv(q) << std::endl;
  }
  out << "  values:" << std::endl;
  for (int i=0; i<hstat->GetNbinsX(); i++) {
    auto xbin = hstat->GetBinCenter(i+1);
    if (xbin < range_l || xbin > range_h) continue;
    out << "  - value: " << Form("%.1f", hstat->GetBinContent(i+1)) << std::endl;
    out << "    errors:" << std::endl;
    out << "    - {symerror: " << Form("%.1f", hstat->GetBinError(i+1)) << ", label: stat}" << std::endl;

    
  }
}
