//////////LIVING/////////

#include <iostream>
#include <vector>
#include "items.h"
#include "spells.h"

class Monster; 

///////////////////////////// L i v i n g 
class Living {
    protected:
        string name;
        int level;
        int health;
        int curHealth;
    
    public:
        Living(string name, int level);
        int getCurHealth();                 //returns current health of hero/monster
        int getHealth();                    //returns max health of hero/monster
        virtual void regain();              //regains a small amound of health
        string getName();                   //returns name of hero/monster
        void print();                       //prints stats of hero/monster
};

////////////////////////////////////HEROES
class Hero: public Living {
    protected:
        vector <Spell*> spells;             //inventory for spelss
        vector <Item*> inventory;           //inventory for items
        Weapon* weapons;                    //equipped weapon
        Armor* armor;                       //equipped armor
        int strength;
        int dexerity;
        int magicPower;
        int agility;
        float money;
        float experience;
        int x;                              //position x on map
        int y;                              //position y on map

    public:
        Hero(string name, int strength, int dexerity, int magicPower, int agility);
        ~Hero();
        int getLevel();                         //return level of hero
        void displayStats();                    //prints stats of hero
        void BuyItem(Item* item);               //buy the item given, if hero has enough coins
        void BuySpell(Spell* spell);            //buy spell given, if hero has enough coins
        void sell();                            //sell an item or spell of player choice
        void checkInventory();                  //view inventory and make changes if player wants
        int getInventorySize();                 //returns inventory size
        bool Equip(Item* item);                 //equips given item
        bool equipInBattle();                   //equip a weapon or armor while in battle
        bool use(Item* item);                   //use a potions
        bool useInBattle();                     //use a potion in battle
        void move(short move);                  //change the position of heroes in battle
        void moveToStart();                     //move heroes to start
        void attack(Monster* monster);          //attack the given monster
        bool castSpell(Monster* monster);       //cast a spell to the given monster
        void takeDamage(int damage);            //lose health
        void gainExp();                         //gain expirience
        void revive(int index);                 //depents on index hero regains all health or half health
        virtual void levelUp();                 //hero level up
        void regain();                          //regain a small amount of health and magic power
        int getX();                             //return x position
        int getY();                             //return y position
        int getCoins();                         //return coins of hero
};

//has more damage and agility
class Warrior: public Hero {
    public:
        Warrior(string name);
        void levelUp();
};

//has more dexerity and agility
class Sorcerer: public Hero {
    public:
        Sorcerer(string name);
        void levelUp();
};

//has more damage and dexerity
class Paladin: public Hero { 
    public:
        Paladin(string name);
        void levelUp();
};

////////////////////////////////// M O N S T E R S
class Monster: public Living {
    protected:
        int rounds;                     //counts how long an effect will last
        int averageDmg;                 //how much damage the monster does normally
        int decreasedmg;                //how much averageDmg should be decreased after a spell
        int defence;                    //how much defence the monster has 
        int decreasedef;                //how much defence should be decreased after a spell
        int agility;                    //how much agility the monster has
        int decreaseag;                 //how much agility should be decreased after a spell
    
    public:
        Monster(string name, int level, int averageDamage, int defence, int agility);
        void spellDamage(int dexerity, Spell* spell);       //the spells used on the monster
        void takeDamage(int dmg);               //how much damage a hero has done to the monster
        void regainStats();                     //after the rounds are done of a spell the effect goes away
        void attack(Hero* hero);                //the monster's attack on hero
        int getRounds();                        //returns which round the spell is on
        void setRounds();                       //round-1 when a round is done
        void displayStats();                    //display stats of monst
};

//has more damage
class Dragon: public Monster {
    public:
        Dragon(string name, int level);
};
//has mor defence
class Exoskeleton: public Monster {
    public:
        Exoskeleton(string name, int level);
};
//has more agility
class Spirit: public Monster {
    public:
        Spirit(string name, int level);
};