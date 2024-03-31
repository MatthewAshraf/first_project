/*
 * File:CS112_A2_T2_S9-S10_20230820_20230244_20230596.cpp
 * Authors:
 1- Malek abdul malek moqbel -(ID:20230820)- Solved Problem 1. Affine Cipher
 2- Emad George Mattar Hanna -(ID:20230244)- Solved Problem 5. Baconian Cipher
 3- Matthew Ashraf Moris Farag -(ID:20230596)- Solved Problem 7. Polybius Square Cipher
 Date: 11/3/2024
 Version : 1.0
 */
# include <iostream>
#include <unordered_map>
#include <cstdlib>
using namespace std;

// 1-Affine Cipher:

bool valid(int a) {
    return (a >= 1 && a <= 25); //input a must be between 1 and 25//
}

string affine_encrypt(const string& message, int a, int b) {
    if (!valid(a)) {
        throw invalid_argument("invalid key");
    }
    string cipherText;
    for (char c : message) {
        if (isalpha(c)) {
            c = toupper(c);//make the input uppercase//
            cipherText += static_cast<char>((((a * (c - 'A')) + b) % 26) + 'A');
        } else {
            cipherText += c;
        }
    }
    return cipherText;
}

string affine_decrypt(const string& cipherText, int a, int b) {
    if (!valid(a)) {
        throw invalid_argument("invalid key");
    }
    int a_inv = 0;
    // Find modular inverse of 'a'
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }
    string message;
    for (char c : cipherText) {
        if (isalpha(c)) {
            c = toupper(c); //alos make the input uppercase//
            message += static_cast<char>((((a_inv * (c - 'A' - b)) % 26) + 26) % 26 + 'A');
        } else {
            message += c;
        }
    }
    return message;
}


// 2-Baconian Cipher

string lookup(char ch) {
    switch (toupper(ch)) {
    case 'A': return "aaaaa";
    case 'B': return "aaaab";
    case 'C': return "aaaba";
    case 'D': return "aaabb";
    case 'E': return "aabaa";
    case 'F': return "aabab";
    case 'G': return "aabba"; // Duplicate, can be ignored.
    case 'H': return "aabbb";
    case 'I': return "abaaa";
    case 'J': return "abaab";
    case 'K': return "ababa";
    case 'L': return "ababb";
    case 'M': return "abbaa";
    case 'N': return "abbab";
    case 'O': return "abbba"; // Duplicate, can be ignored.
    case 'P': return "abbbb";
    case 'Q': return "baaaa";
    case 'R': return "baaab";
    case 'S': return "baaba";
    case 'T': return "baabb";
    case 'U': return "babaa";
    case 'V': return "babab";
    case 'W': return "babba";
    case 'X': return "babbb";
    case 'Y': return "bbaaa";
    case 'Z': return "bbaab";
    default: return "";
    }
}

string baconian_encrypt(string message) {
    string result = "";
    for (char ch : message) {
        if (isalpha(ch)) {
            result += lookup(ch);
        }
        else {
            result += ch; // Non-alphabetic characters are not encrypted
        }
    }
    return result;
}

string Baconian_decrypt(string ciphertext) {
    string result = "";
    string current = "";
    for (char ch : ciphertext) {
        if (ch == 'a' || ch == 'b') {
            current += ch;
            if (current.length() == 5) {
                // Reverse lookup
                for (char letter = 'A'; letter <= 'Z'; ++letter) {
                    if (current == lookup(letter)) {
                        result += letter;
                        break;
                    }
                }
                current = "";
            }
        }
        else {
            result += ch; // Non-'a' or 'b' characters are left unchanged
        }
    }
    return result;
}


// 3-Polybius Square Cipher

string correct_key(string key){
    string new_key;
    string to_append;
    for (char ch : key){
        if (isalnum(ch)){
            to_append = ch;
            new_key.append(to_append);
        }
    }
    return new_key;
}

pair<int, int> char_to_code(char ch) {
    static const unordered_map<char, pair<int, int>> char_code_map = {
        {'A', {1, 1}}, {'B', {1, 2}}, {'C', {1, 3}}, {'D', {1, 4}}, {'E', {1, 5}},
        {'F', {2, 1}}, {'G', {2, 2}}, {'H', {2, 3}}, {'I', {2, 4}}, {'K', {2, 5}},
        {'L', {3, 1}}, {'M', {3, 2}}, {'N', {3, 3}}, {'O', {3, 4}}, {'P', {3, 5}},
        {'Q', {4, 1}}, {'R', {4, 2}}, {'S', {4, 3}}, {'T', {4, 4}}, {'U', {4, 5}},
        {'V', {5, 1}}, {'W', {5, 2}}, {'X', {5, 3}}, {'Y', {5, 4}}, {'Z', {5, 5}}

    };

    if (char_code_map.count(ch) == 0) {
        // Handle invalid character (not A-Z)
        return make_pair(-1, -1);
    }

    return char_code_map.at(ch);
}

string polybius_encrypt(string message, string key){
    string encryption;
    string char_to_append;
    pair <int, int> cords;
    for (char ch : message){
        if (!isalnum(ch)){
            encryption += ch;
        }
        else {
            cords = char_to_code(toupper(ch));
            char_to_append = key[cords.first - 1];
            encryption.append(char_to_append);
            char_to_append = key[cords.second - 1];
            encryption.append(char_to_append);
            
        }
    }
    return encryption;
}

char code_to_char(pair<int, int> code) {
    static const unordered_map<char, pair<int, int>> char_code_map = {
        {'A', {1, 1}}, {'B', {1, 2}}, {'C', {1, 3}}, {'D', {1, 4}}, {'E', {1, 5}},
        {'F', {2, 1}}, {'G', {2, 2}}, {'H', {2, 3}}, {'I', {2, 4}}, {'K', {2, 5}},
        {'L', {3, 1}}, {'M', {3, 2}}, {'N', {3, 3}}, {'O', {3, 4}}, {'P', {3, 5}},
        {'Q', {4, 1}}, {'R', {4, 2}}, {'S', {4, 3}}, {'T', {4, 4}}, {'U', {4, 5}},
        {'V', {5, 1}}, {'W', {5, 2}}, {'X', {5, 3}}, {'Y', {5, 4}}, {'Z', {5, 5}}

    };

    for (auto it = char_code_map.begin(); it != char_code_map.end(); ++it) {
        if (it->second == code) {
            return it->first;
        }
    }
}

string polybius_decrypt(string ciphered_message, string key){
    pair<int, int> code;
    string message;
    int key_letter_value;
    string to_append;
    for (int i = 0; i < ciphered_message.length(); i += 2){
        
        key_letter_value = key.find(ciphered_message[i]);
        code.first = key_letter_value + 1;

        key_letter_value = key.find(ciphered_message[i + 1]);
        code.second = key_letter_value + 1;
        to_append = code_to_char(code);
        message.append(to_append);
        
        
    }
    return message;
}




int main(){

  string user_menu_operation;
  string user_menu_cipher;
  string message;
  do {
    cout << "What do you like to do today? " << '\n';
    cout << "1- Cipher a message" << '\n';
    cout << "2- Decipher a message" << '\n';
    cout << "3- End" << '\n';
    cout << ">> ";
    cin >> user_menu_operation;
    if (user_menu_operation == "1"){

      // recieve message
      cout << "Please enter the message to cipher: ";
      getline(cin >> ws, message);
      // decide which cipher to use
      cout << "Which Cipher do you like to choose?" << '\n';
      cout << "1-Affine Cipher" << '\n';
      cout << "2-Baconian Cipher" << '\n';
      cout << "3-Polybius Square Cipher" << '\n';
      cout << "4-Return" << '\n';
      cin >> user_menu_cipher;

      if (user_menu_cipher == "1"){
        int a, b;

        cout << "Enter key a: ";
        cin >> a;

        cout << "Enter key b: ";
        cin >> b;
        string cipherText = affine_encrypt(message, a, b);
        cout << "Encrypted message: " << cipherText << endl;
        
      }
      else if (user_menu_cipher == "2"){
            string ciphertext;
            ciphertext = baconian_encrypt(message);
            cout << "Encrypted message: " << ciphertext << '\n';    
      }
      else if (user_menu_cipher == "3"){
        string key;
        string encryption;
        cout << "key: ";
        getline(cin >> ws, key);
        key = correct_key(key);
        encryption = polybius_encrypt(message, key);
        cout << "Encrypted message: " << encryption << '\n';
      }
      else if (user_menu_cipher == "4"){
        continue;
      }
    }
    
    else if (user_menu_operation == "2"){      
        // decide which cipher to use
        cout << "Which Cipher do you like to choose?" << '\n';
        cout << "1-Affine Cipher" << '\n';
        cout << "2-Baconian Cipher" << '\n';
        cout << "3-Polybius Square Cipher" << '\n';
        cout << "4-Return" << '\n';
        cin >> user_menu_cipher;
        if (user_menu_cipher == "1"){
            string cipherText;
            cout << "enter the message you want to decipher: ";
            getline(cin >> ws, cipherText);
            int a, b;
            cout << "Enter key a: ";
            cin >> a;
            cout << "Enter key b: ";
            cin >> b;
            string decryptedMessage = affine_decrypt(cipherText, a, b);
            cout << "Decrypted message: " << decryptedMessage << endl;
        
        }
        else if (user_menu_cipher == "2"){
            string ciphered_message;
            string message;
            cout << "enter the message woy want to decipher: ";
            getline(cin >> ws, ciphered_message);
            message = Baconian_decrypt(ciphered_message);
            cout << "Decrypted message: " << message << '\n';
        }
        else if (user_menu_cipher == "3"){
            string ciphered_message;
            string key;
            string message;
            cout << "enter the message you want to decipher: ";
            getline(cin >> ws, ciphered_message);
            cout << "enter the key: ";
            getline(cin >> ws, key);
            message = polybius_decrypt(ciphered_message, key);
            cout << "Decrypted message: " << message << '\n';
        }
    }

    else if (user_menu_operation == "3"){
        break;
    }

    
  } while (user_menu_operation != "3");

  return 0;
}