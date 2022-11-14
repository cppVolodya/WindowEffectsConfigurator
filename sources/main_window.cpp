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

void MainWindow::ConfigureBoxLayout()
{
	QVBoxLayout *layout_of_check_boxes_of_effect_config = std::make_unique<QVBoxLayout>().release();
	this->ConfigureBoxLayoutForCheckBoxOfEffectConfig(layout_of_check_boxes_of_effect_config);

	QHBoxLayout *layout_of_alpha_color_channel = std::make_unique<QHBoxLayout>().release();
	this->ConfigureBoxLayoutForAlphaColorChannel(layout_of_alpha_color_channel);

	QHBoxLayout *layout_of_combo_box_of_effect_type = std::make_unique<QHBoxLayout>().release();
	this->ConfigureComboBoxOfEffectType(layout_of_combo_box_of_effect_type);

	QVBoxLayout *layout_of_effects = std::make_unique<QVBoxLayout>().release();
	MainWindow::ConfigureBoxLayoutForEffects(layout_of_effects,
									         layout_of_combo_box_of_effect_type,
									         layout_of_check_boxes_of_effect_config,
									         layout_of_alpha_color_channel);

	QHBoxLayout *layout_of_window_flags = std::make_unique<QHBoxLayout>().release();
	this->ConfigureBoxLayoutForWindowFlags(layout_of_window_flags);

	QHBoxLayout *layout_of_window_shape = std::make_unique<QHBoxLayout>().release();
	this->ConfigureBoxLayoutForWindowShape(layout_of_window_shape);

	QVBoxLayout *layout_of_main = std::make_unique<QVBoxLayout>().release();
	this->ConfigureMainBoxLayout(layout_of_main,
								 layout_of_window_shape,
								 layout_of_window_flags,
								 layout_of_effects);

	this->setLayout(layout_of_main);
}

inline void MainWindow::ConfigureBoxLayoutForCheckBoxOfEffectConfig(QVBoxLayout *box_layout)
{
	box_layout->addWidget(this->m_check_box_of_effect_config_of_enable_gradient_color);
	box_layout->addWidget(this->m_check_box_of_effect_config_of_expand_to_fullscreen);
	box_layout->addWidget(this->m_check_box_of_effect_config_of_enable_blur_behind_masks);
}

inline void MainWindow::ConfigureBoxLayoutForAlphaColorChannel(QHBoxLayout *box_layout)
{
	box_layout->addWidget(this->m_slider_of_alpha_color_channel);
	box_layout->addWidget(this->m_label_of_alpha_color_channel);
}

inline void MainWindow::ConfigureComboBoxOfEffectType(QHBoxLayout *box_layout)
{
	box_layout->addWidget(this->m_combo_box_of_effect_type);
	box_layout->addWidget(this->m_label_of_effect_type);
}

inline void MainWindow::ConfigureBoxLayoutForEffects(QVBoxLayout *box_layout,
													 QHBoxLayout *layout_of_combo_box_of_effect_type,
											         QVBoxLayout *layout_of_check_boxes_of_effect_config,
											         QHBoxLayout *layout_of_alpha_color_channel)
{
	box_layout->addLayout(layout_of_combo_box_of_effect_type);
	box_layout->addLayout(layout_of_check_boxes_of_effect_config);
	box_layout->addLayout(layout_of_alpha_color_channel);
}

inline void MainWindow::ConfigureBoxLayoutForWindowFlags(QHBoxLayout *box_layout)
{
	box_layout->addWidget(this->m_check_box_of_transparent);
	box_layout->addWidget(this->m_check_box_of_frameless_window_hint);
}

inline void MainWindow::ConfigureBoxLayoutForWindowShape(QHBoxLayout *box_layout)
{
	box_layout->addWidget(this->m_combo_box_of_window_shape);
	box_layout->addWidget(this->m_label_of_window_shape);
}

void MainWindow::ConfigureMainBoxLayout(QVBoxLayout *box_layout,
										QHBoxLayout *layout_of_window_shape,
										QHBoxLayout *layout_of_window_flags,
										QVBoxLayout *layout_of_effects)
{
	box_layout->addWidget(this->m_exit_button);

	box_layout->addLayout(layout_of_window_shape);
	box_layout->addLayout(layout_of_window_flags);
	box_layout->addLayout(layout_of_effects);

	box_layout->addWidget(this->m_button_choose_color);
}

void MainWindow::ConnectSignalsToSlots()
{
	(void)QObject::connect(this->m_slider_of_alpha_color_channel, &QSlider::valueChanged,
						   this, 								  &MainWindow::SlotSetAlphaColorChannel);

	this->ConnectSignalsToSlotsForButtons   ();
	this->ConnectSignalsToSlotsForComboBoxes();
	this->ConnectSignalsToSlotsForCheckBoxes();
}

inline void MainWindow::ConnectSignalsToSlotsForButtons()
{
	(void)QObject::connect(this->m_button_choose_color, &QPushButton::clicked,
						   this,					    &MainWindow::SlotOpenColorDialog);

	(void)QObject::connect(this->m_exit_button, &QPushButton::clicked,
						   this, 				&MainWindow::close);
}

inline void MainWindow::ConnectSignalsToSlotsForComboBoxes()
{
	(void)QObject::connect(this->m_combo_box_of_effect_type, &QComboBox::currentIndexChanged,
						   this,                             &MainWindow::SlotSetEffectType);

	(void)QObject::connect(this->m_combo_box_of_window_shape, &QComboBox::currentIndexChanged,
						   this,                              &MainWindow::SlotSetWindowShape);
}

inline void MainWindow::ConnectSignalsToSlotsForCheckBoxes()
{
	this->ConnectSignalsToSlotsForCheckBoxOfEffectConfig();
	this->ConnectSignalsToSlotsForCheckBoxOfWindowFlags();
}

void MainWindow::ConnectSignalsToSlotsForCheckBoxOfEffectConfig()
{
	(void)QObject::connect(this->m_check_box_of_effect_config_of_enable_gradient_color, &QCheckBox::stateChanged,
						   this,                                                        &MainWindow::SlotSetEffectConfigOfEnableGradientColor);

	(void)QObject::connect(this->m_check_box_of_effect_config_of_expand_to_fullscreen, &QCheckBox::stateChanged,
						   this,                                                       &MainWindow::SlotSetEffectConfigOfExpandToFullscreen);

	(void)QObject::connect(this->m_check_box_of_effect_config_of_enable_blur_behind_masks, &QCheckBox::stateChanged,
						   this,                                                           &MainWindow::SlotSetEffectConfigOfEnableBlurBehindMasks);
}

inline void MainWindow::ConnectSignalsToSlotsForCheckBoxOfWindowFlags()
{
	(void)QObject::connect(this->m_check_box_of_transparent, &QCheckBox::stateChanged,
						   this, 							 &MainWindow::SlotSetTransparent);
	(void)QObject::connect(this->m_check_box_of_frameless_window_hint, &QCheckBox::stateChanged,
						   this, 									   &MainWindow::SlotSetFramelessWindowHint);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	this->m_mouse_is_pressed = true;
	this->m_last_drag_position = event->globalPosition();

	QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	this->m_mouse_is_pressed = false;

	QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(this->m_mouse_is_pressed)
	{
		this->move((event->globalPosition() - m_last_drag_position).toPoint() + this->pos());
		this->m_last_drag_position = event->globalPosition();
	}

	QWidget::mouseMoveEvent(event);
}

void MainWindow::SlotOpenColorDialog()
{
	this->m_chosen_color = QColorDialog::getColor(Qt::white, this, "Select Color");
	m_chosen_color.setAlpha(this->m_slider_of_alpha_color_channel->value());
	this->m_window_effects_configurator->SetGradientColor(this->m_chosen_color);
	this->m_window_effects_configurator->ApplyEffects();
}

void MainWindow::SlotSetEffectType(int index)
{
	const QString effect_type = this->m_combo_box_of_effect_type->itemText(index);

	bool is_set{this->TrySetDisabledEffect(effect_type)};

	if(not is_set)
	{
		is_set = this->TrySetGradientEffect(effect_type);
	}

	if(not is_set)
	{
		is_set = this->TrySetTransparentGradientEffect(effect_type);
	}

	if(not is_set)
	{
		is_set = this->TrySetBlurBehindEffect(effect_type);
	}

	if(not is_set)
	{
		is_set = this->TrySetAcrylicBlurBehindEffect(effect_type);
	}

	if(not is_set)
	{
		(void)this->TrySetTranslucentBackgroundEffect(effect_type);
	}

	this->m_window_effects_configurator->ApplyEffects();
}

inline bool MainWindow::TrySetDisabledEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Disabled")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::disabled);

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetGradientEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Gradient")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::gradient);

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetTransparentGradientEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Transparent gradient")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::transparent_gradient);

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetBlurBehindEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Blur behind")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::blur_behind);

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetAcrylicBlurBehindEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Acrylic blur behind")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::acrylic_blur_behind);

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetTranslucentBackgroundEffect(const QString &effect)
{
	bool result{false};
	if(effect == "Translucent background")
	{
		this->m_window_effects_configurator->SetEffectType
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectType::translucent_background);

		result = true;
	}

	return result;
}


void MainWindow::SlotSetEffectConfigOfEnableGradientColor(int state)
{
	if(state == Qt::Checked)
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::enable_gradient_color, true);

		this->m_window_effects_configurator->ApplyEffects();
	}
	else
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::enable_gradient_color, false);

		this->m_window_effects_configurator->ApplyEffects();
	}
}

void MainWindow::SlotSetEffectConfigOfExpandToFullscreen(int state)
{
	if(state == Qt::Checked)
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::expand_to_fullscreen, true);

		this->m_window_effects_configurator->ApplyEffects();
	}
	else
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::expand_to_fullscreen, false);

		this->m_window_effects_configurator->ApplyEffects();
	}
}

void MainWindow::SlotSetEffectConfigOfEnableBlurBehindMasks(int state)
{
	if(state == Qt::Checked)
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::enable_blur_behind_masks, true);

		this->m_window_effects_configurator->ApplyEffects();
	}
	else
	{
		this->m_window_effects_configurator->SetEffectConfigs
			(N_WindowEffectsConfigurator::WindowEffectsConfigurator::EffectConfig::enable_blur_behind_masks, false);

		this->m_window_effects_configurator->ApplyEffects();
	}
}

void MainWindow::SlotSetAlphaColorChannel(int value)
{
	this->m_chosen_color.setAlpha(value);
	this->m_window_effects_configurator->SetGradientColor(this->m_chosen_color);
	this->m_window_effects_configurator->ApplyEffects();
}

void MainWindow::SlotSetTransparent(int state)
{
	if(state == Qt::Checked)
	{
		this->setStyleSheet("QWidget#main_window { background-color: transparent; }");
	}
	else
	{
		this->setStyleSheet("QWidget#main_window { background-color: white; }");
	}
}

void MainWindow::SlotSetFramelessWindowHint(int state)
{
	if(state == Qt::Checked)
	{
		this->setWindowFlag(Qt::FramelessWindowHint, true);
	}
	else
	{
		this->setWindowFlag(Qt::FramelessWindowHint, false);
	}

	this->show();
}

void MainWindow::SlotSetWindowShape(int index)
{
	const auto window_shape = this->m_combo_box_of_window_shape->itemText(index);

	bool is_set{this->TrySetDefaultWindowShape(window_shape)};

	if(not is_set)
	{
		is_set = this->TrySetRectangleWindowShape(window_shape);
	}
	if(not is_set)
	{
		is_set = this->TrySetRoundedRectangleWindowShape(window_shape);
	}
	if(not is_set)
	{
		(void)this->TrySetEllipseWindowShape(window_shape);
	}
}

inline bool MainWindow::TrySetDefaultWindowShape(const QString &shape)
{
	bool result{false};
	if(shape == "Default")
	{
		this->setMask(QRegion());
		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetRectangleWindowShape(const QString &shape)
{
	bool result{false};
	if(shape == "Rectangle")
	{
		this->setMask(QRegion(this->rect()));
		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetRoundedRectangleWindowShape(const QString &shape)
{
	bool result{false};
	if(shape == "Rounded rectangle")
	{
		QPainterPath path;
		path.addRoundedRect(this->rect(), S_ROUNDNESS_OF_WINDOW_SHAPE,
							S_ROUNDNESS_OF_WINDOW_SHAPE);
		this->setMask(QRegion(path.toFillPolygon().toPolygon()));

		result = true;
	}

	return result;
}

inline bool MainWindow::TrySetEllipseWindowShape(const QString &shape)
{
	bool result{false};
	if(shape == "Ellipse")
	{
		this->setMask(QRegion(this->rect(), QRegion::Ellipse));

		result = true;
	}

	return result;
}
}  // namespace N_WindowEffectsConfigurator
