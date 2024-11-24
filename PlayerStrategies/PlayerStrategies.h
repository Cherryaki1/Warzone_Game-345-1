#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include "Player.h"

class PlayerStrategy{
public:
    virtual void issueOrder(Order* o) = 0;
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
private:
    Player* p;
};

class Neutral:public PlayerStrategy{
public:
     void issueOrder(Order* o) override;
     vector<Territory*> toAttack() override;
     vector<Territory*> toDefend() override;
};

class Cheater:public PlayerStrategy{
public:
    void issueOrder(Order* o) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Human:public PlayerStrategy{
public:
    void issueOrder(Order* o) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Aggressive:public PlayerStrategy{
public:
    void issueOrder(Order* o) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};

class Benevolent:public PlayerStrategy{
public:
    void issueOrder(Order* o) override;
    vector<Territory*> toAttack() override;
    vector<Territory*> toDefend() override;
};


#endif //PLAYERSTRATEGIES_H
