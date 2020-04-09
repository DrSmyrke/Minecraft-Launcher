#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "global.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void slot_start();
	void slot_javaSelect();
private:
	Ui::MainWindow *ui;

	void scanDir(const QString &path, QStringList &list);
};

#endif // MAINWINDOW_H
