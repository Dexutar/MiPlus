#include <iostream>
#include "ConnectionManager.hh"

int main ()
{
  ConnectionManager cm{25565};
  cm.wait();
}