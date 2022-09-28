// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITION_ATTRIB_DATA_HPP
#define IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITION_ATTRIB_DATA_HPP

#include <windef.h>

#include "window_composite_attrib.hpp"


namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects
{
struct WindowCompositionAttribData
{
	WindowCompositeAttrib   m_attrib;
	PVOID 					m_pv_data;
	SIZE_T 					m_cb_data;
};
}  // namespace N_WindowEffectsConfigurator::N_ImplementationOfEffects

#endif  // IMPLEMENTATION_OF_EFFECTS_WINDOW_COMPOSITION_ATTRIB_DATA_HPP
