///////////////GRID//////////////
#include "living.h"

class Shop {
    vector <Item*> items;                       //items in the shop
    vector <Spell*> spells;                     //spells in the shop
    public:
        Shop();
        ~Shop();
        void print(vector<Hero*> heroes);      //print the items and spells 
        void sell(vector<Hero*> heroes);       //sell a hero's item
};

class Block {
    int x;                              //position in x 
    int y;                              //position in y
    short type;                         // 0 if common, 1 if shop, 2 if unaccecible
    bool visited;                       //if visited true, else false
    bool fight;                         //there is a change it has a fight
    Shop* market;                       //if it has a market
    
    public:                   
        Block(int x , int y,short type,bool fight);
        ~Block();
        short getType();                //returns type
        int getX();                     //returns x
        int getY();                     //returns y
        void setFight();                //if fight is over then set it to false
        bool getFight();                //returns fight
        void setVisited();              //set visited to true
        bool getVisited();              //returns visited
        void shopping(vector<Hero*> heroes);    //goes into shop
};


class Grid {
    int counter;        //counts every block that gets visited by the player and if every block has been visited then you win!
    int unaccesible;    //counts every unaccesible block
    vector <Hero*> heroes;
    vector <Hero*> attacking;       //temporarily saves players for each round
    vector <Monster*> monsters;
    Block* blocks[11][11];

    public:
        Grid();
        ~Grid();
        void print();               //displays the grid and its blocks
        void move(short move);      //to move the player on the blocks of the grid
        void start();               //for each action on the grid the function calls itself and displays the choices of actions the player has
        void checkInventory();      //displays the inventory of the player
        void displayStats();        //display the statistics of the chosen player
        void Actions(int heroid);   //the actions the hero can take in the battle
        void printBattle();         //displays the monsters and the heroes in the battle
        void fight();               //creates the enemies and starts the battle 
        int selectHero();           //to choose which hero to pick  
};