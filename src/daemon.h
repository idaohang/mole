/*
 * Mole - Mobile Organic Localisation Engine
 * Copyright 2010 Nokia Corporation.
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

#ifndef DAEMON_H_
#define DAEMON_H_

#include <QCoreApplication>

class Binder;
class Localizer;
class LocalServer;
class Scanner;
class ScanQueue;
class SpeedSensor;
class Proximity;

class Daemon : public QCoreApplication
{
  Q_OBJECT

public:
  Daemon(int argc = 0, char *argv[] = 0);
  ~Daemon();

  int run();

public slots:
  void handle_quit();

private:
  Localizer *m_localizer;
  Binder *m_binder;
  LocalServer *m_localServer;
  Scanner *m_scanner;
  ScanQueue *m_scanQueue;
  SpeedSensor *m_speedSensor;
  Proximity *m_proximity;
};

#endif /* DAEMON_H_ */
