#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "player.h"
#include "character.h"
#include "floor.h"
#include "chamber.h"

using namespace std;


bool check (shared_ptr<Floor> floor, string dir, char c) {
    return floor->checkDisplay(floor->checkTile(dir)[0],floor->checkTile(dir)[1] ,c);
}

int main(int argc, char* argv[]) {
    string filename;
    if (argc ==2) {
        filename = argv[1];
    }


    while(1) {
        cout << "Welcome to CCK3+!" << endl;

        ifstream intro{"welcome.txt"};
        string line;
        while(getline(intro, line)){
            cout << line << endl;
        }

        auto newfloor = make_shared<Floor>(1);
        newfloor->genChamber();
        //newfloor->printFloor();
        char race;
        cin >> race;
        while(1) {
            if (race == 'h') {
                auto player = make_shared<Human>();
                newfloor->setPlayer(player);

                break;
            } else if (race == 'd') {
                auto player = make_shared<Dwarf>();
                newfloor->setPlayer(player);

                break;
            } else if (race == 'e') {
                auto player = make_shared<Elf>();
                newfloor->setPlayer(player);

                break;
            } else if (race == 'o') {
                auto player = make_shared<Orc>();
                newfloor->setPlayer(player);

                break;
            }
            else {
                cout << "Please enter a valid command for players" << endl;
                cin >> race;
            }
        }
        
        if(argc == 1) {
            newfloor->genPlayer();
            newfloor->genStair();
            newfloor->genPotion();
            newfloor->genGold();
            newfloor->genEnemy();
        }
        if (argc ==2){
            newfloor->readFloor(filename);
        }
        newfloor->printFloor();

        cout <<"\033[1m\033[36m"<< "Here are the commands you use:" << endl;
        cout << "DIR: no, so, ea, we, ne, se, sw, nw" << endl;
        cout << "USE POTION: u <direction>" << endl;
        cout << "ATTACK ENEMY: a <direction>" << endl;
        cout << "RESET GAME: r" << endl;
        cout << "QUIT: q" << endl << "\033[0m";
        string c;
        while (cin >> c) {
            if (c == "no" ||c == "so" ||c == "ea"
                ||c ==  "we" ||c == "ne" ||c == "se" ||c == "sw" ||c == "nw") {
                if (check(newfloor,c, '\\')) {
                    if(newfloor->getLevel() == 5) {
                        newfloor->sethasWon(true);
                        
                        ifstream intro{"win.txt"};
                        string line;
                        while(getline(intro, line)){
                            cout << line << endl;
                        }
                        cout << "You've won!! Your final score is: ";
                        if(race == 'h') { // add getGold function
                            cout << (newfloor->getGold()*1.5) << endl;
                        }
                        else if(race == 'd') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'o') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'e') {
                            cout <<newfloor->getGold() << endl;
                        }
                        break;
                    }
                    else {
                        newfloor->setLevel(newfloor->getLevel() + 1);
                        newfloor->setAction("Welcome to a new floor!"); // add getplayer function
                        // add this function
                        newfloor->reset();
                        newfloor->readfile("default.txt");
                        newfloor->genChamber();
                        if (argc == 2){
                            newfloor->readFloor(filename);
                            newfloor->newLevel();
                        } else if(argc == 1){
                            //auto newfloor = make_shared<Floor>(newfloor->getLevel() + 1);                            
                            newfloor->genPlayer();
                            newfloor->newLevel();
                            newfloor->genStair();
                            newfloor->genPotion();
                            newfloor->genGold();
                            newfloor->genEnemy();

                        }
                        newfloor->printFloor();
                    }
                }
                else if (newfloor->movePlayer(c)) {
                    //cout << "moved player" << endl;
                    newfloor->moveEnemy();
                    newfloor->printFloor();
                    if (newfloor->hasLost()){
                        ifstream intro{"dead.txt"};
                        string line;
                        while(getline(intro, line)){
                            cout << line << endl;
                        }
                        cout << "You've lost!! Your final score is: ";
                        if(race == 'h') { // add getGold function
                            cout << (newfloor->getGold()*1.5) << endl;
                        }
                        else if(race == 'd') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'o') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'e') {
                            cout <<newfloor->getGold() << endl;
                        }
                        break;
                    }
                } else {
                    cout << "Invalid command" <<endl;
                }
            }
                // 
            else if (c == "a") {
                cin >> c;  // read in the direction  and check if enemy is in the area
                if (check(newfloor,c, 'W') || check(newfloor,c, 'V') || check(newfloor,c, 'D') ||
                    check(newfloor,c, 'M') || check(newfloor,c, 'N') || check(newfloor,c, 'X') ||
                    check(newfloor,c, 'T')) {
                    newfloor->pAttack(c);  // class floor's pAttack
                    newfloor->moveEnemy();
                    newfloor->printFloor();
                    if (newfloor->hasLost()){
                        ifstream intro{"dead.txt"};
                        string line;
                        while(getline(intro, line)){
                            cout << line << endl;
                        }
                        cout << "You've lost!! Your final score is: ";
                        if(race == 'h') { // add getGold function
                            cout << (newfloor->getGold()*1.5) << endl;
                        }
                        else if(race == 'd') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'o') {
                            cout << newfloor->getGold() << endl;
                        }
                        else if(race == 'e') {
                            cout <<newfloor->getGold() << endl;
                        }
                        break;
                    }
                } else {
                    cout << "No enemies in the area" << endl;
                }
            }
            else if (c == "r") {
                newfloor->reset(); //add
                break;
            }
            else if (c == "q") {
                break;
            }
            else if(c == "u"){
                cin >> c;
                if(newfloor->usePotion(c)){
                    newfloor->moveEnemy();
                    newfloor->printFloor();
                } else {
                    cout << "Not Valid, try again " << endl;
                }
            }

            else {
                cout << "Not Valid, try again " << endl;
            }
        }
        if (c == "q") {
            ifstream intro{"bye.txt"};
            string line;
            while(getline(intro, line)){
                cout << line << endl;
            }
            break;
        }
    }
}


