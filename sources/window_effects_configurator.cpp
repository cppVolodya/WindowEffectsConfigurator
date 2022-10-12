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
}  // namespace N_WindowEffectsConfigurator
