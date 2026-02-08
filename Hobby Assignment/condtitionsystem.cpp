//Item condition and wear system similar to CS item system
#include "condtitionsystem.h"
#include <cstdlib>

string condtitionsystem::conditiongen()
{
	int conditionfloat = rand() % 101;
	if(conditionfloat < 20) {
		return "Battle-Scarred";
	}
	else if (conditionfloat >= 20 && conditionfloat < 40) {
		return "Well-Worn";
	}
	else if (conditionfloat >= 40 && conditionfloat < 60) {
		return "Field-Tested";
	}
	else if (conditionfloat >= 60 && conditionfloat < 80) {
		return "Minimal Wear";
	}
	else if (conditionfloat >= 80) {
		return "Factory New";
	}
	else {
		return "Field-Tested";
	}
};