#include "include/Interface.h"
#include <iostream>


int main()
{
	// singleton pattern
	std::unique_ptr<Interface> init = std::make_unique<Interface>();
	init->Init(init);
	return 0;
}
