/////////ITEMS//////////

#include <iostream>
#include <vector>

using namespace std;

class Item {
    short type;                             //0 if weapon , 1 if armor, 2 if potion
    bool equipped;                          //true if item equipped, else false
    
    protected:
        string name;
        int price;
        int levelRequired;
    
    
    public:
        Item(short type,int price, int levelRequired);
        int getPrice();                                     //returns price of item
        string getName();                                   //returns name of item
        int getLevel();                                     //returns level of item
        short getType();                                    //returns type of iterm
        virtual void print() = 0;                           
        bool isEquipped();                                  //check if a hero has the item equipped
        void setEquipped(bool value);                       //set item equipped
};

class Weapon: public Item {
    int damage;
    bool oneHanded;                                            //if a weapon is one handed then true, else false
    
    public:
        Weapon(int price, int levelRequired,bool oneHanded);
        int getDamage();                                      //returns damage of weapon
        void print();                                         //prints stats of weapon
};

class Armor: public Item {
    int damage_reduction;                   
    
    public:
        Armor(int price, int levelRequired);
        int getDef();                                           //returns damage reduction of item
        void print();                                           //prints stats of armor
};

class Potion: public Item {
    short stat;                                          //0 for strength,1 for dexerity,2 for magic 
                                                        //3 for agility, 4 for health
    int percent;                                                  
    public:
        Potion(short stat, int price, int levelRequired);
        void print();                                       //prints stats of potion
        short getStat();                                    //returns type of potion
        int getPercent();                                   //returns percent 
};