// Copyright [2022] <Volodymyr Dorozhovets>"

#include <stdexcept>
#include <qdebug.h>

#include "window_effects_configurator.hpp"
#include "accent_flags.hpp"


namespace N_WindowEffectsConfigurator
{
void WindowEffectsConfigurator::ApplyEffects()
{
	N_ImplementationOfEffects::AccentPolicy accent_policy{this->CreateAccentPolicy()};

	N_ImplementationOfEffects::WindowCompositionAttribData data{this->CreateWindowCompositionAttribData(accent_policy)};

	this->m_FunctionOfSetWindowCompositionAttribute(this->m_hwnd, &data);
}

void WindowEffectsConfigurator::GetFunctionOfSetWindowCompositionAttrib()
{
	const HMODULE user_module{GetModuleHandle(L"user32.dll")};

	if(user_module)
	{
		this->m_FunctionOfSetWindowCompositionAttribute
			= (WindowEffectsConfigurator::T_SetWindowCompositionAttribute)GetProcAddress(user_module, "SetWindowCompositionAttribute");

		if (m_FunctionOfSetWindowCompositionAttribute == nullptr)
		{
			throw std::runtime_error("Can't get SetWindowCompositionAttribute function");
		}
	}
	else
	{
		throw std::runtime_error("Can't get user32.dll module");
	}
}

N_ImplementationOfEffects::AccentPolicy WindowEffectsConfigurator::CreateAccentPolicy()
{
	N_ImplementationOfEffects::AccentPolicy accent_policy;

	accent_policy.m_accent_state   = static_cast<N_ImplementationOfEffects::AccentState>(this->m_effect_type);
	accent_policy.m_accent_flags   = this->CreateAccentFlags();
	accent_policy.m_gradient_color = Color_ABGR::FromQColor(this->m_gradient_color).ToDword();
	accent_policy.m_animation_id   = 0x0;

	return accent_policy;
}

DWORD WindowEffectsConfigurator::CreateAccentFlags()
{
	DWORD accent_flags{0x0};

	if(this->m_effect_configs & static_cast<DWORD>(EffectConfig::enable_gradient_color))
	{
		accent_flags |= static_cast<DWORD>(N_ImplementationOfEffects::AccentFlags::enable_gradient_color);
	}

	if(this->m_effect_configs & static_cast<DWORD>(EffectConfig::expand_to_fullscreen))
	{
		accent_flags |= static_cast<DWORD>(N_ImplementationOfEffects::AccentFlags::expand_to_fullscreen);
	}

	if(this->m_effect_configs & static_cast<DWORD>(EffectConfig::enable_blur_behind_masks))
	{
		accent_flags |= static_cast<DWORD>(N_ImplementationOfEffects::AccentFlags::enable_blur_behind_masks);
	}
	else
	{
		this->DisableBlurBehindMasks();
	}

	return accent_flags;
}

void WindowEffectsConfigurator::DisableBlurBehindMasks()
{
	N_ImplementationOfEffects::AccentPolicy accent_policy;
	accent_policy.m_accent_state   = static_cast<N_ImplementationOfEffects::AccentState>(EffectType::disabled);
	accent_policy.m_accent_flags   = static_cast<DWORD>(EffectConfig::disable_all);
	accent_policy.m_gradient_color = Color_ABGR::FromQColor(QColor(Qt::white)).ToDword();
	accent_policy.m_animation_id   = 0x0;

	N_ImplementationOfEffects::WindowCompositionAttribData data{this->CreateWindowCompositionAttribData(accent_policy)};

	this->m_FunctionOfSetWindowCompositionAttribute(this->m_hwnd, &data);
}

N_ImplementationOfEffects::WindowCompositionAttribData WindowEffectsConfigurator::CreateWindowCompositionAttribData
	(N_ImplementationOfEffects::AccentPolicy &accent_policy)
{
	N_ImplementationOfEffects::WindowCompositionAttribData data{};
	data.m_attrib  = N_ImplementationOfEffects::WindowCompositeAttrib::accent_policy;
	data.m_pv_data = &accent_policy;
	data.m_cb_data = sizeof(accent_policy);

	return data;
}
}  // namespace N_WindowEffectsConfigurator
