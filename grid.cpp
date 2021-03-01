#include "grid.h"

/////////////////////////////////////////////Shop
Shop::Shop() {
    int number = rand() % 2 + 3;                    
    for (int i = 0; i < number; i++) {
        Item* weapon = new Weapon(rand() % 500 + 500, rand() % 15 + 10, rand() % 1);
        items.push_back(weapon);   
    }
    number = rand() % 2 + 3;
    for (int i = 0; i < number; i++) {
        Item* armor = new Armor(rand() % 500 + 500, rand() % 15 + 10);
        items.push_back(armor);   
    }
    number = rand() % 1 + 2;
    for (int i = 0; i < number; i++) {
        Item* potion = new Potion(rand() % 5, rand() % 200 + 100, rand() % 5 + 5);
        items.push_back(potion);   
    }
    int type = rand() % 4;          // there is a change a shop has not spells
    if (type == 0) {
        Spell* icespell = new IceSpell(rand() % 1000 + 1000, rand() % 17 + 13);
        spells.push_back(icespell);
    }
    else if (type == 1) {
        Spell* firespell = new FireSpell(rand() % 1000 + 1000, rand() % 17 + 13);
        spells.push_back(firespell);
    }
    else if(type == 2) {
        Spell* lightingspell = new LightingSpell(rand() % 1000 + 1000, rand() % 17 + 13);
        spells.push_back(lightingspell);
    }
}

Shop::~Shop(){
    for(int i = 0; i < items.size(); i++){
        delete items.at(i);
    }
    items.clear();
    for(int i = 0; i < spells.size(); i++){
        delete spells.at(i);
    }
    spells.clear();
}

void Shop::print(vector<Hero*> heroes) {
    system ("clear");
    cout << "\033[1m\033[37m" << "~~~~~~~ S H O P ~~~~~~~" << "\033[0m" << endl;
    cout << "Actions:\n1. Browse Items\n2. Browse Spells\n3. Sell\n4. Exit \n\nAction(1-4): ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > 4) {
            cout << "Invalid action. Please, try again!" << endl;
        }
    } while (action < 1 || action > 4);
    system ("clear");
    if (action != 4) {
        if (action == 1) {
            cout << "The items are:" << endl;
            for (int i = 0; i < items.size(); i++) {
                cout << i+1 << ". ";
                if (items.at(i)->getType() == 0) {
                    cout << "Weapon: ";
                }
                else if (items.at(i)->getType() == 1) {
                    cout << "Armor: ";
                }
                else {
                    cout << "Potion: ";
                }
                cout << items.at(i)->getName() << " Cost: " << items.at(i)->getPrice() << endl;
            }
            cout << items.size()+1 << ". Back" << endl;
            cout << "\nAction:";
            do {
                cin >> action;
                if (action < 1 || action > items.size() + 1) {
                    cout << "Invalid action. Please, try again." << endl;
                }
            } while (action < 1 || action > items.size() + 1);
            system ("clear");
            if (action != items.size() + 1)  {
                int itemid = action - 1;
                cout << "1. Buy\n2. Info\n3. Cancel\n\nAction(1-3): "; 
                do {
                    cin >> action;
                    if (action < 1 || action > 3 ) {
                        cout << "Invalid action. Please, try again!" << endl;
                    }
                } while (action < 1 || action > 3);
                ////////////////////////////////////////////////Buy items
                if (action == 1) {
                    cout << "\nWhich hero should buy the item?" << endl;
                    for(int i = 0; i < heroes.size(); i++) {
                        cout << i+1 << ". " << heroes.at(i)->getName() << " Coins: " << heroes.at(i)->getCoins() << endl;
                    }
                    cout << heroes.size() + 1 << ". Back" << endl;
                    cout << "Select a hero(1-" << heroes.size() + 1 << "): ";
                    do {
                        cin >> action;
                        if (action < 1 || action > heroes.size() + 1 ) {
                            cout << "Invalid action. Try again" << endl;
                        }
                    } while (action < 1 || action > heroes.size() + 1);
                    if (action != heroes.size() + 1) {
                        int selected = action - 1;
                        heroes.at(selected)->BuyItem(items.at(itemid));
                        items.erase(items.begin() + itemid);
                        cout << "Continue shopping? (yes/no)" << endl;
                        cout << "Answer(yes/no): ";
                        string answer;
                        do {
                            cin >> answer;
                            if (answer != "yes" && answer != "no") {
                                cout << "Invalid answer. Please, try again." << endl;
                            }
                        } while (answer != "yes" && answer != "no");
                        if (answer == "yes"){
                            print(heroes);
                        } 
                    }
                    else {
                        print(heroes);
                    }
                }
                ////////////////////////////////////////info
                else if (action == 2) {
                    items.at(itemid)->print();
                    cout << "Do you wanna buy " << items.at(itemid)->getName() << "?" << endl;
                    cout << "Answer(yes/no): ";
                    string answer;
                    do {
                        cin >> answer;
                        if (answer != "yes" && answer != "no") {
                            cout << "Invalid answer. Please, try again." << endl;
                        }
                    } while (answer != "yes" && answer != "no");

                    if (answer == "yes") {
                        cout << "\nWhich hero should buy the item?" << endl;
                        for(int i = 0; i < heroes.size(); i++) {
                            cout << i+1 << ". " << heroes.at(i)->getName() << " Coins: " << heroes.at(i)->getCoins() << endl;
                        }
                        cout << heroes.size() + 1 << ". Back" << endl;
                        cout << "Select a hero(1-" << heroes.size() + 1 << "): ";
                        do {
                            cin >> action;
                            if (action < 1 || action > heroes.size() + 1 ) {
                                cout << "Invalid action. Try again" << endl;
                            }
                        } while (action < 1 || action > heroes.size() + 1);
                        if (action != heroes.size() + 1) {
                            int selected = action - 1;
                            heroes.at(selected)->BuyItem(items.at(itemid));
                            items.erase(items.begin() + itemid);
                            cout << "Continue shopping?" << endl;
                            cout << "Answer(yes/no): ";
                            string answer;
                            do {
                                cin >> answer;
                                if (answer != "yes" && answer != "no") {
                                    cout << "Invalid answer. Please, try again." << endl;
                                }
                            } while (answer != "yes" && answer != "no");
                            if (answer == "yes"){
                                print(heroes);
                            }
                        }
                    }
                    else{
                        print(heroes);
                    }
                }
                else{
                    print(heroes);
                }
            }
            else {
                print(heroes);
            }
        }

        ///////////////////////////////////////////////////////////////Buy Spells
        else if (action == 2) {
            system("clear");
            if (spells.size() == 0) {
                cout << "No spells available." << endl;
            }
            for (int i = 0; i < spells.size(); i++) {
                cout << i+1 << ". " << spells.at(i)->getName() << " Price: " << spells.at(i)->getPrice() << endl;
            }
            cout << spells.size() + 1 <<". Back" << endl;
            cout << "\nAction(1-" << spells.size() << "): ";
            do {
                cin >> action;
                if (action < 1 || action > spells.size() + 1 ) {
                    cout << "Invalid action. Please, try again!" << endl;
                }
            } while (action < 1 || action > spells.size() + 1);
            if (action != spells.size() + 1) {
                int spellid = action - 1;
                system("clear");
                cout << "1. Buy\n2. Info\n3. Cancel" << endl;
                cout << "\nAction(1-3): ";
                do {
                    cin >> action;
                    if (action < 1 || action > 3 ) {
                        cout << "Invalid action. Please, try again!" << endl;
                    }
                } while (action < 1 || action > 3);
                if (action == 1) {
                    cout << "\nWhich hero should buy the spell?" << endl;
                    for(int i = 0; i < heroes.size(); i++) {
                        cout << i+1 << ". " << heroes.at(i)->getName() << " Coins: " << heroes.at(i)->getCoins() << endl;
                    }
                    cout << heroes.size() + 1 << ". Back" << endl;
                    cout << "\nSelect a hero(1-" << heroes.size() + 1 << "): ";
                    do {
                        cin >> action;
                        if (action < 1 || action > heroes.size() + 1 ) {
                            cout << "Invalid action. Try again" << endl;
                        }
                    } while (action < 1 || action > heroes.size() + 1);
                    if (action != heroes.size() + 1) {
                        int selected = action - 1;
                        heroes.at(selected)->BuySpell(spells.at(spellid));
                        spells.erase(spells.begin() + spellid);
                        cout << "Continue shopping?" << endl;
                        cout << "Answer(yes/no): ";
                        string answer;
                        do {
                            cin >> answer;
                            if (answer != "yes" && answer != "no") {
                                cout << "Invalid answer. Please, try again." << endl;
                            }
                        } while (answer != "yes" && answer != "no");
                        if (answer == "yes") {
                            print(heroes);
                        }
                    }
                }
                else if (action == 2) {
                    spells.at(spellid)->print(); 
                    cout << "\nDo you wanna buy " << spells.at(spellid)->getName() << "?" << endl;
                    cout << "Answer(yes/no): ";
                    string answer;
                    do {
                        cin >> answer;
                        if (answer != "yes" && answer != "no") {
                            cout << "Invalid answer. Please, try again." << endl;
                        }
                    } while (answer != "yes" && answer != "no");

                    if (answer == "yes") {
                        cout << "\nWhich hero should buy the spell?" << endl;
                        for(int i = 0; i < heroes.size(); i++) {
                            cout << i+1 << ". " << heroes.at(i)->getName() << " Coins: " << heroes.at(i)->getCoins() << endl;
                        }
                        cout << heroes.size() + 1 << ". Back" << endl;
                        cout << "Select a hero(1-" << heroes.size() + 1 << "): ";
                        do {
                            cin >> action;
                            if (action < 1 || action > heroes.size() + 1 ) {
                                cout << "Invalid action. Try again" << endl;
                            }
                        } while (action < 1 || action > heroes.size() + 1);
                        if (action != heroes.size() + 1) {
                            int selected = action - 1;
                            heroes.at(selected)->BuySpell(spells.at(spellid));
                            spells.erase(spells.begin() + spellid);
                            cout << "Continue shopping?" << endl;
                            cout << "Answer(yes/no): ";
                            string answer;
                            do {
                                cin >> answer;
                                if (answer != "yes" && answer != "no") {
                                    cout << "Invalid answer. Please, try again." << endl;
                                }
                            } while (answer != "yes" && answer != "no");
                            if (answer == "yes"){
                                print(heroes);
                            }
                        }            
                    }
                    else {
                        print(heroes);
                    }
                }
                else {
                    print(heroes);
                }
            }
            else {
                print(heroes);
            }
        }
        else if (action == 3) {
            sell(heroes);
        }
    }    
}

void Shop::sell(vector<Hero*> heroes) {
    system("clear");
    cout << "Select Hero: " << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << i + 1 << ". " << heroes.at(i)->getName() << endl;
    }
    cout << heroes.size() + 1 << ". Back" << endl;
    cout << "Action(1-" << heroes.size() + 1 << "): ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > heroes.size() + 1 ) {
            cout << "Invalid action. Try again" << endl;
        }
    } while (action < 1 || action > heroes.size() + 1);
    if (action != heroes.size() + 1) {
        heroes.at(action - 1)->sell();
    }
    print(heroes);
}

/////////////////////////////////////////////Block
Block::Block(int x, int y, short type, bool fight) {
    this->x = x;
    this->y = y;
    this->type = type;
    visited = false;
    if (this->type == 1) {
        market = new Shop();
    }
    else{
        market = NULL;
    }
    this->fight = fight;
}
Block::~Block(){
    if(market != NULL){
        delete market;
    }
}

int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}
short Block::getType() {
    return type;
}

void Block::setVisited() {
    visited = true;
}

bool Block::getVisited() {
    return visited;
}

void Block::shopping(vector<Hero*> heroes) {
    market->print(heroes);
}

bool Block::getFight() {
    return fight;
}

void Block::setFight() {
    fight = false;
}

////////////////////////////////////////////Grid
Grid::Grid() {
    srand(time(NULL));
    counter = 0;
    unaccesible = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (i != 5 && j != 5) {
                if (rand() % 15 == 1) {
                    blocks[i][j] = new Block(i, j, 1, false);
                }
                else {
                    if (rand() % 17 == 1) {
                        blocks[i][j] = new Block(i, j, 2, false);
                        unaccesible++;
                    }
                    else {
                        if (rand() % 10 == 1) {
                           blocks[i][j] = new Block(i, j, 0, true);
                        } 
                        else {
                            blocks[i][j] = new Block(i, j, 0, false);
                        }                   
                    }
                }
            }
            else {
                blocks[i][j] = new Block(i, j, 0, false); 
            }
        }
    }
    
    system("clear");
    cout << "How many heroes do you want to have?(you can have up until 3)" << endl;
    int number;
    do{
        cin >> number;
        if (number > 3 || number < 1) {
            cout << "You have up until 3 heroes. Please, try again." << endl;
        }
    } while (number > 3 || number < 1);
    system("clear");
    for (int i = 0; i < number; i++) {
        cout << "Name your Hero:" << endl;
        cout << "-";
        string name;
        cin >> name;
        cout << "Select Class:\n1. Warrior\n2. Sorcerer\n3. Paladin " << endl;
        int answer;
        do {
            cin >> answer;
            if (answer > 3 || answer < 1){
                cout << "Invalide answer. Please, try again." << endl;
            }
        } while (answer > 3 || answer < 1);
        Hero* newhero;
        if (answer == 1) {
            newhero = new Warrior(name);
        }
        else if (answer == 2) {
            newhero = new Sorcerer(name);
        }
        else {
            newhero = new Paladin(name);   
        }
        heroes.push_back(newhero);
        system ("clear");
    }
    system ("clear");
    for (int i = 0; i < heroes.size(); i++) {
        heroes.at(i)->displayStats();
        cout << endl;
    }
}

Grid::~Grid(){
    for(int i = 0; i < heroes.size(); i++){
        delete heroes.at(i);
    }
    heroes.clear();
    for(int i = 0; i < 11; i ++){
        for(int j = 0; j < 11; j++){
            delete blocks[i][j];
        }
    }
}

//////////////////////////////////////////////// G r i d
void Grid::print() {
    system ("clear");
    if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getVisited() == false) {
        blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->setVisited();
        counter++;
    }
    for (int i = heroes.at(0)->getX() - 5; i < heroes.at(0)->getX() + 6; i++) {
        cout << "\033[0;30;40m" << "                                                                                                   " << "\033[0m"<< endl;
        for (int j = heroes.at(0)->getY() - 5; j < heroes.at(0)->getY() + 6; j++) {
            cout << "\033[0;30;40m " << "\033[0m";
            //out of bound
            if (i < 0 || j < 0 || i > 10 || j > 10) {
                cout << "\033[0;30;40m        " << "\033[0m";
            }
            // non accessible
            else if (blocks[i][j]->getType() == 2) {
                cout << "\033[0;97;41m" << "        " << "\033[0m"; 
            }
            else if (heroes.at(0)->getY() == blocks[i][j]->getY() && heroes.at(0)->getX()==blocks[i][j]->getX()) {
                if (blocks[i][j]->getType() == 1) {
                    cout << "Shop" << "\033[1m\033[31m" << "(Pl)" << "\033[0m";
                }
                else if (blocks[i][j]->getFight() == true) {
                    cout << "\033[1m\033[31m" << " Danger " << "\033[0m";                    
                }
                else {
                    cout << "\033[1m\033[31m" << " Player " << "\033[0m";
                }
            }
            else if (blocks[i][j]->getType() == 1) {
                
                if (blocks[i][j]->getVisited() == true) {
                    cout << "\033[33m" << "  Shop  " << "\033[0m";
                }
                else {
                    cout << "\033[32m" <<"  Shop  " <<  "\033[0m";
                }
            }
            else {
                if (blocks[i][j]->getVisited() == true) {
                        if (blocks[i][j]->getFight() == true) {
                            cout << "\033[1m\033[31m" << " Danger " << "\033[0m";
                        }
                        else {
                            cout << "\033[0;90;100m" << "        " << "\033[0m";
                        }
                }
                else {
                    cout << "        "; 
                }
            }
        } 
        cout << endl;
    }
}

void Grid::move(short move) {
    for (int i = 0; i < heroes.size(); i++) {
        heroes.at(i)->move(move);
    }
}
//game starts
void Grid::start() {
    print();
    if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getType() == 1) {
        cout << "\n\nDo you want to go to the Shop?" << endl;
        cout << "Action(yes/no): ";
        string answer;
        do {
            cin >> answer;
            if (answer != "yes" && answer != "no"){
                cout << "Invalide action. Please, try again!" << endl;
            }
        } while(answer != "yes" && answer != "no");
        if (answer == "yes") {
            blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->shopping(heroes);
            print();
        }
        else {
            print();
        }
    }
    else if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getFight() == true) {
        cout << "\nYou encounter a Fight!\nPress any key to continue.." << endl;
        char key;
        cin >> key;
        fight();
        print();
    }
    if (counter == 11*11 - unaccesible) {
        system("clear");
        cout << "\n\n\n~~~Y O U  W I N~~~\n\n\n";
    }
    else{
        cout << "\n\n";
        cout << "Actions:\n1. Up(Press W)\t\t\t5. Check Inventory(Press E)\n2. Down(Press S)\t\t6. Display Stats(Press Q)\n3. Left(Press A)\t\t7. Quit Game(Press X)\n4. Right(Press D)\nAction: ";
        char action;
        do {
            cin >> action;
            if (action != 'w' && action != 's' && action != 'd' && action != 'a' && action != 'e' && action != 'x' && action != 'q') {
                cout << "Invalid action. Please, try again!" << endl;
            }
        } while (action != 'w' && action != 's' && action != 'd' && action != 'a' && action != 'e' && action != 'x' && action != 'q');
        if (action != 'x') {
            if (action == 'e') {
                checkInventory();
            }
            else if (action == 'q') {
                displayStats();
            }
            else if (action == 'w') {
                move(0);
                if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getType() == 2) {
                    move(1);
                }
            }
            else if (action == 's') {
                move(1);
                if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getType() == 2) {
                    move(0);
                }
            }
            else if (action == 'd') {
                move(2);
                if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getType() == 2) {
                    move(3);
                }
            }
            else if (action == 'a') {
                move(3);
                if (blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->getType() == 2) {
                    move(2);
                }
            }
            
            start();
        }
        else {
            print();
            cout << "\n\nAre you sure you want to quit?(yes/no)" << endl;
            string answer;
            do {
                cin >> answer;
                if(answer != "yes" && answer != "no"){
                    cout << "Invalid answer. Please, try again!" << endl;
                }     
            } while (answer != "yes" && answer != "no");
            if (answer == "no") {
                start();
            }
            else if(answer == "yes"){
                system ("clear");
            }
        }
    }
}

void Grid::checkInventory() {
    system ("clear");
    cout << "Select Hero: " << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << i+1 << ". " << heroes.at(i)->getName() << endl;
    }
    cout << heroes.size() + 1 << ". Back" << endl;
    cout << "Action: ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > heroes.size() + 1 ) {
            cout << "Invalid action. Try again" << endl;
        }
    } while (action < 1 || action > heroes.size() + 1);
    if (action != heroes.size() + 1) {
        system ("clear");
        heroes.at(action-1)->checkInventory();
    }
    start();
}

void Grid::displayStats() {
    system ("clear");
    cout << "Which hero's stats should be displayed?" << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << i+1 << ". " << heroes.at(i)->getName() << endl;
    }
    cout << heroes.size() + 1 << ". Back" << endl;
    cout << "\nAction(1-" << heroes.size() + 1 << "): ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > heroes.size() + 1) {
            cout << "Invalide action. Please, try again." << endl;
        }
    } while (action < 1 || action > heroes.size() + 1);
    if (action != heroes.size() + 1) {
        system ("clear");
        heroes.at(action - 1)->displayStats();
        cout << "\nDo you want to display other heroes stats?" << endl;
        string answer;
        cout << "Answer(yes/no): ";
        do {
            cin >> answer;
            if (answer != "yes" && answer != "no") {
                cout << "Invalide answer. Please, try again." << endl;
            }
        } while (answer != "yes" && answer != "no");
        if (answer == "yes") {
            displayStats();
        }
    }
    start();
}

void Grid::Actions(int heroid) {
    cout << "Hero " << attacking.at(heroid)->getName() << " actions:" << endl;
    cout << "\n1. Attack\n2. Cast Spell\n3. Use Potions\n4. Equip Weapons/Armors\n5. Display Stats\n6. Back" << endl;
    cout << "\nAction(1-6): ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > 6) {
            cout << "Invalide action. Please, try again." << endl;
        }
    } while (action < 1 || action > 6);
    //attack
    if (action == 1) {
        printBattle();
        cout << "\nPick a monster to attack!" << endl;
        for (int i = 0; i < monsters.size(); i++) {
            cout << i+1 << ". " << monsters.at(i)->getName();
            cout << endl;
        }
        cout << monsters.size() + 1 << ". Back" << endl;
        cout << "\nAction(1-" << monsters.size() + 1 << "): ";
        int action;
        do {
            cin >> action;
            if (action < 1 || action > monsters.size() + 1) {
                cout << "Invalide action. Please, try again." << endl;
            }
        } while (action < 1 || action > monsters.size() + 1); 
        if (action != monsters.size() + 1) {
            printBattle();
            attacking.at(heroid)->attack(monsters.at(action - 1));
            //after attack
            if (monsters.at(action-1)->getCurHealth() <= 0) {
                delete monsters.at(action - 1);
                monsters.erase(monsters.begin() + (action - 1));
            }
            attacking.erase(attacking.begin() + heroid);   
            printBattle(); 
        }
        else {
            printBattle();
            Actions(heroid);
        }
    }
    //Cast Spells
    else if (action == 2) {
        printBattle();
        cout << "\nPick a monster to cast a spell!" << endl;
        for (int i = 0; i < monsters.size(); i++) {
            cout << i+1 << ". " << monsters.at(i)->getName();
            cout << endl;
        }
        cout << monsters.size() + 1 << ". Back" << endl;
        cout << "\nAction(1-" << monsters.size() + 1 << "): ";
        int action;
        do {
            cin >> action;
            if (action < 1 || action > monsters.size() + 1) {
                cout << "Invalide action. Please, try again." << endl;
            }
        } while (action < 1 || action > monsters.size() + 1); 
        if (action != monsters.size() + 1) {
            printBattle();
            if (attacking.at(heroid)->castSpell(monsters.at(action-1))) {
                if (monsters.at(action-1)->getCurHealth() <= 0) {
                    delete monsters.at(action - 1);
                    monsters.erase(monsters.begin()+(action-1));
                }
                attacking.erase(attacking.begin() + heroid);
                printBattle();
            }
            else {
                printBattle();
                Actions(heroid);
            }
            //after attack    
        }
        else {
            printBattle();
            Actions(heroid);
        }
    }
    //use Potions
    else if (action == 3) {
        printBattle();
        cout << "\n\n";
        bool usedPotion = attacking.at(heroid)->useInBattle();
        if (usedPotion) {
            attacking.erase(attacking.begin() + heroid);
        }
        else {
            printBattle();
            Actions(heroid);            
        }
        printBattle();
    }
    //Equip armor or weapon
    else if (action == 4) {
        printBattle();
        cout << "\n\n";
        bool equipped = attacking.at(heroid)->equipInBattle();  
        if (equipped) {
            attacking.erase(attacking.begin() + heroid);
        }
        else {
            printBattle();
            Actions(heroid);            
        }
        printBattle();  
    }
    //Display stats
    else if (action == 5) {
        printBattle();
        cout << "Display Stats of:" << endl;
        for (int j = 0; j < heroes.size(); j++) {
            cout << j+1 << ". Hero: " << heroes.at(j)->getName() << endl; 
        }               
        for (int j = 0; j < monsters.size(); j++) {
            cout << j + heroes.size() + 1 << ". Monster: " << monsters.at(j)->getName() << endl; 
        }
        cout << monsters.size() + heroes.size() + 1 << ". Back" << endl;
        cout << "\nAction(1-" << attacking.size() << "): ";
        int action;
        do {
            cin >> action;
            if (action < 1 || action > monsters.size() + heroes.size() + 1) {
                cout << "Invalide action. Please, try again." << endl;
            }
        } while (action < 1 || action > monsters.size() + heroes.size() + 1);
        printBattle();
        if (action < heroes.size() + 1) {
            heroes.at(action -1)->displayStats();
        }
        else if (action < monsters.size() + heroes.size() + 1) {
            monsters.at(action - heroes.size()-1)->displayStats();
        }
        cout << "\nPress any key to continue..." << endl;
        char key;
        cin >> key;
        printBattle();
        Actions(heroid);
    }
    else {
        printBattle();
        selectHero();
    }
}

void Grid::printBattle() {
    system("clear");
    cout << "\033[1m\033[37m" << "\t\t\t~~~~ F I G H T ~~~~" << "\033[0m\n" << endl;
    for(int i = 0; i < monsters.size(); i++){
        cout << "\t\t\t\t\t\t"; 
        cout << "(" << monsters.at(i)->getCurHealth() << "/" << monsters.at(i)->getHealth() << ")" << monsters.at(i)->getName() << endl;
    }
    cout << "\t\t\t     VS "<< endl;
    for(int i = 0; i < heroes.size(); i++){
        cout << "\033[0;36m   " << heroes.at(i)->getName() << "\033[0m";
        cout << "(" << heroes.at(i)->getCurHealth() << "/" << heroes.at(i)->getHealth() << ")" << endl; 
    }
    cout << "\n\n" << endl;
}

void Grid::fight() {
    for (int i = 0; i < heroes.size(); i++) {
        int monsterType = rand() % 3;
        Monster* monster;
        if (monsterType == 0) {
            monster = new Dragon("\033[1m\033[31mDragon\033[0m", heroes.at(i)->getLevel());
        }
        else if (monsterType == 1) {
            monster = new Exoskeleton("\033[1m\033[31mExoskeleton\033[0m", heroes.at(i)->getLevel());
        }
        else {
            monster = new Spirit("\033[1m\033[31mSpirit\033[0m", heroes.at(i)->getLevel());
        }
        monsters.push_back(monster);
    } 
    printBattle();
    int round = 0;
    int herohealth = 0;
    for (int i = 0; i < heroes.size(); i++) {
        herohealth += heroes.at(i)->getCurHealth();
    }
    bool giveup = false;                                    //if action selected is give up then fight is over
    bool victory = false;                                   //when either monsters or heroes wins fight is over
    while (herohealth > 0 || monsters.size() > 0) {
        round++;
        printBattle();
        cout << "ROUND " << round << endl;
        for (int i = 0; i < heroes.size(); i++) {
            if(heroes.at(i)->getCurHealth() > 0){
                attacking.push_back(heroes.at(i));
            }
        }
        for (int i = 0; i < heroes.size(); i++) {
            if(heroes.at(i)->getCurHealth() > 0 ){
                int heroid;
                if (monsters.size() != 0) {
                    heroid = selectHero() - 1;   
                }
                else {
                    victory = true;
                    break;
                }
                if (heroid == -1) {
                    giveup = true;
                    for (int i = 0; i < heroes.size(); i++) {
                        heroes.at(i)->moveToStart();
                    }
                    cout << "Each Hero lost 100 coins..." << endl;
                    cout << "\nPress any key to continue..." << endl;
                    char key;
                    cin >> key; 
                    break;
                }
                Actions(heroid);
            }
        }
        if (giveup == true) {
            attacking.clear();
            break;
        }
        if (victory == true) {
            break;
        }
        printBattle();
        for (int i = 0; i < heroes.size(); i++) {
            if (heroes.at(i)->getCurHealth() > 0) {
                attacking.push_back(heroes.at(i));
            }
        }
        //monsters attack
        for (int i = 0; i < monsters.size(); i++) {
            int heroid = rand() % attacking.size();
            cout << "\n" << monsters.at(i)->getName() << " is attacking Hero " << attacking.at(heroid)->getName() << "!" << endl; 
            monsters.at(i)->attack(attacking.at(heroid));   
            if(attacking.at(heroid)->getCurHealth() <= 0 ){
                attacking.erase(attacking.begin() + heroid);
            } 
        }
        attacking.clear();
        cout << "Press any key to continue..." << endl;
        char key;
        cin >> key;
        herohealth = 0;
        for (int i = 0; i < heroes.size(); i++) {
            herohealth += heroes.at(i)->getCurHealth();
        }
        if (herohealth == 0) {
            break;
        }
        for (int i = 0; i < heroes.size(); i++) {
            if (heroes.at(i)->getCurHealth() > 0) {
                heroes.at(i)->regain();                 //after each round heroes regain a small amound of health and magic power
            }   
        }
        for (int i = 0; i < monsters.size(); i++) {
            if (monsters.at(i)->getCurHealth() > 0) {
                monsters.at(i)->regain();               //after each round monsters regain a small amound of health 
                //rounds
                if (monsters.at(i)->getRounds() > 0) {              //this aplies if monster has an effect from spell
                    monsters.at(i)->setRounds();
                    if (monsters.at(i)->getRounds() == 0) {
                        monsters.at(i)->regainStats();
                    }
                }
            }
        }
    }
    if (victory == true || monsters.size() == 0) {
        attacking.clear();
        system ("clear");
        blocks[heroes.at(0)->getX()][heroes.at(0)->getY()]->setFight();
        cout << "\n\t\t\tV I C T O R Y\n" << endl;
        for (int i = 0; i < heroes.size(); i++){
            if (heroes.at(i)->getCurHealth()<= 0){
                heroes.at(i)->revive(1);
            }
            else {
                heroes.at(i)->revive(2);
            }
            heroes.at(i)->gainExp();
        }
        cout << "Press any key to continue..." << endl;
        char key;
        cin >> key;
    }
    if (victory == false && giveup == false) {
        for (int i = 0; i < monsters.size(); i++) {
            delete monsters.at(i);
        }
        monsters.clear();
        system ("clear");
        cout << "\n\t\t\tD E F E A T\n" << endl;
        cout << "Heroes lost 100 coins each!\n" << endl;
        for (int i = 0; i < heroes.size(); i++) {
            heroes.at(i)->moveToStart();
            heroes.at(i)->revive(2);
        }
        cout << "Press any key to continue..." << endl;
        char key;
        cin >> key;
    }
    if(giveup == true){
        for(int i = 0; i < monsters.size(); i++){
            delete monsters.at(i);
        }
        monsters.clear();
    }
}   

int Grid::selectHero() {
    cout << "\nSelect your hero:" << endl;
    for (int j = 0; j < attacking.size(); j++) {
        cout << j+1 << ". " << attacking.at(j)->getName() << endl;
    }
    cout << attacking.size() + 1 << ". Give up" << endl;
    cout << "\nAction(1-" << attacking.size() + 1 << "): ";
    int action;
    do {
        cin >> action;
        if (action < 1 || action > attacking.size() + 1) {
            cout << "Invalide action. Please, try again." << endl;
        }
    } while (action < 1 || action > attacking.size() + 1);
    printBattle();
    if(action == attacking.size() + 1){
        return 0;
    }
    return action;
}
