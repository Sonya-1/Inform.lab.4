//Ввести строку. Вывести пословно в порядке убывания длин слов.

#include <stdio.h>
#include <stdlib.h>

int strlen(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

void my_swap(char** s1, char** s2) {
	char* tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int strcomp(char* s1, char* s2) {
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);

	if (s1_len == s2_len) {
		return 0;
	}
	if (s1_len > s2_len) {
		return 1;
	}
	return -1;
}

void copy_word(char* sub, char* str, int start, int end) {
	int j = 0, k = 0;

	for (j = start; j < end; j++) {
		sub[k] = str[j];
		k++;
	}
	sub[k] = 0;
}

void fill_subs(char *subs[], char *str, int *begin, int end, int *count) {
	int letters = end - *begin;
	char* sub_item;

	if (letters < 1) {
		*begin = end + 1;
		return;
	}

	sub_item  = (char*)malloc((letters + 1) * sizeof(*sub_item));

	if (sub_item == NULL) {
		printf("Allocation error.");
		exit(1);
	}
	copy_word(sub_item, str, *begin, end);
	subs[*count] = sub_item;

	*begin = end + 1;
	*count += 1;
}


void sort_subs(char* subs[], int count) {
	int k, fl = 0;

	while (fl == 0) {
		fl = 1;
		for (k = 0; k < count - 1; k++) {
			if (strcomp(subs[k], subs[k + 1]) < 0) {
				fl = 0;
				my_swap(&subs[k], &subs[k + 1]);
			}
		}
	}
}

int main()
{
	char* subs[1000];
	int i, letters = 0, begin = 0, count = 0;
	char str[256];

	printf("Input string: ");
	fgets(str, 256, stdin);

	for (i = 0; ; i++) {
		if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n' || str[i] == '\t') {
			fill_subs(subs, str, &begin, i, &count);
		}
		if (str[i] == '\0') {
			break;
		}
	}
	sort_subs(subs, count);

	if (count == 0) {
		printf("No words\n");
	}
	
	for (i = 0; i < count; i++) {
		if (subs[i] != 0) {
			puts(subs[i]);
			free(subs[i]);
		}
	}
	return 0;
}