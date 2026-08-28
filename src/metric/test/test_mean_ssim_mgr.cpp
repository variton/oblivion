#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>

#include <env_mgr.h>
#include <filehandler.h>
#include <fmt/core.h>
#include <inputimg.h>
#include <jpeg_decoder.h>
#include <jpeg_decompressor.h>
#include <mean_ssim_mgr.h>

TEST_CASE("ComputeMeanSSIM OK") {
  /* remark they might be a problem the way the decompressor is used.
   * i should use a different decompressor for each image
   */
  std::string rc{"/home/cxx-core/rc"};
  using namespace img;
  std::string input{rc + "/ur.jpg"};
  auto input_file = fio::FileHandler::open(input.data(), "rb");
  CHECK(input_file.has_value());
  // jpeg decompressor creation =============================================
  JpegDecompressor decompressor{};
  auto ret_init_decompressor = decompressor.init(input_file.value().get());
  CHECK(ret_init_decompressor.has_value());
  auto ret_decompress = decompressor.decompress();
  CHECK(ret_decompress.has_value());
  // image object creation ==================================================
  InputImg inputimg{decompressor.cinfo()};
  // jpeg decoder ===========================================================
  /*the decoding is a bottleneck 2x time*/
  JpegDecoder original{inputimg.width, inputimg.height, inputimg.components};
  original.decode(decompressor);
  JpegDecoder watermarked{inputimg.width, inputimg.height, inputimg.components};
  watermarked.decode(decompressor);
  // pnsr mgr ===============================================================
  metric::MeanSSIMMgr mean_ssim_mgr{original.pixels(), watermarked.pixels()};
  auto ret_mean_ssim = mean_ssim_mgr.computeMeanSSIM(
      inputimg.width, inputimg.height, inputimg.components);
  CHECK(ret_mean_ssim.has_value());
  volatile double mean_ssim = ret_mean_ssim.value();
  fmt::println("Mean SSIM: {}\n", mean_ssim);
  CHECK(ret_mean_ssim.value() <= 1);
}

TEST_CASE("MT ComputeMeanSSIM OK") {
  /* remark they might be a problem the way the decompressor is used.
   * i should use a different decompressor for each image
   * the mt computing mean ssim should be used
   */
  std::string rc{"/home/cxx-core/rc"};
  using namespace img;
  std::string input{rc + "/ur.jpg"};
  auto input_file = fio::FileHandler::open(input.data(), "rb");
  CHECK(input_file.has_value());
  // jpeg decompressor creation =============================================
  JpegDecompressor decompressor{};
  auto ret_init_decompressor = decompressor.init(input_file.value().get());
  CHECK(ret_init_decompressor.has_value());
  auto ret_decompress = decompressor.decompress();
  CHECK(ret_decompress.has_value());
  // image object creation ==================================================
  InputImg inputimg{decompressor.cinfo()};
  // jpeg decoder ===========================================================
  /*the decoding is a bottleneck 2x time*/
  JpegDecoder original{inputimg.width, inputimg.height, inputimg.components};
  original.decode(decompressor);
  JpegDecoder watermarked{inputimg.width, inputimg.height, inputimg.components};
  watermarked.decode(decompressor);
  // pnsr mgr ===============================================================
  metric::MeanSSIMMgr mean_ssim_mgr{original.pixels(), watermarked.pixels()};
  auto ret_mean_ssim = mean_ssim_mgr.computeMeanSSIM(
      inputimg.width, inputimg.height, inputimg.components);
  CHECK(ret_mean_ssim.has_value());
  volatile double mean_ssim = ret_mean_ssim.value();
  fmt::println("Mean SSIM: {}\n", mean_ssim);
  CHECK(ret_mean_ssim.value() <= 1);
}
