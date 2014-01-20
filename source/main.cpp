#include "header/mainAdam.h"
#include "header/mainGeneral.h"
#include "header/mainArtur.h"


enum MAIN{ GENERAL, ADAM, ARTUR };

int main(void)
{
	int m = ADAM;

	if (m == GENERAL)
		mainGeneral();
	else if (m == ADAM)
		mainAdam();
	else if (m == ARTUR)
		mainArtur();

	return 0;
}	