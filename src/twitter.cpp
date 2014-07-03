#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <cmath>
#include <exception>
#include "../include/user.h"

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

	Set<User*> usersList;

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
		User** u;
		User* tempUser;
		for(u = usersList.first(); u != NULL; u = usersList.next()){
			if ((*u)->name() == tempUsername){
				while(usersList.next()){
					}
				break;
			}
		}
		
		if(u == NULL){
			tempUser = new User(tempUsername);
			usersList.add(tempUser);
		}
		else{
			tempUser = *u;
		}

		token = strtok(NULL," ");
		while(token){
			string tempFollowing(token);
			User** u2;
			for(u2 = usersList.first(); u2 != NULL; u2 = usersList.next()){
				if ((*u2)->name() == tempFollowing){
					while(usersList.next()){
					}
					break;
				}
			}
			if(u2 == NULL){
				User* tempFollowingUser = new User(tempFollowing);
				tempUser->addFollowing(tempFollowingUser);
				usersList.add(tempFollowingUser);

			}
			else{
				tempUser->addFollowing(*u2);
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


		string tempText;
		token = strtok(NULL," ");
		while(token){
			string tempToken(token);
			tempText += (tempToken + " ");
			token = strtok(NULL, " ");
		}

		//removes extra space at the end
		tempText.pop_back();

		DateTime tempDateTime(tempHour, tempMinute, tempSecond, tempYear, tempMonth, tempDate);
		User** u3;
		for(u3 = usersList.first(); u3 != NULL; u3 = usersList.next()){
			if((*u3)->name() == tempName){
				Tweet* tempTweet = new Tweet((*u3), tempDateTime, tempText);
				//cout << *tempTweet << endl;
				(*u3)->addTweet(tempTweet);
			}
		}

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

	while(usersList.next()){

	}

	/*User** u4;
	for(u4 = usersList.first(); u4 != NULL; u4 = usersList.next()){
		cout << (*u4)->name() << endl;
		for(int i = 0; i < (*u4)->tweets().size(); i++){
			cout << (*(*u4)->tweets().get(i)) << endl;
		}	
	}*/


	

	User** u;
	for(u = usersList.first(); u != NULL; u = usersList.next()){
		oFile = (*u)->name();
		oFile += ".feed";
		ofstream ofile(oFile.c_str());
		ofile << (*u)->name() << endl;
		int size = (*u)->getFeed().size();
		for(int i = 0; i < size; i++){
			ofile << (*(*u)->getFeed().get(i)) << endl;
		}
		ofile.close();
	}

	return 0;

}

/*bool checkUsers(char* token, vector<string>& users){

	for (unsigned int i = 0; i < users.size(); i++){
		if (token == users[i]){
			return false;
		}
	}

	return true;

}

bool checkTags(char* token, vector<string>& tags){

	for (unsigned int i = 0; i < tags.size(); i++){
		if (token == tags[i]){
			return false;
		}
		
	}

	return true;


}

void tagRemove(char* token){

	int length = strlen(token);

	for (int i = 0; i < (length); i ++){
		token[i] = token[i+1];
	}


}

void removePunctuation(char* token){ //removes any punctuation that may occur after a username or hashtag


	int length = strlen(token);
	int stopIndex = length;

	for (int p = 0; p < length; p++){ //checks the entire string for any symbol

		if (!isalnum(token[p])){
			stopIndex = p; //index value of symbol character
			break;
		}

	}

	for (int a = length; a >= stopIndex; a--){ //makes each character a null char to store into the string
		token[a] = '\0';

	}


	int lastChar = strlen(token);
	lastChar--; //index value of the last character, neglecting the null char

	if (!isalnum(token[lastChar])){ // if last character is punctuation, we will replace that with a null char

		token[lastChar] = '\0';


	}*/
//}

