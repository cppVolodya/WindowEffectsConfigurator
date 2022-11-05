// Copyright [2022] <Volodymyr Dorozhovets>"

#include <QColorDialog>
#include <QMouseEvent>

#include "main_window.hpp"


namespace N_WindowEffectsConfigurator
{
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent, Qt::Window),
	  m_window_effects_configurator(std::make_unique<WindowEffectsConfigurator>(this->winId())),

      m_button_choose_color(nullptr),
      m_exit_button		   (nullptr),

      m_combo_box_of_effect_type(nullptr),
	  m_label_of_effect_type	(nullptr),


      m_check_box_of_effect_config_of_enable_gradient_color	  (nullptr),
      m_check_box_of_effect_config_of_expand_to_fullscreen	  (nullptr),
      m_check_box_of_effect_config_of_enable_blur_behind_masks(nullptr),

      m_slider_of_alpha_color_channel(nullptr),
      m_label_of_alpha_color_channel (nullptr),

      m_check_box_of_transparent		  (nullptr),
      m_check_box_of_frameless_window_hint(nullptr),

      m_combo_box_of_window_shape(nullptr),
	  m_label_of_window_shape	 (nullptr),

      m_mouse_is_pressed(false)
{
	this->SetDefaultSettings   ();
	this->CustomizeWidgets	   ();
	this->ConfigureBoxLayout   ();
	this->ConnectSignalsToSlots();
}

void MainWindow::SetDefaultSettings()
{
	this->setObjectName("main_window");

	this->setStyleSheet("QWidget#main_window { background-color: white; }");

	this->setWindowTitle("Window Effects Configurator");

	this->setWindowIcon(QIcon(MainWindow::S_PATH_TO_ICON_OF_WINDOW.data()));

	this->resize(MainWindow::S_WIDTH_OF_WINDOW,
				 MainWindow::S_HEIGHT_OF_WINDOW);
}
}  // namespace N_WindowEffectsConfigurator
