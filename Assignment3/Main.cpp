#include <iostream>
#include "CoffeeShop.h"


int main(int argc, char* argv[])
{

	CoffeeShop* new_shop = new CoffeeShop;
	new_shop->manage_shop(argv[1], argv[2], 0);

	CoffeeShop* new_shop_N_3 = new CoffeeShop;
	new_shop_N_3->manage_shop(argv[1], argv[2], 1);
}
