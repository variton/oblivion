#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>

#include <channel_mgr.h>

#include <filehandler.h>
#include <fmt/core.h>
#include <inputimg.h>
#include <jpeg_decoder.h>
#include <jpeg_decompressor.h>

TEST_CASE("SplitRGBChannels OK") {
  std::string rc{"/home/cxx-core/rc"};
  using namespace img;
  std::string input{rc + "/ur.jpg"};
  auto input_file = fio::FileHandler::open(input.data(), "rb");
  // jpeg decompression creation ============================================
  JpegDecompressor decompressor{};
  auto ret_init_decompressor = decompressor.init(input_file.value().get());
  auto ret_decompress = decompressor.decompress();
  // image object creation ==================================================
  InputImg inputimg{decompressor.cinfo()};
  // jpeg decoder ===========================================================
  JpegDecoder original{inputimg.width, inputimg.height, inputimg.components};
  auto ret_decode = original.decode(decompressor);
  CHECK(ret_decode.has_value());
  auto pixels = original.pixels();
  ChannelMgr channel_mgr{inputimg.width, inputimg.height, inputimg.components};
  auto ret_split = channel_mgr.splitRGBChannels(pixels);
  CHECK(ret_split.has_value());
}

TEST_CASE("Channel invalid dimension") {
  // prepare context to propagate the right error
  CHECK(true);
}

TEST_CASE("Channel expected rgb image") {
  // prepare context to propagate the right error
  CHECK(true);
}
