#ifndef _XJJC_UTI_H_
#define _XJJC_UTI_H_

/* xjjcuti.h */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <string>
#include <cmath>
#include <vector>
#include <cxxabi.h>
#include <algorithm>
#include <regex>
#include <ctime>
#include <cctype>

namespace xjjc
{
  const std::string nc("\e[0m");
  std::vector<std::string> speciallist = {" ", "/", "(", ")", "^", "#", "%", "$", ",", ".", "*"};

  template<size_t N, typename T> void initarray(T (*array_)[N], T initval_=0);
  template<size_t N, typename T> int findibin(const T (*array_)[N], T element_); // overflow: -1
  template<typename T> int findibin(const std::vector<T> array_, T element_); // overflow: -1
  template<size_t N, typename T> int findiedge(const T (*array_)[N], T element_);
  template<typename T> int findiedge(const std::vector<T> array_, T element_);

  template<typename T> std::string number_to_string(T param_);
  template<typename T> std::string number_remove_zero(T param_);
  template<typename T> std::string number_range(T val1_, T val2_, std::string var, std::string opt="");

  void progressbar(int index_, int total_, int morespace_=0);
  void progressbar_summary(int total_);

  template<typename T> char* gettype(T exp);

  template<class T> bool sortbydes(const T &a, const T &b) { return a > b; }
  template<class T1, class T2> bool sortbyfirst_des(const std::pair<T1,T2> &a, const std::pair<T1,T2> &b) { return a.first > b.first; }
  template<class T1, class T2> bool sortbyfirst_as(const std::pair<T1,T2> &a, const std::pair<T1,T2> &b) { return a.first < b.first; }
  template<class T1, class T2> bool sortbysecond_des(const std::pair<T1,T2> &a, const std::pair<T1,T2> &b) { return a.second > b.second; }
  template<class T1, class T2> bool sortbysecond_as(const std::pair<T1,T2> &a, const std::pair<T1,T2> &b) { return a.second < b.second; }

  std::string str_replaceall(std::string strs, std::string sub, std::string newsub);
  std::string str_replaceallspecial(std::string strs);
  bool str_contains(std::string str1, std::string str2) { return str1.find(str2)!=std::string::npos; }
  bool str_isnumber(std::string strs) { return (std::regex_match(strs, std::regex("-?[0-9]+([.][0-9]*)?")) || std::regex_match(strs, std::regex("-?[0-9]*[.][0-9]+"))); }
  bool str_isinteger(std::string strs) { return std::regex_match(strs, std::regex("-?[0-9]+")); }
  std::vector<std::string> str_divide(std::string str, std::string div);
  std::string str_divide_lastel(std::string str, std::string div);
  std::string str_getdir(std::string filename);
  std::string str_tolower(std::string str);
  std::string str_toupper(std::string str);

  std::string currenttime();
  std::string prt_divider(std::string color="\e[0m", int len=35) { std::cout<<color<<std::string(len, '-')<<"\e[0m"<<std::endl;
}

/* ---------- */

template<size_t N, typename T>
void xjjc::initarray(T (*array_)[N], T initval_/*=0*/)
{
  for(std::size_t i=0;i<(sizeof(*array_)/sizeof((*array_)[0]));i++)
    {
      (*array_)[i]  = initval_;
    }
}

template<size_t N, typename T>
int xjjc::findibin(const T (*array_)[N], T element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<((sizeof(*array_)/sizeof((*array_)[0]))-1) && ielement<0;i++)
    {
      if(element_>=(*array_)[i] && element_<(*array_)[i+1]) ielement = i;
    }
  return ielement;
}

template<typename T>
int xjjc::findibin(const std::vector<T> array_, T element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<(array_.size()-1) && ielement<0;i++)
    {
      if(element_>=array_[i] && element_<array_[i+1]) ielement = i;
    }
  return ielement;
}

template<size_t N, typename T>
int xjjc::findiedge(const T (*array_)[N], T element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<(sizeof(*array_)/sizeof((*array_)[0])) && ielement<0;i++)
    {
      if(element_==(*array_)[i]) ielement = i;
    }
  return ielement;
}

template<typename T>
int xjjc::findiedge(const std::vector<T> array_, T element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<array_.size() && ielement<0;i++)
    {
      if(element_==array_[i]) ielement = i;
    }
  return ielement;
}

template<typename T>
std::string xjjc::number_to_string(T param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos)
    {
      str+="p0";
      return str;
    }
  str.replace(found,1,"p");
  while(*(str.end()-1)=='0' && *(str.end()-2)!='p' && !str.empty()) str.erase(str.end()-1);
  return str;
}

template<typename T>
std::string xjjc::number_remove_zero(T param_)
{
  bool negative = param_<0;
  // if(param_<0) return "";
  if(negative) param_ = 0-param_;
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos) return str;
  while(*(str.end()-1)=='0') str.erase(str.end()-1);
  if(*(str.end()-1)=='.') str.erase(str.end()-1);
  if(negative) str = "-"+str;
  return str;
}

template<typename T>
std::string xjjc::number_range(T val1_, T val2_, std::string var, std::string opt/*=""*/)
{
  std::string str = "";
  if(val1_ == val2_) { return str; }
  if(val1_<val2_ && opt=="fmax") { T valtmp_ = val1_; val1_ = val2_; val2_ = valtmp_; }
  if(val1_>val2_ && opt=="fmin") { T valtmp_ = val1_; val1_ = val2_; val2_ = valtmp_; }
  std::string sign = val1_<val2_?"<":">";
  if(opt!="fmax" && opt!="fmin" ) { str += (number_remove_zero(val1_)+" "+sign+" "); }
  str += var;
  str += (" "+sign+" "+number_remove_zero(val2_)); 
  return str;
}

void xjjc::progressbar(int index_, int total_, int morespace_/*=0*/)
{
  if(total_ > 0)
    std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10+morespace_)<<index_<<"\033[0m"<<" / "<<std::setw(10+morespace_)<<total_<<" ] "<<"\033[1;36m"<<round(100.*index_/total_)<<"%\033[0m"<<"\r"<<std::flush;
  else
    std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10+morespace_)<<index_<<"\033[0m ]"<<"\r"<<std::flush;
}

void xjjc::progressbar_summary(int total_)
{
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<total_<<"\033[0m event(s)."<<std::endl;
}

template<typename T>
char* xjjc::gettype(T exp)
{
  const std::type_info &ti = typeid(exp);
  int status = 0;
  char* humantypename = abi::__cxa_demangle(ti.name(), 0, 0, &status);
  return humantypename;
}

std::string xjjc::str_replaceall(std::string strs, std::string sub, std::string newsub)
{
  std::string result(strs);
  std::string str(strs);
  size_t pos = str.find(sub, 0);
  size_t thispos = 0;
  while(pos != std::string::npos)
    {
      result.replace(pos + thispos, sub.size(), newsub);
      thispos += (newsub.size() - sub.size());
      pos = str.find(sub, pos+1);
    }
  return result;
}

std::string xjjc::str_replaceallspecial(std::string strs)
{
  std::string result(strs);
  for(auto& isp : speciallist) { result = xjjc::str_replaceall(result, isp, "_"); }
  return result;
}

std::vector<std::string> xjjc::str_divide(std::string str, std::string div)
{
  std::vector<std::string> token;
  size_t lastpos = 0;
  size_t pos = str.find(div, 0);
  while(pos != std::string::npos) 
    {
      std::string thistoken = str.substr(lastpos, pos-lastpos);
      token.push_back(thistoken);
      lastpos = pos+1;
      pos = str.find(div, pos+1);
    }
  if(lastpos != 0) { token.push_back(str.substr(lastpos, str.size()-lastpos)); }
  if(token.empty()) token.push_back(str);
  return token;
}

std::string xjjc::str_divide_lastel(std::string str, std::string div)
{
  std::vector<std::string> token = str_divide(str, div);
  if(token.empty()) return "";
  return token[token.size()-1];
}

std::string xjjc::str_tolower(std::string str)
{
  std::string newstr(str);
  std::transform(newstr.begin(), newstr.end(), newstr.begin(),
                 [](unsigned char c){ return std::tolower(c); });
  return newstr;
}

std::string xjjc::str_toupper(std::string str)
{
  std::string newstr(str);
  std::transform(newstr.begin(), newstr.end(), newstr.begin(),
                 [](unsigned char c){ return std::toupper(c); });
  return newstr;
}

std::string xjjc::currenttime()
{
  std::time_t t = std::time(0);   // get time now
  std::tm* now = std::localtime(&t);
  char chartime[29]; // yyyymmdd-hhmmss
  sprintf(chartime, "%d%s%d%d-%d%d%d", now->tm_year+1900, (now->tm_mon>=9?"":"0"), now->tm_mon+1, now->tm_mday,
          now->tm_hour, now->tm_min, now->tm_sec);
  return std::string(chartime);
}

std::string xjjc::str_getdir(std::string filename)
{
  std::string dir = str_replaceall(filename, str_divide(filename, "/").back(), "");
  return dir;
}

#ifndef __PRMYERR
#define __PRMYERR(info) { std::cout<<"\e[42m("<<__FUNCTION__<<")\e[0m \e[31;1merror: \e[0m"<<#info<<std::endl; }
#endif

#endif
