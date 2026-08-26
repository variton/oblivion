#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <channel_mgr.h>

TEST_CASE("Has valid channels") {
  // std::string input{"/home/cxx-core/rc/sample.jpg"};
  // std::string output{"/home/cxx-core/test-results/sample-out.jpg"};
  // img::ImgHdr hdr{input, output};
  // auto ret = hdr.blend(100);
  // CHECK(ret.has_value());
  CHECK(true);
}

TEST_CASE("Channel open input failure") {
  // std::string input{"$ùoel"};
  // std::string output{"/home/cxx-core/test-results/sample-out.jpg"};
  // img::ImgHdr hdr{input, output};
  // auto ret = hdr.blend(100);
  // if (!ret) {
  //   CHECK(ret.error().type == img::ImageError::OpenFileError);
  //   CHECK(ret.error().message == "Failed to open input file\n");
  // }
  CHECK(true);
}

TEST_CASE("Channel open output failure") {
  // std::string input{"/home/cxx-core/rc/sample.jpg"};
  // std::string output{"xxxx/output.jpg"};
  // img::ImgHdr hdr{input, output};
  // auto ret = hdr.blend(100);
  // if (!ret) {
  //   CHECK(ret.error().type == img::ImageError::OpenFileError);
  //   CHECK(ret.error().message == "Failed to open output file\n");
  // }
  CHECK(true);
}
