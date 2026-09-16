#pragma once

namespace xjjroot {
  struct Inputpar {
    std::string content;
    std::string tex;
    std::string tag;
  };
  Inputpar parse_input(const std::string& inputname);
}

xjjroot::Inputpar xjjroot::parse_input(const std::string& inputname) {
  auto parse = xjjc::str_divide_trim(inputname, ";");
  Inputpar p = { .content = "", .tex = "", .tag = "" };
  if (parse.size() > 0)
    p.content = parse[0];
  if (parse.size() > 1)
    p.tex = parse[1];
  if (parse.size() > 2)
    p.tag = parse[2];

  return p;
}
