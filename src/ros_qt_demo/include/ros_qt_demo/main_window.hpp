/**
 * @file /include/ros_qt_demo/main_window.hpp
 *
 * @brief Qt based gui for ros_qt_demo.
 *
 * @date November 2010
 **/
#ifndef ros_qt_demo_MAIN_WINDOW_H
#define ros_qt_demo_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace ros_qt_demo {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
  void on_actionShow_status_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

  /******************************************
  ** Manual connections
  *******************************************/
  void updateLoggingView(); // no idea why this can't connect automatically

  void on_ImageStartButton_clicked();
  void on_ImageStopButton_clicked();
  void slot_update_image(QImage);//收到图像数据信号要执行的操作函数

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace ros_qt_demo

#endif // ros_qt_demo_MAIN_WINDOW_H
