#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "../include/user.h"
#include <ostream>
#include <fstream>
#include <ctime>
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
#include <QLineEdit>
#include <QMessageBox>

class MainWindow : public QMainWindow {

  Q_OBJECT

  private:
 	std::set<User*> users;
 	QComboBox * combo;
 	QComboBox * otherCombo;
 	QTextEdit * newTweet;
 	QLineEdit * outputFileName;
 	QPushButton* btnSubmit;
 	QPushButton* btnReset;
 	QPushButton* btnFollow;
 	QPushButton* btnOutput;
 	QListWidget * feed;
 	QListWidget * mentionsFeed;
 	QLabel * feedLabel;
 	QLabel * mentionsLabel;
 	QLabel * otherUserLabel;
 	QLabel * currentUserLabel;
 	QLabel * enterTweetLabel;
 	QLabel * enterOutputLabel;
 	typename std::set<User*>::iterator it;
 	std::vector<std::string> mentionedName;

  private slots:
  	void chooseUser();
  	void submit();
  	void reset();
  	void output();
  	void follow();



  public:
    MainWindow(std::set<User*>& u);
    void updateWindow();

};

#endif
