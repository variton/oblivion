
#include <mgr.h>
#include <fmt/core.h>
#include <runtime.h>

//#include <pixel_mgr.h>

MICRO_CLOCK_RUNTIME_MAIN {
  clock();
  //todo integrate pixel_mgr & mgr
  fmt::println("{}",argv[1]);
  //quality check to gather picture metric 
  //argv[1] input path
  //argv[2] output path pnsr ssim
  clock();
  fmt::println("time elasped: {} us", clock.elapsed());
  return 0;
}
