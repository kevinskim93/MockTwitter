#include "../include/mainwindow.h"

MainWindow::MainWindow(std::set<User*>& u) : users(u){
  setGeometry( 0, 0, 800, 600 );

  combo = new QComboBox;

  typename std::set<User*>::iterator it = users.begin();
  for(it = users.begin(); it != users.end(); ++it){
  	QString qstr = QString::fromStdString((*it)->name());
  	combo->addItem(qstr);
  }

  otherCombo = new QComboBox;

  it = users.begin();
  for(std::set<User*>::iterator it3 = users.begin(); it3 != users.end(); ++it3){
    if((*it)->name() != (*it3)->name()){ 
      QString qstr = QString::fromStdString((*it3)->name());
      otherCombo->addItem(qstr);
    }
  }

  btnSubmit = new QPushButton(tr("&Submit"));
  btnReset = new QPushButton(tr("&Reset"));

  QHBoxLayout * submitreset = new QHBoxLayout;
  
  newTweet = new QTextEdit();

  submitreset->addWidget(btnSubmit);
  submitreset->addWidget(btnReset);

  QHBoxLayout * usersList = new QHBoxLayout;
  usersList->addWidget(combo);

  btnFollow = new QPushButton(tr("&Follow"));

  QHBoxLayout * otherUsersList = new QHBoxLayout;
  otherUsersList->addWidget(otherCombo);
  otherUsersList->addWidget(btnFollow);

  enterTweetLabel = new QLabel("Enter new tweet here:");
  currentUserLabel = new QLabel("Current User:");
  otherUserLabel = new QLabel("Other User:");
  feedLabel = new QLabel("Feed");
  mentionsLabel = new QLabel("Mentions Feed");


  feed = new QListWidget;
  it = users.begin();

  for(unsigned int i = 0; i < (*it)->getFeed().size(); i++){
    std::string tweetString = (*it)->getFeed().at(i)->time().stringTime() + " " + (*it)->getFeed().at(i)->text(); 
    QString qstr = QString::fromStdString(tweetString);
  	feed->addItem(qstr);
  }



  mentionsFeed = new QListWidget;
  typename std::set<User*>::iterator it2 = users.begin();

  for(unsigned int i = 0; i < (*it2)->getMentionedFeed().size(); i++){
    std::string tweetString = (*it2)->getMentionedFeed().at(i)->time().stringTime() + " " + (*it2)->getMentionedFeed().at(i)->text(); 
    QString qstr = QString::fromStdString(tweetString);
    mentionsFeed->addItem(qstr);
  }




  QVBoxLayout * mainLayout = new QVBoxLayout; //this is the main layout

  //here you will add layouts to the main layout

  mainLayout->addWidget(currentUserLabel);
  mainLayout->addLayout(usersList);

  mainLayout->addWidget(otherUserLabel);
  mainLayout->addLayout(otherUsersList);

  mainLayout->addWidget(feedLabel);
  mainLayout->addWidget(feed);

  mainLayout->addWidget(mentionsLabel);
  mainLayout->addWidget(mentionsFeed);

  mainLayout->addWidget(enterTweetLabel);
  mainLayout->addWidget(newTweet);
  mainLayout->addLayout(submitreset);

 
  //mainLayout->addWidget()

  QWidget * centWidget = new QWidget(this);
  centWidget->setLayout(mainLayout);
  this->setCentralWidget(centWidget);


  //connect
  //connect
  connect(combo, SIGNAL(activated(const QString&) ), this, SLOT (chooseUser(const QString&) ) );
  connect(btnSubmit, SIGNAL(clicked()), this, SLOT(submit(const QString&)) );
  connect(btnReset, SIGNAL(clicked()), this, SLOT(reset()) );

  //buttons = new Buttons();

  //Display the board in the central widget
  

  //Create GUI players

}

void MainWindow::chooseUser(const QString& thisUser){
  feed->clear();
  mentionsFeed->clear();

  std::string thisUserString = thisUser.toStdString();

  
  for(typename std::set<User*>::iterator it = users.begin(); it != users.end(); ++it){
    
    if(thisUserString == (*it)->name()){

      for(unsigned int i = 0; i < (*it)->getFeed().size(); i++){
        std::string tweetString = (*it)->getFeed().at(i)->time().stringTime() + " " + (*it)->getFeed().at(i)->text(); 
        QString qstr = QString::fromStdString(tweetString);
        feed->addItem(qstr);
      }

      for(unsigned int i = 0; i < (*it)->getMentionedFeed().size(); i++){
        std::string tweetString = (*it)->getMentionedFeed().at(i)->time().stringTime() + " " + (*it)->getMentionedFeed().at(i)->text(); 
        QString qstr = QString::fromStdString(tweetString);
        mentionsFeed->addItem(qstr);
      }
    }
  }
}


void MainWindow::submit(const QString& otherTweet){
  std::string tweet = otherTweet.toStdString();

}

void MainWindow::reset(){

	newTweet->clear();
}
