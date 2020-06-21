// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include "testing/SimpleTest.h"
#include "map.h"
#include "set.h"
#include <string>
#include <iostream>
#include "filelib.h"
#include <fstream>
#include "simpio.h"
#include "strlib.h"
#include "stack.h"
#include "search.h"

#include <set>
#include <map>
#include<vector>

using namespace std;

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Map<string, Set<string>> readDocs(string dbfile)
{
    Map<string, Set<string>> result;
    // TODO: your code here
    // this function should open named file read it line by line and build a map from URL
    // to a set<string> representing the uniques words contained on that page
    ifstream infile;
    infile.open(dbfile);

    if(!infile){
        cerr<<"Could not find this file.";
        exit(1);
    }
    string line;
    int string_number=0;
    string set_key;
    Set<string> set_value;
    while(getline(infile,line))
    {
        //string_number++;
        if(string_number % 2 == 0){
            // this line belongs to a "website string" line
            set_key = line;
            set_value.clear();
            string_number++;
        }
        else
        {
            Vector<std::string> vec=stringSplit(line,' '); // vec is a vector which contains several words
            //Vector<string> temp_vec;
            // the preprocessing for each vector element begins here
            for (auto it=vec.begin();it!=vec.end();it++)
            {
                string s=*it; // iterate over the vector
                int occurance=0;

                for(int i=0; i<s.length();i++)
                {

                    if(isalpha(s[i]))
                    {
                        s[i]=tolower(s[i]);
                        occurance++;
                    }
                }
                // there is at least one letter in this vector element

                if (occurance!=0)
                {
                    string new_string;
                    int pos1=0;
                    int pos2=s.length()-1;
                    for(int i=0;i!=s.length();i++){
                        if(!ispunct(s[i])){
                            pos1=i;
                            break;
                        }
                    }
                    for(int j = s.length()- 1; j > - 1 ;j--){
                        if(!ispunct(s[j])){
                            pos2=j;
                            break;
                        }
                    }
                    new_string=s.substr(pos1,pos2-pos1+1);
                    set_value.add(new_string);
                    result.add(set_key,set_value);
                }
            }
            string_number++;
        }
    }
    infile.close();
    return result;
}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Map<string, Set<string>> buildIndex(Map<string, Set<string>>& docs)
{
    // inverted index creates a mapping from content to locations in a document
    // parameter string : website set<string> : dictionary,which contains kinds of words
    Map<string, Set<string>> result;
    Map<string,Set<string>> copy=docs;
    // TODO: your code here
    string words;

    // iterate over the map docs get the value
    // iterate over the value and put its key into set
    // return the result

    while(!copy.isEmpty()){
        string first_key=copy.front(); // first key in the map
        Set<string> first_value=copy.get(first_key); // first Value in the map
        while ( !first_value.isEmpty() )
        {
            words= first_value . first();
            result [words].add( first_key );
            first_value.remove( words) ;
        }
        copy.remove(first_key);
   }
    return result;
}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    // TODO: your code here
    // the query string can either be a single search term or a compound sequence of multiple terms

    Stack<Set<string>> result_stack;

    string s=query;
    int occurance=0;

    for(int i=0; i<s.length();i++)
    {
        if(isalpha(s[i]))
        {
            s[i]=tolower(s[i]);
            occurance++;
        }
    }
    // there is at least one letter in this vector element

    if (occurance!=0)
    {
        string new_string;
        int pos1=0;
        int pos2=s.length()-1;
        for(int i=0;i!=s.length();i++){
            if(!ispunct(s[i])){
                pos1=i;
                break;
            }
        }
        for(int j = s.length()- 1; j > - 1 ;j--){
            if(!ispunct(s[j])){
                pos2=j;
                break;
            }
        }
        s=s.substr(pos1,pos2-pos1+1);
    }

    Vector<std::string> vec=stringSplit( s , ' ' );

    for(int i=0;i<vec.size();i++){

        string key_word=vec[i];

        if(key_word.find('+')==string::npos && key_word.find('-')==string::npos)

        {
            Set<string> key_value=index.get(key_word);

            if(result_stack.isEmpty())
            {
                result_stack.push(key_value);
            }
            else{
                Set<string> previous_web = result_stack.pop( );
                result_stack.push( previous_web + key_value);
            }
        }

        else if( key_word.find('-') != string::npos )
        {
            // the website which contains previous word minus the website which does
            // contain "-"

            Set<string> previous_web = result_stack.pop( );
            key_word = key_word.substr( key_word.find( '-' )+1, string::npos-key_word.find( '-' ) );
            Set<string> to_be_substratec_web = index.get( key_word) ;
            result_stack.push( previous_web - to_be_substratec_web );

        }
        else if( key_word.find('+') != string::npos )
        {
            Set<string> previous_web = result_stack.pop( );
            key_word = key_word.substr( key_word.find( '+' )+1, string::npos-key_word.find( '+' ) );
            Set<string> to_be_intersected_web = index.get( key_word) ;
            result_stack.push( previous_web * to_be_intersected_web );
        }
    }

    result=result_stack.pop();

    return result;

}

// TODO: Add a function header comment here to explain the 
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile)
{
    // TODO: your code here
    Map <string , Set<string>> map = readDocs(dbfile);
    // map is a mapping from website to dictionary
    Map <string, Set<string>> inverted= buildIndex(map);
    // index is a mapping from word to websites

    cout<<"Stand by while building index..."<<endl;
    cout<<"Indexed "<<map.size()<<"pages " << "containing " << inverted.size() << " unique terms."<<endl;
    while(true)
    {
        cout<<endl<<endl<<"Enter query sentence (RETURN/ENTER to quit): ";
        string query;
        while(cin>>query)
        {
            if(query==""){
                cout<< "All done!";
                break;
            }
            else{
                Set<string> found_match=findQueryMatches(inverted,query);
                cout<<"Found "<< found_match.size() << " matching pages"<<endl;
                while(!found_match.isEmpty())
                {
                    string str=found_match.back();
                    cout<< str <<" , ";
                    found_match.remove(str);
                }
            }

        }

    }

}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("readDocs from tiny.txt, contains 4 documents") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    EXPECT_EQUAL(docs.size(), 4);
}

PROVIDED_TEST("readDocs from tiny.txt, suess has 5 unique words and includes lowercase fish") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Set<string> seuss = docs["www.dr.seuss.net"];


    EXPECT_EQUAL(seuss.size(), 5);
    EXPECT(seuss.contains("fish"));
    EXPECT(!seuss.contains("Fish"));


}
PROVIDED_TEST("readDocs from tiny.txt, bigbadwof has 6 unique words and includes lowercase i'm") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");

    Set<string> bigbadwolf=docs["www.bigbadwolf.com"];

    EXPECT_EQUAL(bigbadwolf.size(),6);
    EXPECT(bigbadwolf.contains("i'm"));
    //EXPECT(!bigbadwolf.contains())

}

PROVIDED_TEST("buildIndex from tiny.txt, 20 unique tokens overall") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    EXPECT_EQUAL(index.size(), 20);
    EXPECT(index.containsKey("fish"));
    EXPECT(!index.containsKey("@"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 20 unique tokens overall") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    EXPECT_EQUAL(index.size(), 20);
    EXPECT(index.containsKey("you"));
    EXPECT(index["blue"].contains("www.rainbow.org"));
    EXPECT(!index.containsKey("@"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> docs = readDocs("res/tiny.txt");
    Map<string, Set<string>> index = buildIndex(docs);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 3);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here


