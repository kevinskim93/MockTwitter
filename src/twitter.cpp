#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <cmath>
#include <exception>
#include <QApplication>
#include <algorithm>
//#include "../include/user.h"
#include "../include/mainwindow.h"

using namespace std;

/*bool checkUsers(char* token, vector<string>& users);
bool checkTags(char* token, vector<string>& tags);
void tagRemove(char* token);
void removePunctuation(char* token);*/

int main(int argc, char *argv[]){

	if (argc != 2){
		cout << "Incorrect number of inputs. Exiting program." << endl;
		return 0;
	}

	char* token;
	char line[300];

	int numUsers = 0;

	ifstream ifile;

	set<User*> usersList;

	vector<string> mentionedName;

	string oFile;

	//Map<string, User*> twitterHandles;
	//AList<string> tweets;

	string iFile;

	iFile = argv[1];

	ifile.open(iFile.c_str());

	if (ifile.fail()) //checks input file
	{
		cout << "Error! Invalid file, exiting." << endl;
		return 0;
	}

	ifile.getline(line,300);
	token = strtok(line, "\n");
	if (token == NULL){
		cout << "There was an empty line. Exiting." << endl;
		return 0;
	}

	int len = strlen(token);
	for (int i = 0; i < len; i++){
		if(!isdigit(token[i])){
			cout << "Error, first line was not an integer." << endl;
		}
	}
	stringstream ss;
	ss << token;
	ss >> numUsers;

	//User* users = new User[numUsers];

	//loop through based on number of users
	for(int i = 0; i < numUsers; i++){		
		//if(token[0] is not a character) error
		ifile.getline(line,300);
		token = strtok(line, " ");
		string tempUsername(token);
		set<User*>::iterator it;
		User* tempUser;
		for(it = usersList.begin(); it != usersList.end(); ++it){
			if ((*it)->name() == tempUsername){
				break;
			}
		}
		
		if(it == usersList.end()){
			tempUser = new User(tempUsername);
			usersList.insert(tempUser);
		}
		else{
			tempUser = *it;
		}

		token = strtok(NULL," ");
		while(token){
			string tempFollowing(token);
			set<User*>::iterator it2;
			for(it2 = usersList.begin(); it2 != usersList.end(); ++it2){
				if ((*it2)->name() == tempFollowing){
					break;
				}
			}
			if(it2 == usersList.end()){
				User* tempFollowingUser = new User(tempFollowing);
				tempUser->addFollowing(tempFollowingUser);
				usersList.insert(tempFollowingUser);

			}
			else{
				tempUser->addFollowing(*it2);
			}
			token = strtok(NULL, " ");

		}	
	}

	//finished parsing the users, now time to read the tweets


	while(ifile.getline(line,300)){ //reading each line, which is a tweet

		if(isalpha(line[0])){
			cout << "Error." << endl;
		}

		stringstream ss;

		token = strtok(line, "-");
		int tempYear;
		
		ss << token;
		ss >> tempYear;
		ss.clear();
		ss.str("");


		token = strtok(NULL, "-");
		int tempMonth;
		
		ss << token;
		ss >> tempMonth;
		ss.clear();
		ss.str("");

		token = strtok(NULL, " ");
		int tempDate;
		
		ss << token;
		ss >> tempDate;
		ss.clear();
		ss.str("");

		token = strtok(NULL, ":");
		int tempHour;
		
		ss << token;
		ss >> tempHour;
		ss.clear();
		ss.str("");

		token = strtok(NULL, ":");
		int tempMinute;
		
		ss << token;
		ss >> tempMinute;
		ss.clear();
		ss.str("");

		token = strtok(NULL, " ");
		int tempSecond;
 
		ss << token;
		ss >> tempSecond;
		ss.clear();
		ss.str("");


		//this token is the username of the person tweeting
		token = strtok(NULL," ");
		string tempName(token);

		bool mentionsFeed1 = false;
		bool mentionsFeed2 = false;

		string tempText = tempName + " ";
		token = strtok(NULL," ");
		if(token[0] == '@'){ //first string is an @ mention
			mentionsFeed1 = true;
			string tempMentionedName(token);
			tempMentionedName.erase(tempMentionedName.begin()); //erases the at sign
			mentionedName.push_back(tempMentionedName);
			token = strtok(NULL," ");
			//cout << "mentioned: " << tempMentionedName << endl;
		}
		while(token){
			if(token[0] == '@'){ //@ mention in the tweet, not the first string
				mentionsFeed2 = true;
				string tempMentionedName(token);
				tempMentionedName.erase(tempMentionedName.begin()); //erases the at sign
				mentionedName.push_back(tempMentionedName);
			}

			string tempToken(token);
			tempText += (tempToken + " ");
			token = strtok(NULL, " ");
		}

		//removes extra space at the end
		if (tempText.size () > 0) {
			tempText.resize (tempText.size () - 1);
		}

		DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);

		for(set<User*>::iterator it3 = usersList.begin(); it3 != usersList.end(); ++it3){
			if((*it3)->name() == tempName){ //finds the user for which the name we are currently on
				Tweet* tempTweet = new Tweet((*it3), tempDateTime, tempText); //makes a new tweet


				if(mentionsFeed1){ //this tweet will enter the mentionsfeed of the user, the tweet had at mentions inside the tweet
					(*it3)->addMentions(tempTweet);
					for(unsigned int i = 0; i < mentionedName.size(); i++){ //search through the temporary mentioned users list
						for(set<User*>::iterator it4 = usersList.begin(); it4 != usersList.end(); ++it4){ //serach through full users list
							
							std::string tempMentionedName = mentionedName[i];
        					std::transform(tempMentionedName.begin(), tempMentionedName.end(), tempMentionedName.begin(), ::tolower);

							string tempstrName = (*it4)->name();
							std::transform(tempstrName.begin(), tempstrName.end(), tempstrName.begin(), ::tolower);
							if(tempMentionedName == tempstrName){ //finds if the name equals the mentioned user then add it to their mentioned feed
								(*it4)->addMentioned(tempTweet);
							}
						}
					}
				}

				else if(mentionsFeed2){
					for(unsigned int i = 0; i < mentionedName.size(); i++){ //search through the temporary mentioned users list
						for(set<User*>::iterator it4 = usersList.begin(); it4 != usersList.end(); ++it4){ //serach through full users list

							std::string tempMentionedName = mentionedName[i];
					        std::transform(tempMentionedName.begin(), tempMentionedName.end(), tempMentionedName.begin(), ::tolower);

							string tempstrName = (*it4)->name();
							std::transform(tempstrName.begin(), tempstrName.end(), tempstrName.begin(), ::tolower);
							if(tempMentionedName == tempstrName){ //finds if the name equals the mentioned user then add it to their mentioned feed
								(*it4)->addMentioned(tempTweet);
							}
						}
					}
					(*it3)->addTweet(tempTweet); //these tweets will still be displayed as main tweets
				}

				else {
					(*it3)->addTweet(tempTweet);
				}
			}
		}

		mentionedName.clear(); //empty the temporary mentioned name list
	}

	/*for(User** d = usersList.first(); d != NULL; d = usersList.next()){
		cout << (*d)->name() << endl;
		Set<User*> test = (*d)->following();

		cout << "following: " ;
		for(User** t = test.first(); t != NULL; t = test.next()){
			cout << (*t)->name() << " " ;
		}
		cout << endl;
		test = (*d)->followers();
		cout << "followers: " ;
		for(User** t = test.first(); t != NULL; t = test.next()){
			cout << (*t)->name() << " " ;
		}
		cout << endl;
	}*/





	ifile.close();

	//done parsing all the data

	/*User** u4;
	for(u4 = usersList.first(); u4 != NULL; u4 = usersList.next()){
		cout << (*u4)->name() << endl;
		for(int i = 0; i < (*u4)->tweets().size(); i++){
			cout << (*(*u4)->tweets().get(i)) << endl;
		}	
	}*/


	//creates output files for each user

	for(typename std::set<User*>::iterator it = usersList.begin(); it != usersList.end(); ++it){
		//oFile = (*it)->name();
		//oFile += ".feed";
		//ofstream ofile(oFile.c_str());
		//ofile << (*it)->name() << endl;
		(*it)->makeFeed();
		(*it)->makeMentionedFeed();
		//int size = (*it)->getFeed().size();
		//for(int i = 0; i < size; i++){
		//	ofile << (*(*it)->getFeed().at(i)) << endl;
		//}
		//ofile.close();
	}



	QApplication app( argc, argv );

	MainWindow mainwin(usersList);
	mainwin.setWindowTitle("Twitter");
	mainwin.show();

	


	/*for(typename std::set<User*>::iterator it = usersList.begin(); it != usersList.end(); ++it){
		for(unsigned int i = 0; i < (*it)->tweets().size(); i++){
			delete (*it)->tweets().at(i);
		}

		for(unsigned int i = 0; i < (*it)->mentionstweets().size(); i++){
			delete (*it)->mentionstweets().at(i);
		}

		delete *it;
	}*/

	
	return app.exec();

	//return 0;

}

