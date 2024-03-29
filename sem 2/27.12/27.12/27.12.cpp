#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "format_type.h"
//#include <conio.h>

struct statistic_t
{
	int min;
	int max;
	float avg;
	float standard_deviation;
	int range;
};

//====================================================================================================
int load(const char *filename, int ***ptr, enum save_format_t format)
{
	if (filename == NULL || ptr == NULL) return 1;

	if (format == fmt_text)
	{
		int spr = 0;
		/*for (int i = 0;*(filename+i)!='\0'; i++)
		if (*(filename + i) == '.' &&*(filename + i + 1) == 't' &&*(filename + i + 2) == 'x' &&*(filename + i + 3) == 't') spr++;
		if (spr == 0)
		return 3;*/
		FILE *f;
		f = fopen(filename, "r");
		if (f == NULL) return 2;
		int counter = 0, liczba;

		if (fscanf(f, "%d", &spr) != 1)
		{
			fclose(f);
			return 3;
		}
		fseek(f, 0, SEEK_SET);

		for (int i = 0; feof(f) == 0; i++)
		{
			liczba = 0;
			fscanf(f, "%d", &liczba);
			//printf("liczba: %d\n",liczba);
			if (liczba == -1) counter++;
		}
		//printf("counter: %d\n",counter);
		fseek(f, 0, SEEK_SET);
		*ptr = (int**)malloc(sizeof(int*) * (counter + 1));
		if (*ptr == NULL)
		{
			fclose(f);
			return 4;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				liczba = 0;
				spr = fscanf(f, "%d", &liczba);
				//printf("i: %d liczba: %d spr: %d\n", i,liczba,spr);
				if (spr != 1)
				{
					for (int j = 0; j <= i; j++)
						free(*((*ptr) + j));
					free(*ptr);
					fclose(f);
					return 3;
				}
				if (liczba == -1)
				{
					//printf("debug\n");
					*((*ptr) + i) = (int*)malloc(sizeof(int)*(j + 1));
					if (*((*ptr) + i) == NULL)
					{
						for (int j = 0; j <= i; j++)
							free(*((*ptr) + j));
						free(*ptr);
						fclose(f);
						return 4;
					}
					break;
				}
			}
		}
		//printf("counter: %d", counter);
		// koniec alokacji
		fseek(f, 0, SEEK_SET);
		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				spr = fscanf(f, "%d", &liczba);
				if (spr == 1) *(*((*ptr) + i) + j) = liczba;
				else
				{
					for (int k = 0; k < i; k++)
						free(*((*ptr) + k));
					free((*ptr));
					fclose(f);
					return 3;
				}
				//	printf("%3d ", *(*((*ptr) + i) + j));
				if (liczba == -1) break;
			}
			//printf("\n");
		}
		/*(*((*ptr) + counter)) = (int*)malloc(sizeof(int));
		if ((*((*ptr) + counter)) == NULL)
		{
		for (int i = 0; i < counter; i++)
		{
		free(*((*ptr) + i));
		free(*ptr);
		fclose(f);
		return 2;
		}
		}*/
		(*((*ptr) + counter)) = NULL;
		fclose(f);
	}
	else if (format == fmt_binary)
	{
		int spr = 0;
		/*for (int i = 0; *(filename + i) != '\0'; i++)
		if (*(filename + i) == '.' &&*(filename + i + 1) == 'b' &&*(filename + i + 2) == 'i' &&*(filename + i + 3) == 'n') spr++;
		if (spr == 0) return 3;*/

		FILE *f;
		f = fopen(filename, "rb");
		if (f == NULL) return 2;
		int counter = 0, liczba;

		if (fread(&spr, sizeof(int), 1, f) != 1)
		{
			fclose(f);
			return 3;
		}
		fseek(f, 0, SEEK_SET);
		for (int i = 0; feof(f) == 0; i++)
		{
			liczba = 0;
			fread(&liczba, sizeof(int), 1, f);
			//printf("liczba: %d\n",liczba);
			if (liczba == -1) counter++;
		}
		//printf("counter: %d\n",counter);
		fseek(f, 0, SEEK_SET);
		*ptr = (int**)malloc(sizeof(int*) * (counter + 1));
		if (*ptr == NULL)
		{
			fclose(f);
			return 4;
		}

		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				liczba = 0;
				spr = fread(&liczba, sizeof(int), 1, f);
				//printf("i: %d liczba: %d spr: %d\n", i,liczba,spr);
				if (spr != 1)
				{
					for (int j = 0; j <= i; j++)
						free(*((*ptr) + j));
					free(*ptr);
					fclose(f);
					return 3;
				}
				if (liczba == -1)
				{
					//printf("debug\n");
					*((*ptr) + i) = (int*)malloc(sizeof(int)*(j + 1));
					if (*((*ptr) + i) == NULL)
					{
						for (int j = 0; j <= i; j++)
							free(*((*ptr) + j));
						free(*ptr);
						fclose(f);
						return 4;
					}
					break;
				}
			}
		}
		//printf("counter: %d", counter);
		// koniec alokacji
		fseek(f, 0, SEEK_SET);
		for (int i = 0; i < counter; i++)
		{
			for (int j = 0;; j++)
			{
				spr = fread(&liczba, sizeof(int), 1, f);
				if (spr == 1) *(*((*ptr) + i) + j) = liczba;
				else
				{
					for (int k = 0; k < i; k++)
						free(*((*ptr) + k));
					free((*ptr));
					fclose(f);
					return 3;
				}
				//	printf("%3d ", *(*((*ptr) + i) + j));
				if (liczba == -1) break;
			}
			//printf("\n");
		}
		/*(*((*ptr) + counter)) = (int*)malloc(sizeof(int));
		if ((*((*ptr) + counter)) == NULL)
		{
		for (int i = 0; i < counter; i++)
		{
		free(*((*ptr) + i));
		free(*ptr);
		fclose(f);
		return 2;
		}
		}*/
		(*((*ptr) + counter)) = NULL;
		fclose(f);
	}
	else return 1;
	return 0;
}
//===================================================================================================
int statistics_row(int **ptr, struct statistic_t **stats)
{
	if (ptr == NULL || stats == NULL) return -1;

	int ile_wierszy = 0;
	for (int i = 0; *(ptr + i) != NULL; i++)
	{
		ile_wierszy++;
		//printf("ile wierszy: %d\n", ile_wierszy);
	}

	*stats = (struct statistic_t*)malloc(sizeof(struct statistic_t)*ile_wierszy);
	if (*stats == NULL)
		return -2;
	/*for (int i = 0; i < ile_wierszy; i++)
	{
	*(stats + i) = (struct statistic_t*)malloc(sizeof(struct statistic_t));
	if (*(stats + i) == NULL)
	{
	for (int j = i - 1; j >= 0; j--)
	free(*(stats + j));
	return -2;
	}
	}*/
	float min, max, avg, st_dev, range, sum = 0, ile = 0;

	for (int k = 0; k < ile_wierszy; k++)
	{
		min = *(*(ptr + k)), max = *(*(ptr + k)), avg = 0, st_dev = 0, range = 0, sum = 0, ile = 0;
		//	printf("k: %d\n", k);
		for (int j = 0; *(*(ptr + k) + j) != -1; j++)
		{
			sum += *(*(ptr + k) + j);
			if (*(*(ptr + k) + j) > max) max = *(*(ptr + k) + j);
			if (*(*(ptr + k) + j) < min) min = *(*(ptr + k) + j);
			//printf("%3d ", *(*(ptr + k) + j));
			ile++;
		}
		//printf("\n");
		if (ile == 0)
		{
			(*stats + k)->avg = -1;
			(*stats + k)->max = -1;
			(*stats + k)->min = -1;
			(*stats + k)->range = -1;
			(*stats + k)->standard_deviation = -1;
		}
		else
		{

			avg = sum / ile;
			sum = 0;
			range = max - min;

			for (int j = 0; *(*(ptr + k) + j) != -1; j++)
			{
				sum += (*(*(ptr + k) + j) - avg)*(*(*(ptr + k) + j) - avg);
			}

			st_dev = sqrt(sum / ile);
			(*stats + k)->avg = avg;
			(*stats + k)->max = max;
			(*stats + k)->min = min;
			(*stats + k)->range = range;
			(*stats + k)->standard_deviation = st_dev;
		}
		//printf("min:%d max:%d range:%d avg:%f st:%f\n", (*stats + k)->min, (*stats + k)->max, (*stats + k)->range, (*stats + k)->avg, (*stats + k)->standard_deviation);
	}
	return ile_wierszy;
}
//===================================================================================================
void destroy(int ***ptr)
{
	for (int i = 0; *((*ptr) + i) != NULL; i++)
	{
		if (*((*ptr) + i) != NULL) free(*((*ptr) + i));
	}
	free(*ptr);
}
//========================================================================================================
int save(const char *filename, int **ptr, enum save_format_t format)
{
	if (filename == NULL || ptr == NULL) return 1;

	if (format == fmt_text)
	{
		FILE *f;
		f = fopen(filename, "w");
		if (f == NULL) return 2;
		for (int i = 0; *(ptr + i) != NULL; i++)
		{
			for (int j = 0;; j++)
			{
				if (*(*(ptr + i) + j) == -1) fprintf(f, "%d", *(*(ptr + i) + j));
				else fprintf(f, "%d ", *(*(ptr + i) + j));
				if (*(*(ptr + i) + j) == -1) break;
			}
			fprintf(f, "\n");
		}
		fclose(f);
	}
	else if (format == fmt_binary)
	{
		FILE *f;
		f = fopen(filename, "wb");
		if (f == NULL) return 2;
		for (int i = 0; *(ptr + i) != NULL; i++)
		{
			for (int j = 0;; j++)
			{
				//printf("wielkosc inta: %lui\n", sizeof(int));
				fwrite((*(ptr + i) + j), sizeof(int), 1, f);
				if (*(*(ptr + i) + j) == -1) break;
			}
			//fprintf(f, "\n");
		}
		fclose(f);
	}
	else return 1;
	return 0;
}
//==============================================================================================================
int statistics(int **ptr, struct statistic_t **stats)
{
	if (ptr == NULL || stats == NULL) return 1;
	int counter = 0;

	for (int i = 0; *(ptr + i) != NULL; i++)
	{
		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			counter++;
		}
	}
	if (counter == 0) return 3;

	*stats = (struct statistic_t*)malloc(sizeof(struct statistic_t));
	if (*stats == NULL) return 2;
	float min = *(*(ptr)), max = *(*(ptr)), avg = 0, st_dev = 0, range = 0, sum = 0, ile = 0;

	for (int i = 0; *(ptr + i) != NULL; i++)
	{
		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			sum += *(*(ptr + i) + j);
			if (*(*(ptr + i) + j) > max) max = *(*(ptr + i) + j);
			if (*(*(ptr + i) + j) < min) min = *(*(ptr + i) + j);
			ile++;
		}
	}
	avg = sum / ile;
	sum = 0;
	range = max - min;
	for (int i = 0; *(ptr + i) != NULL; i++)
	{
		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			sum += (*(*(ptr + i) + j) - avg)*(*(*(ptr + i) + j) - avg);
		}
	}
	st_dev = sqrt(sum / ile);
	(*stats)->avg = avg;
	(*stats)->max = max;
	(*stats)->min = min;
	(*stats)->range = range;
	(*stats)->standard_deviation = st_dev;
	return 0;
}
//==============================================================================================================
void display(int **ptr)
{
	if (ptr == NULL) return;

	for (int i = 0; *(ptr + i) != NULL; i++)
	{

		for (int j = 0; *(*(ptr + i) + j) != -1; j++)
		{
			printf("%3d ", *(*(ptr + i) + j));
		}
		printf("\n");
	}
}
//================================================================================================================
int main()
/*
{
int **ptr;
load("b.bin", &ptr, fmt_binary);
display(ptr);
_getch();
return 0;

}*/
/*
struct statistic_t *stats;

int X[] = { -21, -717, -609, -569, -82, -818, -408, -1 };
int K[] = { 31, 93, 731, 155, -1 };
int G[] = { -305, -922, -1 };
int T[] = { -135, -961, -840, -1 };
int E[] = { -1 };
int U[] = { -736, -525, -1 };
int J[] = { 633, 359, 67, 258, 776, 627, 370, 600, 633, -1 };
int R[] = { 629, 467, -1 };
int Z[] = { -555, -1 };
int A[] = { -816, -754, -822, -1 };
int W[] = { 877, 363, 185, 789, 932, 55, 230, 820, -1 };
int B[] = { -525, -371, -484, -657, -512, -411, -89, -1 };
int *D[] = { X, K, G, T, E, U, J, R, Z, A, W, B, NULL };


int err_code = statistics_row(D, &stats);


_getch();
return 0;
}*/

{
	int **ptr, x, spr = 0;
	struct statistic_t *stats;
	char *filename = (char*)malloc(40);
	if (filename == NULL)
	{
		printf("Failed to allocate memory");
		return 4;
	}

	printf("podaj nazwe pliku: ");
	scanf("%39s", filename);

	for (int i = 0; *(filename + i) != '\0'; i++)
	{
		if (*(filename + i) == '.' &&*(filename + i + 1) == 't' &&*(filename + i + 2) == 'x' &&*(filename + i + 3) == 't' &&*(filename + i + 4) == '\0')
		{
			x = load(filename, &ptr, fmt_text);
			switch (x)
			{
			case 2:
				printf("Couldn't open file");
				free(filename);
				return 2;
			case 3:
				printf("File corrupted");
				free(filename);
				return 3;
			case 4:
				printf("Failed to allocate memory");
				free(filename);
				return 4;
			}
			x = statistics_row(ptr, &stats);
			if (x == -2)
			{
				printf("Failed to allocate memory");
				destroy(&ptr);
				free(filename);
				return 4;
			}

			for (int j = 0; j < x; j++)
			{
				printf("%d %d %d %f %f\n", (stats + j)->min, (stats + j)->max, (stats + j)->range, (stats + j)->avg, (stats + j)->standard_deviation);
			}
			spr++;
		}
		else if (*(filename + i) == '.' &&*(filename + i + 1) == 'b' &&*(filename + i + 2) == 'i' &&*(filename + i + 3) == 'n' &&*(filename + i + 4) == '\0')
		{
			x = load(filename, &ptr, fmt_binary);
			switch (x)
			{
			case 2:
				printf("Couldn't open file");
				free(filename);
				return 2;
			case 3:
				printf("File corrupted");
				free(filename);
				return 3;
			case 4:
				printf("Failed to allocate memory");
				free(filename);
				return 4;
			}
			x = statistics_row(ptr, &stats);
			if (x == -2)
			{
				printf("Failed to allocate memory");
				destroy(&ptr);
				free(filename);
				return 4;
			}

			for (int j = 0; j < x; j++)
			{
				printf("%d %d %d %f %f\n", (stats + j)->min, (stats + j)->max, (stats + j)->range, (stats + j)->avg, (stats + j)->standard_deviation);
			}
			spr++;
		}
	}
	if (spr == 0)
	{
		printf("Wrong filename");
		free(filename);
		return 1;
	}
	free(stats);
	destroy(&ptr);
	free(filename);
	//_getch();
	return 0;
}
/*
int main()
{
int X[] = { -1 };
int K[] = { -1 };
int G[] = { -1 };
int *T[] = { X, K, G, NULL };
save("fig.bin", T, fmt_text);

//_getch();
return 0;
}*/