#include "items.h"
#include <stdlib.h>
#include <time.h>

//a namespace that has all possible names of items in shops
namespace Names {
    vector <string> potionNames = {"Potion","Hi-Potion","X-Potion","Mega-Potion","Ether","Turbo Ether","Elixir","Megalixir","Phoenix Down","Mega Phoenix","Antidote","Echo Screen","Eye Drops","Holy Water","Remedy","Soft","Al Bhed Potion","Healing Water","Tetra Elemental","Candle of Life","Dream Powder","Farplane Shadow","Farplane Wind","Frag Grenade","Silence Grenade","Sleeping Powder","Smoke Bomb","Petrify Grenade","Poison Fang","Blessed Gem","Dark Matter","Shadow Gem","Shining Gem","Supreme Gem","Gold Hourglass","Healing Spring","Light Curtain","Lunar Curtain","Mana Spring","Mana Tablet","Mana Tonic","Purifying Salt","Silver Hourglass","Soul Spring","Stamina Spring","Stamina Tablet","Stamina Tonic","Star Curtain","Three Stars","Twin Stars","Ability Distiller","Amulet","Designer Wallet","Door to Tomorrow","Gambler's Spirit","Hypello Potion","Mana Distiller","Map","Musk","Pendulum","Power Distiller","Shining Thorn","Speed Distiller","Underdog's Secret","Wings to Discovery","Winning Formula"};
    vector <string> weaponNames = {"Caladbolg","Taming Sword","Crystal Sword","Excalibur","Ragnarok","Balmung","Save the Queen","Heartbreaker","Lionheart","Durandal","Ascalon","Ambitious","Hrunting","Astral Sword","Apocalypse","Slowstrike","Master Sword","Rune-Master","Warlock","Arc Sword","Gilventure","Tri-Steel","Helter-Skelter","Vendetta","Avenger","Prism Steel","Mirage Sword","Lifesaver","Sonic Steel","Vigilante","Dance Macabre","Largamente","Gravestone","Sidewinder","Nightmare","Mage Masher","Nightbringer","Knight Sword","Wizard Sword","Double-Edge","Razzmatazz","Deathbringer","Stunning Steel","Basilisk Steel","Poison Steel","Lullaby Steel","Muted Steel","Twilight Steel","Hunter's Sword","Flametongue","Ice Brand","Lightning Steel","Force Saber","Baroque Sword","Sorcery Sword","Soldier's Saber","Rune Steel","Enchanted Sword","Fencing Saber","Slasher","Nirvana","Herding Staff","Arc Arcana","Abraxas","Heavenly Axis","Judgment","Seraphim Rod","Rod of Roses","Nimbus Rod","Wing Wand","Wonder Wand","Laevatein","Astral Rod","Chaos Rod","Power Staff","Shining Staff","Faerie Staff","Magistral Rod","El Dorado","Tri-Rod","Wicked Wand","Nemesis Rod","Defender","Prism Rod","Mirage Rod","Healing Rod","Wind Rod","Conductor","Punisher","Calcite Staff","Bizarre Staff","Staff of Thorns","Reticent Staff","Darkness Staff","Monk Staff","Mage's Staff","Dual Rod","Ominous Rod","Death Wand","Entangling Rod","Break Rod","Belladonna Wand","Lullaby Rod","Rod of Silence","Rod of Darkness","Rod of Wisdom","Rod of Fire","Rod of Ice","Rod of Lightning","Rod of Water","Malleable Staff","Force Rod","Ductile Rod","Sorcery Rod","Full Metal Rod","Rune Rod","Enchanted Rod","Rod of Striking","Spiked Rod"};
    vector <string> armorNames = {"Genji Shield","Emblem","Crystal Shield","Aegis Shield","Golem Shield","Revive Shield","Rescue Shield","Paladin Shield","Diamond Shield","Ruby Shield","Dynasty Shield","Magister Shield","Collector's Shield","Treasure Shield","Shield of Hope","Assault Shield","Phantom Shield","Recovery Shield","Spiritual Shield","Phoenix Shield","Curative Shield","Rainbow Shield","Shining Shield","Faerie Shield","Peaceful Shield","Shaman Shield","Barrier Shield","Star Shield","Marching Shield","Moon Shield","Regen Shield","Haste Shield","Reflect Shield","Protect Shield","Shell Shield","Platinum Shield","Sapphire Shield","Knight's Shield","Wizard Shield","Elemental Shield","Defending Shield","Crimson Shield","Snow Shield","Ochre Shield","Cerulean Shield","Medical Shield","Lucid Shield","Serene Shield","Light Shield","Soul Shield","Blessed Shield","Soft Shield","Serum Shield","Alert Shield","Echo Shield","Bright Shield","Red Shield","White Shield","Yellow Shield","Blue Shield","NulTide Shield","NulBlaze Shield","NulFrost Shield","Adept's Shield","Tetra Shield","Mythril Shield","Gold Shield","Emerald Shield","Soldier's Shield","Mage's Shield","Silver Shield","Onyx Shield","Sorcery Shield","Warrior's Shield","Glorious Shield","Metal Shield","Pearl Shield","Magic Shield","Seeker's Shield"};

};

//////////////////////////////////////////////////////////// I t e m
Item::Item(short type, int price, int levelRequired) {
    this->type = type;
    using namespace Names;
    if (type == 0) {
        name = weaponNames.at(weaponNames.size()-1);                
        weaponNames.erase(weaponNames.end());
    }
    else if (type == 1) {
        name = armorNames.at(armorNames.size()-1);
        armorNames.erase(armorNames.end());
    }
    else {
        name = potionNames.at(potionNames.size()-1);
        potionNames.erase(potionNames.end());
    }
    
    equipped = false;
    this->price = price;
    this->levelRequired = levelRequired;
}

int Item::getPrice() {
    return price;
}

string Item::getName() {
    return name;
}

int Item::getLevel() {
    return levelRequired;
}

short Item::getType() {
    return type;
}

void Item::setEquipped(bool value) {
    equipped = value;
}

bool Item::isEquipped() {
    return equipped;
}

//item print is pure virtual
void Item::print() {}

////////////////////////////////////////////////////////////W W e a p o n
Weapon::Weapon(int price, int levelRequired, bool oneHanded): Item(0, price, levelRequired) {
    this->oneHanded = oneHanded;
    if (this->oneHanded == true) {
        this->damage = levelRequired + (rand() % 10 + 40);
    }
    else {
        this->damage = levelRequired + (rand() % 10 + 50);
    }
} 

void Weapon::print() {
    cout << "\nName: " << name << "\nCost: " << price << "\nDamage: " << damage << "\nLevel Required: ";
    cout << levelRequired << endl;
    cout << endl;
}

int Weapon::getDamage() {
    return damage;
}

//////////////////////////////////////////////////////////// A r m o r
Armor::Armor(int price, int levelRequired): Item(1, price, levelRequired) {
    this->damage_reduction = levelRequired + (rand() % 15 + 5);
}

void Armor::print() {
    cout << "\nName: " << name << "\nCost: " << price << "\nDamage Reduction: " << damage_reduction << "\nLevel Required: ";
    cout << levelRequired << endl;
    cout << endl; 
}

int Armor::getDef() {
    return damage_reduction;
}

///////////////////////////////////////////////////////////// P o t i o n
Potion::Potion(short stat, int price, int levelRequired): Item(2, price, levelRequired) {
    this->stat = stat;
    percent = rand() % 3 + 1;
}

void Potion::print() {
    cout << "Potion " << name << " will increase the ";
    //depents of stat potion will affect different stat of heroes
    if (stat == 0) {
        cout << "strength";
    }
    else if (stat == 1) { 
        cout << "dexerity";
    }
    else if (stat == 2){
        cout << "magic power";
    }
    else if (stat == 3) {
        cout << "agility";
    }
    else if (stat == 4) {
        cout << "health";
    }
    cout << " by " << percent << "!" << endl;
    cout << "Cost: " << price << endl;
    cout << "Level Required: " << levelRequired << endl;
}

short Potion::getStat(){
    return stat;
}

int Potion::getPercent(){
    return percent;
}