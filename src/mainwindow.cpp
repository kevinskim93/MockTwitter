#include "../include/mainwindow.h"

MainWindow::MainWindow(std::set<User*>& u, std::map<std::string,std::set<Tweet*> >& t) : users(u), tagsMap(t) {
  setGeometry( 0, 0, 800, 600 );

  TweetWin = new TweetWindow(users, tagsMap);
  TweetWin->setWindowTitle("Trending Tweets");

  //make the combobox to select the current user
  combo = new QComboBox;

  it = users.begin();
  for(it = users.begin(); it != users.end(); ++it){
  	QString qstr = QString::fromStdString((*it)->name());
  	combo->addItem(qstr);
  }

  //make the combobox to select the other user which you will follow
  otherCombo = new QComboBox;

  it = users.begin();
  for(std::set<User*>::iterator it3 = users.begin(); it3 != users.end(); ++it3){
    if((*it)->name() != (*it3)->name()){ 
      QString qstr = QString::fromStdString((*it3)->name());
      otherCombo->addItem(qstr);
    }
  }

  //submit and reset button for textbox
TweetWin = new TweetWindow(users, tagsMap);
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



  enterTweetLabel = new QLabel("Enter new tweet here:");
  currentUserLabel = new QLabel("Current User:");
  feedLabel = new QLabel("Feed");
  mentionsLabel = new QLabel("Mentions Feed");
  enterOutputLabel = new QLabel("Enter Name of Output File:");
  otherUsersLabel = new QLabel("Other Users: ");
  currentlyFollowLabel = new QLabel("Currently Following:");



  btnOutput = new QPushButton(tr("&Output to a File"));

  //create the hbox for the output area

  outputFileName = new QLineEdit();


  QHBoxLayout * outputArea = new QHBoxLayout;
  outputArea->addWidget(outputFileName);
  outputArea->addWidget(btnOutput);

  it = users.begin();
  std::set<User*> followingTemp = (*it)->following();

  followingList = new QListWidget;

  for(std::set<User*>::iterator it4 = followingTemp.begin(); it4 != followingTemp.end(); ++it4){
    QString qstr = QString::fromStdString((*it4)->name());
    followingList->addItem(qstr);
  }

  //followingList->setFixedSize(QSize(550, 100));

  //hbox for the following list
  //QVBoxLayout * followingListWidget = new QVBoxLayout;
  //followingListWidget->addWidget(followingList);

  //HBox for the other users and the follow button
  QHBoxLayout * otherUsersButtons = new QHBoxLayout;
  otherUsersButtons->addWidget(otherCombo);
  otherUsersButtons->addWidget(btnFollow);


  //creates the widget for the feed
  feed = new QListWidget;
  it = users.begin();

  for(unsigned int i = 0; i < (*it)->getFeed().size(); i++){
    std::string tweetString = (*it)->getFeed().at(i)->time().stringTime() + " " + (*it)->getFeed().at(i)->text(); 
    QString qstr = QString::fromStdString(tweetString);
  	feed->addItem(qstr);
  }


  //create the widget for the mentions feed
  mentionsFeed = new QListWidget;
  typename std::set<User*>::iterator it2 = users.begin();

  for(unsigned int i = 0; i < (*it2)->getMentionedFeed().size(); i++){
    std::string tweetString = (*it2)->getMentionedFeed().at(i)->time().stringTime() + " " + (*it2)->getMentionedFeed().at(i)->text(); 
    QString qstr = QString::fromStdString(tweetString);
    mentionsFeed->addItem(qstr);
  }


  //portion for adding trending tweets function
  trendingTweets = new QPushButton(tr("&View Trending Tweets"));




  QVBoxLayout * mainLayout = new QVBoxLayout; //this is the main layout

  //here you will add layouts to the main layout

  //current user:
  //combobox with list of users to choose from
  mainLayout->addWidget(currentUserLabel);
  mainLayout->addLayout(usersList);

  //currently following:
  //list box with who the current user is following
  mainLayout->addWidget(currentlyFollowLabel);
  mainLayout->addWidget(followingList);

  //combobox list of other users with button to follow the other user
  mainLayout->addWidget(otherUsersLabel);
  mainLayout->addLayout(otherUsersButtons);

  //feed
  mainLayout->addWidget(feedLabel);
  mainLayout->addWidget(feed);

  //mentions feed
  mainLayout->addWidget(mentionsLabel);
  mainLayout->addWidget(mentionsFeed);


  //enter tweet with a textbox
  mainLayout->addWidget(enterTweetLabel);
  //mainLayout->addWidget(newTweet);
  mainLayout->addLayout(textbox);

  //button to view trending tweets
  mainLayout->addWidget(trendingTweets);

  //output area for file
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
  connect(trendingTweets,SIGNAL(clicked()), this, SLOT(trending()) );

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
    (*it)->addTweet(tempTweet);
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

  //now adding implementation to check through all new tweets and add them to the tagsmap

  //go through each of the tweets of the user you are on, find any tags, and add them to the map
  
  std::string tweetString = tempTweet->time().stringTime() + " " + tempTweet->text();

  std::string word;

  std::stringstream ss(tweetString);
  while(ss >> word){
    //theres a tag!!
    if(word[0] == '#'){
      for(unsigned int j = 0; j < word.size()-1; j++){
        word[j] = word[j+1];

      }
      //std::cout<<word;
    //removes the extra character at the end
      word.resize(word.size()-1);


      //iterate through the map to see which tweetswithtags set you will be adding this word into
      for(typename std::map<std::string,std::set<Tweet*> >::iterator it2 = tagsMap.begin(); it2 != tagsMap.end(); ++it2){
        //the word was in the map's keytype, so we'll just add it to the set
        if(word == (*it2).first){
          //add it to this word's set of tweets which will have tags
          (*it2).second.insert(tempTweet);
        }
        //word wasnt found, add it to temporary set to pass into map

      }
        std::set<Tweet*> tweetsWithTags;
        tweetsWithTags.insert(tempTweet);
        tagsMap.insert(std::pair<std::string,std::set<Tweet*> >(word, tweetsWithTags));
    }
  }
      
    
    
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

      otherCombo->clear();

      QString otherUserQ = combo->currentText();
      std::string otherUser = otherUserQ.toStdString();

      std::set<User*>::iterator it3 = users.begin();
      for(it3 = users.begin(); it3 != users.end(); ++it3){
        if((*it)->name() != (*it3)->name()){ 
          QString qstr = QString::fromStdString((*it3)->name());
          otherCombo->addItem(qstr);
        }
      }

      followingList->clear();
      std::set<User*> followingTemp = (*it)->following();



      for(std::set<User*>::iterator it4 = followingTemp.begin(); it4 != followingTemp.end(); ++it4){
        QString qstr = QString::fromStdString((*it4)->name());
        followingList->addItem(qstr);
      }



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

void MainWindow::trending(){

  delete TweetWin;
  //updates the new window with any new tags
  TweetWin = new TweetWindow(users, tagsMap);
  TweetWin->updateWindow();

  TweetWin->show();
}