# Question-Answering-System

1. Introduction
In this project, we implemented a simple question answering algorithm with
C++. There are 3 different files, questions are in the question.txt file,
the_truman_show_script.txt file is the text we are searching the answers for,
and an answers.txt file which includes the answers of the questions. All
questions have answers.
a. About libraries
#include <iostream>
This library is used for console to work.
#include <fstream>
This library is used for reading the files.
#include <string>
This library is used for parse and other string methods. Because this
algorithm we used includes lots of work with strings.
#include <vector>
This library is used for iterations.
#include <sstream>
This library is used to get words one by one from sentences.
#include <chrono>
This library is used to keep time.
b. About average speed
Usually, the average speed of this algorithm is between 20 – 50
milliseconds.
  c. About average correctness
Without any problems, the algorithm finds the correct answer. Every input
gives the correct output.
2. Explanation of Main Functions
In this algorithm there are multiple functions but there are three main important
functions that includes string matching methods and the complexity. In the
below, these functions are explained.
a. eliminateWords()
This function gets the chosen sentences from the question.txt and
the_truman_show_script.txt file and removes the same words and returns the
parsed sentence. This is algorithm is Brute-Force Algorithm. There are n times of
comparison. And the Big-Oh Complexity is O(n).
In the while loop, this algorithm seperates the question sentences with first
index and last index and in every loop last index and first index are updated due to
the lastoflastindex and firstoffirstindex.
Every word of question is compared with the text sentence to find if the same
word exists or not. If it exists, remove from the text sentence. Else, keep the word
in the sentence. Lastly, parsed of the text sentence is returned.
string eliminateWords(string sntc, string qst){
 int firstIndex = 0;
 int lastOffirstIndex = 0;
 int lastIndex = qst.find(" ");
 int lastOflastIndex = 1;
 string temp;
 bool first = 0;
 if (sntc == "-1") {
 return "-1";
 }
 while (true) {
 temp = qst.substr(firstIndex, (lastIndex - firstIndex));
 if (sntc.find(temp) != -1) {
 if (sntc.find(temp) == 0) {
 sntc.erase(sntc.find(temp), temp.length() + 1);
 }
 else {
 sntc.erase(sntc.find(temp) - 1, temp.length() + 1);
 }
 }
 if (first == 1) {
 first = 0;
 continue;
 }
 lastOffirstIndex = firstIndex; lastOflastIndex = lastIndex;
 lastOffirstIndex++, lastIndex++;
 firstIndex = qst.find(" ", firstIndex) + 1;
 lastIndex = qst.find(" ", lastIndex);
 if (firstIndex == 0) {
 break;
 }
 if (lastIndex == -1) {
 lastIndex = sntc.length();
 }
return sntc
}
b. isWanted()
This function compares the text sentence and finds if the text sentence
includes the answer of question sentence or not. This algorithm is BruteForce Algorithm with Big-Oh complexity of O(n) which depends on the text
sentence. There are n-comparisons.
This function gets the text sentence and question sentence as a parameter.
Firstly, this function finds the every space (“ “) in the text sentence and
for every sentenceSpaceCount increased by one. Then, question sentence are
seperated with firstIndex and lastIndex in the while loop and in every loop
firstIndex and lastIndex are updated so due to that the word is also updated.
Furthermore, if text sentence has the word of question sentence match
count is increased by one.
Lastly, if match count and space count are equal, this text sentence is the
one we are looking for so it is returned.
bool isWanted(string sntc, string qst) {
 int firstIndex = 0;
 int lastIndex = qst.find(" ");
 int matchCount = 0;
 int sentenceSpaceCount = 0;
 int spacePoint = 0;
 string temp;
 bool first = 0;
 while (true) {
 spacePoint = sntc.find(" ", spacePoint);
 if (spacePoint == -1) {
 break;
 }
 spacePoint++;
 sentenceSpaceCount++;
 }
 while (true) {
 temp = qst.substr(firstIndex, (lastIndex - firstIndex));
 //cout << temp << endl;
 if (sntc.find(temp) != -1)
 {
 matchCount++;
 }
 firstIndex++, lastIndex++;
 firstIndex = qst.find(" ", firstIndex) + 1;
 lastIndex = qst.find(" ", lastIndex);
 if (firstIndex == 0) {
 break;
 }
 if (lastIndex == -1) {
 lastIndex = qst.length() - 1;
 }
 }
 if (matchCount == sentenceSpaceCount) {
 return true;
 }
 else {
 return false;
 }
}
c. removeWords()
The purpose of this function is to remove the unwanted words. The
algorithm that is used in this function is Brute-Force Algorithm. And there
n^2 comparisions because for every word of the text sentence we compare
the every word that is included in “stop_words_english.txt” file. The Big-Oh
Complexity is O(n^2).
This function removes the unwanted words and send them to the
filterStopWords function with the help of the sstream library.
filterStopWords function opens a file called “stop_words_english.txt” which
includes the unwanted words and puts them into a vector.
Owing to this vector, iterations are occured and if the word we have is in
the stop words, this word is assigned to null. Lastly, the function removes
the unwanted word from the sentence without making any returns because it
works with reference.
void filterStopWords(std::string& str) {
 string lineread;
 ifstream sw("stop_words_english.txt");
 vector<string>stopwords;
 string stop;
 if (!sw.is_open()) {
 cerr << "Could not open the file - '"<<endl;
 }
 while (getline(sw, stop)) {
 stopwords.push_back(stop);
 }
 sw.close();
 vector<string>::iterator itrStop;
 std::string buff;
 for (itrStop = stopwords.begin(); itrStop < stopwords.end(); itrStop++) {
 if (*itrStop == str) {
 str = "";
 }
 }
}
string removeWords(string str){
 istringstream ss(str);
 string word;
 string temp="";
 while (ss >> word){
 filterStopWords(word);
 if (word != "") {
 temp = temp + word + " ";
 };
 };
 temp.erase(temp.find_last_of(' ') , 1);
 return temp;
}
