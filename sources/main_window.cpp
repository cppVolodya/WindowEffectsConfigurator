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

void MainWindow::CustomizeWidgets()
{
	this->CustomizeButtonWidgets  ();
	this->CustomizeComboBoxWidgets();
	this->CustomizeCheckBoxWidgets();
	this->CustomizeSliderWidgets  ();
	this->CustomizeLabelWidgets   ();
}

inline void MainWindow::CustomizeButtonWidgets()
{
	this->m_button_choose_color = std::make_unique<QPushButton>("Choose Color", this).release();
	this->m_exit_button 		= std::make_unique<QPushButton>("Exit", this).release();
}

inline void MainWindow::CustomizeComboBoxWidgets()
{
	this->CustomizeComboBoxOfEffectTypeWidgets ();
	this->CustomizeComboBoxOfWindowShapeWidgets();
}

void MainWindow::CustomizeComboBoxOfEffectTypeWidgets()
{
	this->m_combo_box_of_effect_type = std::make_unique<QComboBox>(this).release();
	this->m_combo_box_of_effect_type->addItem("Disabled");
	this->m_combo_box_of_effect_type->addItem("Gradient");
	this->m_combo_box_of_effect_type->addItem("Transparent gradient");
	this->m_combo_box_of_effect_type->addItem("Blur behind");
	this->m_combo_box_of_effect_type->addItem("Acrylic blur behind");
	this->m_combo_box_of_effect_type->addItem("Translucent background");
}

void MainWindow::CustomizeComboBoxOfWindowShapeWidgets()
{
	this->m_combo_box_of_window_shape = std::make_unique<QComboBox>(this).release();
	this->m_combo_box_of_window_shape->addItem("Default");
	this->m_combo_box_of_window_shape->addItem("Rectangle");
	this->m_combo_box_of_window_shape->addItem("Rounded rectangle");
	this->m_combo_box_of_window_shape->addItem("Ellipse");
}

inline void MainWindow::CustomizeCheckBoxWidgets()
{
	this->CustomizeCheckBoxOfEffectConfigWidgets();

	this->m_check_box_of_transparent = std::make_unique<QCheckBox>("Transparent", this).release();
	this->m_check_box_of_frameless_window_hint  = std::make_unique<QCheckBox>("Frameless window hint", this).release();
}

inline void MainWindow::CustomizeCheckBoxOfEffectConfigWidgets()
{
	this->m_check_box_of_effect_config_of_enable_gradient_color    = std::make_unique<QCheckBox>("Enable gradient color", this).release();
	this->m_check_box_of_effect_config_of_expand_to_fullscreen     = std::make_unique<QCheckBox>("Expand to fullscreen", this).release();
	this->m_check_box_of_effect_config_of_enable_blur_behind_masks = std::make_unique<QCheckBox>("Enable blur behind masks", this).release();
}

inline void MainWindow::CustomizeSliderWidgets()
{
	this->m_slider_of_alpha_color_channel = std::make_unique<QSlider>(Qt::Horizontal, this).release();
	this->m_slider_of_alpha_color_channel->setRange(S_RANGE_OF_ALPHA_COLOR_CHANNEL_MIN,
													S_RANGE_OF_ALPHA_COLOR_CHANNEL_MAX);
}

inline void MainWindow::CustomizeLabelWidgets()
{
	this->m_label_of_alpha_color_channel = std::make_unique<QLabel>("Alpha color channel", this).release();
	this->m_label_of_window_shape 	  	 = std::make_unique<QLabel>("Window shape",	    this).release();
	this->m_label_of_effect_type		 = std::make_unique<QLabel>("Effect type", 	    this).release();
}
}  // namespace N_WindowEffectsConfigurator
