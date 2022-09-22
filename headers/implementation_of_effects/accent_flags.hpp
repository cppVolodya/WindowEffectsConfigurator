// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef IMPLEMENTATION_OF_EFFECTS_ACCENT_FLAGS_HPP
#define IMPLEMENTATION_OF_EFFECTS_ACCENT_FLAGS_HPP

#include <windef.h>


namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects
{
enum class AccentFlags : DWORD
{
	enable_gradient_color    = 0x2,
	expand_to_fullscreen     = 0x4,
	enable_blur_behind_masks = 0x10
};
}  // namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects

#endif  // IMPLEMENTATION_OF_EFFECTS_ACCENT_FLAGS_HPP
