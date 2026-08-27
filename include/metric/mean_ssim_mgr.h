
#ifndef MEAN_SSIM_MGR_H
#define MEAN_SSIM_MGR_H

#include <cstdint>
#include <memory>
#include <ncnm.h>
#include <span>

#include <err_utils.h>
#include <tl/expected.hpp>

namespace metric {

template <typename T> using Default = core::NCNM<T>;

enum class MeanSSIMMgrError {
  MeanSSIMImgDimError,
  MeanSSIMStructError,
  MeanSSIMChannelError
};

ERR_DEFINE_ERROR_INFO(MeanSSIMMgrError, MeanSSIMMgrErrorInfo);

class MeanSSIMMgr : public Default<MeanSSIMMgr> {
public:
  explicit MeanSSIMMgr(std::span<const std::uint8_t> original,
                       std::span<const std::uint8_t> watermarked) noexcept;

  ~MeanSSIMMgr();

  tl::expected<double, MeanSSIMMgrErrorInfo>
  computeMeanSSIM(int width, int height, int components) noexcept;
  tl::expected<double, MeanSSIMMgrErrorInfo>
  MtComputeMeanSSIM(int width, int height, int components) noexcept;

private:
  std::span<const std::uint8_t> original_; /**< Original image data view. */
  std::span<const std::uint8_t>
      watermarked_; /**< Watermarked image data view. */
};

} // namespace metric

#endif // MEAN_SSIM_MGR_H
