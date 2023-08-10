#include "include/Interface.h"
#include <iostream>


int main()
{
	std::unique_ptr<Interface> init = std::make_unique<Interface>();
	init->Init(init);
	return 0;
}
