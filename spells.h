/////////SPELLS////////

#include <iostream>
#include <vector>

using namespace std;

class Spell {
    short type;                     // if 0 then IceSpell, if 1 then FireSpell, if 2 then LightingSpell
    
    protected:
        string name;
        int price;
        int requiredLevel;
        int damage;
        int manaCost;

    public:
        Spell(short type, int price, int requiredLevel);
        virtual void print();       //prints stats of the spell
        virtual int decrease() = 0;
        int getPrice();             //returns the price of the spell
        int getDamage();            //returns the damage the spell makes
        int getMana();              //returns the mana of the spell
        short getType();            //returns the type of the spell (icespell=0, firespell=1, lightingspell=2)
        string getName();           //returns the name of the spell
};

class IceSpell: public Spell {
    int decreaseDmg;                //enemy will do less Damage
    
    public:
        IceSpell(int price, int requiredlevel);
        int decrease();
        void print();
};

class FireSpell: public Spell {
    int decreaseDef;                //enemy has less Defence
    
    public:
        FireSpell(int price, int requiredlevel);
        int decrease();
        void print();
}; 

class LightingSpell: public Spell {
    int decreaseAg;                 //enemy will do less Agility
    
    public:
        LightingSpell(int price, int requiredlevel);
        int decrease();
        void print();
};