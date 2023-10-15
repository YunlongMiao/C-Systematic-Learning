#pragma once

#define PATHFILE "calculate.txt"
//char stunum[128] = "";

FILE* FileOpen(const char *Command);
void GetData();
void CalculateData(char* stunumx);
void WriteFile(char* stu);