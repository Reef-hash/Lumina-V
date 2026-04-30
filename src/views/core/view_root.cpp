
#include "views/view.hpp"
#include "lua/lua_manager.hpp"
#include "gui/modern_ui/ModernUI.hpp"
#include "pointers.hpp"

namespace big
{
       void view::root()
       {
	       // Use Modern UI as the main menu
	       if (g_pointers && g_pointers->m_gta.m_resolution_x && g_pointers->m_gta.m_resolution_y)
	       {
		       modern_ui::RenderModernTheme((float)*g_pointers->m_gta.m_resolution_x, (float)*g_pointers->m_gta.m_resolution_y);
	       }
       }
}
