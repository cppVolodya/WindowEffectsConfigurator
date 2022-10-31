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
private:
	inline bool TrySetDisabledEffect			 (const QString &effect);
	inline bool TrySetGradientEffect			 (const QString &effect);
	inline bool TrySetTransparentGradientEffect  (const QString &effect);
	inline bool TrySetBlurBehindEffect		     (const QString &effect);
	inline bool TrySetAcrylicBlurBehindEffect	 (const QString &effect);
	inline bool TrySetTranslucentBackgroundEffect(const QString &effect);

	inline bool TrySetDefaultWindowShape		 (const QString &shape);
	inline bool TrySetRectangleWindowShape		 (const QString &shape);
	inline bool TrySetRoundedRectangleWindowShape(const QString &shape);
	inline bool TrySetEllipseWindowShape		 (const QString &shape);

	void SetDefaultSettings();

	inline void CustomizeWidgets					   ();
	inline void CustomizeButtonWidgets				   ();
	void        CustomizeComboBoxWidgets			   ();
	void        CustomizeComboBoxOfEffectTypeWidgets   ();
	void        CustomizeComboBoxOfWindowShapeWidgets  ();
	inline void CustomizeCheckBoxWidgets			   ();
	inline void CustomizeCheckBoxOfEffectConfigWidgets ();
	inline void CustomizeSliderWidgets				   ();
	inline void CustomizeLabelWidgets				   ();

	void ConfigureBoxLayout();
	inline void ConfigureBoxLayoutForCheckBoxOfEffectConfig(QVBoxLayout *box_layout);
	inline void ConfigureBoxLayoutForAlphaColorChannel(QHBoxLayout *box_layout);
	inline void ConfigureComboBoxOfEffectType(QHBoxLayout *box_layout);
	static inline void ConfigureBoxLayoutForEffects(QVBoxLayout *box_layout,
											        QHBoxLayout *layout_of_combo_box_of_effect_type,
											        QVBoxLayout *layout_of_check_boxes_of_effect_config,
											        QHBoxLayout *layout_of_alpha_color_channel);
	inline void ConfigureBoxLayoutForWindowFlags(QHBoxLayout *box_layout);
	inline void ConfigureBoxLayoutForWindowShape(QHBoxLayout *box_layout);
	void ConfigureMainBoxLayout(QVBoxLayout *box_layout,
							    QHBoxLayout *layout_of_window_shape,
							    QHBoxLayout *layout_of_window_flags,
							    QVBoxLayout *layout_of_effects);

	void 		ConnectSignalsToSlots					      ();
	inline void ConnectSignalsToSlotsForButtons			   	  ();
	inline void ConnectSignalsToSlotsForComboBoxes			  ();
	inline void ConnectSignalsToSlotsForCheckBoxes			  ();
	void 	    ConnectSignalsToSlotsForCheckBoxOfEffectConfig();
	inline void ConnectSignalsToSlotsForCheckBoxOfWindowFlags ();
};
}  // namespace N_WindowEffectsConfigurator

#endif  // MAIN_WINDOW_H
