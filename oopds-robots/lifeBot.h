#ifndef lifeBot_H
#define lifeBot_H

#include "GenericRobot.h"

class lifeBot : virtual public GenericRobot
{
public:
    lifeBot(string id = "", int x = -1, int y = -1);
    virtual ~lifeBot();
    lifeBot(const lifeBot &other);
    lifeBot &operator=(const lifeBot &other);
      virtual void actionFire(Battlefield *battlefield) override;


protected:
     int lifeupg_;                 // New attribute for health
    void upgradeHealth();
};

#endif // lifeBot_H
