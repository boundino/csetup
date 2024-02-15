#include "csv.h"

int main(int argc, char* argv[]) {
  if (argc == 3) {
    xjjc::csv c(argv[1], atoi(argv[2]));
    c.print();
    return 0;
  }
  return 1;
}
