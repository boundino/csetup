#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "xjjcuti.h"
#include "merge.h"

std::vector<std::string> trees = {
  // "HFAdcana/adc",
  // "hltanalysis/HltTree",
  "hiEvtAnalyzer/HiTree",
  "zdcanalyzer/zdcrechit",
};

int macro(std::string outputname, std::string filelist, bool isskim = false, int ntotal = -1)
{
  xjjroot::merge m(trees, filelist, outputname, ntotal);

  Long64_t nentries = m.n;
  std::cout<<__FUNCTION__<<": -- Event reading"<<std::endl;
  for(Long64_t i=0; i<nentries; i++)
    {
      if(i%10000==0) { xjjc::progressbar(i, nentries); }

      m.GetEntry(i);

      if(isskim && false) continue; // skim

      m.Fill();
    }
  xjjc::progressbar_summary(nentries);
      
  std::cout<<__FUNCTION__<<": -- Writing new trees done"<<std::endl;
  m.Write();

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc==5) { return macro(argv[1], argv[2], atoi(argv[3]), atoi(argv[4])); }
  if(argc==4) { return macro(argv[1], argv[2], atoi(argv[3])); }
  std::cout<<__FUNCTION__<<": ./macro.exe [outputname] [filelist] (optional)[number of files]";
  return 1;
}
