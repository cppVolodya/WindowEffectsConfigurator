// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef COLOR_ABGR_HPP
#define COLOR_ABGR_HPP

#include <windef.h>

#include <QColor>


namespace N_WindowEffectsConfigurator
{
class Color_ABGR
{
public:
	constexpr inline explicit Color_ABGR(uint32_t abgr = 0U);

	constexpr inline explicit Color_ABGR(uint8_t alpha,
							             uint8_t blue,
							             uint8_t green,
							             uint8_t red);

	inline static Color_ABGR FromQColor(const QColor& color);

	[[nodiscard]] constexpr inline uint32_t GetValue() const noexcept;

	[[nodiscard]] constexpr inline DWORD ToDword() const;
private:
	uint32_t m_value;
};
constexpr inline Color_ABGR::Color_ABGR(uint32_t color_abgr)
	: m_value(color_abgr)
{
}

constexpr inline Color_ABGR::Color_ABGR(uint8_t alpha, uint8_t blue, uint8_t green, uint8_t red)
	: m_value((static_cast<uint32_t>(alpha) << 24) |
			  (static_cast<uint32_t>(blue ) << 16) |
			  (static_cast<uint32_t>(green) << 8)  |
			   static_cast<uint32_t>(red  ))
{
}

inline Color_ABGR Color_ABGR::FromQColor(const QColor& color)
{
	return Color_ABGR(static_cast<uint8_t>(color.alpha()),
					  static_cast<uint8_t>(color.blue ()),
					  static_cast<uint8_t>(color.green()),
					  static_cast<uint8_t>(color.red  ()));
}

[[nodiscard]] constexpr inline uint32_t Color_ABGR::GetValue() const noexcept
{
	return this->m_value;
}

[[nodiscard]] constexpr inline DWORD Color_ABGR::ToDword() const
{
	return static_cast<DWORD>(m_value);
}
}  // namespace N_WindowEffectsConfigurator

#endif  // COLOR_ABGR_HPP
