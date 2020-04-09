#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle( "Minecraft Launcher v" + app::conf.version );
	this->setWindowIcon( QIcon( "://index.ico" ) );

	ui->loginBox->setText( app::conf.login );

	connect( ui->startB, &QPushButton::clicked, this, &MainWindow::slot_start );
	connect( ui->loginBox, &QLineEdit::returnPressed, this, &MainWindow::slot_start );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::slot_start()
{
	auto login = ui->loginBox->text();

	if( login.isEmpty() ){
		return;
	}

	app::conf.login = login;
	app::saveSettings();



	emit close();
}
