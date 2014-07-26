#ifndef TWEETWINDOW_H
#define TWEETWINDOW_H

#include "../include/user.h"
#include <map>
#include <ostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <QMainWindow>
#include <QComboBox>
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <QListWidgetItem>
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

class TweetWindow : public QMainWindow {

  Q_OBJECT

  private:
   	std::set<User*> users;
    std::map<std::string, std::set<Tweet*> > tagsMap;
    typename std::map<std::string, std::set<Tweet*> >::iterator it;

    QComboBox* alltimeorToday;
    QLabel* selectTime;
    QLabel* trendingTweetsLabel;
    QLabel* theseTweetsLabel;
    QLabel* tagsizeLabel;
    QLabel* lastUpdatedLabel;
    QPushButton* refreshBtn;
    QListWidget * theTags;
    QListWidget * theTweets;

   	

  private slots:
    void chooseTag(QListWidgetItem*);
    void refresh();
    void chooseTime();
  	


  public:
    TweetWindow();
    TweetWindow(std::set<User*>& u, std::map<std::string,std::set<Tweet*> >& t);
    void updateWindow();
    void collectTags();
    
};

#endif
