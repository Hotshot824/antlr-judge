#include <chrono>

#include "lib/judge.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  Judge autoJudge;
  autoJudge.antlr_generate();
  autoJudge.antlr_parse_tree_judge();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";

  return 0;
}
