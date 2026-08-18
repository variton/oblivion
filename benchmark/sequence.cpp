
#include <mgr.h>
#include <fmt/core.h>
#include <runtime.h>

MICRO_CLOCK_RUNTIME_MAIN {
  clock();
  //quality check to gather picture metric 
  //argv[1] input path
  //argv[2] output path pnsr ssim
  clock();
  fmt::println("time elasped: {}", clock.elapsed());
  return 0;
}
