/*
 * Mole - Mobile Organic Localisation Engine
 * Copyright 2010-2012 Nokia Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QApplication>

#include "binderGui.h"
#include "common.h"

void usage();
void version();

int main(int argc, char *argv[])
{
  initSettings();

  QApplication *app = new QApplication(argc, argv);

  // let user's settings override system's via fallback mechanism
  settings = new QSettings(MOLE_ORGANIZATION, MOLE_APPLICATION, app);

  if (settings->contains("map_server_url"))
    mapServerURL = settings->value("map_server_url").toString();

  if (settings->contains("fingerprint_server_url"))
    staticServerURL = settings->value("fingerprint_server_url").toString();

  char* logFilename = NULL;

  QStringList args = QCoreApplication::arguments();
  QStringListIterator argsIter(args);
  argsIter.next(); // = mole-binder

  while (argsIter.hasNext()) {
    QString arg = argsIter.next();
    if (arg == "-d") {
      debug = true;
    } else if (arg == "-v") {
      version();
    } else if (arg == "-s") {
      mapServerURL = argsIter.next();
    } else if (arg == "-f") {
      staticServerURL = argsIter.next();
    } else if (arg == "-l") {
      logFilename = argsIter.next().toAscii().data();
    } else {
      usage();
    }
  }

  qDebug () << "servers:" 
	    << "static" << staticServerURL
	    << "dynamic" << mapServerURL;

  initCommon(app, logFilename);

  QMainWindow *mainWindow = new QMainWindow();

  mainWindow->setWindowTitle("Organic Indoor Positioning");

  mainWindow->setWindowIcon(QIcon(MOLE_ICON_PATH + "mole-binder.png"));

#ifdef Q_WS_MAEMO_5
  mainWindow->setStyleSheet("QMainWindow { background-color: #222222; } QGroupBox { background-color: #000000; }");
#endif

  QWidget *mainWidget = new QWidget(mainWindow);
  mainWindow->setCentralWidget(mainWidget);

  BinderGUI *binder = new BinderGUI(mainWidget);
  app->connect(app, SIGNAL(aboutToQuit()), binder, SLOT(handleQuit()));

#ifdef Q_WS_MAEMO_5
  mainWindow->showMaximized();
#else
  mainWindow->show();
  mainWindow->resize(UI_WIDTH, UI_HEIGHT);
#endif

  return app->exec();
}

void usage()
{
  qCritical()
    << "mole-binder\n"
    << "-d debug\n"
    << "-s map server url\n"
    << "-f fingerprint (static) server\n"
    << "-l log file\n"
    << "-T ground truth file (for evaluation)";
}

void version()
{
  qCritical("mole-binder version %s\n", MOLE_VERSION);
  exit(0);
}
