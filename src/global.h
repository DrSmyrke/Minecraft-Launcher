#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

struct Config{
	QString version;
	QString login;
	QString javaPath;
};

namespace app {
	extern Config conf;

	bool parsArgs(int argc, char *argv[]);
	void loadSettings();
	void saveSettings();
}

#endif // GLOBAL_H
