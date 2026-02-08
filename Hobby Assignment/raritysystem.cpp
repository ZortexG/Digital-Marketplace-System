#include "raritysystem.h"
#include <cstdlib>

string raritysystem::raritygen()
{
	int rarityfloat = rand() % 101;
	if (rarityfloat < 40) {
		return "Common";
	}
	else if (rarityfloat >= 70 && rarityfloat < 80) {
		return "Rare";
	}
	else if (rarityfloat >= 80 && rarityfloat < 90) {
		return "Epic";
	}
	else if (rarityfloat >= 90) {
		return "Legendary";
	}
	else {
		return "Common";
	}
}
