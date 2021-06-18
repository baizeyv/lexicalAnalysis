#include <defMain.h>
/**
 * Author: baizeyv
 * Date: 2021-06-12
 * Mail: baizeyv@Gmail.com
 * Link: occs.cc
 * Github: Github.com/baizeyv
 */

/*
 * the introduction details will not be repeated here
 * please read the 'defMain.h'
 *
 * ACCESS CHECK !
 */
bool isLetter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}

/*
 * the introduction details will not be repeated here
 * please read the 'defMain.h'
 *
 * ACCESS CHECK !
 */
bool isDigit(char c)
{
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

/*
 * the introduction details will not be repeated here
 * please read the 'defMain.h'
 *
 * ACCESS CHECK !
 */
bool isKeyword(string str)
{
    // built-in array of keyword which belong to current program
    string keyword[keywordNums] = { "do", "double", "auto", "break", "case",
        "char", "const", "continue", "default", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "struct", "switch", "typedef", "short", "signed",
        "sizeof", "static", "union", "unsigned", "void",
        "volatile", "while" };
    /*
   * vector container in STL
   * the first argument is begin, the second one is end
   * vector(begin, end)
   * copy[begin, end) to vector newVec
   */
    vector<string> newVec(keyword, keyword + keywordNums);
    for (unsigned long i = 0; i < newVec.size(); i++) {
        if (!str.compare(
                newVec[i])) { // while str.compare(***) is true ,gain a value 0
            return true;
        }
    }
    return false;
}

/*
 * find the position where is't space, '\n', '\t' first
 * return this position
 *
 * ACCESS CHECK !
 */
int rmSpaceEnter(string str, int i)
{
    while (true) {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            return i;
        }
        i++;
    }
}

/*
 * write in output file
 * include LEX
 *         number
 *         file content number
 *
 * ACCESS CHECK !
 */
bool outputFunc(vector<pair<string, string>>& v, recordNum& rN)
{
    for (int i = 0; i < int(v.size()); i++) {
        if (v[i].first == "Constant" || v[i].first == "Digit") {
            string temp = v[i].second;

            // resolve it (index to double or float)
            if (int(temp.find('e')) != -1) {
                string beforeEsubstr = temp.substr(0, temp.find('e'));
                string afterEsubstr = temp.substr(temp.find('e') + 1, temp.length());
                cout << "before:" << beforeEsubstr << endl;
                cout << "after:" << afterEsubstr << endl;
                double beforsEdb = stod(beforeEsubstr);
                int afterEint = stoi(afterEsubstr);
                double indexResult = beforsEdb * pow(10, afterEint);
                cout << indexResult << endl;
                temp = to_string(indexResult);
            }
            if (int(temp.find(".")) == -1) {
                int num = stoi(temp);
                stack<int> bi = intToBinary(num);
                string swt;
                while (!bi.empty()) {
                    swt.append(to_string(bi.top()));
                    bi.pop();
                }
                v[i].second.append(" binary: ").append(swt);
            } else {
                double num = stod(temp);
                string swt = doubleToBinary(num);
                v[i].second.append(" binary: ").append(swt);
            }
        }
    }
    cout << "Please Enter The Path Of The Output File (Include Extension name):";
    cin >> outputFileName;

    /*
   * create a object of type of ofstream
   * ofstream ***(filename, mode)
   * mode: ios::in -> read
   *       ios::out -> write
   *       ios::ate -> begin position is tail of file
   *       ios::app -> all output add to the tail of file
   *       ios::trunc -> if exist, delete this file
   *       ios::binary -> binary way
   * they can be used in the same time by '|'
   */
    ofstream outfile(outputFileName.c_str(), ios::out);
    if (!outfile) {
        cout << "Can Not Open Target File:" << outputFileName.c_str() << endl;
        return false;
    }
    cout << endl;
    // add content to the file
    outfile << "Type"
            << "\t\t\t"
            << "Expression" << endl;
    for (unsigned long i = 0; i < v.size(); i++) {
        // the content of 'v.first' is type, 'v.second' is expression
        outfile << v[i].first << "\t\t\t" << v[i].second << endl;
        // the number of letters ++
        rN.letters += v[i].second.size();
    }

    // create a new vector container of type of bool named expressionKey
    vector<bool> expressionKey;
    // initialize the vector named expressionKey by false value
    for (unsigned long i = 0; i < v.size(); i++) {
        // add elements to the tail of vector which named expressionKey
        expressionKey.push_back(false);
    }

    outfile << "-----------------------------------------------" << endl;
    outfile << "Expression"
            << "\t\t\t"
            << "Number" << endl;
    // record the number of duplicates by variable 'sum'
    for (unsigned long i = 0; i < v.size(); i++) {
        if (expressionKey[i] == false) {
            int sum = 0;
            for (unsigned long j = 0; j < v.size(); j++) {
                if (v[j].second == v[i].second) {
                    expressionKey[j] = true;
                    sum++;
                }
            }
            outfile << v[i].second << "\t\t\t" << sum << endl;
        }
    }

    // create a new vector container of type of bool named typeKey
    vector<bool> typeKey;
    // initialize the vector named typeKey by false value
    for (unsigned long i = 0; i < v.size(); i++) {
        // add elements to the tail of vector which named typeKey
        typeKey.push_back(false);
    }
    outfile << "-----------------------------------------------" << endl;
    outfile << "Type"
            << "\t\t\t"
            << "Number" << endl;
    for (unsigned long i = 0; i < v.size(); i++) {
        if (typeKey[i] == false) {
            int sum = 0;
            for (unsigned long j = 0; j < v.size(); j++) {
                if (v[i].first == v[j].first) {
                    typeKey[j] = true;
                    sum++;
                }
            }
            outfile << v[i].first << "\t\t\t" << sum << endl;
        }
    }
    outfile << "-----------------------------------------------" << endl;
    outfile << "Lines:" << rN.lines << endl;
    outfile << "Words:" << rN.words << endl;
    outfile << "Letters:" << rN.letters << endl;
    // close the file
    outfile.close();
    return true;
}

/*
 * truncate the word before the delimiter
 *
 * ACCESS CHECK !
 */
string getWord(string str, int posBegin, int& posFlag)
{
    // create a object of type of string
    string symbol("\\%#:,^~{}[]() \'\";\n\t?");
    /*
   * find_first_of function: find the first same char in symbol
   * and return the position in str
   * ***.find_first_of(string, begin position)
   */
    posFlag = str.find_first_of(symbol, posBegin);
    if (posFlag == -1) {
        return " ";
    }
    if (posBegin != posFlag) {
        posFlag--;
    }
    /*
   * get a part of string
   * substr(begin, length)
   */
    return str.substr(posBegin, posFlag - posBegin + 1);
}

/*
 * switch integer to binary
 */
stack<int> intToBinary(int num)
{
    int tmpnum = num;
    string rest;
    // if the number is less than zero, num = -num
    if (num <= 0) {
        num = -num;
    }
    stack<int> binarySt;
    while (num != 0) {
        binarySt.push(num % 2);
        num /= 2;
    }
    if (tmpnum >= 0) {
        binarySt.push(0);
    } else {
        binarySt.push(1);
    }
    return binarySt;
}

/*
 *  IEEE-754 standard version
 */
string doubleToBinary(double num)
{
    string tmpnum = to_string(num);
    // index of postion of dot
    int pos = tmpnum.find('.');
    // substr before dot
    string beforesubstr = tmpnum.substr(0, pos);
    // string to int
    int bestrint = stoi(beforesubstr);
    // create a new container of stack, content:binary of substr before dot
    stack<int> tst = intToBinary(bestrint);
    string temp1;
    string temp2;
    string temp3;
    while (!tst.empty()) {
        temp1.append(to_string(tst.top()));
        temp2.append(to_string(tst.top()));
        temp3.append(to_string(tst.top()));
        tst.pop();
    }
    // substr after dot
    string aftersubstr = tmpnum.substr(pos, tmpnum.size());
    // zero string
    string zero = "0";
    // 0.****
    aftersubstr = zero.append(aftersubstr);
    // create a new container of queue
    queue<int> afterqueue;
    int flag = 0;
    while (true) {
        if (flag == int(33 - temp1.size())) {
            break;
        }
        double d = stod(aftersubstr);
        double db = d * 2;
        aftersubstr = to_string(db);
        if (aftersubstr[0] == '1') {
            afterqueue.push(1);
            aftersubstr[0] = '0';
        } else {
            afterqueue.push(0);
        }
        flag++;
    }
    string afterbistr;
    while (!afterqueue.empty()) {
        afterbistr.append(to_string(afterqueue.front()));
        afterqueue.pop();
    }
    string dot = ".";
    string re = temp1.append(dot).append(afterbistr);
    if (stod(re) >= 1) {
        for (int i = temp2.length() - 1; i > int(temp2.find("1") + 1); i--) {
            temp2[i] = temp2[i - 1];
        }
        temp2[temp2.find("1") + 1] = '.';
        string tail = string(1, temp3[temp3.length() - 1]);
        temp2.append(tail);
        int index = temp3.length() - temp3.find("1") - 1;
        int indexplus = 127 + index;
        stack<int> indexplusbi = intToBinary(indexplus);
        string result("");
        if (num > 0) {
            result.append("0");
        } else {
            result.append("1");
        }
        string midresult;
        while (!indexplusbi.empty()) {
            midresult.append(to_string(indexplusbi.top()));
            indexplusbi.pop();
        }
        midresult = midresult.substr(1, re.length());
        result.append(midresult);
        result.append(temp2.substr(temp2.find(".") + 1, temp2.length()));
        result.append(re.substr(re.find(".") + 1, re.length()));
        if (result.length() > 32) {
            result = result.substr(0, 32);
        }
        return result;
    } else {
        int onepos = afterbistr.find("1");
        for (int i = afterbistr.length() - 1; i > onepos + 1; i--) {
            afterbistr[i] = afterbistr[i - 1];
        }
        afterbistr[onepos + 1] = '.';
        int index = re.find(".") - re.find("1");
        stack<int> itobistack = intToBinary(127 + index);
        string result("");
        if (num > 0) {
            result.append("0");
        } else {
            result.append("1");
        }
        while (!itobistack.empty()) {
            result.append(to_string(itobistack.top()));
            itobistack.pop();
        }
        result.append(afterbistr.substr(afterbistr.find(".") + 1, afterbistr.length()));

        if (result.length() > 32) {
            result = result.substr(0, 32);
        }
        return result;
    }
}

// main function
vector<pair<string, string>> lexAnalysis(vector<wordStr>& vec, recordNum& rN)
{
    // temp vector
    vector<pair<string, string>> tmpv;

    // variable of state to switch function, initialize it
    state = initState;

    string word;

    // position pointer
    int pos = -1;

    // pointer of type of bool
    bool flag = true;

    for (unsigned long i = 0; i < vec.size(); i++) {
        pos = -1;
        do {
            switch (state) {
            case initState: // initial state
                // initialize variable named 'word'
                word = "";
                pos++;
                switch (vec[i].Str[pos]) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case '_':
                    state = letterState;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = digitState;
                    break;
                case '<':
                    state = lessState;
                    break;
                case '>':
                    state = greaterState;
                    break;
                case '=':
                    state = equalState;
                    break;
                case '/':
                    state = slashState;
                    break;
                case '!':
                    state = exclamationState;
                    break;
                case '&':
                    state = andState;
                    break;
                case '|':
                    state = orState;
                    break;
                case '+':
                    // if next char is '\0', pointer 'pos' move to next char
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "+"));
                    break;
                case '-':
                    state = minusState;
                    break;
                case '*':
                    // if next char is '\0', pointer 'pos' move to next char
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "*"));
                    break;
                case '.':
                    // if next char is '\0', pointer 'pos' move to next char
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "."));
                    break;
                case '(':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "("));
                    break;
                case ')':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", ")"));
                    break;
                case ';':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", ";"));
                    break;
                case '#':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "#"));
                    break;
                case '\\':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Escapes", "\\"));
                    break;
                case '\'':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "\'"));
                    break;
                case '\"':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "\""));
                    break;
                case '[':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "["));
                    break;
                case ']':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    tmpv.push_back(pair<string, string>("Delimiter", "]"));
                    break;
                case '{':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "{"));
                    break;
                case '}':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", "}"));
                    break;
                case ',':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Delimiter", ","));
                    break;
                case '~':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "~"));
                    break;
                case '^':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "^"));
                    break;
                case '%':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "%"));
                    break;
                case '?':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "?"));
                    break;
                case ':':
                    // pointer 'pos' move to next char
                    pos++;
                    // initialize state
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", ":"));
                    break;
                case '@':
                    pos = vec[i].Str.length() - 1; //
                    break;
                default:
                    word += vec[i].Str[pos];
                    state = initState;
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    cout << "The " << vec[i].lineNum << "th line has illegal char !" << endl;
                    break;
                }
                break;
            case letterState: // identifier status
                word += vec[i].Str[pos];
                pos++;
                if (isDigit(vec[i].Str[pos]) || isLetter(vec[i].Str[pos]) || vec[i].Str[pos] == '_' || vec[i].Str[pos] == '@') {
                    if (vec[i].Str[pos] == '@') {
                        state = initState;
                        rN.words++;
                        tmpv.push_back(pair<string, string>("identifier", vec[i].Str));
                        pos = vec[i].Str.find('@') - 1;
                    }
                } else {
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    if (isKeyword(word)) {
                        rN.words++;
                        tmpv.push_back(pair<string, string>("Keyword", word));
                    } else {
                        rN.words++;
                        tmpv.push_back(pair<string, string>("identifier", word));
                    }
                }
                break;
            case digitState: // constant state
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = digitState;
                    break;
                case '.':
                    state = dotState;
                    break;
                case 'E':
                case 'e':
                    state = indexState;
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Constant", word));
                    break;
                }
                break;
            case dotState: // state of dot of float
                word += vec[i].Str[pos];
                pos++;
                if (isDigit(vec[i].Str[pos])) {
                    state = floatState;
                } else {
                    cout << "The " << vec[i].lineNum
                         << "th has word error:" << word + vec[i].Str[pos] << endl;
                    if (vec[i].Str[pos] != '\0' && vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    state = initState;
                }
                break;
            case floatState: // state of float
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = floatState;
                    break;
                case 'E':
                case 'e':
                    state = indexState;
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Digit", word));
                    break;
                }
                break;
            case indexState: // state of index
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    state = noSymNum;
                    break;
                case '+':
                case '-':
                    state = index2State;
                    break;
                default:
                    cout << "The " << vec[i].lineNum
                         << "th has word error:" << word + vec[i].Str[pos] << endl;
                    if (vec[i].Str[pos] != '\0' && vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    state = initState;
                    break;
                }
                break;
            case 6: // the second state of index
                word += vec[i].Str[pos];
                pos++;
                if (isDigit(vec[i].Str[pos])) {
                    state = noSymNum;
                } else {
                    cout << "The " << vec[i].lineNum
                         << "th has word error:" << word + vec[i].Str[pos] << endl;
                    if (vec[i].Str[pos] != '\0' && vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    state = initState;
                }
                break;
            case 7: // state of none symbol
                word += vec[i].Str[pos];
                pos++;
                if (isDigit(vec[i].Str[pos])) {
                    state = noSymNum;
                } else {
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = 0;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Digit", word));
                }
                break;
            case lessState: // state of '<'
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '=':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "<="));
                    break;
                case '<':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "<<"));
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "<"));
                    break;
                }
                break;
            case greaterState: // state of '>'
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '=':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", ">="));
                    break;
                case '>':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", ">>"));
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", ">"));
                    break;
                }
                break;
            case equalState: // state of '='
                word += vec[i].Str[pos];
                pos++;
                if (vec[i].Str[pos] == '=') {
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "=="));
                } else {
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "="));
                }
                break;
            case slashState: // state of '/'
                word += vec[i].Str[pos];
                pos++;
                if (vec[i].Str[pos] == '*') {
                    state = slashStarState;
                    flag = true;
                } else if (vec[i].Str[pos] == '/') {
                    state = slashDoubleState;
                } else {
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "/"));
                }
                break;
            case slashStarState: // state of comment of '/*'
                pos++;
                while (vec[i].Str[pos] != '*') {
                    pos++;
                    if (pos >= int(vec[i].Str.size())) {
                        if (i == vec.size() - 1) {
                            flag = false;
                            state = initState;
                            break;
                        }
                        i++;
                        pos = 0;
                    }
                }
                if (flag) {
                    pos++;
                    if (vec[i].Str[pos] == '/') {
                        state = initState;
                        if (vec[i].Str[pos + 1] == '\0') {
                            pos++;
                        }
                    } else {
                        if (vec[i].Str[pos] != '\0') {
                            pos--;
                        }
                        state = slashStarState;
                        if (pos == int(vec[i].Str.size()) && i == vec.size() - 1) {
                            state = initState;
                        }
                    }
                }
                break;
            case exclamationState: // state of '!'
                word += vec[i].Str[pos];
                pos++;
                if (vec[i].Str[pos] == '=') {
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "!="));
                } else {
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "!"));
                }
                break;

            case andState: // state of '&'
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '&':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "&&"));
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "&"));
                    break;
                }
                break;
            case orState: // state of '|'
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '|':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "||"));
                    break;
                default:
                    if (vec[i].Str[pos] != '\0') {
                        pos--;
                    }
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "|"));
                    break;
                }
                break;
            case minusState: { // state of '-'
                word += vec[i].Str[pos];
                pos++;
                switch (vec[i].Str[pos]) {
                case '>':
                    if (vec[i].Str[pos + 1] == '\0') {
                        pos++;
                    }
                    word += vec[i].Str[pos];
                    state = initState;
                    rN.words++;
                    tmpv.push_back(pair<string, string>("Operator", "->"));
                    break;
                default:
                    // firstly, check the number which is less than zero
                    //                    cout << vec[i].Str << endl;
                    // float less than zero
                    if (vec[i].Str.find('-') == 0 && int(vec[i].Str.find('.')) != -1) {
                        state = initState;
                        rN.words++;
                        pos = -1;
                        tmpv.push_back(pair<string, string>("Constant", vec[i].Str));
                        break;
                    }
                    vector<wordStr> flagWSv;
                    wordStr flagwS;
                    recordNum flagRN;
                    for (int j = 0; j < int(vec[i - 1].Str.size()); j++) {
                        flagwS.Str = vec[i - 1].Str;
                        flagwS.lineNum = 0;
                        flagWSv.push_back(flagwS);
                    }
                    vector<pair<string, string>> flagv = lexAnalysis(flagWSv, flagRN);
                    if (!(flagv[0].first.compare("identifier")) || !(flagv[0].first.compare("Constant"))) {
                        if (vec[i].Str[pos + 1] != '\0') {
                            pos--;
                        }
                        state = initState;
                        rN.words++;
                        tmpv.push_back(pair<string, string>("Operator", "-"));
                        break;
                    } else {
                        vector<wordStr> flagWSv1;
                        wordStr flagwS1;
                        recordNum flagRN1;
                        //                        for (int k = 0; k < int(vec[i].Str.size()); k++) {
                        flagwS1.Str = vec[i].Str.substr(1);
                        flagwS1.lineNum = 0;
                        flagWSv1.push_back(flagwS1);
                        //                        }
                        vector<pair<string, string>> flagv1 = lexAnalysis(flagWSv1, flagRN1);
                        if (!flagv1[0].first.compare("Constant")) {
                            state = initState;
                            rN.words++;
                            pos = -1;
                            tmpv.push_back(pair<string, string>("Constant", vec[i].Str));
                            break;
                        }
                    }
                }
                break;
            }
            case slashDoubleState: // state of comment of '//'
                int tmpLine = i;
                while (i < vec.size() && vec[i].lineNum == vec[tmpLine].lineNum) {
                    i++;
                }
                i--;
                pos = vec[i].Str.size();
                state = initState;
                break;
            }
        } while (vec[i].Str[pos] != '\0');
    }
    return tmpv;
}

int main()
{
    // create a new pointer struct named p
    pointer p;
    // create a new recordNum struct named rN
    recordNum rN;
    /*
     * while read file, exclude the example string
     */
    string example_1 = " ";
    string example_2 = "\n";

    string lineContent; // content of a line of current file

    /*
     * create a new vector of type of wordStr class
     * vector<type> example_name(int nSize) -> nSize is the number of elements
     * initialize the size to 0
     */
    vector<wordStr> vecArray(0);

    string inputFileName; // the name of file in which you write code (include path and extension name)

    // input and output stream
    cout << "Please Enter The Path Of Code File (Include Extension name):";
    cin >> inputFileName;

    // input file stream
    ifstream infile(inputFileName.c_str(), ios::in);

    if (!infile) {
        // while open the file failed, tips
        cerr << "Can Not Open This File!" << inputFileName.c_str() << endl;
    } else {
        // while open the file successful, run the following code
        cout << endl;
        // eof == end of file
        while (!infile.eof()) {

            /*
             * getline（istream &is,string &str,char delim）
             * the first argument is the 'input stream'
             * save the content of variable 'is' to variable 'str'
             * the thired argument is the 'end symbols(delimiter)'
             */
            getline(infile, lineContent, '\n');

            // add '\n' to the tail of line which is read just now
            lineContent += "\n";

            /*
             *  number of lines ++
             *  rN is a recordNum struct
             */
            rN.lines++;

            // create a variable of type of wordStr struct
            wordStr neoStr;

            // initialize the pointer named p; begin position and end position
            p.start = 0;
            p.over = 0;

            for (int i = 0; lineContent[i] != '\0' && p.over != -1; i++) {
                // initialize the start position by rmSpaceEnter function
                p.start = rmSpaceEnter(lineContent, p.start);

                // read the content of current line, begin position is 'p.start', return 'p.over' position
                neoStr.Str = getWord(lineContent, p.start, p.over);
                // record number of current line
                neoStr.lineNum = rN.lines;
                /*
                 * in compare function, successful return 0
                 * equal -> pass current if
                 * not equal -> push elements of 'neoStr' to 'vecArray'
                 */
                if (neoStr.Str.compare(example_1) && neoStr.Str.compare(example_2)) {
                    vecArray.push_back(neoStr);
                }

                // modify start position, set the next position of end position as the new start position
                p.start = p.over + 1;
            }
        }

        // create a vector container of type of pair<string, string> named vecResult
        vector<pair<string, string>> vecResult;

        /*
         *  call function named lexAnalysis
         *  and the functions will return a vector container which is resolved
         */
        vecResult = lexAnalysis(vecArray, rN);

        // a flag of output
        bool outFlag = outputFunc(vecResult, rN);

        if (outFlag) {
            cout << "-----------------------------------------------\n";
            cout << "Finished! Result is in " << outputFileName << "\n";
            cout << "-----------------------------------------------\n";
        }
    }
    return 0;
}
