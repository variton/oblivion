
#ifndef BLENDER_H
#define BLENDER_H

#include <tuple>

#include <error_info.h>
#include <errty.h>
#include <jpeg_compressor.h>
#include <jpeg_decompressor.h>
#include <ncnm.h>
#include <tl/expected.hpp>

namespace img {

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * Uses the CRTP pattern to disable copy and move operations for the derived
 * type.
 *
 * @tparam T Derived type.
 */
template <typename T> using Default = core::NCNM<T>;

enum class BlenderError {
  BlendFinishCompressionError,
  BlendFinishDecompressionError,
};

/**
 * @brief Structured error information for image operations.
 */
using BlenderErrorInfo = err::ErrorInfo<BlenderError>;

static_assert(topology::ErrorInfoTy<BlenderErrorInfo>);

/**
 * @brief Image dimensions represented as width and height.
 */
using ImgDimension = std::tuple<int, int>;

class Blender : public Default<Blender> {
public:
  explicit Blender(const InputImg &inputimg) noexcept;
  ~Blender();

  tl::expected<ImgDimension, BlenderErrorInfo>
  blend(JpegCompressor &compressor, JpegDecompressor &decompressor) noexcept;

private:
  const InputImg &inputimg_;
};

} // namespace img

#endif // BLENDER_H
