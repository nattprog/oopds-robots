#include "Battlefield.h"

Battlefield::Battlefield()
{
    //ctor
}

Battlefield::~Battlefield()
{
    //dtor
}

Battlefield::Battlefield(const Battlefield& other)
{
    //copy ctor
}

Battlefield& Battlefield::operator=(const Battlefield& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
