#include "spells.h"

namespace SpellNames {
    // names of spells that can be bought in shops
    vector <string> spellNames = {"Flame","Torch","Eruption","Flare","Blaze","Inferno","Fireball",
    "Explosion","Meteor","Salamander’s Blade","Dragon Fire","Sinkhole","Pit","Chasm","Vine","Thorn",
    "Nettle","Rockfall","Landslide","Avalanche","Chill","Freeze","Frostbite","Douse","Deluge","Flood",
    "Wave","Surge","Tsunami","Nyad’s Lore","Sleep","Slumber","Shock","Bolt","Plasma","Gust","Gale",
    "Tempest","Whirlwhind","Cyclone","Vortex","Wyvern’s Wings","Daze","Stun","Confuse","Light","Flash",
    "Radiance","Cleanse","Scour","Purge","Wrath","Retribution","Judgment","Angel’s Mercy","Darkness",
    "Shade","Gloom","Decay","Fester","Corrupt","Spite","Rancor","Malice","Demon’s Rage","Drain","Siphon",
    "Void","Bolt Strike","Freeze Wave","Inferno Blaze","Channel Energy","Shadow Blade","Heaven's Sword",
    "Blazing Katana","Staff of Ice","Arrow of Purity","Blazing Arrows","Burn the Soul","Fire Wings",
    "Fury of Osano-Wo","Gaijin Flames","Hungry Blade","Yakamo’s Wrath","Yakamo’s Eye","Breath of Suitengu",
    "The Inner Ocean","Surging Soul","Endless Depth","Kharmic Intent","Whispered Blade"};
}

//////////////////////////////////////////////////////// S p e l l
Spell::Spell(short type, int price, int requiredlevel) {
    using namespace SpellNames;
    name = spellNames.at(spellNames.size() - 1);        // naming the spell using the names from the vector 
    spellNames.erase(spellNames.end());                 //spellNames from namespace SpellNames
    this->price = price;
    requiredLevel = requiredlevel;
    damage = requiredLevel + rand() % 20 + 10;
    manaCost = rand() % 5 + 10;
    this->type = type;
}

void Spell::print() {
    cout << "\nName: " << name << "\nCost: " << price << " \nLevel Required: " << requiredLevel;
    cout << "\nDamage: " << damage << "\nMana Cost: " << manaCost << endl;
}

short Spell::getType(){
    return type;
}

int Spell::getPrice() {
    return price;
}

string Spell::getName() {
    return name;
}

int Spell::decrease() {
    return -1;
}

int Spell::getMana() {
    return manaCost;
}

int Spell::getDamage() {
    return damage;
}

/////////////////////////////////////////////////////// I c e S p e l l
IceSpell::IceSpell(int price, int requiredlevel): Spell(0, price, requiredlevel) {
    decreaseDmg = rand() % 3 + 2;
}

void IceSpell::print() {
    cout << "\n\033[36m" <<"~~~IceSpell~~~" << "\033[0m" <<endl;
    Spell::print();
    cout << "Decrease Damage: " << decreaseDmg << endl;
}

int IceSpell::decrease() {
    return decreaseDmg;
}

/////////////////////////////////////////////////////// F i r e S p e l l 
FireSpell::FireSpell(int price, int requiredlevel): Spell(1, price, requiredlevel) {
    decreaseDef = rand() % 3 +  2;
}

void FireSpell::print() {
    cout << "\n\033[31m" << "~~~FireSpell~~~" << "\033[0m" << endl;
    Spell::print();
    cout << "Decrease Deffence: " << decreaseDef << endl;
}

int FireSpell::decrease() {
    return decreaseDef;    
}

/////////////////////////////////////////////////////// L i g h t i n g S p e l l
LightingSpell::LightingSpell(int price ,int requiredlevel): Spell(2, price, requiredlevel) {
    decreaseAg = rand() % 3 + 2;
}

void LightingSpell::print(){
    cout << "\n\033[33m" << "~~~LightingSpell~~~" << "\033[0m" <<endl;
    Spell::print();
    cout << "Decrease Agility: " << decreaseAg << endl;
}

int LightingSpell::decrease() {
    return decreaseAg;
}
