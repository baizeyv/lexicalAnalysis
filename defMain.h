#pragma once

/**
 * Author: baizeyv
 * Date: 2021-06-12
 * Mail: baizeyv@Gmail.com
 * Link: occs.cc
 * Github: Github.com/baizeyv
 */

#include <cstdlib> // c standard library
#include <fstream> // file stream component
#include <iostream> // built-in input output stream component
#include <math.h> // math library
#include <queue> // STL queue component
#include <stack> // STL stack component
#include <string> // built-in string component
#include <vector> // STL vector component

// number of keywords
#define keywordNums 32

/*
 * 'switch-case' will use this
 * 'state'
 */
#define initState 0 // next step is to switch
#define letterState 1 // letter state
#define digitState 2 // digit state
#define dotState 3 // dot state
#define floatState 4 // float state
#define indexState 5 // index state
#define index2State 6 // index second position state
#define noSymNum 7 // none symbol number
#define lessState 8 // less than sign state
#define greaterState 9 // greater than sign state
#define equalState 10 // equal sign state
#define slashState 11 // slash sign state
#define slashStarState 12 // slash star sign state
#define exclamationState 13 // exclamation mark state
#define slashDoubleState 14 // double slash state
#define andState 15 // and mark state
#define orState 16 // or mark state
#define minusState 17 // minus sign state

using namespace std;

/*
 * pointer struct
 */
struct pointer {
    int start = 0;
    int over = 0;
    int first = 0;
};

/*
 * record number of letters, lines and words
 */
struct recordNum {
    int letters = 0;
    int lines = 0;
    int words = 0;
};

// variable of state
int state;

// class of words
class wordStr {
public:
    int lineNum;
    string Str;
};

// name of file which is outputed
string outputFileName;

/*
 * it's going to return words or symbols
 * find from position of 'posBegin'
 * quote argument 'posFlag' to return the position of the first char of current word in str
 */
string getWord(string str, int posBegin, int& posFlag);

/*
 * Remove consecutive spaces and newlines in the string
 * the first argument is target string
 * the second argument is position of start
 * it's going to return the position of effective char of the first in string
 */
int rmSpaceEnter(string str, int i);

/*
 * Function of output
 * successful: return true
 * failed: return false
 */
bool outputFunc(vector<pair<string, string>>& v, recordNum& rN);

/*
 * main functions of lexical analysis
 * it's going to return an array of type of pair
 */
vector<pair<string, string>> lexAnalysis(vector<wordStr>& vec, recordNum& rN);

/*
 * determine whether it is keyword
 * if true: return true
 * if false: return false
 */
bool isKeyword(string str);

/*
 * determine whether it is letter
 * if true: return true
 * if false: return false
 */
bool isLetter(char c);

/*
 * determine whether it is digit
 * if true: return true
 * if false: return false
 */
bool isDigit(char c);

/*
 * switch integer to binary
 */
stack<int> intToBinary(int num);

/*
 * switch double or float to binary
 */
string doubleToBinary(double num);
