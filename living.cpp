#include "living.h"

////////////////////////////////Living
Living::Living(string name, int level) {
    this->name = name;
    this->level = level;
    health = this->level * 10;
    curHealth = health;
}

void Living::print() {
    cout << "Name: " << name << "\nLevel: " << level << "\nHealth: " << health << endl;
}

int Living::getHealth() {
    return health;
}

int Living::getCurHealth() {
    return curHealth;
}

string Living::getName() {
    return name;
}

void Living::regain() {
    if (curHealth <= health - 10) {
        curHealth += 10;
    }
    else {
        curHealth = health;   //if current health need less that 10 points to be full, then curent health is max health
    }
}

///////////////////////////////Hero
Hero::Hero(string name, int strength, int dexerity, int magicPower, int agility):
    Living(name, 15) {
    this->strength = strength;
    this->dexerity = dexerity;
    this->magicPower = magicPower;
    this->agility = agility;
    money = 3000;                           //each hero will start with 3000 coins
    experience = 0;
    x = 5;                                  //heroes will start in the center of the map
    y = 5;
}

Hero::~Hero(){
    for(int i = 0; i < inventory.size(); i++){
        delete inventory.at(i);
    }
    inventory.clear();
    for(int i = 0; i < spells.size(); i++){
        delete spells.at(i);
    }
    spells.clear();
}

int Hero::getLevel() {
    return level;
}

void Hero::regain() {
    Living::regain();
    magicPower +=20;
}

void Hero::revive(int index) {
    switch (index) {
    case 1:                     // if a hero dies in battle he will revive with half health
        curHealth = health/2;
        break;
    case 2:
        curHealth = health;     //if all heroes die, they will revive with full health
    default:
        break;
    }
}

void Hero::displayStats() {
    cout << "\nHero's ";
    print();
    cout << "Strength: " << strength << "\nDexerity: " << dexerity << "\nMagicPower: ";
    cout << magicPower << "\nAgility: " << agility << "\nMoney: " << money << "\nExperience: ";
    cout << experience << endl; 
}

void Hero::BuyItem(Item* item) {
    if (money >= item->getPrice()) {        //if hero has enough coins to buy the item
        cout << "\nThe hero " << "\033[36m" << name << "\033[0m" << " bought the item " << "\033[37m" << item->getName() << "\033[0m" << "!" << endl;
        cout << "Money went from " << money << " coins to " << money-item->getPrice() << " coins." <<endl;
        money -= item->getPrice();          //substract the price of the item from coins of hero
        inventory.push_back(item);          //add the item to heros inventory
    }
    else {
        cout << "\nThe hero doesn't have the required money to buy this item." << endl;
    }
}
void Hero::BuySpell(Spell* spell) {
    if (money >= spell->getPrice()) {       //if hero has enough coins to buy the spells
        cout << "\nThe hero " << "\033[36m" << name << "\033[0m" << " bought the spell " << "\033[37m" << spell->getName() << "\033[0m" << "!" << endl;
        cout << "Money went from " << money << " coins to " << money-spell->getPrice() << " coins." <<endl;
        money -= spell->getPrice();         //substract the price of the spells from coins of hero
        spells.push_back(spell);            //add the spell to heroes inventory of spells
    }
    else {
        cout << "\nThe hero doesn't have the required money to buy this item." << endl;
    }
}

void Hero::checkInventory() {
    cout << "\n" << name << "'s Inventory:" << endl;
    if (inventory.size() == 0 && spells.size() == 0) {
        cout << "Inventory is empty." << endl;
    }
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory.at(i)->getType() == 0) {
            cout << i+1 << ". Weapon: " << inventory.at(i)->getName();
            if (inventory.at(i)->isEquipped() == true) {
                cout << " (Equipped)"; 
            }
            cout << endl;
        }
        else if (inventory.at(i)->getType() == 1) {
            cout << i+1 << ". Armor: " << inventory.at(i)->getName();
            if (inventory.at(i)->isEquipped() == true) {
                cout << " (Equipped)"; 
            }
            cout << endl;
        }
        else {
            cout << i+1 << ". Potion: " << inventory.at(i)->getName() << endl;
        }
    }
    for (int i = 0; i < spells.size(); i++) {
        cout << i + inventory.size() + 1 << ". Spell" << spells.at(i)->getName() << endl;
    }
    cout  << spells.size() + inventory.size()+1 << ". Exit" << endl;
    int action;
    do {
        cout << "\nAction(1-" << spells.size() + inventory.size() + 1 << "): ";  //spells.size() + inventory.size() + 1 = number of actions
        cin >> action; 
        if (action <= 0 || action > spells.size() + inventory.size()+1) {
            cout << "Invalid action. Try again." << endl;
        }
    } while(action <= 0 || action > spells.size() + inventory.size()+1);

    if (action != spells.size() + inventory.size()+1) {
        if(action <= inventory.size()) {                        //action indicates item
            int itemId = action-1;
            if (inventory.at(itemId)->getType() != 2) {         //item is either weapon or armor
                cout << "1. Equip\n2. Stats\n3. Cancel" << endl;  
                do{
                    cout << "\nAction(1-3): ";
                    cin >> action;
                    if (action <= 0 || action > 3 ) {
                        cout << "Invalid action." << endl;
                    }
                } while (action <= 0 || action > 3);
                if (action == 1) {
                    system("clear");
                    Equip(inventory.at(itemId)); 
                }
                else if (action == 2) {
                    inventory.at(itemId)->print();
                    cout << "Do you want to equip the item " << inventory.at(itemId)->getName() << "? (yes/no)" << endl;
                    string answer;
                    do{
                        cin >> answer;
                        if (answer != "yes" && answer != "no"){
                            cout << "Invalid answer. Try again!" << endl;
                        }                
                    } while(answer != "yes" && answer != "no");
                    if (answer == "yes") {
                        system("clear");
                        Equip(inventory.at(itemId));
                    }
                    else {
                        system("clear");
                    }
                }
                else {
                    system("clear");
                }
                checkInventory();
            }
            else {                                              //item is a potion
                cout << "1. Use\n2. Info\n3. Cancel" << endl;
                do{
                    cout << "\nAction: ";
                    cin >> action;
                    if (action <= 0 || action > 3 ) {
                        cout << "Invalid action." << endl;
                    }
                } while (action <= 0 || action > 3);
                if (action == 1) {
                    system("clear");
                    if(use(inventory.at(itemId)) == true){
                        delete inventory.at(itemId);
                        inventory.erase(inventory.begin() + itemId);
                    }
                }
                else if (action == 2) {
                    inventory.at(itemId)->print();
                    cout << "Do you want to use the potion " << inventory.at(itemId)->getName() << "? (yes/no)" << endl;
                    string answer;
                    do{
                        cin >> answer;
                        if (answer != "yes" && answer != "no"){
                            cout << "Invalid answer. Try again!" << endl;
                        }                
                    } while(answer != "yes" && answer != "no");
                    if (answer == "yes") {
                        system("clear");
                        if(use(inventory.at(itemId))){
                            delete inventory.at(itemId);
                            inventory.erase(inventory.begin() + itemId);
                        }
                    }
                    else {
                        system("clear");
                    }
                }
                else {
                    system("clear");
                }
                checkInventory();
            }
        }
        else {                                                  //action indicates a spell
            system("clear");
            int spellid = action - inventory.size() - 1;
            cout << "1. Info\n2. Cancel" << endl;
            cout << "\nAction(1-2): ";
            do {
                cin >> action;
                if (action <= 0 || action > 2 ) {
                    cout << "Invalid action. Please, try again!" << endl;
                }
            } while (action <= 0 || action > 2);
            if (action == 1) {
                spells.at(spellid)->print();
                cout << "\nPress any key to go back.." << endl;
                char key;
                cin >> key;
                checkInventory();
            }
            else {
                checkInventory();
            }
        }
    }
    else {
        system("clear");
    }
}

bool Hero::Equip(Item* item) {
    if (item->getType() == 0) {
        if (weapons == (Weapon*)item) {
            cout << "\nHero " << name  << " already equipped the weapon " << weapons->getName() << "!" << endl;
            return false;
        }
        else {
            if (item->getLevel() > level)  {
                cout << "\nHero " << name << " does not have the required level to equip this weapon!" << endl;
                return false;
            }
            else {
                if (weapons != NULL) {
                    weapons->setEquipped(false);
                }
                weapons = (Weapon*)item;
                weapons->setEquipped(true);
                cout << "\nHero " << name << " equipped the weapon " << weapons->getName() << "!" << endl;
            }
        }
    }
    else if (item->getType() == 1) {
        if (armor == (Armor*)item) {
            cout << "\nHero " << name << " already equipped the armor " << armor->getName() << "!" << endl;
            return false;
        }
        else { 
            if (item->getLevel() > level) {
                cout << "\nHero " << name << " does not have the required level to equip this armor!" << endl;
                return false;
            }
            else {
                if (armor != NULL) {
                    armor->setEquipped(false);
                }
                armor = (Armor*)item;
                armor->setEquipped(true); 
                cout << "\nHero " << name << " equipped the armor " << armor->getName() << "!" << endl;
            }
        }
    }
    return true;
}

bool Hero::use(Item* item) {
    Potion* potion = (Potion*)item;
    if (potion->getLevel() <= level) {
        cout << "\nPotion " << potion->getName() << " was used!" << endl;
        if(potion->getStat() == 0) {
            cout << "Hero " << name << "'s strength was increased by " << potion->getPercent();
            cout << "(" << strength << "->" << strength + potion->getPercent() << ")" << endl; 
            strength += potion->getPercent(); 
        }
        else if (potion->getStat() == 1) {
            cout << "Hero " << name << "'s dexerity was increased by " << potion->getPercent() << "!";
            cout << "(" << dexerity << "->" << dexerity + potion->getPercent() << ")" << endl;
            dexerity += potion->getPercent();
        }
        else if (potion->getStat() == 2) {
            cout << "Hero " << name << "'s Magic Power was increased by " << potion->getPercent();
            cout << "(" << magicPower << "->" << magicPower + potion->getPercent() << ")" << endl; 
            magicPower += potion->getPercent();
        }
        else if (potion->getStat() == 3) {
            cout << "Hero " << name << "'s agility was increased by " << potion->getPercent() << "!";
            cout << "(" << agility << "->" << agility + potion->getPercent() << ")" << endl;
            agility += potion->getPercent();
        }
        else if (potion->getStat() == 4) {
            cout << "Hero " << name << "'s health was increased by " << potion->getPercent();
            cout << "(" << health << "->" << health + potion->getPercent() << ")" << endl; 
            health += potion->getPercent();
        }  
        return true;      
    }
    else {
        cout << "Hero " << name << "doesn't have the required level to use this potion." << endl;
        return false;
    }
}

bool Hero::useInBattle() { 
    vector <Potion*> potions;                               //temporary vector for potions
    cout << "Which potion do you want to use?" << endl;
    for (int i = 0; i < inventory.size(); i++) {            //go through inventory
        if (inventory.at(i)->getType() == 2) {              //when a potion is found
            cout << potions.size() + 1 << ". " << inventory.at(i)->getName() << ":" << endl;
            potions.push_back((Potion*)inventory.at(i));
            inventory.at(i)->print();                       //add it to vector
            cout << endl;
        }
    }
    cout << potions.size() + 1 << ". Back" << endl;
    cout << "\nAction(1-" << potions.size() + 1 << "): ";
    int action;
    cin >> action;
    do {
        if (action < 1 || action > potions.size() + 1) {
            cout << "Invalid action. Please, try again!" << endl;
        }
    } while (action < 1 || action > potions.size() + 1);
    if (action != potions.size() + 1) {
        bool yes = use(potions.at(action - 1));
        cout << "Press any key to continue..." << endl;
        char key;
        cin >> key;
        if (yes) {
            for(int i = 0; i < inventory.size(); i++){
                if(inventory.at(i) == potions.at(action - 1)){
                    delete inventory.at(i);
                    inventory.erase(inventory.begin() + i);
                }
            }
            potions.clear();
            return true;
        }
        else {
            return false;
        }
    }
    else {
        potions.clear();
        return false;
    }
}

bool Hero::equipInBattle() {
    vector <Item*> items;                   //temporary vectory to hold weapons and armor
    cout << "\nWhich weapon/armor do you want to equip?" << endl;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory.at(i)->getType() == 0 || inventory.at(i)->getType() == 1) {
            cout << items.size() + 1 << ". ";
            if (inventory.at(i)->getType() == 0) {
                cout << "Weapon: ";
            }
            else {
                cout << "Armor: ";
            }
            cout << inventory.at(i)->getName() << ":";
            if(inventory.at(i)->isEquipped() == true){
                cout << "(Equipted)";
            }
            items.push_back(inventory.at(i));
            inventory.at(i)->print(); 
            cout << endl;
        }
    }
    cout << items.size() + 1 << ". Back" << endl;
    cout << "\nAction(1-" << items.size() + 1 << "): ";
    int action;
    cin >> action;
    do {
        if (action < 1 || action > items.size() + 1) {
            cout << "Invalid action. Please, try again!" << endl;
        }
    } while (action < 1 || action > items.size() + 1);
    if (action != items.size() + 1) {
        bool yes = Equip(items.at(action - 1));
        cout << "Press any key to continue..." << endl;
        char key;
        cin >> key; 
        items.clear();
        if (yes) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        items.clear();
        return false;
    }
}

void Hero::move(short move) {
    //up
    if (move == 0 ) {
        if (x-1 >= 0) {
            x--;
        }
        else {
            cout << "Out of Bounds." << endl;
        }
    }
    //down
    else if (move == 1) {
        if (x+1 <= 10) {
            x++;   
        }
        else {
            cout << "Out of Bounds." << endl;
        }
    }
    //right
    else if (move == 2) {
        if (y+1 <= 10) {
            y++;
        }
        else {
            cout << "Out of Bounds." << endl;
        }
    }
    //left
    else {
        if (y-1 >= 0) {
            y--;
        }
        else {
            cout << "Out of Bounds." << endl;
        }
    }
}

void Hero::moveToStart() {
    //each time heros move to start they lose money
    if (money >= 100) {
        money -= 100;
    }
    else {
        money = 0;
    }
    x = 5;
    y = 5; 
}

void Hero::gainExp() {
    cout << "\nHero " << name << " gained 1000 coins and 500xp!\n" << endl;
    money += 1000;
    experience += 500;
    if (experience >= level * 60) {       
        experience -= level * 60;
        levelUp();
    }
}

void Hero::levelUp() {
    level++;
    cout << "Hero " << name << " has leveled up!(" << level - 1 << "->" << level << ")" << endl;    
}

void Hero::sell() {
    system("clear");
    if (inventory.size() == 0 && spells.size() == 0){                       //hero has nothing to sell
        cout << "Hero's inventory is empty." << endl;
        cout << "Press any key to exit..." << endl;
        char key;
        cin >> key;
    }
    else {
        cout << "Which item or spell do you want to sell?" << endl;
        for (int i = 0; i < inventory.size(); i++){
            cout << i + 1 << ". ";
            if(inventory.at(i)->getType() == 0 ){
                cout << "Weapon: ";
            } 
            else if(inventory.at(i)->getType() == 1){
                cout << "Armor: ";
            }
            else{
                cout << "Potion: ";
            }
            cout << inventory.at(i)->getName() << " Value: " << inventory.at(i)->getPrice()/2 << endl;
        }
        for (int i = 0; i < spells.size(); i++) {
            cout << inventory.size() + i + 1 << ". Spell: " << spells.at(i)->getName();
            cout << " Value: " << spells.at(i)->getPrice()/2 << endl;
        }
        cout  << spells.size() + inventory.size()+1 << ". Back" << endl;
        cout << "Action(1-" << inventory.size() + spells.size() + 1 << "): ";
        int action;
        do {
            cin >> action;
            if (action < 1 || action > inventory.size() + spells.size() + 1) {
                cout << "Invalid action. Please, try again!" << endl;
            }
        } while (action < 1 || action > inventory.size() + spells.size() + 1);
        if (action != inventory.size() + spells.size() + 1) {
            if (action <= inventory.size()) {
                system("clear");
                int itemid = action - 1;
                cout << "Are you sure you want to sell the item " << inventory.at(itemid)->getName();
                cout  << " for " << inventory.at(itemid)->getPrice()/2 << " Coins?(yes/no)" << endl;
                string answer;
                do {
                    cin >> answer;
                    if (answer != "yes" && answer != "no") {
                        cout << "Invalid answer. Please, try again!" << endl;
                    }
                } while(answer != "yes" && answer != "no");
                if (answer == "yes") {
                    cout << "Hero " << name << " has sold the item " << inventory.at(itemid)->getName() << "!" << endl;
                    cout << "Coins went from " << money << " to " << money + inventory.at(itemid)->getPrice()/2 << endl;
                    money += inventory.at(itemid)->getPrice()/2;
                    delete inventory.at(itemid);
                    inventory.erase(inventory.begin() + itemid);
                    cout << "\n1. Go back to the Shop\n2. Sell more Items or Spells" << endl;
                    cout << "\nAction(1-2): ";
                    do {    
                        cin >> action;
                        if (action < 1 || action > 2 ) {
                            cout << "Invalid action. Please, try again!" << endl;
                        }
                    } while (action < 1 || action > 2);
                    if (action == 2){
                        sell();
                    }
                }
                else {
                    sell();
                }
            }
            else {
                system("clear");
                int spellid = action - inventory.size() - 1;
                cout << "Are you sure you want to sell the spell " << spells.at(spellid)->getName();
                cout << " for " << spells.at(spellid)->getPrice()/2 << " Coins?(yes/no)" << endl;
                string answer;
                do {
                    cin >> answer;
                    if (answer != "yes" && answer != "no") {
                        cout << "Invalid answer. Please, try again!" << endl;
                    }
                } while(answer != "yes" && answer != "no");
                if (answer == "yes") {
                    cout << "Hero " << name << " has sold the spell " << spells.at(spellid)->getName() << "!" << endl; 
                    cout << "Coins went from " << money << " to " << money + spells.at(spellid)->getPrice()/2 << endl;
                    money += spells.at(spellid)->getPrice()/2;
                    delete spells.at(spellid);
                    spells.erase(spells.begin() + spellid);
                    cout << "\n1. Go back to the Shop\n2. Sell more Items or Spells" << endl;
                    cout << "\nAction(1-2): ";
                    do {    
                        cin >> action;
                        if (action < 1 || action > 2 ) {
                            cout << "Invalid action. Please, try again!" << endl;
                        }
                    } while (action < 1 || action > 2);
                    if (action == 2){
                        sell();
                    }
                }
                else {
                    sell();
                }
            }
        }
    }
}
int Hero::getInventorySize(){
    return inventory.size();
}
int Hero::getX() {
    return x;
}

int Hero::getY() {
    return y;
}

int Hero::getCoins(){
    return money;
} 

void Hero::attack(Monster* monster) {
    int damage = strength;
    if (weapons != NULL) {
        damage += weapons->getDamage();
    }
    monster->takeDamage(damage);
}

bool Hero::castSpell(Monster* monster) {
    cout << "Which spell do you want to cast?" << endl;
    for (int i = 0; i < spells.size(); i++) {
        cout << i + 1 << ". ";
        spells.at(i)->print();
        cout << endl;
    }
    cout << spells.size() + 1 << ". Back" << endl;
    cout << "\nAction(1-" << spells.size() + 1 << "): ";
    int action;
    do {    
        cin >> action;
        if (action < 1 || action > spells.size() + 1 ) {
            cout << "Invalid action. Please, try again!" << endl;
        }
    } while (action < 1 || action > spells.size() + 1);
    if (action != spells.size() + 1) {
        magicPower -= spells.at(action - 1)->getMana();
        monster->spellDamage(dexerity,spells.at(action-1));
        return true;
    }
    else {
        return false;
    }
}

void Hero::takeDamage(int dmg) {
    if (rand() % 100 <= agility) {
        cout << name << " dodged monster's attack!" << endl;
    }
    else {
        if (armor != NULL) {
            dmg -= armor->getDef();
        }
        cout << "\nHero " << name << " took " << dmg << " damage!" << endl; 
        cout << "Health went from " << curHealth << " to ";
        curHealth -= dmg;
        if (curHealth < 0 ) {
            curHealth = 0;
            cout << curHealth << "!" << endl;
            cout << "Hero " << name << " D E A D(for now)!" << endl;
        }
        else {
            cout << curHealth << "!\n" << endl;
        }
    }
}

///////////////////////////////Warrior
Warrior::Warrior(string name) : Hero(name, 20, 15, 100, (int)(0.05*(float)10)) {

}

void Warrior::levelUp(){
    Hero::levelUp();
    strength += 3;
    dexerity += 1;
    agility += 1;
}

Sorcerer::Sorcerer(string name) : Hero(name, 10, 20, 100, (int)(0.05*(float)level)) {

}

void Sorcerer::levelUp() {
    Hero::levelUp();
    strength += 1;
    dexerity += 3;
    agility += 1;
}

Paladin::Paladin(string name) : Hero(name, 20, 20, 100, (int)(0.03*(float)level)) {

}

void Paladin::levelUp() {
    Hero::levelUp();
    strength += 3;
    dexerity += 3;
    agility += 1;
}

////////////////////////////////////////////////////////// M o n s t e r
Monster::Monster(string name, int level, int averageDamage, int defence, int agility):
    Living(name, level) {
    this->averageDmg = averageDamage;
    this->defence = defence;
    this->agility = agility;
    rounds = 0;
    decreaseag = 0;
    decreasedef = 0;
    decreasedmg = 0;
}

void Monster::displayStats() {
    cout << "\nMonster's ";
    print();
    cout << "Damage: " << averageDmg << "\nDefence: " << defence;
    cout << "\nAgility: " << agility << endl;    
}

void Monster::takeDamage(int damage) {
    if (rand() % 100 <= agility) {      //possibility of the monster to dodge an attack based on the agility
        cout << name << " dodged hero's attack!" << endl;
    }
    else {
        int dmgreduction = ((float)defence/100)*damage;     //there's a chance the defence is too strong for
        if (dmgreduction > damage) {                        //the monster to take damage
            cout << "Enemy too strong!" << endl; 
        }
        else {
            cout << name << " took " << damage - dmgreduction << " damage from hero's attack!" << endl;
            cout << "Current health went from " << curHealth;
            curHealth = curHealth - damage + dmgreduction;  //current health after anattack is minus the damage of the attack 
                                                            //plus the damage reduction of the monster
            if (curHealth < 0) {
                curHealth = 0;
                cout << " to " << curHealth << "!" << endl;
                cout << name << " D E A D!" << endl;
            }
            else {
                cout << " to " << curHealth << "!" << endl;
            }
        }
    }
    cout << "\nPress any key to continue..." << endl;
    char key;
    cin >> key;
}

void Monster::spellDamage(int dexerity, Spell* spell) {
    if (rand() % 100 <= agility/2) {            //based of the agility of the monster, there's a chance it dodged the spell
        cout << name << " dodged hero's spell!" << endl;
    }
    else {
        if (rounds == 0) {                      //if there's no spell currently on the monster 
            rounds = 3;                         //make the spell last for 3 rounds
            if (spell->getType() == 0) {
                //icespell
                cout << "Monster's damage is decreasing from " << averageDmg;
                decreasedmg = spell->decrease();
                averageDmg -= decreasedmg;
                cout << " to " << averageDmg << " for " << rounds << " rounds!" << endl;
            }
            else if (spell->getType() == 1) {
                //firespell
                cout << "Monster's defence is decreasing from " << defence;
                decreasedef = spell->decrease();
                defence -= decreasedef;
                cout << " to " << defence << " for " << rounds << " rounds!" << endl;
            }
            else {
                //lightingspell
                cout << "Monster's agility is decreasing from " << agility;
                decreaseag = spell->decrease();
                agility -= spell->decrease();
                cout << " to " << agility << " for " << rounds << " rounds!" << endl;
            }
        }
        //if there's already a spell, the new spell only does damage
        int damage = spell->getDamage() + dexerity;
        int dmgreduction = ((float)defence/100)*spell->getDamage();     //if the defence of the monster is too strong, it does no dmg
        if (dmgreduction > damage) {
            cout << "Enemy too strong!" << endl; 
        }
        else {
            cout << name << " took " << damage - dmgreduction << " damage from hero's spell!" << endl;
            cout << "Current health went from " << curHealth;
            curHealth = curHealth - damage + dmgreduction;
            if (curHealth < 0) {
                curHealth = 0;
                cout << " to " << curHealth << "!" << endl;
                cout << name << " D E A D" << endl;
            }
            else {
                cout << " to " << curHealth << "!" << endl;
            }
        }
    }
    cout << "\nPress any key to continue..." << endl;
    char key;
    cin >> key;
}

void Monster::attack(Hero* hero) {
    hero->takeDamage(averageDmg);
}

int Monster::getRounds() {
    return rounds;
}

void Monster::setRounds() {
    rounds--;
}

void Monster::regainStats() {
    averageDmg += decreasedmg;
    defence += decreasedef;
    agility += decreaseag;
} 

///////////////////////////////////////////////////////// D r a g o n 
Dragon::Dragon(string name, int level): Monster(name, level, level+10, level, (int)(0.05*(float)level)) {

}

//////////////////////////////////////////////////////// E x o s k e l e t o n
Exoskeleton::Exoskeleton(string name, int level): Monster(name, level, level, level+10, (int)(0.07*(float)level)) {
    
}

//////////////////////////////////////////////////////// S p i r i t
Spirit::Spirit(string name, int level): Monster(name, level, level, level, (int)(0.1*(float)level)) {

}
