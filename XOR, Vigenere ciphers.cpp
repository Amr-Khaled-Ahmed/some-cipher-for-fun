#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;

bool check_for_characters(const string& str);
bool check_for_hexadecimal(const string& statement);
void main_vigenere();
void vigenere_decipher(const string& message, const string& keyword);
void vigenere_cipher(const string& statement, const string& keyword);
void XOR_cipher();
string ignore_statement(string before);
int main(){
    string choice;

    cout << "please choose\n1 to vigenere cipher\n2 to XOR cipher\n3 to close\n";
    cin>>choice;
    while (!(choice == "1" || choice == "2" || choice == "3")){
        cout << "Invalid choice. Please choose\n1 to vigenere cipher\n2 to XOR cipher\n3 to close\n";
        cin >> choice;
    }
    if(choice == "1"){
        cout << "*** Welcome to vigenere cipher ***\n";
        main_vigenere();
    }else if (choice == "2"){
        cout << "*** Welcome to XOR cipher ***\n";
        XOR_cipher();
    }else{ exit(0) ;}
}


void XOR_cipher(){
    string statement, keyword, choice;
    // Asking the user to choose an option
    cout << "Please choose\n1 to enter the cipher\n2 to decipher\n3 to exit\n";
    cin >> choice;
    // Validating the user's choice
    while (!(choice == "1" || choice == "2" || choice == "3")) {
        cout << "Invalid input. Please choose\n1 to enter the cipher\n2 to decipher\n3 to exit\n";
        cin >> choice;
    }

    cin.ignore(); // Clearing input buffer

    // choose between cipher or decipher or exit
    if (choice == "1"){
//        here I will take the key then convert it to ascii code then to binary
        // declare the ascii code and the ascii key
        bool notLetter = false;
        string encrypted_text, encrypted_hex;
        string key;
        cout << "Enter the security key" << endl;
        cin >> key;
        // This part will ask for the key again if it is not a character by ignoring anything otherwise characters then check
        for (char i : key) {
            if (!isalpha(i)){
                notLetter = true;
                break;
            }
        }
        while(notLetter){
            cout << "Invalid input. Please enter a valid key (It must be letters)" << endl;
            cin >> key;
            // This part will ask for the key again if it is not a character by ignoring anything otherwise characters then check
            notLetter = false;
            for (char i : key) {
                if (!isalpha(i)){
                    notLetter = true;
                    break;
                }
            }
        }
        cout << "Enter the statement" << endl;
        cin.ignore();
        getline(cin,statement);
        // get the input again if the input is all does not include and characters
        while(statement.empty()){
            cout << "Invalid input. please enter a valid statement" << endl;
            cin.ignore();
            getline(cin,statement);

        }

        //cipher the text by Xor and Hexadecimal by getting the ascii code for every character
        int j = 0;
        for (char i : statement) {
            stringstream ss;
            encrypted_text += (char)(key[j]^i);
            ss << hex << setw(2) << setfill('0') << (int)(key[j] ^ i);
            encrypted_hex += ss.str() + " ";
            j = ++j % key.size(); // to repeat on the key again
        }
        // ignore anything otherwise digits and alphabets and white spaces then print the massage
        encrypted_text = ignore_statement(encrypted_text);
        cout << "Cipher text: " << encrypted_text << endl;
        cout << "Cipher by hexadecimal: " << encrypted_hex << endl;
    }else if (choice == "2"){
        int temp_ascii;
        bool notLetter = false,notHex;
        string decrypted_text;
        string key;
        cout << "Enter the security key" << endl;
        cin >> key;
        // This part will ask for the key again if it is not a character by ignoring anything otherwise characters then check
        for (char i : key) {
            if (!isalpha(i)){
                notLetter = true;
                break;
            }
        }
        while(notLetter){
            cout << "Invalid input. Please enter a valid key (It must be letters)" << endl;
            cin >> key;
            // This part will ask for the key again if it is not a character by ignoring anything otherwise characters then check
            notLetter = false;
            for (char i : key) {
                if (!isalpha(i)){
                    notLetter = true;
                    break;
                }
            }
        }
        cout << "Enter the encrypted statement (Hexadecimal code):" << endl;
        cin.ignore();
        getline(cin,statement);
        notHex = check_for_hexadecimal(statement);
        while(notHex){
            cout << "Invalid input. Please enter a valid encrypted statement (Hexadecimal code):" << endl;
            cin.ignore();
            getline(cin,statement);
            notHex = check_for_hexadecimal(statement);
        }
        // this part will ignore any spaces

        //decipher the Hexadecimal by Xor and text by getting the ascii code for every 2 hexadecimal
        int j = 0;
        for (int i = 0 ; i < statement.size() ; i+=2 ) {
            if(isspace(statement[i])){
                i++;
            }
           temp_ascii = stoi(statement.substr(i, 2), 0, 16);
           decrypted_text += (char)(temp_ascii ^ key[j]);
           j = ++j % key.size(); // to repeat on the key again
        }
        cout << "The decrypted text is: "<< decrypted_text << endl;
    }else{ exit(0);}

    // print the menu to play again
    cout << "Do you want to play again or exit?\npress\n1 to play XOR cipher again\n2 to return to main menu\n3 to exit\n";
    cin >> choice;
    while (!(choice == "1" || choice == "2" || choice == "3")){
        cout << "Invalid choice. Please press\n1 to play XOR cipher again\n2 to return to main menu\n3 to exit\n";
        cin >> choice;
    }
    if (choice == "1"){
        XOR_cipher();
    }else if (choice == "2"){
        main();
    }else { exit(0);}
}


bool check_for_hexadecimal(const string& statement){
    // this part will check if the hexadecimal code is valid or not
    regex hex("0x[0-9A-Fa-f]+");
    return regex_match(statement, hex);
}
































void main_vigenere() {
    string statement, keyword, choice;
    // Asking the user to choose an option
    cout << "Please choose\n1 to enter the cipher\n2 to decipher\n3 to exit\n";
    cin >> choice;
    // Validating the user's choice
    while (!(choice == "1" || choice == "2" || choice == "3")) {
        cout << "Invalid input. Please choose\n1 to enter the cipher\n2 to decipher\n3 to exit\n";
        cin >> choice;
    }

    cin.ignore(); // Clearing input buffer

    // choose between cipher or decipher or exit
    if (choice == "1") {
        // Getting the statement from the user
        cout << "Enter the statement (up to 80 characters):\n";
        do {
            getline(cin, statement);
            // if wrong input print this massage and repeat
            if (statement.size() > 80) { cout << "Please, enter the statement (up to 80 characters):\n"; }
        } while (statement.size() > 80 || statement.empty());

        // Getting the keyword from the user
        cout << "Enter the keyword (up to 8 characters):\n";
        do {
            getline(cin, keyword);
            // if wrong input print this massage and repeat
            if (keyword.size() > 8 || keyword.empty() || !check_for_characters(keyword)) {
                cout << "Please, enter the keyword (up to 8 characters) and it must be alphabetic:\n";
            }
        } while (keyword.size() > 8 || keyword.empty() || !check_for_characters(keyword));

        // Convert statement to uppercase
        for (char& c : statement) {
            c = toupper(c);
        }

        // Repeat the keyword to match the length of the statement
        string repeatedKeyword;
        for (int i = 0; i < statement.length(); ++i) {
            repeatedKeyword += keyword[i % keyword.length()];
        }
        // call Vigenere Cipher
        vigenere_cipher(statement, repeatedKeyword);

    } else if (choice == "2") {
        // Getting the statement from the user
        cout << "Enter the statement (up to 80 characters):\n";
        do {
            getline(cin, statement);
            // if wrong input print this massage and repeat
            if (statement.size() > 80 || statement.empty()) { cout << "Please, enter the statement (up to 80 characters):\n"; }
        } while (statement.size() > 80 || statement.empty());

        // Getting the keyword from the user
        cout << "Enter the keyword (up to 8 characters):\n";
        do {
            getline(cin, keyword);
            // if wrong input print this massage and repeat
            if (keyword.size() > 8 || keyword.empty() || !check_for_characters(keyword)) {
                cout << "Please, enter the keyword (up to 8 characters) and it must be alphabetic:\n";
            }
        } while (keyword.size() > 8 || keyword.empty() || !check_for_characters(keyword));

        // Convert statement to uppercase
        for (char& c : statement) {
            c = toupper(c);
        }

        // Repeat the keyword to match the length of the statement
        string repeatedKeyword;
        for (int i = 0; i < statement.length(); ++i) {
            repeatedKeyword += keyword[i % keyword.length()];
        }
        // Decrypting the statement using Vigenere Cipher
        vigenere_decipher(statement, repeatedKeyword);

    } else { return; }
    cout << "Do you want to play again or exit?\npress\n1 to play vigenere cipher again\n2 to return to main menu\n3 to exit\n";
    cin >> choice;
    while (!(choice == "1" || choice == "2" || choice == "3")){
        cout << "Invalid choice. Please press\n1 to play vigenere cipher again\n2 to return to main menu\n3 to exit\n";
        cin >> choice;
    }
    if (choice == "1"){
        main_vigenere();
    }else if (choice == "2"){
        main();
    }else { exit(0);}
    return;
}

// Function to check if a string contains only alphabetic characters
bool check_for_characters(const string& str) {
    for (char c : str) {
        if (!isalpha(c))
            return false;
    }
    return true;
}

// Function to decipher a message using Vigenere Cipher
void vigenere_decipher(const string& message, const string& keyword) {
    string decryptedMessage;
    int keyword_index = 0;

    for (char c : message) {
        if (isalpha(c)) {
            // to decrypt the char by the key
            char decryptedChar = ((c - 'A') - (toupper(keyword[keyword_index]) - 'A') + 26) % 26 + 'A';
            decryptedMessage += decryptedChar;
            keyword_index = (keyword_index + 1) % keyword.length();
        } else {
            decryptedMessage += c;
            keyword_index = (keyword_index + 1) % keyword.length();
        }
    }

    cout << "Decryption statement is : " << decryptedMessage << endl;
}

// Function to encrypt a statement using Vigenere Cipher
void vigenere_cipher(const string& statement, const string& keyword) {
    string encryptedMessage;
    int keyword_index = 0;

    for (char c : statement) {
        if (isalpha(c)) {
            // to encrypt the char by the key
            char encryptedChar = ((c - 'A') + (toupper(keyword[keyword_index]) - 'A')) % 26 + 'A';
            encryptedMessage += encryptedChar;
            keyword_index = (keyword_index + 1) % keyword.length();
        } else {
            encryptedMessage += c;
            keyword_index = (keyword_index + 1) % keyword.length();
        }
    }
    cout << "Encrypted statement: " << encryptedMessage << endl;
}
string ignore_statement(string before){
//    to ignore anything otherwise alphabetic and digits then return only alphabetic characters and digits
    string after;
    for (int i = 0; i < before.size(); ++i) {
        if (isalpha(before[i]) || isspace(before[i]) || isdigit(before[i]) || ispunct(before[i])){
            after += before[i];
        }
    }
    return after;
}
