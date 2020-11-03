#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//Вводится строка и массив индексов. Затем выводятся слова согласно массиву индексов. 
//Индекс == порядковый номер слова в строке.

//заполнение массива одним значением
void init_arr(int* arr, int len, int value) {
    int i;
    for (i = 0; i < len; i++) {
        arr[i] = value;
    }
}

int strlen(char* str, int max_len) {
    int i;
    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0' || str[i] == '\n') {
            break;
        }
    }
    return i;
}

// возвращает позицию символа c в строке str
int char_index(char c, char* str) {
    int i;

    for (i = 0; str[i] > 0; i++) {
        if (c == str[i]) {
            return i;
        }

    }
    if (c == 0) {
        return i;
    }
    return -1;
}

// добавляет одно слово в массив words
// start - индекс первого символя слова
// end - индекс разделитея после в конце слова
void push(char* words[1000], char* str, int start, int end) {
    int len = end - start;
    int i, word_index;

    if (len < 1) {
        // в слове нет ни одной буквы
        return;
    }
   
    // выделение памяти под новую строку
    char * word = (char*)malloc((len + 1) * sizeof(*word));

    if (word == NULL) {
        printf("Allocation error");
        exit(1);
    }
    word[len] = 0; // конец строки

    // скопируем символы в строку word
    for (i = 0; i < len; i++) {
        word[i] = str[start + i];
    }
    // найдем наименьший свободный индекс массива words
    for (word_index = 0; word_index < 1000; word_index++) {
        if (words[word_index] == NULL) {
            break;
        }
    }
    // добавим строку в массив
    words[word_index] = word;
}

// заполняет массив words отдельными словами из str
// любой из символов строки separators рассматривется как разделитель слов
void split(char* words[1000], char* str, char* separators) {
    int i, start = 0;

    // установим все указатели в массиве words на NULL 
    //чтобы потом определить конец заполненой части массива
    for (i = 0; i < 1000; i++) {
        words[i] = NULL;
    }

    for (i = 0; ; i++) {
        if (char_index(str[i], separators) >= 0) {
            // если попался один из разделителей, вставляем слово и сдвигаем start
            push(words, str, start, i);
            start = i + 1;
        }
        // исходная строка закончилась - выход
        if (str[i] == 0) {
            break;
        }
    }
}

int main() {

    char str[256];
 
    // символы-разделители слов
    char* separators = " \t\n,.;!?/~";

    // массив содержащий отдельные слова и массив, в котором храниться слово
    char* words[1000];
    char* word;
  
    int i, n, j = 0, indexes[100], len_str;

    printf("Input string: ");
    fgets(str, 256, stdin);
    len_str = strlen(str, 256);
    if (len_str == 0) {
        printf("Empty string\n");
        return 0;
    }

    init_arr(indexes, 100, 0);

    // заполним массив словами из str
    split(words, str, separators);

    //ввод и заполнение массива индексов
    printf("Input indexes ('0' for exit): ");

    do {
        int sf_res = scanf("%i", &n);

        if (sf_res == 0) {
            char c;
            if (1 == scanf("%c", &c)) {
                printf("Ignored incorrect input \"%c\"\n", c);
                continue;
            }
        }
        indexes[j] = n;
        j++;

    } while (n != 0);

    //вывод слов согласно идексам из массива
    for (i = 0; indexes[i] > 0; i++) {
        n = indexes[i];
        word = words[n - 1];

        if (word == NULL) {
            printf("Can't found word #%i in this string\n", n);
        }
        else {
            printf("%i\t%s\n", n, words[n - 1]);
        }
    }
    return 0;
}