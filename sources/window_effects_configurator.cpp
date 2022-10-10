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
}  // namespace N_WindowEffectsConfigurator
