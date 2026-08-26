
#include <channel_mgr.h>

namespace img {
ChannelMgr::ChannelMgr(int width, int height, int components) noexcept
    : width_(width), height_(height), components_(components) {}

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

tl::expected<Channels, ChannelErrorInfo>
ChannelMgr::splitRGBChannels(std::span<const std::uint8_t> pixels) noexcept {

  auto ret = has_valid_channels();
  if (!ret)
    return err::unexpected(ChannelError::ChannelSplitRGBError,
                           ret.error().message);

  const std::size_t pixel_count =
      static_cast<std::size_t>(width_) * static_cast<std::size_t>(height_);

  Channels channels;

  for (auto &channel : channels) {
    channel.resize(pixel_count);
  }

  for (std::size_t pixel = 0; pixel < pixel_count; ++pixel) {
    const std::size_t offset = pixel * 3;
    channels[0][pixel] = pixels[offset + 0]; // Red
    channels[1][pixel] = pixels[offset + 1]; // Green
    channels[2][pixel] = pixels[offset + 2]; // Blue
  }

  return channels;
}

} // namespace img
