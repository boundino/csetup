#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TClass.h>
#include <TROOT.h>

#include <iostream>
namespace xjjc
{
  class showdir
  {
  public:
    showdir(TDirectory* src);
    ~showdir() { ; }

  private:
    void enterdir(TDirectory* source);
    int fll;
    std::vector<bool> lastll;
  };
}

xjjc::showdir::showdir(TDirectory* src) : fll(0)
{
  lastll.clear();
  lastll.push_back(true);
  enterdir(src);
  std::cout<<std::endl;
}

//
void xjjc::showdir::enterdir(TDirectory* source)
{
  // source->ls();
  TKey* key;
  TIter nextkey(source->GetListOfKeys());
  if(lastll.size()==1) { std::cout<<std::endl<<"   \e[2m("<<source->GetName()<<")\e[0m"<<std::endl<<"   \e[1m./\e[0m"<<std::endl; }
  lastll.push_back(true); fll = lastll.size()-1;
  while((key = (TKey*)nextkey()))
    {
      const char *classname = key->GetClassName(), *keyname = key->GetName();
      TClass* cl = gROOT->GetClass(classname);

      // >> print
      lastll[fll] = TIter(nextkey).Next()==0;
      for(std::vector<bool>::iterator lll = lastll.begin();lll<lastll.end()-1;lll++) { std::cout<<(*lll?" ":"\u2502")<<"   "; }
      std::cout<<(lastll[fll]?"\u2514":"\u251C")<<"\u2500\u2500 \e[32m("<<classname<<")\e[0m\e[2m =>\e[0m \e[1m"<<keyname<<"\e[0m";
      if(cl->InheritsFrom(TTree::Class())) { std::cout<<" \e[33m("<<((TTree*)source->Get(keyname))->GetEntries()<<")\e[0m"; }
      std::cout<<std::endl;
      // << print

      if(!cl) { continue; }
      if(cl->InheritsFrom(TDirectory::Class()))
        {
          source->cd(key->GetName());
          TDirectory* subdir = gDirectory;
          enterdir(subdir);
        }
    }
  lastll.pop_back(); fll = lastll.size()-1;
}

int main(int argc, char* argv[])
{
  if(argc==2)
    { 
      TFile* inf = TFile::Open(argv[1]);
      xjjc::showdir dirs(inf); 
      return 0;
    }
  std::cout<<__FUNCTION__<<": ./showdir [input]"<<std::endl;
  return 1;
}
