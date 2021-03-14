//
//  spellcheck.cpp
//  SpellCheck
//
//  Created by Allister Liu on 9/19/20.
//

#include "hash.hpp"

using namespace std;

void loadDictionary(const string &dictionaryName, hashTable *Hash);
void spellCheck(const string& inFile, hashTable* Hash, const string& outFile);


int main(){
    hashTable *Hash = new hashTable(500);
    
    string dictionaryName, inFile, outFile;
    cout << "Please enter the name of the dictionary to be used: " << flush;
    cin >> dictionaryName;
    
    clock_t t1 = clock();
    loadDictionary(dictionaryName, Hash);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << timeDiff << "s." << endl;
    //Hash->display();
    
    cout << "Enter name of input file: " << flush;
    cin >> inFile;
    cout << "Enter name of output file: " << flush;
    cin >> outFile;
    
    t1 = clock();
    spellCheck(inFile, Hash, outFile);
    t2 = clock();
    timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to spell-check: " << timeDiff << "s." << endl;
    
    return 0;
}

void loadDictionary(const string &dictionaryName, hashTable *Hash){
    ifstream Dictionary;
    Dictionary.open(dictionaryName);
    
    if(!Dictionary.is_open()){
        cerr << "Error: Failed to open file for reading: " << dictionaryName << " " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    
    string line;
    while(getline(Dictionary, line)){
        //ignores invalid words in the dictionary
        
        for (int i = 0; i < line.size(); i++) {
            if (!(isalnum(line[i]) || line[i] == '-' || line[i] == '\'') || line.size() > 20) {
                //cout << "WARNING: the word '" << line << "' is an invalid word." << endl;
                goto ignore;
            }
        }
        //https://www.tutorialspoint.com/how-to-convert-std-string-to-lower-case-in-cplusplus#:~:text=The%20transform%20function%20takes%20the,string%20into%20a%20lowercase%20string.
        transform(line.begin(), line.end(), line.begin(), ::tolower); //The transform function takes the beginning pointer of the string and the ending pointer of the string. It also takes the beginning of the string to store the result, then the fourth argument is ::tolower.
        Hash->insert(line);
    
    ignore:
        line.clear();
     
    }
    
    Dictionary.close();
}

void spellCheck(const string& inFile, hashTable* Hash, const string& outFile){
    ifstream inputFile;
    inputFile.open(inFile);
    
    if(!inputFile.is_open()){
        cerr << "Error: Failed to open file for reading: " << inFile << " " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    
    ofstream outputFile;
    outputFile.open(outFile);
    
    if(!outputFile.is_open()){
        cerr << "Error: Failed to open file for reading: " << outFile << " " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    
    string word, line;
    word.clear(); line.clear();
    bool containsNum = false;
    char tempChar;
    unsigned long lineNum = 0;
    while(getline(inputFile, line)){
        word.clear();
        ++lineNum;
        for (int i = 0; i <= line.size(); ++i) {
            tempChar = tolower(line[i]);
            
            if(isdigit(tempChar) && !containsNum){
                containsNum = true;
            }
            
            if(isalnum(tempChar) || tempChar == '-' || tempChar == '\''){
                word += tempChar;
                //printf("%d\n", tempChar);
                //cout << word << endl;
                
               }
            else{
                if(!word.empty() && !containsNum){
                    if(word.size() > 20){
                        outputFile << "Long word at line " << lineNum << ", starts: " << word.substr(0, 20) << endl;
                        //cout << "clear string cuz long word." << endl;
                        word.clear(); containsNum = false;      //next word
                    }
                    else if(!Hash->contains(word)){
                        outputFile << "Unknown word at line " << lineNum << ": " << word << endl;
                        //cout << "clear string cuz unknown word." << endl;
                        word.clear(); containsNum = false;  //next word
                    }
                    else{
                        //cout << "clear string cuz continuing" << endl;
                        word.clear(); containsNum = false;  //next word
                    }
                }
                else{
                    //cout << "clear string cuz string empty or contains number." << endl;
                    word.clear(); containsNum = false;  //next word
                }
            }
        }
        line.clear();
    }
    inputFile.close();
    outputFile.close();
}
