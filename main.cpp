#include <chrono>

#include "lib/judge.h"

int main(int argc, char* argv[]) {
  // Suppress unused variable warning.
  (void)argc, (void)argv;

  auto start = std::chrono::high_resolution_clock::now();

  Judge autoJudge;
  autoJudge.set_start_rule("program");
  autoJudge.set_parser_tree(false);

  autoJudge.antlr_generate();
  autoJudge.antlr_judge();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";

  return 0;
}
