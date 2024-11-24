#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include "Player.h"

#include <string>
#include <vector>
using std::vector;

class PlayerStrategy{
public:
    virtual void issueOrder(Order* o) = 0;
    virtual void issueOrder() = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
protected:
    Player* player;
    string* type;
};

class Neutral:public PlayerStrategy{
public:
     explicit Neutral(Player* player);
     void issueOrder(Order* o) override;
     void issueOrder() override;
     vector<Territory*> toAttack() override;
     vector<Territory*> toDefend() override;
};

class Cheater:public PlayerStrategy{
public:
    explicit Cheater(Player* player);
    void issueOrder(Order* o) override;
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Human:public PlayerStrategy{
public:
    explicit Human(Player* player);
    void issueOrder(Order* o) override;
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Aggressive:public PlayerStrategy{
public:
    explicit Aggressive(Player* player);
    void issueOrder(Order* o) override;
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Benevolent:public PlayerStrategy{
public:
    explicit Benevolent(Player* player);
    void issueOrder(Order* o) override;
    void issueOrder() override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif //PLAYERSTRATEGIES_H
