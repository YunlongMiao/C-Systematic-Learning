#define   _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "main.h"

char stunum[128] = "";

int main() {

	GetData();
	CalculateData(stunum);
	printf("%s\n", stunum);
	WriteFile(stunum);
}