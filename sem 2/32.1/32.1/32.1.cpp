#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include <conio.h>

int main()
{
	int x;
	struct linked_list_t *ll;
	ll = ll_create();
	x=ll_push_back(ll, 2);
	x=ll_push_front(ll, 3);
	ll_display(ll);

	_getch();
	return 0;
}