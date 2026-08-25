
#include <channel_mgr.h>

namespace img {
ChannelMgr::ChannelMgr(int width, int height,int components) noexcept
  : width_(width), 
    height_(height), 
    components_(components) {}

ChannelMgr::~ChannelMgr() {}

tl::expected<void, ChannelErrorInfo> ChannelMgr::has_valid_channels() noexcept {
  if (width_ <= 0 || height_ <= 0) {
    return err::unexpected(ChannelError::ChannelImgDimError,
                           "Invalid image dimensions");
  }

  if (components_ != 3) {
    return err::unexpected(ChannelError::ChannelStructError, 
                          "Expected a three-channel RGB image");
  } 
  
  return {};
}


}
