// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef WINDOW_EFFECTS_CONFIGURATOR_HPP
#define WINDOW_EFFECTS_CONFIGURATOR_HPP

#include <windef.h>
#include <windows.h>
#include <WinUser.h>

#include <QColor>
#include <qwindowdefs.h>

#include "window_composition_attrib_data.hpp"
#include "accent_policy.hpp"
#include "color_abgr.hpp"


namespace N_WindowEffectsConfigurator
{
class WindowEffectsConfigurator
{
public:
	enum class EffectType
	{
		disabled,
		gradient,
		transparent_gradient,
		blur_behind,
		acrylic_blur_behind,
		host_backdrop,
		translucent_background
	};
public:
	inline explicit WindowEffectsConfigurator(const WId &window_id);

	void ApplyEffects();

	inline void SetEffectType(const EffectType &effect_type) noexcept;

	inline void SetEffectConfigs(const EffectConfig &effect_config, bool is_enable) noexcept;

	inline void SetGradientColor(const QColor &gradient_color) noexcept;
private:
	typedef BOOL(WINAPI *T_SetWindowCompositionAttribute)(HWND, N_ImplementationOfEffects::WindowCompositionAttribData*);
private:
	HWND m_hwnd;

	T_SetWindowCompositionAttribute m_FunctionOfSetWindowCompositionAttribute;

	EffectType m_effect_type;
	DWORD      m_effect_configs;
	QColor     m_gradient_color;
private:
	inline void SaveWindowDescriptor(const WId &window_id);

	void GetFunctionOfSetWindowCompositionAttrib();

	N_ImplementationOfEffects::AccentPolicy CreateAccentPolicy();

	DWORD CreateAccentFlags();

	void DisableBlurBehindMasks();

	N_ImplementationOfEffects::WindowCompositionAttribData CreateWindowCompositionAttribData
		(N_ImplementationOfEffects::AccentPolicy &accent_policy);
};
inline WindowEffectsConfigurator::WindowEffectsConfigurator(const WId &window_id)
	: m_hwnd(nullptr),
	  m_FunctionOfSetWindowCompositionAttribute(nullptr),
	  m_effect_type   (EffectType::disabled),
	  m_effect_configs(static_cast<DWORD>(EffectConfig::disable_all)),
	  m_gradient_color(Qt::white)
{
	this->SaveWindowDescriptor(window_id);
	WindowEffectsConfigurator::GetFunctionOfSetWindowCompositionAttrib();
}

inline void WindowEffectsConfigurator::SetEffectType(const EffectType &effect_type) noexcept
{
	this->m_effect_type = effect_type;
}

inline void WindowEffectsConfigurator::SetEffectConfigs(const EffectConfig &effect_config, bool is_enable) noexcept
{
	if(is_enable)
	{
		this->m_effect_configs |= static_cast<DWORD>(effect_config);
	}
	else
	{
		this->m_effect_configs &= ~static_cast<DWORD>(effect_config);
	}
}

inline void WindowEffectsConfigurator::SetGradientColor(const QColor &gradient_color) noexcept
{
	this->m_gradient_color = gradient_color;
}

inline void WindowEffectsConfigurator::SaveWindowDescriptor(const WId &window_id)
{
	this->m_hwnd = (HWND)window_id;
}
}  // namespace N_WindowEffectsConfigurator

#endif  // WINDOW_EFFECTS_CONFIGURATOR_HPP
