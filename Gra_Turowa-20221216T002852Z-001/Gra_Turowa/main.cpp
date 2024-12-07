#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unistd.h>
#include <random>
#include <fstream>

auto rules()->void{
    sleep(1);
            std::cout  << "In this game, you need to control creatures and use their super abilities\nto defeat enemy creatures. As the name implies, the game is divided into turns,\nin each turn you can use one of the following actions:\n\n";
    sleep(1);
            std::cout <<    "ATTACK - pass a dexterity check, and if the result is successful, deal damage to the opponent's creature\n\n";
    sleep(1);
            std::cout <<  "SPECIAL ABILITY - each creature has its own and is described in its characteristics\n\n";
    sleep(1);
            std::cout <<   "CHANGE CREATURE - replaces the active creature with one creature from the team of the player's choice\n\n";
    sleep(1);
            std::cout <<        "LEVEL UP - if the creature has at least one experience point, it can level up\nand then the player will choose to pump two characteristics of the creature\n\n";
    sleep(1);
            std::cout <<     "HELP - a command that does not transfer the initiative to an enemy creature\nand in which you can check what your acting creature, the opponent's creature, is doing,\ncheck the table of creature types and of course re-read these rules\n\n";

}

auto draw_table()->void{
    std::cout << "       BLOCKING  ->   | WATER | EARTH |  AIR  |  FIRE |  ICE  | STEEL |\n"
    << "ATTACKING -> { WATER }| 0.5X  | 2.0X  | 1.0X  | 2.0X  | 1.0X  | 1.0X  |\n"
    << "ATTACKING -> { EARTH }| 1.0X  | 1.0X  | 0.5X  | 2.0X  | 2.0X  | 2.0X  |\n"
    << "ATTACKING -> {  AIR  }| 1.0X  | 0.5X  | 1.0X  | 2.0X  | 2.0X  | 0.5X  |\n"
    << "ATTACKING -> { FIRE  }| 0.5X  | 0.5X  | 1.0X  | 1.0X  | 2.0X  | 2.0X  |\n"
    << "ATTACKING -> {  ICE  }| 0.5X  | 2.0X  | 1.0X  | 0.5X  | 0.5X  | 2.0X  |\n"
    << "ATTACKING -> { STEEL }| 2.0X  | 1.0X  | 2.0X  | 0.5X  | 1.0X  | 0.5X  |\n\n";
}

auto start_game()->void{      /////////////////////////////// дописать
    std::cout << "\nWelcome to my turn based game\n\n";
    sleep(1);
}

auto start_round(int i)->void{        /////////////////////////////// дописать
    std::cout << "Round " << i << " starts now\n";
    sleep(2);
    std::cout << "You must defeat all creatures in enemy team";
    sleep(2);
}


enum class type{
    water, earth, air, fire, ice, steel
};

std::random_device rd;

struct creature{


    int power;
    int health;
    int dexterity;

    int default_power;
    int default_health;
    int default_dexterity;

    int stone_gloves=-1;

    int special_move_counter;
    int special_move_limit;

    type typ;

    std::string name;
    std::string sm_name;

    int paralyzed_counter = 0;
    int burn_counter = -1;
    bool poison = false;

    int hiding_timer=0;
    int exp = 0;
    bool fainted = false;
    int id;

    virtual void special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& enemy_vec,std::vector<std::unique_ptr<creature>>& player_vec ) = 0;
    virtual auto attack_flavor_description()->void =0;
    virtual auto special_move_description()-> void = 0;
    virtual auto special_move_flavor_description()-> void=0;
    virtual auto creature_description()->void=0;
    virtual auto clone()->std::unique_ptr<creature> =0;

    void setStoneGloves(int stoneGloves,creature& a) {
        a.stone_gloves = stoneGloves;
    }

    int getStoneGloves()  {
        return stone_gloves;
    }

    void setParalyzedCounter(int paralyzedCounter,creature& a) {
        a.paralyzed_counter = paralyzedCounter;
    }

    void setHidingTimer(int hidingTimer,creature& a) {
        a.hiding_timer = hidingTimer;
    }

    void setExp(int exp,creature& a) {
        a.exp = exp;
    }

    auto getParalyzedCounter() const -> int {
        return paralyzed_counter;
    }

    auto getHidingTimer() const -> int {
        return hiding_timer;
    }

    auto getExp() const -> int {
        return exp;
    }

    void setPoison(bool poison,creature& a) {
        a.poison = poison;
    }

    auto isPoison() -> bool {
        return poison;
    }

    void setBurnCounter(int burnCounter,creature& a) {
        a.burn_counter = burnCounter;
    }

    auto getBurnCounter() const -> int{
        return burn_counter;
    }

    void setDefaultPower(int defaultPower, creature& a) {
        a.default_power = defaultPower;
    }

    void setDefaultHealth(int defaultHealth, creature& a) {
        a.default_health = defaultHealth;
    }

    void setDefaultDexterity(int defaultDexterity, creature& a) {
        a.default_dexterity = defaultDexterity;
    }

    void setSpecialMoveCounter(int specialMoveCounter, creature& a) {
        a.special_move_counter = specialMoveCounter;
    }


    void setHealth(int health, creature& a)  {
        a.health = health;
    }

    void setPower(int power, creature& a)  {
       a.power = power;
    }

    void setDexterity(int dex, creature& a) {
       a.dexterity = dex;
    }


    auto getDefaultPower() const -> int {
        return default_power;
    }

    auto getDefaultHealth() const -> int  {
        return default_health;
    }

    auto getDefaultDexterity() const ->  int{
        return default_dexterity;
    }


    auto getSmName() const -> std::string {
        return sm_name;
    }

    auto getName() const -> std::string  {
        return name;
    }

    auto getType() const -> type {
        return typ;
    }


    auto getHealth() const -> int{
        return health;
    }

    auto getDexterity() const -> int {
        return dexterity;
    }


    auto getPower() const -> int {
        return power;
    }

    auto getSpecialMoveLimit() const -> int{
        return special_move_limit;
    }

    auto getSpecialMoveCounter()  const -> int{
        return special_move_counter;
    }

auto is_hits(creature& a,creature& b)->bool {
    std::uniform_int_distribution<int> distr(1,100);
    int dice_roll = distr(rd);
    return dice_roll + a.getDexterity() /3 >= b.getDexterity();
}
    /** enemy_choices()
     * The function of random selection of actions
     * for the enemy depending on the situation
     *
     * @param a and b are references of creature
     * @param enemy_vec and player_vec are references of vector of std::unique_ptr<creature>
     */
    auto enemy_choices(creature& a,creature& b,std::vector<std::unique_ptr<creature>>& player_vec,std::vector<std::unique_ptr<creature>>& enemy_vec) -> void {
        if (enemy_vec.size() > 0) {

            std::cout << "ENEMY : \n";
            if (a.getHidingTimer() == 0 && b.getHidingTimer() == 0) {

                if (a.getSpecialMoveCounter() > 0) {

                    std::uniform_int_distribution<int> distribution(0, 1);
                    int dice_roll = distribution(rd);

                    if (dice_roll == 0) {

                        attack(a, b);

                    } else if (dice_roll == 1) {

                        special_move(a, b, player_vec, enemy_vec);

                    }
                } else if (a.getHealth() < 50 && enemy_vec.size() > 1) {

                    std::swap(enemy_vec[1], enemy_vec.front());
                    std::cout << "Changing a creature\nNow " << enemy_vec.front()->getName()
                              << " in the head of ENEMY team\n\n";

                } else {

                    attack(a, b);

                }
            } else if (b.getHidingTimer() == 1 && a.getHidingTimer() == 0) {

                std::cout << "YOUR " << b.getName() << " is hiding\n\n";

            } else if (a.getHidingTimer() == 1) {

                a.setHidingTimer(0, a);
                std::cout << "*Rook jumps out of the smoke and backstab the creature*\n";
                std::cout << "and dealt " << (int) (a.getPower() * type_mod(a, b) * 2) << " damage\n\n";
                b.setHealth(b.getHealth() - a.getPower() * type_mod(a, b) * 2, b);

            }
        }
}

auto player_level_up(creature& a)->void{
            int choice;
            a.setExp(a.getExp()-1, a);
            for (int i = 0; i < 2; i++){

                    std::cout << "What stat do you want to increase in " << a.getName() << "?\n"
                              << "[1] HP\n" << "[2] POWER\n" << "[3] DEXTERITY\n";

                    std::cin >> choice;
                    if (choice == 1) {
                        a.setDefaultHealth(getDefaultHealth() + 15,a);
                        a.setHealth(a.getHealth() + 15,a);
                        std::cout << "Now " << a.getName() << " health is " << a.getHealth() << "\n\n";
                    } else if (choice == 2) {
                        a.setDefaultPower(a.getDefaultPower() + 3,a);
                        a.setPower(a.getPower() + 3,a);
                        std::cout << "Now " << a.getName() << " power is " << a.getPower() << "\n\n";
                    } else if (choice == 3) {
                        a.setDefaultDexterity(a.getDefaultDexterity() + 3,a);
                        a.setDexterity(a.getDexterity() + 3,a);
                        std::cout << "Now " << a.getName() << " dexterity is " << a.getDexterity() << "\n\n";
                    }

        }

}
    /** creature_rest()
       * a function that removes all effects and damage from the creature
       * and is used at the end of each round
       *
       * @param  player_vec is reference of vector of std::unique_ptr<creature>
       */

auto creature_rest(std::vector<std::unique_ptr<creature>>& player_vec)->void{
    for (auto& e : player_vec){
        e->setPower(e->getDefaultPower(),*e);
        e->setHealth(e->getDefaultHealth(),*e);
        e->setDexterity(e->getDefaultDexterity(),*e);
        e->fainted = false;
        e->setSpecialMoveCounter(e->getSpecialMoveLimit(),*e);
        e->setParalyzedCounter(0,*e);
        e->setStoneGloves(-1,*e);
        e->setBurnCounter(-1,*e);
        e->setPoison(false,*e);
        std::cout << e->getName() << " is rested\n";
        sleep(1);
    }
}

        /** type_mod()
          * returns an integer depending on the creatures given in the arguments
          *
          * @param  a and b are references of creature
          */
    auto  static type_mod(creature& a,creature& b)->double{
        if(a.getType() == type::earth){
            switch (b.getType()) {
                case type::earth :
                    return 1;
                case type::steel :
                    return 2;
                case type::ice :
                    return 2;
                case type::fire :
                    return 2;
                case type::air :
                    return 0.5;
                case type::water :
                    return 1;
            }
        }else if(a.getType() == type::water){
            switch (b.getType()) {
                case type::earth :
                    return 2;
                case type::steel :
                    return 1;
                case type::ice :
                    return 1;
                case type::fire :
                    return 2;
                case type::air :
                    return 1;
                case type::water :
                    return 1;
            }
        }else if(a.getType() == type::air){
            switch (b.getType()) {
                case type::earth :
                    return 0.5;
                case type::steel :
                    return 0.5;
                case type::ice :
                    return 2;
                case type::fire :
                    return 2;
                case type::air :
                    return 1;
                case type::water :
                    return 1;
            }
        }else if(a.getType() == type::fire){
            switch (b.getType()) {
                case type::earth :
                    return 0.5;
                case type::steel :
                    return 2;
                case type::ice :
                    return 2;
                case type::fire :
                    return 1;
                case type::air :
                    return 1;
                case type::water :
                    return 0.5;
            }
        }else if(a.getType() == type::ice){
            switch (b.getType()) {
                case type::earth :
                    return 2;
                case type::steel :
                    return 2;
                case type::ice :
                    return 0.5;
                case type::fire :
                    return 0.5;
                case type::air :
                    return 1;
                case type::water :
                    return 0.5;
            }
        }else if(a.getType() == type::steel){
            switch (b.getType()) {
                case type::earth :
                    return 1;
                case type::steel :
                    return 0.5;
                case type::ice :
                    return 1;
                case type::fire :
                    return 0.5;
                case type::air  :
                    return 2;
                case type::water :
                    return 2;
            }
        }
    }

    auto change_if_fainted(creature& a,std::vector<std::unique_ptr<creature>>& player_vec){

        if(a.getHealth() <= 0 ){
            a.fainted = true;
            a.setHealth(0,a);
            std::cout <<a.getName() << " is fainted\n" << "you should change your creature\n\n";
            change_creature(player_vec);
        }
}
        /** player_choices()
           * a function asking to enter a string from the keyboard and,
           * depending on the input, perform actions
           *
           * @param  a and b are references of creature
           * @param enemy_vec and player_vec are references of vector of std::unique_ptr<creature>
           */
    auto player_choices(creature& a, creature& b,std::vector<std::unique_ptr<creature>>& enemy_vec,std::vector<std::unique_ptr<creature>>& player_vec ) -> void{
        std::cout << "[YOUR active creature (" << a.getName()
        << ": HP|" << a.getHealth() << " PW|" << a.getPower()
        << " DX|" << a.getDexterity() << " SM|" <<
        a.getSpecialMoveCounter() << " EXP|" << a.getExp() << ")" << '\n';
        std::cout << "ENEMY active creature (" << b.getName() << ": HP|" << b.getHealth() << ")]\n\n";
        std::string x;
        bool pl_ch = true;
        while(pl_ch){
        if(a.getHidingTimer() == 0) {
            std::cout << "(1) - [ATTACK] \n"
            << "(2) - " << a.getSmName()
            << "\n(3) - [CHANGE CREATURE] \n";

            if(a.getExp() > 0){
                std::cout << "(4) - [LEVEL UP]\n";
            }
            std::cout << "(H) - [HELP]\n";

            std::cin >> x;
            std::cout << "PLAYER :\n";

            if (x == "1" || x == "ATTACK" || x == "attack") {
                if(b.getHidingTimer() == 0){
                attack(a, b);
                }
                else if(b.getHidingTimer() == 1) {
                    std::cout << "You cant find enemy\n\n";
                }
                break;
            } else if (x == "2" || x == "SM" || x == "sm") {
                if(a.getSpecialMoveCounter() == 0){
                    std::cout << "YOUR SPECIAL MOVE IS EMPTY\n\n";
                }
                else if(b.getHidingTimer() == 0) {
                    special_move(a, b, enemy_vec,player_vec);
                    break;
                } else if(b.getHidingTimer() == 1){
                    std::cout << "You cant find enemy\n\n";
                    break;
                }

            } else if (x == "3" || x == "CHANGE" || x == "change" ||  x == "CHANGE CREATURE" || x == "change creature") {

                int cant_choice_fainted = 0;
                for (auto& e : player_vec){
                    if(e->getHealth() <= 0){
                        cant_choice_fainted++;
                    }
                }
                if (cant_choice_fainted == player_vec.size() - 1 ){
                    std::cout << "All YOUR creatures is fainted and you cant change\n\n";
                } else{
                change_creature(player_vec);
                    break;
                }
            } else if ((x == "4" || x == "level up" || x == "LEVEL UP") && (a.getExp() > 0)) {
                player_level_up(a);
                break;
            }
            else if(x == "h" || x == "H" || x == "help" || x == "HELP"){
                std::cout << "(1) - [YOUR CREATURE DESCRIPTION]\n"
                << "(2) - [ENEMY CREATURE DESCRIPTION]\n"
                <<"(3) - [TYPE TABLE]\n"
                <<"(4) - [RULES]\n";
                std::string help;
                std::cin >> help;
                if(help == "1"){
                    std::cout << "\n-------------------------------------------------\n"
                              <<"\nYOUR creature " << a.getName()
                              << " ( HP|" << a.getHealth()
                              <<  " PW|" << a.getPower()
                              << " DX|" << a.getDexterity()
                              << " )\n\n";
                    a.creature_description();
                    a.special_move_description();
                    std::cout << "\n-------------------------------------------------\n";
                }
               else if(help == "2"){
                    std::cout << "\n-------------------------------------------------\n"
                              <<"\nENEMY creature " << b.getName()
                              << " ( HP|" << b.getDefaultHealth()
                              <<  " PW|" << b.getDefaultPower()
                              << " DX|" << b.getDefaultDexterity()
                              << " )\n\n";
                    b.creature_description();
                    b.special_move_description();
                    std::cout << "\n-------------------------------------------------\n";
                }else if (help == "3"){
                   draw_table();
               }else if (help == "4"){
                   rules();
               }
            }
                else {
                std::cout << "You must choice variant in the brackets\n" << '\n';
            }
        } else if(a.getHidingTimer() == 1) {
            std::cout << "PLAYER :\n";
            std::cout << "*Rook jumps out of the smoke and backstab the creature*\n"
            << "and dealt " << (int)(a.getPower()* type_mod(a,b)*2) << " damage\n\n";
            b.setHealth(b.getHealth() - a.getPower()* type_mod(a,b)*2,b);
            a.setHidingTimer(0,a);
            break;
        }
        }
    }

    void attack(creature& a,creature& b) {
        std::uniform_real_distribution<double> damage(0.7,1.1);
        double attack_damage = damage(rd);
        if(is_hits(a,b) && a.getParalyzedCounter() == 0){
            attack_flavor_description();
            std::cout <<"and dealt " << (int)(a.getPower()* type_mod(a,b)*attack_damage) << " damage\n\n";
            b.setHealth(b.getHealth() - a.getPower()* type_mod(a,b)*attack_damage,b);

        } else if(a.getParalyzedCounter() > 0) {
            std::uniform_int_distribution<int> d(0,1);

            int dice_roll = d(rd);

            if (dice_roll == 0) {

                std::cout << getName() << " is paralyzed \n";
                std::cout <<  a.getParalyzedCounter() - 1 << " turns left\n\n";

            } else if (dice_roll == 1) {

                std::cout << "Spores doesn't stop " << a.getName() <<" from making this move. \n";
                std::cout <<  a.getParalyzedCounter()- 1 << " turns left\n";
                attack_flavor_description();
                std::cout << getName() << " is attacking\n" << "and dealt " << (int)(a.getPower() * type_mod(a, b)*attack_damage) << " damage\n\n";
                b.setHealth(b.getHealth() - a.getPower() * type_mod(a, b)*attack_damage,b);

            }
            a.setParalyzedCounter(a.getParalyzedCounter()- 1,a);
        } else{
            std::cout << "Attack is missed\n\n";
        }
    }


    void static change_creature(std::vector<std::unique_ptr<creature>>& vec){
        int creature_id =0;
        int change_choice;
        for (auto& e : vec ){
                creature_id++;
                if (creature_id > 1) {
                    std::cout << "[" << creature_id - 1 << "] " << e->getName() << '\n' << "HP|"
                              << e->getHealth() << " SM|" << e->getSpecialMoveCounter() << " EXP|" << e->getExp();
                    if(e->fainted){
                        std::cout << " FAINTED(!)";
                    }
                    std::cout << "\n\n";
                }
        }

        bool change_right_creature = true;
        while (change_right_creature) {
            std::cin >> change_choice;
            if(change_choice >= 6 || change_choice <= 0){
                std::cout << "You should choice creatures in list\n";
            }else if(!vec[change_choice]->fainted && change_choice < 6){
                std::cout << "Now " << vec[change_choice]->getName() << " in the head of team\n" << '\n';
                std::swap(vec[change_choice], vec.front());
                change_right_creature = false;
            }else if (vec[change_choice]->getHealth() <=0) {
                std::cout << "You should choice not-fainted creature\n";
            }
        }

    }


};

struct Gitrog : creature{

    Gitrog(){
      power = 23;
      health = 640;
      dexterity = 30;

      default_power = 23;
      default_health = 640;
      default_dexterity = 30;

      special_move_counter = 3;
      special_move_limit = 3;
      id = 1;
      typ = type::earth;

      name ="Gitrog, the Mushroom Frog" ;
      sm_name="[DEADLY SPORES]";
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& player_vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a);
        special_move_flavor_description();
            b.setParalyzedCounter(b.getParalyzedCounter() + 3,b);

    }

    auto attack_flavor_description() -> void override {
        std::cout <<"*Gitrog turns back and then shoots his tongue straight at the enemy*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Gitrog releases spores, because of which \nthe next three attacks the enemy \nhas a 50% chance of not getting hit}\n";
    }


    auto special_move_flavor_description() -> void override {
        std::cout <<"*Gitrog starts shaking and the whole battlefield is filled with spores*\n\n";
        sleep(1);
    }
    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : EARTH] ->\n" << "{Huge frog with growing mushrooms all over its back}\n\n";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Gitrog>();
    }
};

struct Rook : creature{

    Rook(){
       power = 35;
       health = 430;
       dexterity = 45;

       default_power = 35;
       default_health = 430;
       default_dexterity = 45;
        id =2;
       typ = type::steel;

       name ="Rook, the Ninja Rat" ;
       sm_name="[NINJUTSU]";

       special_move_counter = 2;
       special_move_limit = 2;
    }


    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Rook>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
            a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a);
            special_move_flavor_description();
            a.setHidingTimer(1,a);
    }

    auto attack_flavor_description() -> void override {
        std::cout << "*At the speed of lightning, Rook strikes the enemy with his blade*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Rook disappears from the battlefield for one turn,\nand then cause increased damage}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Rook throws a smoke bomb and hides*\n\n";
        sleep(1);
    }
    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : STEEL] ->\n" << "{A rat raised to be a killer and spy}\n\n";
    }

};

struct Moldive : creature{

    Moldive(){
       power = 28;
       health = 515;
       dexterity = 30;

       default_power = 28;
       default_health = 515;
       default_dexterity = 30;
        id =3;
       typ = type::water;

       name ="Moldive, the Jellyfish of Universe";
       sm_name="[MIND CHAIN]";

       special_move_counter = 2;
       special_move_limit = 2;
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Moldive>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();

        std::uniform_real_distribution<double> damage(0.8,1);

           for (auto& e : vec){
               double sm_damage = damage(rd);
               e->setHealth(e->getHealth() - a.getPower() * type_mod(a,b)/2*sm_damage,*e);
               if(e->getHealth() < 0){
                   e->setHealth(0,*e);
               }
           }
            std::cout << "Every creature in enemy team was dealt damage\n\n";

    }

    auto attack_flavor_description() -> void override {
        std::cout << "*Moldive strikes with its huge tentacle*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Moldive connects the minds of all enemy creatures,\ncausing them to take minor damage.}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Moldive penetrates the thoughts of ALL enemy creatures,\ncausing them to feel terrible pain.*\n";
        sleep(1);
    }
    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : WATER] ->\n" << "{Jellyfish, that wandering through space for thousands of years}\n\n";
    }
};

struct Gage : creature{

    Gage(){
        power = 36;
        health = 500;
        dexterity = 33;

        default_power = 36;
        default_health = 500;
        default_dexterity = 33;
        id =4;
        special_move_counter = 2;
        special_move_limit = 2;
        typ = type::fire;

        name ="Gage, the Racoon Gunslinger";
        sm_name="[HIGH NOON]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Gage>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();
        std::uniform_real_distribution<double> damage(0.8,1.1);
        std::uniform_int_distribution<int> dr(0,2);
            for (int i = 0; i < 6 ; i++ ){
                double sm_damage = damage(rd);
                int dice_roll = dr(rd);
                switch (dice_roll) {
                    case 0 :
                        sleep(1);
                        std::cout << "*MISS!*\n";
                        std::cout << "Gage has dealt 0 damage\n";
                        break;
                    case  1 :
                        sleep(1);
                        std::cout << "*GOT IT!*\n";
                        b.setHealth( b.getHealth() - a.getPower() * type_mod(a,b) * 0.5 * sm_damage,b);
                        std::cout << "Gage has dealt " << (int)(a.getPower() * type_mod(a,b) * 0.5 * sm_damage ) << " damage\n";
                        break;
                    case 2 :
                        sleep(1);
                        std::cout << "*CRIT!!!*\n";
                        b.setHealth( b.getHealth() - a.getPower() * type_mod(a,b) * 1.3,b);
                        std::cout <<"Gage has dealt " << (int)(a.getPower() * type_mod(a,b) * 1.3 * sm_damage) << " damage\n";

                }
          }
        std::cout << "\n";
    }

    auto attack_flavor_description() -> void override {
        std::cout << "*Gage takes aim and shoots*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Gage draws his revolver and fires six shots\nwhich can deal an average amount of damage,\nincreased or no damage at all}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Gage ispects the entire field, puts his paw on the holster and...*\n";
        sleep(1);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : FIRE] ->\n" << "{Racoon bounty hunter with a poncho and faithful revolver}\n\n";
    }
};

struct Kunga : creature{

    Kunga(){
        power = 22;
        health = 425;
        dexterity = 32;

        default_power = 22;
        default_health = 425;
        default_dexterity = 32;

        special_move_counter = 4;
        special_move_limit = 4;

        id =5;
        typ = type::air;
        name ="Kunga, the Flamingo Shaman";
        sm_name="[MYSTERY SOUP]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Kunga>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

            a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
            special_move_flavor_description();

            std::uniform_int_distribution<int> kunga_soup(0,3);

        int soup_effect = kunga_soup(rd);

        switch (soup_effect) {
            case 0 :
                std::cout << "Kunga increased HP!\n";
                a.setHealth(a.getHealth()+150,a);
                break;
            case 1 :
                std::cout << "Kunga increased POWER!\n";
                a.setPower(a.getPower()+25,a);
                break;
            case 2 :
                std::cout << "Kunga increased DEXTERITY!\n";
                a.setDexterity(a.getDexterity()+20,a);
                break;
            case 3 :
                std::cout << "Kunga's soup was bad\nand he took 20 damage...\nBut SM is not lost!\n";
                a.setHealth(a.getHealth()-20,a);
                a.setSpecialMoveCounter(a.getSpecialMoveCounter() + 1,a );
                break;
        }


        std::cout << "\n";
    }

    auto attack_flavor_description() -> void override {
        std::cout << "*Kunga curses the enemy with black magic*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Kunga eats mystery soup and gets a strong\nrandom skill boost for the rest of the fight}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Kunga eat soup and..*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : AIR] ->\n" << "{Flamingo Shaman using the power of spirits and mysterious potions\n\n";
    }
};

struct Yamato : creature{

    Yamato(){
        power = 25;
        health = 550;
        dexterity = 25;

        default_power = 25;
        default_health = 550;
        default_dexterity = 25;
        id =6;
        special_move_counter = 1;
        special_move_limit = 1;

        typ = type::ice;

        name ="Yamato, the Lizard Paladin";
        sm_name="[ICE SMITE]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Yamato>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();
        b.setHealth(b.getHealth() - a.getPower() * type_mod(a,b) * 5,b);
        std::cout << "And he has dealt " <<  a.getPower() * type_mod(a,b) * 5 << " damage\n";
        std::cout << "\n";
    }


    auto attack_flavor_description() -> void override {
        std::cout << "*Yamato strikes with a hammer*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Yamato crushes his enemies with a hammer, dealing a very huge damage\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Yamato pushes off the ground with the help of divine wings,\nand delivers a crushing hammer blow from the sky*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : ICE] ->\n" << "{A silver lizard paladin carrying the faith of his god around the world\nand punishing sinners with his ice hammer}\n\n";
    }
};

struct Bomin : creature{

    Bomin(){
        power = 28;
        health = 475;
        dexterity = 20;

        default_power = 28;
        default_health = 475;
        default_dexterity = 20;

        id = 7;

        special_move_counter = 1;
        special_move_limit = 1;

        typ = type::earth;

        name ="Bomin, the Bison Geomancer";
        sm_name="[STONE ARMOR]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Bomin>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();

        std::uniform_int_distribution<int> bowin_gloves_random(22,35);

        int bowin_gloves_strength = bowin_gloves_random(rd);
        a.setStoneGloves(4,a);
        a.setPower(a.getPower() + bowin_gloves_strength ,a);
        std::cout << "\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Bomin beats the enemy with his hard hoof*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{For three turns, the bomin uses the power of the earth\nto create stone armor and increase his strength.}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Bomin attracts rocks and earth to his hands, creating powerful armor*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : EARTH] ->\n" << "{Bison controlling the land and rocks to defeat his enemies}\n\n";
    }
};
struct Shomak : creature{

    Shomak(){
        power = 25;
        health = 480;
        dexterity = 33;

        default_power = 25;
        default_health = 480;
        default_dexterity = 33;

        id =8;

        special_move_counter = 4;
        special_move_limit = 4;

        typ = type::steel;

        name ="Shomak, the Jackal Samurai";
        sm_name="[DUEL OF FATES]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Shomak>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();

        std::cout << a.getName() << " challenges " << b.getName() << " to a duel\n";
        std::uniform_real_distribution<double> shomak_random_damage(1.2,1.7);
        std::uniform_int_distribution<int> shomak_duel(0,12);
        int shomak = shomak_duel(rd);
        int enemy = shomak_duel(rd);
        if(a.getPower()+shomak > b.getPower()+enemy){

            double shomak_damage = shomak_random_damage(rd);
            std::cout << "Shomak wins this duel and inflicts deep wounds on the enemy.\n";
            b.setHealth(b.getHealth() - a.getPower() * type_mod(a,b)*shomak_damage,b);
            std::cout << "he has dealt " <<  a.getPower() * type_mod(a,b) << " damage\n" << "he increased power and restored health\n";
            a.setDefaultPower(a.getPower() + 4,a);
            a.setPower(a.getPower() + 4,a);

            if(a.getHealth() <= a.getDefaultHealth() - 40){

            a.setHealth(a.getHealth()+40,a);}

            else {

                a.setHealth(a.getDefaultHealth(),a);

            }
        }else if (b.getPower()+enemy > a.getPower()+shomak){

            std::cout << "Shomak lost the duel and took 25 damage\n";
            a.setHealth(a.getHealth() - 25,a);

        }else if (a.getPower()+shomak == b.getPower()+enemy){

            std::cout << "No one won the duel and SM is not lost\n";
            a.setSpecialMoveCounter(a.getSpecialMoveCounter() + 1,a);

        }

        std::cout << "\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Shomak strikes with his sharp katana*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Shomak challenges an enemy creature to a duel, and if he wins,\nhe will inflict increased damage and\nincrease his power for the rest of the game}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Shomak exposes his blade and points in the direction of the enemy*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : STEEL] ->\n" << "{Jackal samurai, traveling the world and looking for a worthy opponent}\n\n";
    }
};
struct Ezo : creature{

    Ezo(){
        power = 18;
        health = 660;
        dexterity = 29;
        id =9;
        default_power = 18;
        default_health = 650;
        default_dexterity = 29;

        special_move_counter = 1;
        special_move_limit = 1;

        typ = type::water;

        name ="Ezo, the Rock Whale";
        sm_name="[WHALE MUST GO ON]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Ezo>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::uniform_int_distribution<int> ezo_heal(90,180);
        special_move_flavor_description();
        for(auto& e : pl_vec){
            if(e->fainted== false){
                int heal = ezo_heal(rd);
                e->setParalyzedCounter(0,*e);
                e->setBurnCounter(-1,*e);
                e->setPoison(false,*e);
                if(e->getHealth() <= e->getDefaultHealth() - heal){
                    e->setHealth(e->getHealth() + heal,*e);
                }else {
                    e->setHealth(e->getDefaultHealth(),*e);
                }
            }
        }
        std::cout << "Everyone in team healed\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Ezo beats the enemy with his mighty tail*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Ezo restores a huge amount of health and removes all negative effects\nto all creatures in the team except fainted}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Ezo jumps out of the water, singing his beautiful song*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : WATER] ->\n" << "{Blue whale with a powerful voice and huge stone growths all over its back e}\n\n";
    }
};
struct Genur : creature{

    Genur(){
        power = 22;
        health = 545;
        dexterity = 31;

        default_power = 22;
        default_health = 545;
        default_dexterity = 31;

        id =10;

        special_move_counter = 2;
        special_move_limit = 2;

        typ = type::fire;

        name ="Genur, the Boar Pyromancer";
        sm_name="[HEAVEN'S ON FIRE]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Genur>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::uniform_int_distribution<int> genur_burn(2,6);
        special_move_flavor_description();
        int burn = genur_burn(rd);
        b.setBurnCounter(burn,b);
        std::cout << "\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Genur spews fire from his mouth*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Genur sets enemy on fire for a random number of turns,\nand at the beginning of each of them the enemy will receive damage.}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Genur waves his hands and the ground beneath the enemy begins to burn*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : FIRE] ->\n" << "{A sinister boar using the power of fire to send his enemies to hell}\n\n";
    }
};
struct Ziram  : creature{

    Ziram(){
        power = 24;
        health = 500;
        dexterity = 20;
        id =11;
        default_power = 24;
        default_health = 500;
        default_dexterity = 20;

        special_move_counter = 3;
        special_move_limit = 3;

        typ = type::ice;

        name ="Ziram, the Hedgehog Death Knight";
        sm_name="[FROZEN FUNERAL]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Ziram>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        special_move_flavor_description();
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::uniform_real_distribution<double> random_ziram_damage(1.5,2);
        double ziram_damage = random_ziram_damage(rd);
        b.setHealth(b.getHealth() - a.getPower() * a.type_mod(a,b) * ziram_damage,b);
        std::cout << "He has dealt " << (int)(a.getPower() * a.type_mod(a,b) * ziram_damage) << " damage " <<
        "and stole " << (int)((a.getPower() * a.type_mod(a,b) * ziram_damage)/2) << " health\n";
        a.setHealth(a.getHealth() + (a.getPower() * a.type_mod(a,b) * ziram_damage)/2,a);
        std::cout << "\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Ziram strikes with his two-handed sword*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Ziram attacks the enemy with increased damage,\nand steals some of his health for the rest of the battle}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Ziram with the help of black magic\ntakes away part of the soul from the enemy*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : ICE] ->\n" << "{Hedgehog who linked his soul with the evil gods\nand now he forced to serve their will forever.}\n\n";
    }
};
struct Zastan : creature{

    Zastan(){
        power = 22;
        health = 445;
        dexterity = 39;
        id =12;
        default_power = 22;
        default_health = 445;
        default_dexterity = 39;

        special_move_counter = 3;
        special_move_limit = 3;

        typ = type::air;

        name ="Zastan, the Rooster Monk ";
        sm_name="[HURRICANE OF KICKS]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Zastan>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        special_move_flavor_description();
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::uniform_int_distribution<int> random_kicks(1,8);
        std::uniform_real_distribution<double> random_kicks_damage(0.7,1.3);
        int kicks_counter = random_kicks(rd);
        for (int i = 0; i < kicks_counter ; i ++ ){
            double kicks_damage = random_kicks_damage(rd);
            b.setHealth(b.getHealth() - a.getPower() * a.type_mod(a,b) * kicks_damage,b);
            std::cout << (int)(a.getPower() * a.type_mod(a,b) * kicks_damage) << " damage!\n";
            sleep(1);
        }
        std::cout << "And Zastan kicked " << kicks_counter << " times!\n";
        std::cout << "\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Zastan dealt several accurate kicks with his wings to the enemy*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Zastan uses his monk skills to dealt\na random number of powerful kicks to the enemy.}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Zastan prepare to inflict a hurricane of kicks..*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : AIR] ->\n" << "{A rooster who has trained in a temple all his life to fight evil}\n\n";
    }
};
struct  Florent : creature{

    Florent(){
        power = 25;
        health = 485;
        dexterity = 35;

        default_power = 25;
        default_health = 485;
        default_dexterity = 35;

        id =13;

        special_move_counter = 3;
        special_move_limit = 3;

        typ = type::steel;

        name ="Florent, the Cat Musketeer";
        sm_name="[DISARM]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Florent>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        special_move_flavor_description();
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::uniform_int_distribution<int> florent_random(4,8);
        int florent_disarm = florent_random(rd);
        if(b.getPower() - florent_disarm > 0){
        b.setPower(b.getPower() - florent_disarm,b);}
        else if (b.getPower() - florent_disarm <= 0 ){
            b.setPower(0,b);
        }
        std::cout << b.getName() << " lost " << florent_disarm << " power\n\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Florent pierces his enemy with a rapier*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Florent, with the help of the blade skills, disarms enemy and reduces its power}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*With a deft movement, the Florent knocks the weapon out of enemy's hands.*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : STEEL] ->\n" << "{a proud and self-confident cat who masterfully owns a rapier}\n\n";
    }
};

struct Thurinrod : creature{

    Thurinrod(){
        power = 20;
        health = 510;
        dexterity = 35;
        id =14;
        default_power = 20;
        default_health = 510;
        default_dexterity = 35;

        special_move_counter = 1;
        special_move_limit = 1;

        typ = type::water;

        name ="Thurinrod, the Timeless Platypus";
        sm_name="[BACK IN TIME]";
    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Thurinrod>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {

        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        special_move_flavor_description();
        std::uniform_int_distribution<int> thur_random(8,20);
        for( auto& e : vec){
            if(e->fainted == false){
                int thur_sm = thur_random(rd);
                if(e->getDexterity() - thur_sm > 0 ){
                    e->setDexterity(e->getDexterity() - thur_sm,*e);
                }else if ( e->getDexterity() - thur_sm <= 0){
                    e->setDexterity(0,*e);
                }
            }
        }

    std::cout << "For each enemy, time has slowed down\n\n";
    }
    auto attack_flavor_description() -> void override {
        std::cout << "*Thurinrod beats its enemy with a mighty tail*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Thurinrod stops time for all enemies and greatly lowers their dexterity score until the end of the battle.}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*With one flap of the paw, Thurinrod makes its enemies freeze in place.*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : WATER] ->\n" << "{The platypus lives outside of time and is able to control it}\n\n";
    }
};

struct Quilla : creature{

    Quilla(){
        power = 23;
        health = 550;
        dexterity = 35;
        id =15;
        default_power = 23;
        default_health = 550;
        default_dexterity = 35;

        special_move_counter = 2;
        special_move_limit = 2;

        typ = type::earth;

        name ="Quilla, the Serpent of True Death";
        sm_name="[KILLER QUEEN]";

    }

    auto clone() -> std::unique_ptr<creature> override {
        return std::make_unique<Quilla>();
    }

    auto special_move(creature& a, creature& b, std::vector<std::unique_ptr<creature>>& vec,std::vector<std::unique_ptr<creature>>& pl_vec)->void override {
        special_move_flavor_description();
        a.setSpecialMoveCounter(a.getSpecialMoveCounter() - 1,a );
        std::cout << "enemy is poisoned\n\n";
        b.setPoison(true,b);
    }

    auto attack_flavor_description() -> void override {
        std::cout << "*Quilla chokes the enemy with her tail, breaking his bones*\n";
        sleep(1);
    }

    auto special_move_description() -> void override {
        std::cout <<"Special move: " << getSmName() << " ->\n{Quilla bites her enemy with all her heads poisoning him for the rest of the fight}\n";
    }

    auto special_move_flavor_description() -> void override {
        std::cout << "*Quilla digs into her enemy with her fangs, poisoning the enemy's blood*\n";
        sleep(2);
    }

    auto creature_description() -> void override {
        std::cout << "Creature Description: [TYPE : EARTH] ->\n" << "{Two-headed snake with sharp as spear fangs and mortal venom}\n\n";
    }
};

/** enemy_random_creatures()
   * a function that fills the vector of creatures with random creatures
   *
   * @paramenemy_vec and all_vec are references of vector of std::unique_ptr<creature>
   */

auto enemy_random_creatures(std::vector<std::unique_ptr<creature>>& enemy_vec,std::vector<std::unique_ptr<creature>>& all_vec)->void{
    std::uniform_int_distribution<int> distr(1,15);

    for (int i = 0; i < 4 ; i++){
        int dice_roll = distr(rd);
        enemy_vec.push_back(all_vec[dice_roll-1]->clone());

    }
}

auto conditions_update(creature& a, std::string str)->void{
    std::uniform_int_distribution<int> random_burning(15,25);
    std::uniform_int_distribution<int> random_poisoned(3,15);

    if(a.getStoneGloves() > 0) {
        std::cout << str << " Stone gloves will break in " << a.getStoneGloves()  << " turns\n";
        a.setStoneGloves(a.getStoneGloves() - 1, a);
    }else if(a.getStoneGloves() == 0){
        std::cout << "Stone gloves broke\n";
        a.setPower(a.getDefaultPower(),a);
        a.setStoneGloves(-1,a);
    }

    if(a.getBurnCounter() > 0) {
        int burning = random_burning(rd);
        std::cout  << str << " " <<  a.getName()  <<" is burning\n";
        std::cout << "and he burns on " << (int)(a.type_mod(*std::make_unique<Genur>(),a) * burning) << " damage\n";
        a.setHealth(a.getHealth() - a.type_mod(*std::make_unique<Genur>(),a) * burning,a);
        a.setBurnCounter(a.getBurnCounter() - 1, a);
    }else if(a.getBurnCounter() == 0){
        std::cout << str << a.getName() << " doesn't burn anymore\n";
        a.setBurnCounter(-1,a);
    }

    if (a.isPoison() == true){
        int poison = random_poisoned(rd);
        std::cout << str << a.getName() << " is poisoned and he took " << (int)(poison * a.type_mod(*std::make_unique<Quilla>(),a)) << "\n" ;
        a.setHealth(a.getHealth() - a.type_mod(*std::make_unique<Quilla>(),a), a);
    }
    std::cout<<"\n";
}

/** enemy_creature_changing()
   * function that replaces an enemy creature
   *
   * @param enemy_vec and player_vec are references of vector of std::unique_ptr<creature>
   */
auto enemy_creature_changing(std::vector<std::unique_ptr<creature>>& enemy_vec,std::vector<std::unique_ptr<creature>>& player_vec)->void{

    if (enemy_vec.front()->getHealth() <= 0 ){
        std::cout << "ENEMY "<< enemy_vec.front()->getName() << " is fainted\n";
        enemy_vec.erase(enemy_vec.begin());
        player_vec.front()->setExp(player_vec.front()->getExp() + 1,*player_vec.front());
        std::cout <<"YOUR "<< player_vec.front()->getName() << " EXP = " << player_vec.front()->getExp() << "\n\n";
    }

}
/** сhoice_your_destiny()
   * a function that fills a vector of creatures of the user's choice
   *
   * @param pvec and acvec are references of vector of std::unique_ptr<creature>
   */
    auto choice_your_destiny( std::vector<std::unique_ptr<creature>>& pvec, std::vector<std::unique_ptr<creature>>&  acvec )->void{

        sleep(1);
        std::cout<<"First you need to create a team with 6 creatures\n";
        sleep(1);
         std::cout << "to select a creature,\nyou need to enter its index in square brackets from the keyboard,\nand then, if you are sure, confirm\n\n";
        sleep(2);
        std::cout << "Each creature has\ndexterity score (DX)\nstrength score (PW)\nhealth points (HP)\nand special skill scores that determine how many times the ability can be used per battle (SM)\n";
        int x;
        int y = 0;
        std::string str;

        for(auto& a : acvec){
            sleep(1);
            y++;
            std::cout << "\n-------------------------------------------------\n"
             <<"\n[" << y << "] " << a->getName()
            << " ( HP|" << a->getHealth()
            <<  " PW|" << a->getPower()
            << " DX|" << a->getDexterity()
            << " SM|" << a->getSpecialMoveLimit()
            << " )\n\n";
            a->creature_description();
            a->special_move_description();
        }

        for(int i = 0; i < 6 ; i++ ) {
            std::cin >> x;
                if(x > acvec.size()){
                    std::cout<<"You should choice creatures from list\n";
                    i--;
                }else if( x <= acvec.size()) {
                    std::cout << "Are you sure you want to have "<< acvec[x-1]->getName() << " in YOUR team?\n" << "yes(y) or no(n)\n";
                    std::cin >> str;
                    if (str == "yes" || str == "y") {
                        pvec.push_back(acvec[x-1]->clone());
                        std::cout << pvec[i]->getName() << " now in YOUR team " << i+1 << "/6\n";

                    } else if (str == "no" || str == "n") {
                        std::cout << "Pick someone else\n";
                        i--;
                    } else {
                        std::cout << "You should answer yes or no\n";
                        i--;
                    }
                }
        }

    };



    auto round(std::vector<std::unique_ptr<creature>>& player_vec)->bool{
        int round_player = 0;
        for (auto& e : player_vec){
            if(e->fainted == true){
                round_player++;
            }
        }
        return (round_player == 6 );
    }

    auto enemy_level_up(std::vector<std::unique_ptr<creature>>& enemy_vec,int const& x){
        std::uniform_int_distribution<int> random_buff(1,3);
        for (auto& e : enemy_vec){
            for (int i = 0; i < x; i++) {
                for (int j = 0 ; j < 2 ; j++ ) {
                    int buff = random_buff(rd);
                    switch (buff) {
                        case 1 :
                            e->setHealth(e->getHealth() + 15, *e);
                            break;
                        case 2 :
                            e->setPower(e->getPower() + 3, *e);
                            break;
                        case 3 :
                            e->setDexterity(e->getDexterity() + 3, *e);
                            break;

                    }
                }
            }
        }
    }
auto game_over(std::vector<std::unique_ptr<creature>>& player_vec)->void{
    int all_fainted = 0;
        for (auto &e: player_vec) {
            if (e->getHealth() <= 0) {
                all_fainted++;
            }
        }
        if (player_vec.size() == all_fainted) {
            std::cout << "Game over\n";
            abort();
        }
    }

auto add_all_creatures(std::vector<std::unique_ptr<creature>>& all_vec)->void{
    all_vec.push_back(std::make_unique<Gitrog>());
    all_vec.push_back(std::make_unique<Rook>());
    all_vec.push_back(std::make_unique<Moldive>());
    all_vec.push_back(std::make_unique<Gage>());
    all_vec.push_back(std::make_unique<Kunga>());
    all_vec.push_back(std::make_unique<Yamato>());
    all_vec.push_back(std::make_unique<Bomin>());
    all_vec.push_back(std::make_unique<Shomak>());
    all_vec.push_back(std::make_unique<Ezo>());
    all_vec.push_back(std::make_unique<Genur>());
    all_vec.push_back(std::make_unique<Ziram>());
    all_vec.push_back(std::make_unique<Zastan>());
    all_vec.push_back(std::make_unique<Florent>());
    all_vec.push_back(std::make_unique<Thurinrod>());
    all_vec.push_back(std::make_unique<Quilla>());
}
auto save_game(std::vector<std::unique_ptr<creature>>& player_vec,int i) -> void{
    /**
    * Zostawiłem ten komentarz, ponieważ miałem problem z linią pod nim.
    * Pierwotnie napisałem ścieżkę do pliku w formie, tak jak Pan napisał w ostatnim opublikowanym nagraniu
    * ale z jakiegoś powodu to nie zadziałało dla mnie, to tylko założenie, ale być może powodem jest to, że napisałem ten kod nie na Windowsie, ale na Linuksie
    * więc zostawiłem na wszelki wypadek wiersz kodu napisany tak, jak w Pana filmie
    */
    auto path = std::string("../saves.txt");
    //auto path = std::string("..\\saves.txt");
    auto save_file_out = std::fstream(path,std::ios::out | std::ios::trunc);
    save_file_out <<"";

        std::cout << "do you wanna save game?\nyes(y) or no(n)\n";
        auto str = std::string();
        auto str1 = std::string();
    while(true) {
            std::cin >> str;
            if (str == "yes" || str == "y") {
                auto save_file_out2 = std::fstream(path,std::ios::out | std::ios::app);
                for(auto& e: player_vec){
                    save_file_out2 << e->id << ' '<< e->getDefaultHealth() << ' ' << e->getDefaultPower()<< ' ' << e->getDexterity()<< ' ' << e->getExp()<< '\n';
                }
              save_file_out2 << i+1;
            } else if (str == "no" || str == "n") {

            }
            std::cout << "Do yo wanna continue?\nyes(y) or no(n)\n";
            std::cin >> str1;
            if(str1 == "yes" || str1 == "y"){
                break;
            }else if(str1 == "no" || str1 == "n"){
                abort();
            }
        }
    }

    auto load_game(std::vector<std::unique_ptr<creature>>& player_vec, std::vector<std::unique_ptr<creature>>& all_vec,int& turn_number) ->void {
        auto path = std::string("../saves.txt");
        //auto path = std::string("..\\saves.txt");
        auto save_file_in = std::fstream(path);
        auto test = std::string();
        save_file_in >> test;
        if(test != ""){
        save_file_in.clear();
        save_file_in.seekg(0,std::ios::beg);
        auto id = int();
        auto health = int();
        auto power = int();
        auto dexterity = int();
        auto exp = int();
        auto turn = int();

       std::cout << "Do you wanna load game?\n" << "yes(y) or no(n)\n";
       auto str = std::string();
       std::cin >> str;
       if(str == "yes" || str == "y"){
           for(int i = 0; i < 6 ; i++) {
               save_file_in >> id;
               player_vec.push_back(all_vec[id - 1]->clone());
               save_file_in >> health;
               player_vec[i]->setHealth(health, *player_vec[i]);
               player_vec[i]->setDefaultHealth(health, *player_vec[i]);
               save_file_in >> power;
               player_vec[i]->setPower(power, *player_vec[i]);
               player_vec[i]->setDefaultPower(power, *player_vec[i]);
               save_file_in >> dexterity;
               player_vec[i]->setDexterity(dexterity, *player_vec[i]);
               player_vec[i]->setDefaultDexterity(dexterity, *player_vec[i]);
               save_file_in >> exp;
               player_vec[i]->setExp(exp, *player_vec[i]);
           }
           save_file_in >> turn;
           turn_number = turn;
           }
       }

    }
auto main()->int {
    auto all_creatures = std::vector<std::unique_ptr<creature>>();
    add_all_creatures(all_creatures);

    auto enemies = std::vector<std::unique_ptr<creature>>();
    auto player_creatures = std::vector<std::unique_ptr<creature>>();
    while (true) {
        start_game();
        rules();
        int turn = 0;
        load_game(player_creatures,all_creatures,turn);
        if(player_creatures.size() == 0) {
            choice_your_destiny(player_creatures, all_creatures);
        }
        for ( turn ; turn < 4 ; turn++) {
                enemy_random_creatures(enemies,all_creatures);
                enemy_level_up(enemies,turn*2);
                start_round(turn+1);
                while (true) {
                    game_over(player_creatures);
                    conditions_update(*player_creatures.front(), "YOUR CONDITION :\n");
                    player_creatures.front()->change_if_fainted(*player_creatures.front(), player_creatures);
                    conditions_update(*enemies.front(), "ENEMY CONDITION :\n");
                    enemy_creature_changing(enemies, player_creatures);
                    player_creatures.front()->player_choices(*player_creatures.front(), *enemies.front(),enemies,player_creatures);
                    enemy_creature_changing(enemies, player_creatures);
                    if(turn == 3 && !round(player_creatures) && enemies.size() == 0){
                        std::cout<< "Game is over";
                        break;
                    } else if (!round(player_creatures) && enemies.size() == 0) {
                        std::cout << " End of the round \n";
                        player_creatures.front()->creature_rest(player_creatures);
                        save_game(player_creatures,turn);
                        break;
                    }
                        enemies.front()->enemy_choices(*enemies.front(), *player_creatures.front(),player_creatures, enemies);
                }
        }

            break;

    }
}

