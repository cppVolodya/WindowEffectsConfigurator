// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef IMPLEMENTATION_OF_EFFECTS_ACCENT_STATE_HPP
#define IMPLEMENTATION_OF_EFFECTS_ACCENT_STATE_HPP


namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects
{
enum class AccentState
{
	disabled,
	enable_gradient,
	enable_transparent_gradient,
	enable_blur_behind,
	enable_acrylic_blur_behind,
	enable_host_backdrop,
	invalid_stat,
};
}  // namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects

#endif  // IMPLEMENTATION_OF_EFFECTS_ACCENT_STATE_HPP
