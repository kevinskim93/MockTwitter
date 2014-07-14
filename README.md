##CSCI 104 Project Repository

###Student Information
  + Name: Kevin Kim
  + USC Email: kevinsk@usc.edu
  + USC ID: 5680658336

###Project Description
This is part 2 of the Twitter project. It will read in a file of tweets, as well as information as to which users are following which users, and how mnay users there are. Then it will create output files for each user and their feed, based on who they are following and what their followers tweeted. This part will also include a thorough qt implementation of twitter.


###Compile & Run Instructions
To compile this problem, run the following commands after cloning the repository
```bash
cd proj_kevinsk
qmake -project
qmake
make
```

The problem requires 1 argument
```bash
./proj_kevinsk twitter.dat
```