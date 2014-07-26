##CSCI 104 Project Repository

###Student Information
  + Name: Kevin Kim
  + USC Email: kevinsk@usc.edu
  + USC ID: 5680658336

###Project Description
This is part 3 of the Twitter project. It will read in a file of tweets, as well as information as to which users are following which users, and how mnay users there are. Then it will create output files for each user and their feed, based on who they are following and what their followers tweeted. This part will also include a thorough qt implementation of twitter.

This part includes the popular tweets portion of the assignment. The user can select if he or she wants to view the most popular tweets of all time, or in the past day.

Also, heapsort is implemented into the sorting of the popularity of the tweets in the tweetwindow.cpp file, using the functions makeHeap and heapsort. I use a comparator to compare the size of the sets which store the tweets.
This implementation can be found in two parts of the refresh() function in tweetwindow.cpp

Also, to test the heapsort algorithm on its own, I have included a heapsort directory, with the heapsort.h implementation as well as a file called heapsort.cpp, which is basically a test case of the heapsort in action.

Also, there is a QLabel that will update "Number of Occurences" which basically counts how many tweets there are per tag. This implementation is to make it easy to grade and count and verify that the number of tweets for each tag is accurate and in the correct order.


###Compile & Run Instructions
To compile this problem, run the following commands after cloning the repository
```bash
cd proj_kevinsk
make
```

The problem requires 1 argument
```bash
./proj_kevinsk twitter.dat
```