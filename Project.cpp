#include <iostream>
#include <map>
#include <fstream>
#include <string>

// ======= INSPIRATION BIRD ======== (to inspire you to do better)
//        _ _.-''''''--._
//      .` `.  ...------. - Do better, pl0x. (Inspiration Bird, 2014)      
//     / |O :-`   _,.,---'
//    '      ;--''
//    | _.' (
//    ,' _,' `-.
//    : /       '.
//    |           '
//     `.|         `.
//       `-._	      .
/*           '.  ,-.   .
 .__          _`. ..` 	.
  ,  ''- . _,-'.,-'  ``: .
  '-...._ (( (('-.._    . .
         `--..      `'-. . .
              `..     '   . .
                 `         `"
                    

   ======= INSPIRATION BIRD ========


   ======= PROJECT =================

   Three objectives:
   -Retrieve most frequently used words from a data set (not including stop words defined in "stop.txt"). 
   This means take a frequency count for each word in a data set and report the top 5% in a file "report.txt".

   -Compute the percentage of stop words.

   -Print out all the words within each data set (using dictionary ordering). Provide number of occurrences 
   within a data set (including stop words). 

   ======= PROJECT =================
*/   
using namespace std;

/*
  ===== is_stopWord =====
  Checks if string s is a member of the stopWords list.
 */
bool is_stopWord( const string& s, const map<string,int> &stopWords ) {
  bool is_sWord = true;
  if(stopWords.find(s)==stopWords.end())
    is_sWord=false;
  //if( is_sWord == true ) cout << "FOUND STOP WORD!!" << endl;
  return is_sWord;
}

/* 
   ===== strip_punc ======
   Strips punctuation from the word, if any.
   And lowercase entire word
*/
void strip_punc( string& s ) {
  if( s[0] % 'A' > 25 && s[0] % 'a' > 25 ) s.erase(0,1);
  if( s[0] % 'A' > 25 && s[0] % 'a' > 25 ) s.erase(0,1);
  if( s[s.size() - 1] % 'A' > 25 && s[s.size() - 1] % 'a' > 25 ) s.erase(s.size()-1,1);
  if( s[s.size() - 1] % 'A' > 25 && s[s.size() - 1] % 'a' > 25 ) s.erase(s.size()-1,1);
  s[0]=tolower(s[0]);
  //cout << "stripping: " << s << endl;
}

// =========== main =============

int main(int argc,char *argv[]){
  int unique=0; //count of total unique words
  int total=0; //total number of words
  int stop=0; //number of stop words
  string title,buffer; //title name,standard string buffer
  map<string,int> stopWords; //dict holding stop words

  // ============ Setting up a dictionary of stop words from "stop.txt" =======
  fstream stopFile( "stop.txt", ios::in );
  
  if( stopFile.is_open() ) {
    int stopIter = 0;
    while( getline( stopFile, buffer, '\n' ) ) {
      stopWords.insert(pair<string,int>(buffer,0));
      stopIter++;
    }
  }
  stopFile.close();

  // ========= Filling dictionary ============
  map<string,int> dict; //DICTIONARY

  // argv[0] should be the name of the file being analyzed
  fstream dictFile( argv[1] , ios::in );
  string entry; // Variable for each individual name in buffer

  if( dictFile.is_open() ) {
    while( getline( dictFile, buffer ) ) {
      //Find a better way to do this
      //Filter out the <TITLE> lines
      if( buffer.substr( 0, 1 ) == "<" ) { 
	title = buffer.substr( 8, buffer.size() - 16 ); //title is located between the 8th character from the start and the 9 character from the end
	cout << "Title: " << title << endl;
      }
      //If not a <TITLE> line, parse through the line regularly
      else {
	for( int dictIter = 0; dictIter != string::npos; dictIter=buffer.find(' ',dictIter)+1) { 
	  
	  //If the loop hasn't reached the last word, take the next word in the line.
	  if( buffer.find(' ',dictIter) != string::npos ) {
	    entry = buffer.substr( dictIter, buffer.find(' ',dictIter) - dictIter );
	  }
	  else { //Else, take the last word.
	    entry = buffer.substr( dictIter, buffer.size() - dictIter );
	    break; //kinda makes the break condition for the for-loop useless, but whatever
	  }

	  //Strip any punctuation
	  strip_punc(entry);
	  
	  //Check if a stopWord or not
	  if( !(is_stopWord( entry, stopWords )) ) { 


	    //If the entry doesn't exist in the map, create a new entry (map a new key)
	    if( dict.find( entry ) == dict.end() ) {
	      dict[entry] = 1;
	      unique++; //Although, I disregarded the number of unique stopWords. Idk if you want that.
	    }
	    else { //Else, increment the frequency count associated with that existing entry/key.
	      dict[entry]+=1;
	    }
	  }
	  //If it is a stopWord, increment stopWord count.
	  else {
	    stop++;
	    stopWords[entry]+=1;
	  }
	  total++;
	}
      }
    }
  }
  dictFile.close();

  cout << "Number of stop words: " << stop << endl;
  cout << "Number of unique words: " << unique << endl;
  cout << "Number of words in total: " << total << endl;

  //part 3 printing out all words including occurances
  string dbWord,sWord;
  auto stopIter=stopWords.begin();
  auto dictIter=dict.begin();
  float stopCount,totalCount;
  
  while (dictIter!=dict.end() && stopIter!=stopWords.end()){
    if(stopIter==stopWords.end()){
      cout<<dictIter->first<<"DD"<<dictIter->second<<endl;
      dictIter++;
    }
    else if(dictIter!=dict.end() && (dictIter->first).compare(stopIter->first)>0){
      if(stopIter->second>0)
	cout<<stopIter->first<<"SS"<<stopIter->second<<endl;
      stopIter++;
    }
    else{
      cout<<dictIter->first<<"DD"<<dictIter->second<<endl;
      dictIter++;
    }
  }
  
  //part 2 calculate percent are stop words
  cout<<(float(stop)/total)*100<<"% are stop words"<<endl;
  
  return 0;
}

