#include "../include/mainwindow.h"

MainWindow::MainWindow(std::set<User*>& u) : users(u){
  setGeometry( 0, 0, 800, 600 );

  combo = new QComboBox;

  it = users.begin();
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

  //creates the hbox for the textbox, which will include the vbox for the submit reset buttons after the texteditbox

  QHBoxLayout * textbox = new QHBoxLayout;

  QVBoxLayout * submitreset = new QVBoxLayout;
  
  newTweet = new QTextEdit();

  submitreset->addWidget(btnSubmit);
  submitreset->addWidget(btnReset);

  textbox->addWidget(newTweet);
  textbox->addLayout(submitreset);

  //create the hbox for the combobox

  QHBoxLayout * usersList = new QHBoxLayout;
  usersList->addWidget(combo);

  btnFollow = new QPushButton(tr("&Follow"));

  //create the hbox for the other users combobox

  QHBoxLayout * otherUsersList = new QHBoxLayout;
  otherUsersList->addWidget(otherCombo);
  otherUsersList->addWidget(btnFollow);

  enterTweetLabel = new QLabel("Enter new tweet here:");
  currentUserLabel = new QLabel("Current User:");
  otherUserLabel = new QLabel("Other User:");
  feedLabel = new QLabel("Feed");
  mentionsLabel = new QLabel("Mentions Feed");
  enterOutputLabel = new QLabel("Enter Name of Output File:");



  btnOutput = new QPushButton(tr("&Output to a File"));

  //create the hbox for the output area

  outputFileName = new QLineEdit();


  QHBoxLayout * outputArea = new QHBoxLayout;
  outputArea->addWidget(outputFileName);
  outputArea->addWidget(btnOutput);



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
  //mainLayout->addWidget(newTweet);
  mainLayout->addLayout(textbox);


  mainLayout->addWidget(enterOutputLabel);
  mainLayout->addLayout(outputArea);
 
  //mainLayout->addWidget()

  QWidget * centWidget = new QWidget(this);
  centWidget->setLayout(mainLayout);
  this->setCentralWidget(centWidget);


  //connect
  //connect
  connect(combo, SIGNAL(activated(const QString&) ), this, SLOT (chooseUser() ) );
  connect(btnFollow, SIGNAL(clicked()), this, SLOT(follow() ));
  connect(btnSubmit, SIGNAL(clicked()), this, SLOT(submit() ));
  connect(btnReset, SIGNAL(clicked()), this, SLOT(reset() ));
  connect(btnOutput,SIGNAL(clicked()), this, SLOT(output()) );

  //buttons = new Buttons();

  //Display the board in the central widget
  

  //Create GUI players

}

void MainWindow::chooseUser(){
  updateWindow();





}


void MainWindow::submit(){

  if(newTweet->toPlainText() != NULL){

  QString str= newTweet->toPlainText();

  std::string tempText = (*it)->name() + " " + str.toStdString();

  time_t t = time(0);   // get time now
  struct tm * now = localtime( &t );
  int tempYear = (now->tm_year + 1900);
  int tempMonth = (now->tm_mon + 1);
  int tempDate = now->tm_mday;
  int tempHour = now->tm_hour;
  int tempMinute = now->tm_min;
  int tempSecond = now->tm_sec;
         

  DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);

  Tweet* tempTweet = new Tweet((*it), tempDateTime, tempText);
  //
  //
  bool mentionsFeed1 = false;
  bool mentionsFeed2 = false;
  
  char* token;
  char* tempTweetChar = new char[tempText.size()+1];
  std::copy(tempText.begin(), tempText.end(), tempTweetChar);
  tempTweetChar[tempText.size()] = '\0'; // don't forget the terminating 0


  token = strtok(tempTweetChar," ");
  token = strtok(NULL," ");


  if(token[0] == '@'){ //first string is an @ mention
    mentionsFeed1 = true;
    std::string tempMentionedName(token);
    tempMentionedName.erase(tempMentionedName.begin()); //erases the at sign
    mentionedName.push_back(tempMentionedName);
    token = strtok(NULL," ");
    //cout << "mentioned: " << tempMentionedName << endl;
  }
  while(token){
    if(token[0] == '@'){ //@ mention in the tweet, not the first string
      mentionsFeed2 = true;
      std::string tempMentionedName(token);
      tempMentionedName.erase(tempMentionedName.begin()); //erases the at sign
      mentionedName.push_back(tempMentionedName);
    }

    token = strtok(NULL, " ");

  }

  if(mentionsFeed1){ //this tweet will enter the mentionsfeed of the user, the tweet had at mentions inside the tweet
    (*it)->addMentions(tempTweet);
    for(unsigned int i = 0; i < mentionedName.size(); i++){ //search through the temporary mentioned users list
      for(std::set<User*>::iterator it4 = users.begin(); it4 != users.end(); ++it4){ //serach through full users list
        
        std::string tempMentionedName = mentionedName[i];
        std::transform(tempMentionedName.begin(), tempMentionedName.end(), tempMentionedName.begin(), ::tolower);

        std::string tempstrName = (*it4)->name();
        std::transform(tempstrName.begin(), tempstrName.end(), tempstrName.begin(), ::tolower);
        if(tempMentionedName == tempstrName){ //finds if the name equals the mentioned user then add it to their mentioned feed
          (*it4)->addMentioned(tempTweet);
        }
      }
    }
  }

  else if(mentionsFeed2){
    for(unsigned int i = 0; i < mentionedName.size(); i++){ //search through the temporary mentioned users list
      for(std::set<User*>::iterator it4 = users.begin(); it4 != users.end(); ++it4){ //serach through full users list

        std::string tempMentionedName = mentionedName[i];
        std::transform(tempMentionedName.begin(), tempMentionedName.end(), tempMentionedName.begin(), ::tolower);

        std::string tempstrName = (*it4)->name();
        std::transform(tempstrName.begin(), tempstrName.end(), tempstrName.begin(), ::tolower);
        if(tempMentionedName == tempstrName){ //finds if the name equals the mentioned user then add it to their mentioned feed
          (*it4)->addMentioned(tempTweet);
        }
      }
    }
    (*it)->addTweet(tempTweet); //these tweets will still be displayed as main tweets
  }

  else {
    (*it)->addTweet(tempTweet);
  }
  
  
  mentionedName.clear(); //empty the temporary mentioned name list

  newTweet->clear();

  updateWindow();

}

  //
  //(*it)->addTweet(tempTweet);
  
  else{
    if(outputFileName->text() == NULL){
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Cannot have empty tweet!");
    messageBox.setFixedSize(500,200);
  }
  }

}

void MainWindow::reset(){

	newTweet->clear();
}

void MainWindow::updateWindow(){
  feed->clear();
  mentionsFeed->clear();
  QString qstr = combo->currentText();
  std::string str = qstr.toStdString();
  for(typename std::set<User*>::iterator it2 = users.begin(); it2 != users.end(); ++it2){
    
    if(str == (*it2)->name()){
      it = it2;
      (*it)->deleteFeed();
      (*it)->deleteMentionedFeed();
      (*it)->makeFeed();
      (*it)->makeMentionedFeed();

      for(unsigned int i = 0; i < (*it2)->getFeed().size(); i++){
        std::string tweetString = (*it2)->getFeed().at(i)->time().stringTime() + " " + (*it2)->getFeed().at(i)->text(); 
        QString qstr = QString::fromStdString(tweetString);
        feed->addItem(qstr);
      }

      for(unsigned int i = 0; i < (*it2)->getMentionedFeed().size(); i++){
        std::string tweetString = (*it2)->getMentionedFeed().at(i)->time().stringTime() + " " + (*it2)->getMentionedFeed().at(i)->text(); 
        QString qstr = QString::fromStdString(tweetString);
        mentionsFeed->addItem(qstr);
      }
    }
  }

  outputFileName->clear();
  //outputFileName->insert((*it)->name());
}

void MainWindow::output(){


  updateWindow();

  if(outputFileName->text() == NULL){
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Cannot have empty filename!");
    messageBox.setFixedSize(500,200);
  }

  else{
    std::string oFile;
    oFile = outputFileName->text().toStdString();
    std::ofstream ofile(oFile.c_str());
    ofile << (*it)->name() << std::endl << std::endl;

    int size = (*it)->getFeed().size();
    ofile << "Feed: " << std::endl;
    for(int i = 0; i < size; i++){
      ofile << (*(*it)->getFeed().at(i)) << std::endl;
    }
    ofile << std::endl;

    int size2 = (*it)->getMentionedFeed().size();
    ofile << "Mentioned Feed: " << std::endl;
    for(int i = 0; i < size2; i++){
      ofile << (*(*it)->getMentionedFeed().at(i)) << std::endl;
    }
    ofile << std::endl;

    ofile.close();
  }    



}

void MainWindow::follow(){

  QString otherUserQ = otherCombo->currentText();
  std::string otherUser = otherUserQ.toStdString();

  for(typename std::set<User*>::iterator it2 = users.begin(); it2 != users.end(); ++it2){
    if(otherUser == (*it2)->name()){
      (*it)->addFollowing(*it2);
    }
  }

 


  updateWindow();
}