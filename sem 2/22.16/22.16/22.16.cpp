#include "stdafx.h"
#include <stdio.h>
#include <string.h>
//#include <conio.h>
#define N 10000
int validate_expression(const char *expr);
//=============================================
float zamiana(char a)
{
	if (a == '0') return 0;
	if (a == '1') return 1;
	if (a == '2') return 2;
	if (a == '3') return 3;
	if (a == '4') return 4;
	if (a == '5') return 5;
	if (a == '6') return 6;
	if (a == '7') return 7;
	if (a == '8') return 8;
	if (a == '9') return 9;
	return 0;
}
//=========================================
int potega(int a, int b)
{
	int wynik=1;
	for (int i = 0; i < b; i++)
	{
		wynik *= a;
	}
	return wynik;
}
//=====================================================
int calculate(const char* expr, float *result)
{
	if (validate_expression(expr) == 0) return 0;
	float liczba, liczba1 = 0, liczba2 = 0;
	int licznik=0,spr=0;
	float wynik=0;
	if (expr == NULL || result == NULL) return 0;
	for (int i = 0; *(expr + i) != 0; i++)
	{
		licznik++;
		if (*(expr + i) < '0' || *(expr + i) > '9') spr++;
	}
	if (spr == 0)
	{
		licznik--;
		for (int j = 0; *(expr + j) != 0; j++)
		{
			liczba = zamiana(*(expr + j));
			liczba1 += liczba * potega(10, licznik);
			licznik--;
		}
		*result = liczba1;
		return 1;
	}
	licznik = 0;
	for (int j =0; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
	{
		licznik++;
	}
	licznik--;
	liczba = 0;
	for (int j = 0; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
	{
		liczba = zamiana(*(expr + j));
		wynik += liczba * potega(10, licznik);
		licznik--;
	}
	for (int i = 0; *(expr + i) != 0; i++)
	{
		switch (*(expr+i))
		{
		case '+':
			licznik = 0; liczba2 = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				licznik++;
			}
			licznik--;
			liczba = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				liczba = zamiana(*(expr + j));
				liczba2 += liczba * potega(10, licznik);
				licznik--;
			}
			wynik += liczba2;
			break;
		case '-':
			licznik = 0; liczba2 = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				licznik++;
			}
			licznik--;
			liczba = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				liczba = zamiana(*(expr + j));
				liczba2 += liczba * potega(10, licznik);
				licznik--;
			}
			wynik -= liczba2;
			break;
		case '*':
			licznik = 0; liczba2 = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				licznik++;
			}
			licznik--;
			liczba = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				liczba = zamiana(*(expr + j));
				liczba2 += liczba * potega(10, licznik);
				licznik--;
			}
			wynik *= liczba2;
			break;
		case '/':
			licznik = 0; liczba2 = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				licznik++;
			}
			licznik--;
			liczba = 0;
			for (int j = i + 1; *(expr + j) >= '0'&& *(expr + j) <= '9'; j++)
			{
				liczba = zamiana(*(expr + j));
				liczba2 += liczba * potega(10, licznik);
				licznik--;
			}
			if (liczba2 == 0) return 0;
			wynik /= liczba2;
			break;
		}
		*result = wynik;
	}
	return 1;	
}
//===============================================
int validate_expression(const char *expr)
{
	if (expr == NULL) return -1;
	if (*expr == '-') return 0;
	char znaki[] = "!@#$%^&()_=|][}{:'\";>.<, `~qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
	if (strpbrk(expr, znaki)) return 0;
	
	int spr;
	for (int i = 0; *(expr + i) != 0; i++)
	{
		spr = 0;
		if (*(expr + i) == '+' || *(expr + i) == '-' || *(expr + i) == '*' || *(expr + i) == '/') spr++;
		if (spr != 0)
		{
			i++;
			if (*(expr + i) == '+' || *(expr + i) == '-' || *(expr + i) == '*' || *(expr + i) == '/' || *(expr + i) == 0 || *(expr + i) == 10) return 0;
		}
	}
	/*
	int spr;
	for (int i = 0; *(expr + i) != 0; i ++ )
	{
		spr = 0;
		if (*(expr + i) == '+' || *(expr + i) == '-' || *(expr + i) == '*' || *(expr + i) == '/') spr++;
		if (spr != 0)
		{
			i++;
			if (*(expr + i) == '+' || *(expr + i) == '-' || *(expr + i) == '*' || *(expr + i) == '/' || *(expr + i) == 0 || *(expr + i) == 10) return 0;
		}
	}
	for (int i = 0; *(expr + i) != 0; i++)
	{
		if ((*(expr + i) > '9' || *(expr + i) < '0') && *(expr + i) != '+' && *(expr + i) != '-' && *(expr + i) != '*' && *(expr + i) != '/' )
		{
			return 0;
		}
	}*/
	return 1;
}
//===============================================
int main()
{
	float result=0;
	char expr[N];
	printf("Pije by pasc,padam by wstac, wstaje by zyc, zyje by pic.\n/autor nieznany/\n");
	scanf("%9999s", expr);
	if (validate_expression(expr))
	{
		if (calculate(expr, &result)) printf("%.2f", result);
		else
		{
			printf("error");
			return 1;
		}
	}
	else
	{
		printf("error");
		return 1;
	}
	//_getch();
	return 0;
}