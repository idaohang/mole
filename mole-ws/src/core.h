/*
 * Mole - Mobile Organic Localisation Engine
 * Copyright 2010-2011 Nokia Corporation.
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

#ifndef CORE_H_
#define CORE_H_

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>

#include "simpleScanQueue.h"
#ifdef Q_WS_MAEMO_5
#include "../../common/scanner-maemo.h"
#else
#include "../../common/scanner-nm.h"
#endif

class Core : public QCoreApplication
{
  Q_OBJECT

public:
  Core(int argc = 0, char *argv[] = 0);
  void start();
  void sendRequest();

public slots:
  void scanCompleted();

private:
  int m_targetScanCount;
  int m_scansCompleted;
  QString m_serverUrl;
  QString m_request;
  QString m_container;
  QString m_poi;
  QVariantMap m_requestMap;
  Scanner *m_scanner;
  SimpleScanQueue *m_scanQueue;
  QNetworkAccessManager *m_networkAccessManager;

private slots:
  void handleResponse();

};

#endif /* CORE_H_ */
