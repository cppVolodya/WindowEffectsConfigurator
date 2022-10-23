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
};
}  // namespace N_WindowEffectsConfigurator

#endif  // MAIN_WINDOW_H
