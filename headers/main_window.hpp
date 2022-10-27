// Copyright [2022] <Volodymyr Dorozhovets>"

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QPainterPath>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QVBoxLayout>

#include "window_effects_configurator.hpp"


namespace N_WindowEffectsConfigurator
{
class MainWindow : public QWidget
{
public:
	explicit MainWindow(QWidget *parent = nullptr);
protected:
	void mousePressEvent  (QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent   (QMouseEvent *event) override;
private:
	inline constexpr static int S_WIDTH_OF_WINDOW {600};
	inline constexpr static int S_HEIGHT_OF_WINDOW{600};

	inline constexpr static std::string_view S_PATH_TO_ICON_OF_WINDOW{":/resources/window_effects_configurator.ico"};

	inline constexpr static int S_RANGE_OF_ALPHA_COLOR_CHANNEL_MIN{0};
	inline constexpr static int S_RANGE_OF_ALPHA_COLOR_CHANNEL_MAX{255};

	inline constexpr static qreal S_ROUNDNESS_OF_WINDOW_SHAPE{20.0};
private slots:
	void SlotOpenColorDialog();

	void SlotSetEffectType(int index);

	void SlotSetEffectConfigOfEnableGradientColor(int state);
	void SlotSetEffectConfigOfExpandToFullscreen(int state);
	void SlotSetEffectConfigOfEnableBlurBehindMasks(int state);

	void SlotSetAlphaColorChannel(int value);

	void SlotSetTransparent(int state);
	void SlotSetFramelessWindowHint(int state);

	void SlotSetWindowShape(int index);
private:
	std::unique_ptr<WindowEffectsConfigurator> m_window_effects_configurator;

	QPushButton *m_button_choose_color;
	QPushButton *m_exit_button;

	QComboBox *m_combo_box_of_effect_type;
	QLabel    *m_label_of_effect_type;

	QCheckBox *m_check_box_of_effect_config_of_enable_gradient_color;
	QCheckBox *m_check_box_of_effect_config_of_expand_to_fullscreen;
	QCheckBox *m_check_box_of_effect_config_of_enable_blur_behind_masks;

	QSlider *m_slider_of_alpha_color_channel;
	QLabel  *m_label_of_alpha_color_channel;

	QCheckBox *m_check_box_of_transparent;
	QCheckBox *m_check_box_of_frameless_window_hint;

	QComboBox *m_combo_box_of_window_shape;
	QLabel    *m_label_of_window_shape;

	QColor m_chosen_color;

	QPointF m_last_drag_position;

	bool m_mouse_is_pressed;
};
}  // namespace N_WindowEffectsConfigurator

#endif  // MAIN_WINDOW_H
