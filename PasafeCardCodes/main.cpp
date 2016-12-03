//
//  main.cpp
//  PasafeCardCodes
//
//  Created by Maxim Strzebkowski on 26.11.16.
//  Copyright © 2016 For Loop Studios. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array>
#include <fstream>              // Für das benutzen von txt files
#include <iterator>
#include <unistd.h>             // Für sleep
using namespace std;

bool numbers = true;            //Für spätere "Settings" --
bool characters = false;        //                         |
bool caseSensitive = false;     //                    <----

const int codeSize = 16;

// vector codes und array numOccurrance werden declared

vector<vector<int>> codes;
array<array<int,10>,codeSize> numOccurrance;

string number;

fstream codesFile;

void getSingleCodeVector() {
    //Macht aus user eingabe einen vector
    vector<int>singleCode;                      // Erstellt singleCode vector
    
    for(int i = 0; i < number.size(); i++){     // Looped durch code eingabe vom user
        int singleNum = number[i] - '0';        // Konvertiert String --> Int
        singleCode.push_back(singleNum);        // packt jedes einzelne eingabezeichen in den vector singlecode
    }
    codes.push_back(singleCode);                // stopfed singlecode vector in codes vector
    
    if(!codesFile.is_open()){                                                                   // Wenn datai noch nicht geöffnet
        codesFile.open("codes.txt", ios::app);                                                  // Öffne datei im append mode (nicht überschreiben)
        if(codesFile.is_open()){                                                                // Wenn datei geöffnet
            copy(singleCode.begin(), singleCode.end(), ostream_iterator<int>(codesFile));       // kopiere singleCode.anfang -- bis ---> ende als 'int' zu codeFile
            codesFile << endl;
            codesFile.close();                                                                  // Schließe codeFile
        }else{
            cout << "Couldnt Open File" << endl;
        }
    }
    return;
}

bool isNumberSizeOk(){
    if(number.size() == codeSize){
        return true;
    }else{
        return false;
    }
}

// checkt ob datei existiert
bool isFileExistent(string file){
    ifstream infile(file);
    return infile.good();
}

// Erstellt codes.txt wenn es nicht bereits existiert und speichert variablen in codes vector
void setupCodeFile(){
    if(isFileExistent("codes.txt")){
        codesFile.open("codes.txt");
        if(codesFile.is_open()){
            while(getline(codesFile,number)){
                getSingleCodeVector();
            }
        }else{
            cout << "Couldnt Open File" << endl;
        }
        codesFile.close();
    }else{
        fstream codesFile("codes.txt");
        codesFile.close();
    }
}

void getUserCode() {
    cout << "Enter Code: " << endl;
    cin >> number;                                      // User eingabe wird unter number gespeichert
    if(isNumberSizeOk()){                               // Wenn number = vorgegebene code länge
        getSingleCodeVector();                          // User eingabe wird in vector und in codesFile "gespeichert"
        cout << "[1] Enter another Code" << endl;       // Nochmal Code eingeben
        cout << "[0] Exit" << endl;                     // Exit
    }else{                                                                                      // Wenn number != vorgegebene code länge
        system("clear");
        cout << "ERROR: Code Invalid. Code must be " << codeSize << " digets long" << endl;     // Error ausgabe
        cout << "[1] Reenter Code" << endl;                                                     // Nochmal versuchen
        cout << "[0] Exit" << endl;                                                             // Exit
    }
    return;
}

void menu(){
    //Hier wird das menu interface erstellt
    
    cout << "MENU" << endl;
    cout << endl;
    cout << "[1] Add Code" << endl;
    cout << "[2] Show all Codes" << endl;
    cout << "[3] Compare Codes" << endl;
    cout << "[4] Exit" << endl;
    cout << endl;
    cout << "Choice: ";
    
}

void showCodes(){
    // Zeigt alle vom user eingegebenen codes
    
    for(int i = 0; i < codes.size(); i++) {             // Looped durch alle eingegebenen Codes --
        for(int j = 0; j < codes[i].size(); j++){       //                                        |
            cout << codes[i][j];                        // cout jedes einzelne zeichen            |
        }                                               //                                     <--
        cout << endl;
    }
    cout << endl;
    cout << "[0] Exit" << endl;
    cout << "choice: ";
}

void compareCodes(){
    // numOccurrance wird hier geleert
    
    for(int i = 0; i < numOccurrance.size(); i++){
        for(int j = 0; j < numOccurrance[i].size(); j++){
            numOccurrance[i][j] = 0;
        }
    }
    
    // Guckt nach Häufigkeit von zahlen in codes
    
    for(int i = 0; i < codes.size(); i ++){                     // Looped durch alle eingegebenen codes     ------------------------------
        for(int j = 0; j < codes[i].size(); j++){               // Looped durch jeden einzelenen eingegebenen code    ------------------  |
            for(int k = 0; k < numOccurrance[j].size(); k++){   // Looped durch numOccurrance      ----------------------------------   | |
                if(codes[i][j] == k){                           // wenn das eingegebene zeichen das ist welches gesucht wird         |  | |
                    numOccurrance[j][k] ++;                     // dann ++ häufigkeit                                                |  | |
                    break;                                      //                                                                   |  | |
                }                                               //                                                                   |  | |
            }                                                   //                            <--------------------------------------   | |
        }                                                       //                      <-----------------------------------------------  |
    }                                                           //               <--------------------------------------------------------
    
    // Schreibt häufigkeit der einzelenen zahlen an den einzelnen positionen
    
    for(int i = 0; i < numOccurrance.size(); i++){
        if(i + 1 < 10){
            cout << "0";
        }
        cout << i + 1 << "   ";
    }
    cout << endl;
    
    for(int i = 0; i < numOccurrance[1].size(); i++){       // Vorsicht!! Schleife Oben und unten vertauscht
        for(int j = 0; j < numOccurrance.size(); j++){      // Schleife wurde vertauscht um im querformat anzuzeigen
            cout << i << ": ";
            cout << numOccurrance[j][i];                    // Daher j und i auch vertauscht
            cout << " ";
        }
        cout << endl;
    }
    cout << " " << endl;
    cout << "[0] Exit" << endl;
}

int main() {
    
    setupCodeFile();
    
    int choice = 0;
    while(choice != 4){             // So lange 4 (Exit) nicht gewählt wurde lass programm weiter laufen
        switch(choice){
            case 0:                 // wenn 0
                system("clear");
                menu();             // zeichne menu
                cin >> choice;      // frag nach choice (wälche wahl wurde getroffen)
                break;
            case 1:
                system("clear");
                getUserCode();      // Eingabe für user code
                cin >> choice;
                break;
            case 2:
                system("clear");
                showCodes();        // Zeig alle eingegebene codes
                cin >> choice;
                break;
            case 3:
                system("clear");
                compareCodes();     // Zeig häufigkeit von zeichen an bestimmter stelle des codes
                cin >> choice;
                break;
            default:                                            // keins von den eingaben oben
                system("clear");
                cout << "Not a valid Choice" << endl;
                usleep(2000000);                                // Lass programm 2 sekunden warten
                choice = 0;
                break;
        }
    }
    return 0;
}
