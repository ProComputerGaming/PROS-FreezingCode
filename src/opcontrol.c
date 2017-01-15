#include "main.h"

void operatorControl() {
	int value;
	while (1) {
		value = joystickGetAnalog(1, 1);
		motorSet(2, value);
	}
}
