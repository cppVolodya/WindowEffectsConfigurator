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
}  // namespace N_WindowEffectsConfigurator
