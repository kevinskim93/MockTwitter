#include "../include/tweetwindow.h"

TweetWindow::TweetWindow(){


}

TweetWindow::TweetWindow(std::set<User*>& u, std::map<std::string,std::set<Tweet*> >& tm) : users(u), tagsMap(tm){
	setGeometry( 0, 0, 700, 500 );
	alltimeorToday = new QComboBox;
	alltimeorToday->addItem("All Time");
	alltimeorToday->addItem("Past Day");

	it = tagsMap.begin();

	refreshBtn = new QPushButton(tr("&Refresh"));

	lastUpdatedLabel = new QLabel;
	
	//sets the time when you open the window
	time_t t = time(0);   // get time now
	struct tm * now = localtime( &t );
	int tempYear = (now->tm_year + 1900);
	int tempMonth = (now->tm_mon + 1);
	int tempDate = now->tm_mday;
	int tempHour = now->tm_hour;
	int tempMinute = now->tm_min;
	int tempSecond = now->tm_sec;
	     

	DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);

	std::string itIsNow("It is now: ");
	std::string thisTime(tempDateTime.stringTime());
	std::string combine = itIsNow + thisTime;
	QString qstringTime = QString::fromStdString(combine);
	lastUpdatedLabel->setText(qstringTime);

	//if the user selects to only view the last 24 hours

	QString QtimeText = alltimeorToday->currentText();
  	std::string timeText = QtimeText.toStdString();


	//creates the selection between today, or all time, and the refresh button
	QHBoxLayout * selectTimeandRefresh = new QHBoxLayout;
	selectTimeandRefresh->addWidget(alltimeorToday);
	selectTimeandRefresh->addWidget(refreshBtn);
	selectTimeandRefresh->addWidget(lastUpdatedLabel);

	

	//creates the tags that were found
	theTags = new QListWidget;

	for(it = tagsMap.begin(); it != tagsMap.end(); ++it){
		std::string tweetString = (*it).first; 
    	QString qstr = QString::fromStdString(tweetString);
  		theTags->addItem(qstr);
	}

	//creates the tweets with the tag you select
	theTweets = new QListWidget;

	//lets make some labels
	selectTime = new QLabel("Select Time:");
	trendingTweetsLabel = new QLabel("Trending Tags:");
	theseTweetsLabel = new QLabel("These Tweets Have the Tag:");
	tagsizeLabel = new QLabel("Number of Occurences: 0");


	QVBoxLayout * mainLayout = new QVBoxLayout;

	//select time label and layout for the combobox and refresh btn
	mainLayout->addWidget(selectTime);
	mainLayout->addLayout(selectTimeandRefresh);

	mainLayout->addWidget(trendingTweetsLabel);
	mainLayout->addWidget(theTags);

	mainLayout->addWidget(tagsizeLabel);

	mainLayout->addWidget(theseTweetsLabel);for(it = tagsMap.begin(); it != tagsMap.end(); ++it){
		std::string tweetString = (*it).first; 
    	QString qstr = QString::fromStdString(tweetString);
  		theTags->addItem(qstr);
	}
	mainLayout->addWidget(theTweets);
	

	QWidget * centWidget = new QWidget(this);
  	centWidget->setLayout(mainLayout);
  	this->setCentralWidget(centWidget);


  	connect(alltimeorToday, SIGNAL(activated(const QString&) ), this, SLOT (chooseTime() ) );
  	connect(refreshBtn,SIGNAL(clicked()), this, SLOT(refresh()) );


  	connect(theTags, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseTag(QListWidgetItem*)) );


}

void TweetWindow::chooseTag(QListWidgetItem* item){

	theTweets->clear();
	//tagsizeLabel->clear();

	for(typename std::map<std::string, std::set<Tweet*> >::iterator it2 = tagsMap.begin(); it2 != tagsMap.end(); ++it2){
			
		QString qstr = item->text();
 		std::string str = qstr.toStdString();	
 		//finds which key you have just clicked!!
		if((*it2).first == str){
			it = it2;
		}
	}

	//how you do this part will depend on if you are looking at all time or just 24 hours
	QString QtimeText = alltimeorToday->currentText();
  	std::string timeText = QtimeText.toStdString();

  	//going to only consider tweets from the past 24 hours
	if(timeText == "Past Day"){
		time_t t = time(0);   // get time now
		struct tm * now = localtime( &t );
		int tempYear = (now->tm_year + 1900);
		int tempMonth = (now->tm_mon + 1);
		int tempDate = now->tm_mday;
		int tempHour = now->tm_hour;
		int tempMinute = now->tm_min;
		int tempSecond = now->tm_sec;
		     

		DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);

		DateTime dayAgo(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate-1);
		//std::cout <<tempDate-1;

		Tweet tempTweet(dayAgo);
		int count = 0;

		for(typename std::set<Tweet*>::iterator it3 = (*it).second.begin(); it3 != (*it).second.end(); ++it3){
			if((**it3) > tempTweet){
				std::string tweetString = (*it3)->time().stringTime() + " " + (*it3)->text(); 
		        QString qstr = QString::fromStdString(tweetString);
		        count++;
				theTweets->addItem(qstr);
			}
		}

		std::stringstream ss;
		std::string love;
		ss << count;
		ss >> love;

		std::string tagSize = std::string("Number of Occurences: ") + love;
		QString qSize = QString::fromStdString(tagSize);
		tagsizeLabel->setText(qSize);



	}



	//going to consider all tweets in history
	else{
		for(typename std::set<Tweet*>::iterator it3 = (*it).second.begin(); it3 != (*it).second.end(); ++it3){
			std::string tweetString = (*it3)->time().stringTime() + " " + (*it3)->text(); 
	        QString qstr = QString::fromStdString(tweetString);

			theTweets->addItem(qstr);
		}

		std::stringstream ss;
		std::string love;
		ss << (*it).second.size();
		ss >> love;

		std::string tagSize = std::string("Number of Occurences: ") + love;
		QString qSize = QString::fromStdString(tagSize);
		tagsizeLabel->setText(qSize);

	}
}

void TweetWindow::refresh(){


	time_t t = time(0);   // get time now
	struct tm * now = localtime( &t );
	int tempYear = (now->tm_year + 1900);
	int tempMonth = (now->tm_mon + 1);
	int tempDate = now->tm_mday;
	int tempHour = now->tm_hour;
	int tempMinute = now->tm_min;
	int tempSecond = now->tm_sec;
	     

	DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);

	DateTime dayAgo(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate-1);
	//std::cout <<tempDate-1;

	Tweet tempTweet(dayAgo);

	std::string itIsNow("It is now: ");
	std::string thisTime(tempDateTime.stringTime());
	std::string combine = itIsNow + thisTime;
	QString qstringTime = QString::fromStdString(combine);
	lastUpdatedLabel->setText(qstringTime);

	//if the user selects to only view the last 24 hours

	QString QtimeText = alltimeorToday->currentText();
  	std::string timeText = QtimeText.toStdString();

  	theTags->clear();

	if(timeText == "Past Day"){
	
		//only add the tweets that are within 24 hrs of the current time
		for(typename std::map<std::string, std::set<Tweet*> >::iterator it2 = tagsMap.begin(); it2 != tagsMap.end(); ++it2){
			int count = 0;
			for(typename std::set<Tweet*>::iterator it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3){
				//std::cout<<(**it3)<<std::endl;
				if((**it3) > (tempTweet)){
					bool entered = false;
					for(int i = 0; i < theTags->count(); i++){
						std::string itemstring = theTags->item(i)->text().toStdString();
						if(itemstring == (*it2).first){
							entered = true;
							break;
						}
						//theTags->addItem(QString::fromStdString((*it2).first));
						
					}
					if(!entered) {
						theTags->addItem(QString::fromStdString((*it2).first));
						break;
					}
				}
				count++;
			}

		}
	}

	//selected to view from all time
	else{
		
		std::vector<std::pair<std::string,int> > tweetlist;
		for(typename std::map<std::string, std::set<Tweet*> >::iterator it2 = tagsMap.begin(); it2 != tagsMap.end(); ++it2){
			tweetlist.push_back(std::pair<std::string,int>((*it2).first, (*it2).second.size()));
		}

		//IMPLEMENTATION OF HEAPSORT ALGORITHM
		OccurenceComp comp;
		makeHeap(tweetlist, comp);
		heapsort(tweetlist, comp);

		for(unsigned int i = 1; i < tweetlist.size(); i++){
			std::string tweetString = tweetlist[i].first;
			QString qstr = QString::fromStdString(tweetString);
			theTags->addItem(qstr);
		}

		/*for(typename std::map<std::string, std::set<Tweet*> >::iterator it2 = tagsMap.begin(); it2 != tagsMap.end(); ++it2){
			std::string tweetString = (*it2).first; 
    		QString qstr = QString::fromStdString(tweetString);
  			theTags->addItem(qstr);
		}*/

	}


}

void TweetWindow::updateWindow(){

	refresh();
	tagsizeLabel->setText("Number of Occurences: 0");
	theTweets->clear();
	QString qstr = alltimeorToday->currentText();
  	std::string str = qstr.toStdString();

}

void TweetWindow::chooseTime(){

	updateWindow();
}

void collectTags(){


}