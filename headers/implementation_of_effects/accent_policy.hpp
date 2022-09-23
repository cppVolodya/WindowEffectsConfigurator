// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef IMPLEMENTATION_OF_EFFECTS_ACCENT_POLICY_HPP
#define IMPLEMENTATION_OF_EFFECTS_ACCENT_POLICY_HPP

#include <windef.h>

#include "accent_state.hpp"


namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects
{
struct AccentPolicy
{
	AccentState m_accent_state;

	DWORD m_accent_flags;
	DWORD m_gradient_color;
	DWORD m_animation_id;
};
}  // namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects

#endif  // IMPLEMENTATION_OF_EFFECTS_ACCENT_POLICY_HPP
