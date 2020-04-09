#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle( "Minecraft Launcher v" + app::conf.version );
	this->setWindowIcon( QIcon( "://index.ico" ) );

	ui->loginBox->setText( app::conf.login );
	ui->javaBox->setText( app::conf.javaPath );

	connect( ui->startB, &QPushButton::clicked, this, &MainWindow::slot_start );
	connect( ui->loginBox, &QLineEdit::returnPressed, this, &MainWindow::slot_start );
	connect( ui->javaSB, &QPushButton::clicked, this, &MainWindow::slot_javaSelect );
	connect( ui->javaBox, &QLineEdit::returnPressed, this, &MainWindow::slot_javaSelect );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::slot_start()
{
	auto login = ui->loginBox->text();
	auto javaPath = ui->javaBox->text();

	if( login.isEmpty() || javaPath.isEmpty() ){
		return;
	}

	app::conf.login = login;
	app::conf.javaPath = javaPath;
	app::saveSettings();

	auto appPath = QCoreApplication::applicationDirPath();

	QStringList args;

	args.append( "-Dfml.ignoreInvalidMinecraftCertificates=true" );
	args.append( "-Xincgc" );
	args.append( "-Xmx1024M" );
	args.append( "-Xmn128M" );
	args.append( QString( "-Djava.library.path=\"%1\\versions\\Forge 1.6.4\\natives\"" ).arg( appPath ) );
	args.append( "-cp" );

	QStringList libs;

	scanDir( QString( "%1/libraries" ).arg( appPath ), libs );
	scanDir( QString( "%1/versions" ).arg( appPath ), libs );

	args.append( QString( "\"%1\"" ).arg( libs.join(";") ) );
	args.append( "net.minecraft.launchwrapper.Launch" );
	args.append( "--username" );
	args.append( login );
	args.append( "--session" );
	args.append( "%random%" );
	args.append( "--uuid" );
	args.append( "\"%random%%random%-%random%-%random%-%random%-%random%%random%\"" );
	args.append( "--accessToken" );
	args.append( "\"%random%%random%-%random%-%random%-%random%-%random%%random%\"" );
	args.append( "--version" );
	args.append( "\"Forge 1.6.4\"" );
	args.append( "--gameDir" );
	args.append( QString( "\"%1\"" ).arg( appPath ) );
	args.append( "--assetsDir" );
	args.append( QString( "\"%1/assets\"" ).arg( appPath ) );
	args.append( "--tweakClass" );
	args.append( "cpw.mods.fml.common.launcher.FMLTweaker" );

	QFile f( "start.bat" );
	if( f.open( QIODevice::WriteOnly ) ){
		f.write( QString( "\"%1\"" ).arg( javaPath ).toUtf8() );
		f.write( " " );
		f.write( args.join( " " ).toUtf8() );
		f.close();
	}

	QProcess cmd;
	cmd.startDetached("cmd",QStringList()<<"/C"<<"start.bat");

	emit close();
}

void MainWindow::slot_javaSelect()
{
	auto fileName = QFileDialog::getOpenFileName(this, tr("Open java.exe"), app::conf.javaPath, tr("Java executable (*.exe)"));
	ui->javaBox->setText( fileName );
}

void MainWindow::scanDir(const QString &path, QStringList &list)
{
	if( !QDir( path ).exists() ){
		return;
	}

	QDir dir( path );
	dir.setNameFilters(QStringList("*.jar"));
	for( auto file:dir.entryList() ){
		auto path = QString( "%1/%2" ).arg( dir.absolutePath() ).arg( file );
		list.append( path );
	}

	dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	for( auto dirElem:dir.entryList() ){
		auto path = QString( "%1/%2" ).arg( dir.absolutePath() ).arg( dirElem );
		scanDir( path, list );
	}
}
