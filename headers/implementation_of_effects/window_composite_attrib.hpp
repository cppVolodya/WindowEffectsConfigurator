// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITE_ATTRIB_HPP
#define IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITE_ATTRIB_HPP


namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects
{
enum class WindowCompositeAttrib
{
	undefined,
	nc_rendering_enabled,
	nc_rendering_policy,
	transitions_force_disabled,
	allow_nc_paint,
	caption_button_bounds,
	non_client_rtl_layout,
	force_iconic_representation,
	extended_frame_bounds,
	has_iconic_bitmap,
	theme_attributes,
	nc_rendering_exiled,
	nc_adornment_info,
	excluded_from_live_preview,
	video_overlay_active,
	force_activewindow_appearance,
	disallow_peek,
	cloak,
	cloaked,
	accent_policy,
	freeze_representation,
	ever_uncloaked,
	visual_owner,
	holographic,
	excluded_from_dda,
	passive_update_mode,
	last,
};
}  // namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects

#endif  // IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITE_ATTRIB_HPP
