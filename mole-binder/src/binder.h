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

#ifndef BINDER_H
#define BINDER_H

#include <QWidget>

#include "common.h"

#define MIN_SCANS_TO_BIND 10
enum SubmitState {SCANNING, DISPLAY, EDITING};

class PlaceEdit;
class Settings;

class Binder : public QWidget
{
    Q_OBJECT
public:
    explicit Binder(QWidget *parent = 0);
    ~Binder();

public slots:
  void handleQuit();

private:
  bool m_daemonOnline;
  //int m_requestLocationEstimateCounter;
  SubmitState m_submitState;
  QTimer m_bindTimer;
  QTimer m_requestLocationTimer;
  QTimer m_walkingTimer;
  QTimer m_daemonHeartbeatTimer;
  Settings *m_settingsDialog;

  QPushButton *submitButton;
  QPushButton *rankMsgBoxButton;

  QMessageBox *rankMsgBox;

  QNetworkReply *m_feedbackReply;

  PlaceEdit *countryEdit;
  PlaceEdit *regionEdit;
  PlaceEdit *cityEdit;
  PlaceEdit *areaEdit;
  PlaceEdit *floorEdit;
  PlaceEdit *spaceNameEdit;
  QLineEdit *tagsEdit;

  QString countryEstimate;
  QString regionEstimate;
  QString cityEstimate;
  QString areaEstimate;
  QString floorEstimate;
  QString spaceNameEstimate;
  QString tagsEstimate;

  QLabel *walkingLabel;
  ColoredLabel *netLabel;
  ColoredLabel *daemonLabel;
  QLabel *scanCountLabel;
  QLabel *cacheSpacesLabel;
  QLabel *scanRateLabel;
  QLabel *overlapMaxLabel;
  QLabel *churnLabel;

  void buildUI();
  void setPlacesEnabled(bool);
  void resetBindTimer();
  void setWalkingLabel(bool);
  void refreshLastEstimate();
  void sendBindMsg();
  void setSubmitState(SubmitState state, int scanCount = 0);
  void setDaemonLabel(bool);
  void receivedDaemonMsg ();

private slots:
  void onAboutClicked();
  void onFeedbackClicked();
  void onHelpClicked();
  void onSettingsClicked();

  void onSettingsClosed();

  void onSendFeedbackFinished();
  void onPlaceChanged();

  void onSubmitClicked();
  void onRankMsgBoxButtonClicked();
  void onBindTimeout();
  void handleLocationEstimate(QString);
  void requestLocationEstimate();


  void onWalkingTimeout();
  void onSpeedStatusChanged(int);
  void onlineStateChanged(bool);
  void onDaemonTimerTimeout ();
  

  void handleLocationStats
    (QString fq_name, QDateTime start_time,
     int,int,int,int,int,int,int,
     double,double,double,double,double,double,QVariantMap);
};

#endif // BINDER_H
