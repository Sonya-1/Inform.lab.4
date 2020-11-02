#include <stdio.h>

void print_str(char* str, int len, int begin) {
	int i;
	for (i = begin; i < len; i++) {
		printf("%c", str[i]);
	}
	//printf("\n");
}


int main()
{
	char str[] = "asdf zxcvb qwerty";
	int arr[] = { 2, 1, 3 };
	int i = 0, word = 0, j, letters = 0;
	while (str[i] != '\0') {
		if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n' || str[i] == '\t') {
			word++;
			for (j = 0; j < 2; j++) {
				if (arr[j] == word) {
					print_str(str, letters, i - letters);
				}
			}
			letters = 0;
			i++;
		}
		else {
			i++;
			letters++;
		}
	}

}