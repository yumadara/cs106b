// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "stack.h"
#include "queue.h"
#include "lexicon.h"
using namespace std;
void print_solution(const string filename,const string word1,const string word2){
    ifstream in;
    in.open(filename);
    if(!in){
        cerr<<"Could not find the file '"+filename+" '";
        //exit(1);
    }

    if(word1==word2){
        error("The two words must be different");
    }
    if (word1.length()!=word2.length()){
        error("The two words must be the same length.");
        //exit(1);
    }

    Lexicon dict=Lexicon(filename);
    if(dict.contains(word1) && dict.contains(word2)){

    }
    else{
        error("The two words must be found in the dictionary.");
    }




}
int main() {
    // TODO: Finish the program!
    cout<<"Welcome to CS106B Word Ladder."<<endl;
    cout<<"Please give me two English word, and I will change the "<<endl;
    cout<<"first into the second by changing one letter at a time."<<endl;

    cout<<"DIctionary file name?"<<endl;
    string filename;
    cin>>filename;
    cout<<endl;
    cout<<"Word #1 (or Enter to quit): ";
    string word1;
    //cin>>word1;
    while(getline(cin,word1)){
      if(word1.empty()){
          break;
      }
    }
    cout<<endl;
    cout<<"Word #2 (or Enter to quit): ";
    string word2;
    cin>>word2;
    while(getline(cin,word2)){
      if(word2.empty()){
          break;
      }
    }
    cout<<endl;
    cout<<"A ladder from data back to code:"<<endl;

    cout << "Have a nice day." << endl;
    return 0;
}
