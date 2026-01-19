#include "raritysystem.h"
#include <cstdlib>

int raritysystem::raritygen() //I have designed the rarity sytstem to be random, these are the odds
{
	int rarityfloatval = rand() % 101;
	if (rarityfloatval < 50) {
		return 1;
	}
	else if (rarityfloatval > 50 && rarityfloatval < 95) {
		return 2;
	}
	else if (rarityfloatval >= 95) {
		return 3;
	}
	else {
		return 1;
	}
}

string raritysystem::raritysel(int rarityint) //based on the odds, the rarity will be picked
{
	if (rarityint == 1) {
		return "Common";
	}
	else if (rarityint == 2) {
		return "Rare";
	}
	else if (rarityint == 3) {
		return "Legendary";
	}
	else {
		return "Common";
	}
}
