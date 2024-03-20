#include <iostream>
#include <vector>
#include <string>

using namespace std;
void cipher();
void decipher();
void frame_print();
bool isExist_key(int temp);
bool isDigits(string statement);
int check_for_string();
string encryption(string temp);
string decryption(string before);
string ignore_statement(string before);

int key[5];

vector<vector <string>> frame = {{"A","B","C","D","E"},{"F","G","H","IJ","K"},{"L","M","N","O","P"},{"Q","R","S","T","U"},{"V","W","X","Y","Z"}};


int main() {
    cout << "***** Welcome to polybius-cipher application *****" << endl;
    string choice;
    cout << "please select\n1 if you want to encrypt\n2 if you want decrypt\n3 if you want to exit" << endl;
    // get the choice for play
    cin >> choice;
    if (choice == "1"){
        cipher();
    }else if (choice == "2"){
        decipher();
    }else if (choice == "3") {
        return 0;
    }
    // if the choice was wrong ask the user for it again
    while (choice != "1" && choice != "2" && choice !="3"){
        cout << "Invalid input. please select\n1 if you want to encrypt\n2 if you want 2 decrypt\n3 if you want to exit" << endl;
        cin >> choice;
        if (choice == "1"){
            cipher();
        }else if (choice == "2"){
            decipher();
        }else if (choice == "3"){
            return 0;
        }
    }
}

//// in function



void cipher(){
    string statement, encrypt_word, temp_frame, statement_copy;
    int temp;
    bool isExist = false;
    // get the statement
    cout << "enter the statement:\n";
    getline(cin, statement);
    getline(cin, statement);
    // ignore anything otherwise the alphabetic characters
    statement = ignore_statement(statement);

    // make the statement and its copy to upper
    for (int i = 0; i < statement.size() ; i++ ){
        statement[i] = toupper(statement[i]);

    }
    statement_copy = statement;


    // enter the cipher key
    cout << "Enter the cipher key\n";
    cout << "Enter the key\n";
    for (int i = 0 ; i < 5 ; i++ ){
        do{
            cout << "Enter the index ("<< i+1 << ")" << endl;
            key[i] = check_for_string();
            temp = key[i];
            isExist = isExist_key(temp);
            // if the key element was not right ask for it again
            if (isExist || key[i] < 1 || key[i] > 5){cout << "Invalid input. ";}
        }while (isExist || key[i] < 1 || key[i] > 5);
    }




    frame_print();
        // encrypt the statement
    encrypt_word = encryption(statement);

    cout << "The encryption of " << statement_copy << " is: "<< encrypt_word <<endl;
    // reset the key for reuse
    for (int i = 0; i < 5 ;i++){
        key[i] = 10;
    }

    // ask the user if he wants to play again
    string choice1;
    do {
        cout << "Do you want to continue\npress 1 if yes\npress 2 if no\n";
        cin >> choice1;
        if (choice1 == "1"){
            main();
        }else if(choice1 == "2"){
            return;
        }else {
            cout << "Invalid input.";
        }
        // ask for the choice again if the user input wrong answer
    }while(choice1 != "1" && choice1 != "2");

}


void decipher(){
    string statement, decrypt_word, temp_frame;
    int temp;
    bool isExist = false, isLetter = false, iSduplicate = false, isDigit;
    //get the encrypt statement
    cout << "Please enter the encrypted code\n";
    // there is two getline because the first one destroyed by cin
    getline(cin, statement);
    getline(cin, statement);
    isDigit = isDigits(statement);
    while ((!isDigit) || (statement.size()%2 != 0)){
        cout << "Invalid input .Please enter the encrypted code with numbers only\n";
        getline(cin, statement);
        isDigit = isDigits(statement);
    }
    // enter the cipher key
    cout << "Enter the key\n";
    for (int i = 0 ; i < 5 ; i++ ){
        do{
            cout << "Enter the index ("<< i+1 << ")" << endl;
            key[i] = check_for_string();
            temp = key[i];
            isExist = isExist_key(temp);
            if (isExist || key[i] < 1 || key[i] > 5){cout << "Invalid input. ";}
        }while (isExist || key[i] < 1 || key[i] > 5);
    }


    frame_print();
    decrypt_word = decryption(statement);
    cout << "the word is " << decrypt_word << endl;
    // reset the key for reuse
    for (int i = 0; i < 5 ;i++){
        key[i] = 11;
    }
    string choice1;
    // ask the user if he wants to play again
    do {
        cout << "Do you want to continue\npress 1 if yes\npress 2 if no\n";
        cin >> choice1;
        if (choice1 == "1"){
            main();
        }else if(choice1 == "2"){
            return;
        }else {
            cout << "Invalid input.";
        }
        // ask for the choice again if the user input wrong answer

    }while(choice1 != "1" && choice1 != "2");
}


//// out function // done
string encryption(string temp){
    string res_1;
    string x, row , col;
    // set instead each character his row and column
    for (char ch : temp){
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0 ; k < frame[i][j].size() ; k++){
                    if (frame[i][j][k] == ch) {
                        // cat the row and the col in string
                        row = to_string(key[j]);
                        col = to_string(key[i]);
                        res_1 += col + row;
                    }
                }
            }
        }
    }
    return res_1;
}
string decryption(string before) {
    string after;
    int row, col;
    // this loop to get the right col and the right row
    for (int i = 0; i < before.size(); i += 2) {
        // cast the row character into integer then get his index
        int int_char = before[i] - '0';
        for (int j = 0; j < before.size() + 1; j++) {
            if (key[j] == int_char) {
                row = j;
                break;
            }
        }
        // cast the col character into integer then get his index
        int_char = before[i + 1] - '0';
        for (int j = 0; j < before.size();j++ ) {
            if (key[j] == int_char) {
                col = j;
                break;
            }
        }
        // add it to the return value
        after += frame[row][col];
    }
    return after;
}
void frame_print(){
    // print the game frame
    cout << "  ";
    // print the VL key
    for (int i = 0; i < 5 ; i++){
        cout << " " << key[i] ;
    }
    cout << endl;
    // print the frame
    for (int i = 0 ; i < 5 ; i++){
        // print the HR key
        cout << key[i] << "|";
        for (int j = 0 ; j < 5 ; j++){
            cout << " " << frame[i][j];
        }
        cout << endl;
    }

}
bool isExist_key(int temp){
    // to check if the key is duplicate
    for (int i = 0 ; i < 5 ; i++){
        if (temp == key[i]){
            for (int j = i+1 ; j < 5 ; j++){
                if (temp == key[j]){
                    cout << "Please enter a different number\n";
                    return true;
                }
            }
        }
    }
    return false;
}
bool isDigits(string statement){
    for (char i : statement){
        if (!isdigit(i)){
            return false;
        }
    }
    return true;
}
int check_for_string() {
    //to validate for the row and column is string or no
    string x;
    cin >> x;
    while (true) {
        bool is_digit = true;
        for (char i : x) {
            if (isdigit(i) == 0) {
                is_digit = false;
                break;
            }
        }
        if (is_digit) {
            int y = stoi(x);

            return y;
        }
        else {
            cout << "Please enter an integer: " << endl;
            cin >> x;
        }
    }
}
string ignore_statement(string before){
//    to ignore anything otherwise alphabetic and return only alphabetic characters
    string after;
    for (int i = 0; i < before.size(); ++i) {
        if (isalpha(before[i])){
            after += before[i];
        }
    }
    return after;
}
