//Item condition and wear system similar to CS item system
#include "condtitionsystem.h"
#include <cstdlib>

int condtitionsystem::conditiongen(int itemvalue) //Just like rarity, it is also random but with equal odds
{
	int conditionfloatval = rand() % 101;
	if (conditionfloatval < 20) {
		return 1;
	}
	else if (conditionfloatval >= 20 && conditionfloatval < 40) {
		return 2;
	}
	else if (conditionfloatval >= 40 && conditionfloatval < 60) {
		return 3;
	}
	else if (conditionfloatval >= 60 && conditionfloatval < 80) {
		return 4;
	}
	else if (conditionfloatval >= 80) {
		return 5;
	}
	else {
		return 3;
	}
}

string condtitionsystem::conditionsel(int conditionint)
{
	if (conditionint == 1) {
		return "Battle Scarred";
	}
	else if (conditionint == 2) {
		return "Well Worn";
	}
	else if (conditionint == 3) {
		return "Field Tested";
	}
	else if (conditionint == 4) {
		return "Minimal Wear";
	}
	else if (conditionint == 5) {
		return "Factory New";
	}
	else {
		return "Field Tested";
	}
}
