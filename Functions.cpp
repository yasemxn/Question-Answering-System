#include "Functions.h"

string lowerCase(string s) {  ///lowerCase 
	for (int a = 0; a < s.length(); a++) {
		if (int(s[a] >= 65) && int(s[a] <= 90)) {
			s[a] = char(int(s[a]) + 32);
		}
	}
	return s;
}

void startAlgorithm(){
	string line, temp, text,temp1;
	fstream file;
	int counter = 0;
	int i = 1;
	file.open("questions.txt");
	text = getAllText(); //getting all questions from text
	cout << endl;
	cout << endl;
	while (counter != 8)
	{
		getline(file, line);
		temp = line;
		temp = lowerCase(temp); // turning lower case
		temp = clearSentence(temp);
		temp1 = getSentenceFromTruman(text, temp);
		cout << i << ")" << line << endl; 
		cout << "->" << clearSentence(eliminateWords(temp1, temp)) << endl;
		counter++;
		i++;

	}
	file.close();
	cout << endl;
	cout << "End Of Program." << endl;
	cout << endl;
}

string getAllText()
{
	string line, temp, temp1;
	fstream file;
	file.open("the_truman_show_script.txt");
	while (!file.eof()) {
		getline(file, line);  //get all words from truman
		temp1 = line;
		temp = lowerCase(temp) + lowerCase(temp1); // all word turning lowercase and added to temp
	}
	file.close();
	return temp; //return all text 
}




void filterStopWords(std::string& str) {
	string lineread;
	ifstream sw("stop_words_english.txt");
	vector<string>stopwords;
	string stop;
	if (!sw.is_open()) {
		cerr << "Could not open the file - '"<<endl;
	}
	while (getline(sw, stop)) {
		stopwords.push_back(stop); //push stop words to vector
	}
	sw.close();
	vector<string>::iterator itrStop;
	std::string buff;
	for (itrStop = stopwords.begin(); itrStop < stopwords.end(); itrStop++) {
		if (*itrStop == str) { //compare the word with stopwords
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
		temp = qst.substr(firstIndex, (lastIndex - firstIndex)); // getting word from question
		if (sntc.find(temp) != -1) {
			if (sntc.find(temp) == 0) { //remove from beginng
				sntc.erase(sntc.find(temp), temp.length() + 1);
				//cout << sntc << endl;
				//cout << "********" << endl;
				
			}
			else {

				sntc.erase(sntc.find(temp) - 1, temp.length() + 1);//remove from inner or last
				//cout << sntc << endl;
				//cout << "----" << endl;
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
	}

	return sntc;
}

string getSentenceFromTruman(string txt, string q) {
	int firstDot, lastDot, firstIndex = 0;
	string lastWord = q, sentence, text = txt;
	lastWord = lastWord.erase(0, lastWord.find_last_of(' ') + 1); 

	while (true) {
		firstIndex = txt.find(lastWord, firstIndex);
		if (firstIndex == -1) {
			return "-1"; //no sentence
		}
		firstDot = firstIndex;
		while (txt[firstDot] != '.') {
			firstDot--;
			if (firstDot <= 0) { // right to left
				firstDot = 0;
				break;
			}
		}
		lastDot = firstIndex;
		while (txt[lastDot] != '.') { //left to right
			lastDot++;
		}

		sentence = txt.substr(firstDot, lastDot - firstDot);


		sentence = clearSentence(sentence);



		if (isWanted(sentence, q)) {
			return sentence;
		}
		else {
			firstIndex++;
		}
	}
}

string clearSentence(string sentence) {
	string temp = sentence;
	int a;

	//remove last un letter char
	while (!(int(temp[0]) >= 97 && int(temp[0]) <= 122) && !(int(temp[0]) >= 48 && int(temp[0]) <= 57)) {
		temp = temp.substr(1, temp.length() - 1);
	}
	a = temp.length();
	while (!(int(temp[a - 1]) >= 97 && int(temp[a - 1]) <= 122) && !(int(temp[a - 1]) >= 48 && int(temp[a - 1]) <= 57)) {
		temp = temp.substr(0, temp.length() - 1);
		a = temp.length();
	}
	for (int i = 0; i < sentence.length(); i++) {
		if (sentence[i] == ',') {
			sentence.erase(i, 1);
		}
	}
	temp = removeWords(temp); // remove dont want worsd from sentence
	return temp;
}

bool isWanted(string sntc, string qst) {
	int firstIndex = 0;
	int lastIndex = qst.find(" ");
	int matchCount = 0;
	int sentenceSpaceCount = 0;
	int spacePoint = 0;
	string temp;
	bool first = 0;
	//cout << sntc << endl;
	while (true) {// scaning begins
		spacePoint = sntc.find(" ", spacePoint);

		if (spacePoint == -1) {//end of sentence
			break;
		}
		spacePoint++;
		sentenceSpaceCount++; //findg total spaces
	}
	while (true) {
		temp = qst.substr(firstIndex, (lastIndex - firstIndex)); //getting words
		//cout << temp << endl;
		if (sntc.find(temp) != -1)//compaire question words and sentence word
		{
			matchCount++; //if question and sentece has same word match count ++
		}
		firstIndex++, lastIndex++; //if the words are not same move from left to right
		firstIndex = qst.find(" ", firstIndex) + 1; //getting new indexes

		lastIndex = qst.find(" ", lastIndex);

		if (firstIndex == 0) { //end of sentence
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




