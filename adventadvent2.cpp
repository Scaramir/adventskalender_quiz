//Maximilian Otto - 06.12.2020 - adventadvent2.cpp
//compile with: g++ -std=c++14 -static-libgcc -static-libstdc++ -O3 -pedantic adventadvent2.cpp -o adventadvent2
//still in progress

#include <iostream>
#include <fstream> 
#include <string.h>
#include <algorithm>
#include <vector>
#include <cctype> 
#include <stdio.h>
#ifdef _WIN32      //for using the function sleep
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>    


using namespace std;

vector<string> spiel = {"Space Colony", 
                        "Sims 2", 
                        "Spacetanks", 
                        "Rollercoaster Tycoon 3", 
                        "Itch!", 
                        "Ark", 
                        "Tropico 6", 
                        "Wii Super Mario Bros.", 
                        "Lego Star Wars", 
                        "Railroad Tycoon 3", 
                        "Tetris", 
                        "Spore Creature Creator", 
                        "Need for Speed - Most Wanted", 
                        "Dungeon Keeper 2", 
                        "Herrscher des Olymp - Zeus", 
                        "Civilization VI", 
                        "Far Cry: Primal"
                        };

vector<string> frage = {"Wie lautet der Name des einzigen Norwegers der Crew?",
                        "Wessen Frau ist auf mysterioese Art und Weise verschwunden?\n    Tipp: -> Schoensichtingen\n", 
                        "Wie viele Spacetaler kostet die teuerste Waffe?",
                        "Wo findet Szenario 1 statt?",
                        "Wie nennt sich der regenbogenfarbene Floh?\nTipp: Puzzlespiel\n",
                        "Ab welchem Level kann man \"Notes\" craften?",
                        "Was ist das beste Accessoire fuer den Praesidenten?",
                        "Mit wessen Geburtstag beginnt die Story?",
                        "Wie heisst der erste Charakter, den man in Episode 1 freischaltet?",
                        "Wo spielt das erste Tutorial?",
                        "Welche Farbe hat der Wuerfel?",
                        "Wofuer steht das Schmetterlingssymbol?",
                        "",
                        "Wie heisst der erste kampagnengegner?",
                        "Gegen was fuer eine Kreatur kaempft Zeus im Vorspann?",
                        "Wie lautet der hoechste Schwierigkeitsgrad?",
                        ""
                        };

vector<string> antwort = {"stig",
                          "mortimer grusel",
                          "dickerchen",
                          "vanilla hills",
                          "jokerfloh",
                          "1",
                          "schnuller",
                          "prinzessin peach",
                          "c-3po",
                          "italien",
                          "gelb",
                          "hippity hüpf",
                          "",
                          "fürst antonios",
                          "hydra",
                          "gottheit",
                          ""
                        };

vector<string> symbol = {"Tuerchen",
                         "Musik",
                         "Kakao",
                         "Wein",
                         "Schnee",
                         "Advent",
                         "Frost",
                         "Stern",
                         "Marzipan",
                         "Kamin",
                         "Handschuhe",
                         "Schmetterlingsymbol",
                         "Lichter",
                         "",
                         "Geschenk",
                         "Socken",
                         "Zimt",
                         ""
                        };

/**
 * returns last line of file
 */
string file_reader(){
    ifstream myfile ("saved_game.txt");
    string saved_game; 
    if(!myfile.good()){
        cout << "\n---Error1: Cannot open file 'saved_game.txt'---\n---Let's start with day 1---\n";
        return "0";
    }
    while(getline(myfile, saved_game));
    myfile.close();
    return saved_game;
}

/**
 * writes every number of so far solved riddles in a separate row in the save-file
 * return success state
 */
int file_writer(int d){
    ofstream myfile ("saved_game.txt");
    if(!myfile.is_open()){
        cout << "\n---Error2: Cannot save your progress to 'saved_game.txt'.---\n---Have you tried turning it off and on again?---\n";
        return 1;
    }
    myfile << to_string(1);
    string curr_saved_game = "";
    for(int i = 2; i <= d; ++i){
        curr_saved_game = to_string(i);
        myfile << "\n" << curr_saved_game;
    }
    myfile.close();
    return 0;
}

/**
 * unrolling text on terminal
 * receives text and colour-value; default=10, aka green, red would be ==12
 */ 
void terminal_fill(string s, int c = 10){
    if(s.empty())
        return;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);

    for (uint16_t i = 0; i < s.size()-1; ++i){
        cout << s[i];
        Sleep(35);
    }
    
    cout << endl;
    return;
}

/**
 * liste alle bisher gelösten Rätsel, also d-1, mit zugehoerigen Symbolen auf
 */ 
void listing(int d){
    cout << "\n######################################\n\n";
    terminal_fill("Bisher gespielte Spiele mit geloesten Fragen fuehrten Dich zu folgenden \"Tuerchen\": ");
    for (int i = 0; i < d-1 ; ++i){   
        cout << "    Tag " << (i+1) << ": " << spiel[i] << " --> Antwort: " << symbol[i] << endl;
        Sleep(600);
    }
    cout << endl;
    return;
}

/**
 * input: to be printed string
 * returns user-input
 * colour: light blue
 */
string ask_for_input(string s){
    cin.clear();                                                //#windoof
    terminal_fill(s, 18);
    string b = "";
    getline(cin, b);
    cin.clear(); 
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);   //alles in Kleinbuchstaben umwandeln.
    return b; 
}

int fragen(int a);                                              //redefine later or write a hpp-file instead #compileOrder
/**
 * asks user, if he wants to continue with the next question
 * answer is delivered
 */
bool proceed_quiz(){
    string antwort = ask_for_input("Moechtest Du schon mal das naechste Quiz angehen und etwas vorarbeiten?\n    Type 'yes' or 'no':");
    if (strstr(antwort.c_str(), "y")){
        return true;
    }
    return false;
}

/**
 * alternative games with according Q&As
 * returns alternative correct answer
 */
string alternative_quiz(){
    string alt_games[] = {"alternative1", "alternative2", "alternative3", "alternative4", "alternative5", "alternative6"};
    string alt_quests[] = {"altquest1", "altquest2", "altquest3", "altquest4", "altquest5", "altquest6"};
    string alt_ants[] = {"altant1", "altant2", "altant3", "altant4", "atant5", "altant6"};
    
    terminal_fill("\n\nAlternative Spiele waeren:");
    for(size_t i = 1; i <= sizeof(alt_games)/sizeof(alt_games[0]); ++i ){
        cout << "    " << i << ".) " << alt_games[i-1] << endl;
        Sleep(600);
    }
    int alt_chosen = stoi(ask_for_input("\n\nWaehle eine Option, indem du einfach nur die Nummer des gewuenschten Spiels eintippst: "));
    cout << "    " << alt_games[alt_chosen -1] << endl;
    terminal_fill("Deine zugehoerige Frage lautet: ");
    cout << "    " << alt_quests[alt_chosen -1] << endl;
    return alt_ants[alt_chosen -1];
}

/**
 * receives number of current riddle(/day)
 * it's a game
 * recursion after wrong answer does not terminate
 */ 
int fragen(int a){
    //Fehlerabfang:
    if(a > 24){
        terminal_fill("Herzlichen Glueckwunsch, Du hast es geschafft!",13);
        terminal_fill("Frohe Weihnachten!\n",22);
        return 1;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);          //make sure to go back to green again:
    SetConsoleTextAttribute(hConsole, 10);
    //Texts:
        terminal_fill("\nHeute ist der ");
        cout << a;
        terminal_fill(".12.2020 \nund auf Dich wartet ein neues Raetsel!");
        cout << "\n######################################";
        terminal_fill("\n\nDein heutiges Spiel heisst:");
        cout << "    " << spiel[a-1] << endl;
        terminal_fill("Und deine Frage dazu:");
        cout << "    " << frage[a-1] << endl;
    ///
    string c_answer = "";
    string accept = ask_for_input("Akzeptierst Du diese Aufgabe, oder moechtest Du ein anderes\nSpiel und Raetsel als Alternative?\n    Type 'yes' to accept or 'no' to get a new game:");
    if( strstr(accept.c_str(), "n")){
        c_answer = alternative_quiz();
    }
    ///
    string b = ask_for_input("\n\nBitte gib nun deine Antwort ein:");
    if( strstr(b.c_str(), antwort[a-1].c_str()) ||  strstr(b.c_str(), c_answer.c_str())){              //Checken, ob in der Antwort das richtige Wort enthalten ist
        terminal_fill("\nDiese Antowrt ist korrekt.");
        terminal_fill("\nDein Adventskalendertuerchen fuer heute hat das Symbol\n    ");
        cout << symbol[a-1];
        terminal_fill(" \n\ndarauf. ");
        file_writer(a);
        if(proceed_quiz())                                      //wanna continue? 
            fragen((stoi(file_reader()) +1));
    } 
    else {
        terminal_fill("\n\n--Something happend... \n--I am crashing.. \n-- :o  \n--I am trying to restart myself.\n--...\n\n\n", 12);
        Sleep(1000);
        cout << "--...\n\n\n";
        Sleep(1500);
        fragen(a);                                              //wanna see me do it again? 
    }
    return 0;
}

//##################################################################################
int main() {
    terminal_fill("Hallo.\n \n");
    
    int a = stoi(file_reader()) + 1;                        //last solved riddle +1
    //cin.ignore();                                               //chechpoint;
    cin.clear();
    listing(a);                                                 //Liste aufrufen
    fragen(a);                                                  //Quiz

    //exit:
    terminal_fill("\n\n\n---To end this programm, please press 'Enter'---", 12);
    cin.ignore();

    return 0;
}