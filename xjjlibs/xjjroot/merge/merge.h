// note: should improve mkdir

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "xjjcuti.h"

namespace xjjroot
{
  class merge
  {
  public:
    merge(std::vector<std::string>& trees_, std::string filelist, std::string outputname, int ntotal = -1);
    TFile* outf;
    Long64_t n;
    void GetEntry(Long64_t i) {
      for(auto& t : trs) t.second->GetEntry(i);
    }
    void Fill() {
      for(auto& t : trees)
        {
          dirs[t]->cd();
          newtrs[t]->Fill();
        }
    }
    void Write() { outf->Write(); outf->Close(); }

  private:
    std::vector<std::string> files;
    std::vector<std::string> trees;
    std::map<std::string, TChain*> trs;
    std::map<std::string, TDirectory*> dirs;
    std::map<std::string, TTree*> newtrs;

    void setfiles(std::string filelist, int ntotal);
  };
}

xjjroot::merge::merge(std::vector<std::string>& trees_, std::string filelist, std::string outputname, int ntotal) : trees(trees_)
{
  TTree::SetMaxTreeSize(1LL * 1024 * 1024 * 1024 * 1024);

  setfiles(filelist, ntotal);

  for(auto& t : trees)
      trs[t] = new TChain(t.c_str());
  for(auto& i : files)
    {
      for(auto& t : trs) t.second->Add(i.c_str());
      std::cout<<i<<std::endl;
    }
  std::cout<<__FUNCTION__<<": Merged \e[31;1m"<<files.size()<<"\e[0m files."<<std::endl;

  n = trs[trees.front()]->GetEntries();

  outf = new TFile(outputname.c_str(), "recreate");
  for(auto& t : trees)
    {
      auto parse = xjjc::str_divide(t, "/");
      if(parse.size() == 2) 
        dirs[t] = outf->mkdir(parse[0].c_str(), "");
      else 
        dirs[t] = outf;
    }

  std::cout<<__FUNCTION__<<": -- Clone trees"<<std::endl;
  for(auto& t : trees)
    {
      dirs[t]->cd();
      newtrs[t] = trs[t]->CloneTree(0);
    } 
}

void xjjroot::merge::setfiles(std::string filelist, int ntotal = -1)
{
  std::ifstream getfile(filelist.c_str());
  for(int i=0; (i<ntotal || ntotal<0); i++)
    {
      std::string filename;
      getfile >> filename;
      if(getfile.eof()) { break; }
      files.push_back(filename);
    }
}

