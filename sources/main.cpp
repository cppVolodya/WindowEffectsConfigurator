// Copyright [2022] <Volodymyr Dorozhovets>"

#include <QApplication>

#include "main_window.hpp"


int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	N_WindowEffectsConfigurator::MainWindow main_window;
	main_window.show();

	return application.exec();
}
