#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <conio.h>


int main()
{

	struct dictionary_t *d = create_dictionary(82);
	printf("%d", d);
	_getch();
	/*
	FILE *f;
	char *filename = (char*)malloc(50);
	if (filename == NULL)
	{
		printf("Failed to allocate memory");
		return 2;
	}
	printf("wpisz nazwe pliku: ");
	scanf("%49s", filename);
	f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("File not found");
		free(filename);
		return 1;
	}

	char *one_word = (char*)malloc(30);
	struct dictionary_t *d= create_dictionary(10);

	while (fscanf(f, "%29s", one_word)!=EOF)
	{
		if (!dictionary_add_word(d, one_word));
		else
		{
			free(filename);
			destroy_dictionary(&d);
			free(one_word);
			printf("error");
		}
	}

	dictionary_display(d);
	destroy_dictionary(&d);
	free(filename);
	free(one_word);
	fclose(f);
	*/
	return 0;
}