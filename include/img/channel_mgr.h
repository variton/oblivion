
#ifndef CHANNEL_MGR_H
#define CHANNEL_MGR_H

#include <err_utils.h>
#include <filehandler.h>
#include <ncnm.h>
#include <tl/expected.hpp>

#include <array>
#include <cstdint>
#include <span>
#include <vector>

namespace img {

template <typename T> using Default = core::NCNM<T>;

using Channels = std::array<std::vector<std::uint8_t>, 3>;

enum class ChannelError {
  ChannelImgDimError,
  ChannelStructError,
  ChannelSplitRGBError
};

ERR_DEFINE_ERROR_INFO(ChannelError, ChannelErrorInfo);

class ChannelMgr : public core::NCNM<ChannelMgr> {
public:
  explicit ChannelMgr(int width, int height, int components) noexcept;
  ~ChannelMgr();
  tl::expected<Channels, ChannelErrorInfo>
  splitRGBChannels(std::span<const std::uint8_t> pixels) noexcept;

private:
  tl::expected<void, ChannelErrorInfo> has_valid_channels() noexcept;
  int width_;
  int height_;
  int components_;
};

} // namespace img

#endif
