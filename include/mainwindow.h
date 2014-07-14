#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "../include/user.h"
#include <QMainWindow>
#include <QComboBox>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <string>
#include <QWidget>
#include <QSize>
#include <QString>
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTextEdit>

class MainWindow : public QMainWindow {

  Q_OBJECT

  private:
 	std::set<User*> users;
 	QComboBox * combo;
 	QComboBox * otherCombo;
 	QTextEdit * newTweet;
 	QPushButton* btnSubmit;
 	QPushButton* btnReset;
 	QPushButton* btnFollow;
 	QListWidget * feed;
 	QListWidget * mentionsFeed;
 	QLabel * feedLabel;
 	QLabel * mentionsLabel;
 	QLabel * otherUserLabel;
 	QLabel * currentUserLabel;
 	QLabel * enterTweetLabel;

  private slots:
  	void chooseUser(const QString&);
  	void submit(const QString&);
  	void reset();



  public:
    MainWindow(std::set<User*>& u);

};

#endif
