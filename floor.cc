#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "chamber.h"
#include "item.h"
#include "gold.h"
#include "potion.h"
#include <iostream>//? 
#include <fstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

Floor ::~Floor(){reset();}
Floor::Floor(int level, string file): level{level},player{nullptr} {
	srand(time(NULL));
	ifstream ifs{file};
	string s;
	while (getline(ifs, s))	{
    vector <char> line;
    for( unsigned int i = 0; i< s.length(); i++){
    	line.emplace_back(s.at(i));
    }
    display.emplace_back(line);
	}
	origSymbol = '.';

	barrierLevel = rand()%5+1;
}

void Floor:: printFloor(){  
	for(unsigned int i= 0; i < display.size(); i++){
		for ( unsigned int j = 0; j < display.at(i).size(); j++){
			char c = (display.at(i)).at(j);
			if(c == 'W'||c == 'V'||c == 'N'||c =='D'||c == 'X'||c =='T'||c == 'M'){
				cout<<"\033[1m\033[31m"<<c<<"\033[0m";
			} else if(c == 'P'){
				cout<<"\033[1m\033[32m"<<c<<"\033[0m";
			} else if(c == 'G'){
				cout<<"\033[1m\033[33m"<<c<<"\033[0m";
			} else if(c == '@'){
				cout<<"\033[1m\033[34m"<<c<<"\033[0m";
			} else if(c == 'B'){
				cout<<"\033[1m\033[35m"<<c<<"\033[0m";
			} else {
				cout << "\033[1m\033[36m"<< c << "\033[0m";
			}
		}
		cout << endl;	
	}
	cout <<"\033[1m\033[36m"<<"Race: "<< player->get_race() << " Gold: " << player->getGold();
    cout << "                                                      Floor:" << level<<endl;
    cout << "HP: " << player->get_HP() << endl;
    cout << "Atk: " << player->get_Atk() << endl;
    cout << "Def: " << player->get_Def() << endl;
    cout << "Action: " << player->getAction() << endl<<"\033[0m"; 
}


void Floor::genGold() {
	srand(time(NULL));
  int chamberid;
  int goldtype;
  for (int i = 0; i < 10; i++) { //generate 10 gold
    chamberid = rand() % 5; //
    vector<int> pos = chambers[chamberid]->findRandom();
    display[pos[0]][pos[1]] = 'G';
    goldtype = rand() % 8;
    if (goldtype <= 4) { //5/8 normal
       auto g = make_shared<Gold> (pos[0], pos[1], "normal", 'G', 1, true);
       golds.emplace_back(g);
    } else if (goldtype <= 6) {//2/8 small  
       auto g = make_shared<Gold> (pos[0], pos[1],"small", 'G', 2, true);     
       golds.emplace_back(g);
    } else {//1/8 dragon
       auto g = make_shared<Gold> (pos[0], pos[1], "dragon hoard", 'G', 6, false);
       golds.emplace_back(g);
    }
  }
  if(level == barrierLevel){
  	chamberid = rand() % 5; //
    vector<int> pos = chambers[chamberid]->findRandom();
    display[pos[0]][pos[1]] = 'B';
  	auto g = make_shared<Gold> (pos[0], pos[1], "barrier suit", 'B', 0, false);
  	golds.emplace_back(g);
  }
}

   
 void Floor::genPlayer(){
 	srand(time(NULL));
  	int chamberid = rand() % 5; //
    player->setId(chamberid);
    vector<int> pos = chambers[chamberid]->findRandom();
    display[pos[0]][pos[1]] = '@';
    player->set_x(pos[0]);
    player->set_y(pos[1]);
   
 }

 void Floor::setPlayer (shared_ptr<Player> pp){
 	player = pp;
 }

 void Floor::genStair(){
 	srand(time(NULL));
 	int chamberid = rand() % 5;
    while(chamberid == player->getId()){ 
        chamberid = rand() % 5;
    }
    vector<int> pos = chambers[chamberid]->findRandom();
    display[pos[0]][pos[1]] = '\\';
 }

 void Floor::genPotion(){
 	srand(time(NULL));
 	int chamberid;
	for (int i = 0; i < 10; i++) {
    chamberid = rand() % 5; //generate a random num from 0-4

     vector<int> pos = chambers[chamberid]->findRandom();
    display[pos[0]][pos[1]] = 'P';
    int type = rand() % 6; //generate a random num from 0-5
    if (type == 0) {
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"RH", 'P', 10);
    potions.emplace_back(newpotion);
    } 
    else if (type == 1) {
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"BD", 'P', 5);
    potions.emplace_back(newpotion);
    } 
    else if (type == 2){
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"BA", 'P', 5);
    potions.emplace_back(newpotion);    
    } 
    else if (type == 3) {
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"WA", 'P', -5);
    potions.emplace_back(newpotion);
    } 
    else if (type == 4) {
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"PH", 'P', -10);	
    potions.emplace_back(newpotion);    
    } 
    else {
    auto newpotion = make_shared<Potion> (pos[0], pos[1],"WD", 'P', -5);
    potions.emplace_back(newpotion);
    }
  }
 }  

void Floor::genChamber(){
	for(int id = 0; id < 5; id++){
		auto c = make_shared<Chamber> (id, display);
		chambers.emplace_back(c);
	}

}

void Floor::genEnemy(){
	srand(time(NULL));
	int count_dragon;
	count_dragon = 0;
	for(unsigned int i = 0; i < golds.size(); i++){
		if(golds[i]->getGold() == 6||golds[i]->getGold() == 0){//dragon hoard or barrier suit
			golds[i]->setIspickable(0);
			count_dragon++;
			while(true){
				int possibility = rand()%8;
				if(possibility == 0){
					if(display[golds[i]->get_x()-1][golds[i]->get_y()-1] == '.'){
						display[golds[i]->get_x()-1][golds[i]->get_y()-1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()-1,golds[i]->get_y()-1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 1){
					if(display[golds[i]->get_x()-1][golds[i]->get_y()] == '.'){
						display[golds[i]->get_x()-1][golds[i]->get_y()] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()-1,golds[i]->get_y(),golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 2){
					if(display[golds[i]->get_x()-1][golds[i]->get_y()+1] == '.'){
						display[golds[i]->get_x()-1][golds[i]->get_y()+1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()-1,golds[i]->get_y()+1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 3){
					if(display[golds[i]->get_x()][golds[i]->get_y()-1] == '.'){
						display[golds[i]->get_x()][golds[i]->get_y()-1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x(),golds[i]->get_y()-1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 4){
					if(display[golds[i]->get_x()][golds[i]->get_y()+1] == '.'){
						display[golds[i]->get_x()][golds[i]->get_y()+1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x(),golds[i]->get_y()+1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 5){
					if(display[golds[i]->get_x()+1][golds[i]->get_y()-1] == '.'){
						display[golds[i]->get_x()+1][golds[i]->get_y()-1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()+1,golds[i]->get_y()-1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else if(possibility == 6){
					if(display[golds[i]->get_x()+1][golds[i]->get_y()] == '.'){
						display[golds[i]->get_x()+1][golds[i]->get_y()] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()+1,golds[i]->get_y(),golds[i]);
						enemies.emplace_back(d);
						break;
					}
				} else{
					if(display[golds[i]->get_x()+1][golds[i]->get_y()+1] == '.'){
						display[golds[i]->get_x()+1][golds[i]->get_y()+1] = 'D';
						auto d = make_shared<Dragon> (golds[i]->get_x()+1,golds[i]->get_y()+1,golds[i]);
						enemies.emplace_back(d);
						break;
					}
				}
			}
		}
	}
	for(int i = 0; i < 20 - count_dragon; i++){//generate other enemies
		int chamberNum = rand()%5;
		int enemyNum = rand()%18;
		if(enemyNum < 4){//werewolf
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'W';
			auto w = make_shared<Werewolf> (pos[0], pos[1]);
			enemies.emplace_back(w);
		} else if(enemyNum < 7){//vampire
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'V';
			auto v = make_shared<Vampire> (pos[0], pos[1]);
			enemies.emplace_back(v);
		} else if(enemyNum < 12){//goblin
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'N';
			auto g = make_shared<Goblin> (pos[0], pos[1]);
			enemies.emplace_back(g);
		} else if(enemyNum < 14){//troll
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'T';
			auto t = make_shared<Troll> (pos[0], pos[1]);
			enemies.emplace_back(t);
		} else if(enemyNum < 16){//phoenix
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'X';
			auto p = make_shared<Phoenix> (pos[0], pos[1]);
			enemies.emplace_back(p);
		} else{//merchant
			vector<int> pos = chambers[chamberNum]->findRandom();
			display[pos[0]][pos[1]] = 'M';
			auto m = make_shared<Merchant> (pos[0], pos[1]);
			enemies.emplace_back(m);
		}
	}
}

vector<int> Floor::checkTile(string dir){
	int row = player->get_x();
	int col = player->get_y();
	vector<int> temp;
	if(dir == "no"){
		row--;
	} else if(dir == "ne"){
		row--;
		col++;
	} else if(dir == "ea"){
		col++;
	} else if(dir == "se"){
		row++;
		col++;
	} else if(dir == "so"){
		row++;
	} else if(dir == "sw"){
		row++;
		col--;
	} else if(dir == "we"){
		col--;
	} else if(dir == "nw"){
		row--;
		col--;
	}
	temp.emplace_back(row);
	temp.emplace_back(col);
	return temp;
}

bool Floor::movePlayer(string dir){
	int x1 = player->get_x();
	int y1 = player->get_y();
	char nextTile = display[checkTile(dir)[0]][checkTile(dir)[1]];
	if(nextTile == '.' || nextTile == '+' || nextTile == '#'){
		player->move(dir);
		display[x1][y1]=origSymbol;
		int x2 = player->get_x();
		int y2 = player->get_y();
		display[x2][y2]='@';
		origSymbol=nextTile;
		return true;
	} else if(nextTile == 'G'){
		for(unsigned int i = 0; i < golds.size(); i++){
			if((golds[i]->get_x() == checkTile(dir)[0]) && (golds[i]->get_y() == checkTile(dir)[1])){
				if(golds[i]->isPickable()){
					player->setGold(golds[i]);
					string goldaction = player->getAction();
					golds.erase(golds.begin()+i);
					nextTile = '.';
					player->move(dir);
					player->setAction(player->getAction() +goldaction);
					display[x1][y1]=origSymbol;
					int x2 = player->get_x();
					int y2 = player->get_y();
					display[x2][y2]='@';
					origSymbol=nextTile;
					return true;
				}
			}
		}
	} else if(nextTile == 'B'){
		for(unsigned int i = 0; i < golds.size(); i++){
			if((golds[i]->get_x() == checkTile(dir)[0]) && (golds[i]->get_y() == checkTile(dir)[1])){
				if(golds[i]->isPickable()){
					golds.erase(golds.begin()+i);
					nextTile = '.';
					player->move(dir);
					display[x1][y1]=origSymbol;
					int x2 = player->get_x();
					int y2 = player->get_y();
					display[x2][y2]='@';
					origSymbol=nextTile;
					player->setBarrier(true);
					return true;
				}
			}
		}
	}
	return false;
}

bool Floor::withinBlock(int ex, int ey){ //checks if <ex,ey> is neighbour of player
	int x1 = player->get_x();
	int y1 = player->get_y();
	if((ex == x1-1 && ey == y1-1)||(ex == x1-1 && ey == y1)||(ex == x1-1 && ey == y1+1)){
		return true;
	} else if((ex == x1 && ey == y1-1)||(ex == x1 && ey == y1+1)){
		return true;
	} else if((ex == x1+1 && ey == y1-1)||(ex == x1+1 && ey == y1)||(ex == x1+1 && ey == y1+1)){
		return true;
	}
	return false;
}

void Floor::moveToNeighbour(shared_ptr<Enemy> pe){
	srand(time(NULL));
	int x1 = pe->get_x();
	int y1 = pe->get_y();
	while(true){
		int random = rand() % 9;
		if(random == 0){
			if(checkDisplay(x1-1,y1-1,'.')){
				pe->move("nw");
				display[x1-1][y1-1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 1){
			if(checkDisplay(x1-1,y1,'.')){
				pe->move("no");
				display[x1-1][y1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 2){
			if(checkDisplay(x1-1,y1+1,'.')){
				pe->move("ne");
				display[x1-1][y1+1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 3){
			if(checkDisplay(x1,y1-1,'.')){
				pe->move("we");
				display[x1][y1-1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 4){
			if(checkDisplay(x1,y1+1,'.')){
				pe->move("ea");
				display[x1][y1+1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 5){
			if(checkDisplay(x1+1,y1-1,'.')){
				pe->move("sw");
				display[x1+1][y1-1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 6){
			if(checkDisplay(x1+1,y1,'.')){
				pe->move("so");
				display[x1+1][y1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else if(random == 7){
			if(checkDisplay(x1+1,y1+1,'.')){
				pe->move("se");
				display[x1+1][y1+1] = display[x1][y1];
				display[x1][y1] = '.';
				return;
			}
		} else{ //does not move
			return;
		}
	}	
}

void Floor::moveEnemy(){
	for(unsigned int i = 0; i < enemies.size(); i++){
		if(enemies[i]->get_notation() == 'D'){
			shared_ptr<Gold> hoardorBarrier = enemies[i]->getDragonHoard();
			if(withinBlock(hoardorBarrier->get_x(), hoardorBarrier->get_y())){
				enemies[i]->setHostile(true);
			} else{
				enemies[i]->setHostile(false);
			}
		}
		if(!withinBlock(enemies[i]->get_x(), enemies[i]->get_y())){
			if(enemies[i]->get_notation() != 'D'){
				moveToNeighbour(enemies[i]);
			}
		} 
		if(withinBlock(enemies[i]->get_x(), enemies[i]->get_y())){ //attack if hostile
			if(enemies[i]->getHostile()){
				enemies[i]->attack(player);
			}
		}
	}
}

bool Floor::usePotion(string dir){
	int x1 = checkTile(dir)[0];
	int y1 = checkTile(dir)[1];
	char nextTile = display[x1][y1];
	if(nextTile == 'P'){
		for(unsigned int i = 0; i < potions.size(); i++){
			if(potions[i]->get_x() == x1 && potions[i]->get_y() == y1){
				player->applyPotion(potions[i]);
				display[x1][y1] = '.';
				potions.erase(potions.begin()+i);
				return true;
			}
		}
	} 
	return false;
}

int Floor::getLevel(){
	return level;
}

void Floor::setLevel(int level){
    this->level = level;
}
void Floor::sethasWon(bool won){
	hasWon = won;
}

bool Floor:: hasLost(){	
	return player->get_HP() <= 0;
}

int Floor:: getGold()
{
	return player->getGold();
}
void Floor::setAction(std::string action)
{
	player->setAction(action);
}
bool Floor::checkDisplay (int x, int y,char c)
{
	return display[x][y] == c;
}


void Floor::readfile(string file) {
    ifstream ifs{file};
	string s;
	while (getline(ifs, s))	{
    vector <char> line;
    for( unsigned int i = 0; i< s.length(); i++){
    	line.emplace_back(s.at(i));
    }
    display.emplace_back(line);
	}
	origSymbol = '.';
}

void Floor::reset() {
	   //player.clear();
	for (unsigned int i = 0; i < display.size(); i++) {
		display[i].clear();
	 }
	display.clear();
	enemies.clear();
	chambers.clear();
	potions.clear();
	golds.clear();
}


int Floor::enemyIndex(int x, int y ) {
	for (unsigned int id = 0; id <enemies.size(); id++){
     if( enemies[id]->get_x() == x && enemies[id]->get_y() == y)
     	return id;
	}
	return 0;
}


void Floor::pAttack(string dir) {
    vector<int> pos = checkTile(dir);
    int enemyindex  = enemyIndex(pos[0], pos[1]);
    player->damage(enemies[enemyindex], enemies);
    if (enemies[enemyindex]->get_HP() <= 0) { 
    	if(enemies[enemyindex]->get_notation() == 'M'){ //merchant dies, spawn merchant hoard
    		int x = enemies[enemyindex]->get_x();
    		int y = enemies[enemyindex]->get_y();
    		enemies.erase(enemies.begin()+enemyindex);
    		auto g = make_shared<Gold> (x, y, "merchant hoard", 'G', 4, true);
    		golds.emplace_back(g);
    		display[x][y] = 'G';
    	} else{
    		display[enemies[enemyindex]->get_x()][enemies[enemyindex]->get_y()] = '.';
        	enemies.erase(enemies.begin()+enemyindex); 
    	}
  	}
}


void Floor::newLevel(){
	player->set_Atk(player->getBaseAtk());
    player->set_Def(player->getBaseDef());
}


void Floor::readFloor(string file) {
	ifstream ifs{file};
	string s;
	int x = 0, y=0;
	char temp;
	int baseBegin = 25 * (level-1);
    if(level != 1){
    	for(int i = 0; i < (level-1)*25; i++){
    		getline(ifs,s);
    	}
    }
	for (int begin = baseBegin; begin < baseBegin + 25; ++begin) {
		getline(ifs, s);
	  	vector <char> line;
	    for (unsigned int i = 0; i < s.length(); ++i) {
			if (s.at(i) == '0') {
				line.emplace_back('P');
				auto potion = make_shared<Potion> (begin- baseBegin, i, "RH", 'P', 10);
				potions.emplace_back(potion);
			} else if (s.at(i) == '1') {
			   	line.emplace_back('P');
				auto potion = make_shared<Potion> (begin - baseBegin, i,"BA", 'P', 5);
				potions.emplace_back(potion);				   
	        } else if (s.at(i) == '2') {
			   line.emplace_back('P');
				auto potion = make_shared<Potion> (begin - baseBegin, i,"BD", 'P', 5);
				potions.emplace_back(potion);       
			} else if (s.at(i)== '3') {  				                              
			   	line.emplace_back('P');
				auto potion = make_shared<Potion> (begin - baseBegin, i,"PH", 'P', -10);
				potions.emplace_back(potion);
			} else if (s.at(i)== '4') {
				line.emplace_back('P');
				auto potion = make_shared<Potion> (begin - baseBegin, i,"WA", 'P', -5);
				potions.emplace_back(potion);
			} else if (s.at(i) == '5') {
			   	line.emplace_back('P');
				auto potion = make_shared<Potion> (begin - baseBegin, i,"WD", 'P', -5);
				potions.emplace_back(potion);				   	            
			} else if (s.at(i) == '6') {
			   	line.emplace_back('G');
				auto gold = make_shared<Gold> (begin - baseBegin, i, "normal", 'G', 1, true);
				golds.emplace_back(gold);
            } else if (s.at(i) == '7') {
				line.emplace_back('G');
				auto gold = make_shared<Gold> (begin - baseBegin , i,"small", 'G', 2, true);
				golds.emplace_back(gold);				   
			} else if(s.at(i) == '8') {
				line.emplace_back('G');					
				auto gold = make_shared<Gold> (begin - baseBegin, i, "merchant hoard", 'G', 4, true);
				golds.emplace_back(gold);		
			} else if (s.at(i) == '9') {
				   /*vector<int> pos;
				   pos.emplace_back(start-25*(curFloor-1));
				   pos.emplace_back(i);
				   dGoldPos.emplace_back(pos);*/
			   	   //auto gold = make_shared<Gold> (begin - baseBegin + 25, i,"dragon hoard", 'G', 6, false);
				x = begin - baseBegin ;
				y = i;
				temp = s.at(i);
				line.emplace_back('G');
			} else if (s.at(i) == 'B'){
				x = begin - baseBegin ;
				y = i;
				temp = s.at(i);
				line.emplace_back('B');
			} else  if (s.at(i) == '@') { 
				  /*for (int j = 0; j < 5; ++j) {
					  bool within = theChamber[j]->withinRange(start-25*(curFloor-1), i);
					  if (within) {
						  thePlayer->setChamberId(j+1);
				  }
			}*/
				player->set_x(begin - baseBegin );
				player->set_y(i);
				line.emplace_back('@');
			} else if (s.at(i) == 'V') {
				auto enemy = make_shared<Vampire>(begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('V');
            } else if (s.at(i) == 'W') {
				auto enemy = make_shared<Werewolf> (begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('W');
	        } else if (s.at(i)== 'N') {
				auto enemy = make_shared<Goblin> (begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('N');
		    } else if (s.at(i)== 'M') {
				auto enemy = make_shared<Merchant> (begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('M');
		    } else if (s.at(i)== 'T') {
				auto enemy = make_shared<Troll> (begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('T');
		    } else if (s.at(i) == 'X') {
				auto enemy = make_shared<Phoenix>(begin - baseBegin, i);
				enemies.emplace_back(enemy);
				line.emplace_back('X');
		    } else if (s.at(i)== 'D') {
		    	if(temp == '9'){
		    		auto gold = make_shared<Gold> (x, y,"dragon hoard", 'G', 6, false);
		    		golds.emplace_back(gold);
		    		auto enemy = make_shared<Dragon>(begin - baseBegin, i, gold);
		    		enemies.emplace_back(enemy);
		    	} else if(temp == 'B'){
		    		auto gold = make_shared<Gold> (x, y,"barrier suit", 'B', 0, false);
		    		golds.emplace_back(gold);
		    		auto enemy = make_shared<Dragon>(begin - baseBegin, i, gold);
					enemies.emplace_back(enemy);
		    	}
				   /*vector<int> pos;
				   pos.emplace_back(start-25*(curFloor-1));
                                   pos.emplace_back(i);					 
				   dragonPos.emplace_back(pos);*/
			   	   
				line.emplace_back('D');
			} else {
				line.emplace_back(s.at(i));
			}
		}
		display.erase(display.begin());
		display.emplace_back(line);
	}
}


