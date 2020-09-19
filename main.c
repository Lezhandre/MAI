//
//  main.c
//  прогание наяву
//
//  Created by Michael Duzhenko on 10/09/2020.
//  Copyright © 2020 Michael Duzhenko. All rights reserved.
//

/*\
 #include <stdio.h>

void comrade(FILE*);

int main(int argc, const char * argv[]) {
    FILE* trash = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    comrade(trash);
    return 0;
}

void comrade(FILE* file){
    if (file != NULL) {
        long long sum;
        unsigned i = 0;
        char c = 1, f;
        while (c != EOF){
            ++i;
            sum = 0;
            f = -1;
            while ((c = getc(file)) != EOF && c != '\n'){
                sum += c * f;
                f = -f;
            }
            printf("Контрольная сумма %d-ой строки: %Ld\n", i, sum);
        }
    }
    else
        printf("Файл не найден\n");
}
\*/


#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    FILE *in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "wb");
    u_char str[257];
    if (out != NULL && in != NULL) {
        while (fgets(str, 257, out) != NULL){
            unsigned char i = 0;
            int sum = 0;
            unsigned char num_of_let = 0;
            for (i; str[i] != '\n' && str[i] != '\0'; ++i){
                if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z')
                    ++num_of_let;
                sum += str[i];
            }
            short f = fwrite(&(i), sizeof(char), 1, in);
            if (f < 0) {
                printf("Произошла ошибка сувания инфы в бинарник! Остановка жеппы!");
                return 0;
            }
            f = fwrite(&(num_of_let), sizeof(char), 1, in);
            if (f < 0) {
                printf("Произошла ошибка сувания инфы в бинарник! Остановка жеппы!");
                return 0;
            }
            f = fwrite(&(sum), sizeof(int), 1, in);
            if (f < 0) {
                printf("Произошла ошибка сувания инфы в бинарник! Остановка жеппы!");
                return 0;
            }
            f = fwrite(str, i, 1, in);
            if (f < 0) {
                printf("Произошла ошибка сувания инфы в бинарник! Остановка жеппы!");
                return 0;
            }
        }
    }
    fclose(in);
    fclose(out);
    out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "rb");
    size_t n_obj;
    /*while((n_obj = fread(str, sizeof(char), 40, out)) != 0){
        for (unsigned i = 0; i < n_obj; ++i){
            if (16 > str[i])
                printf("0");
            printf("%X", str[i]);
        }
        printf("\n");
    }*/
    unsigned size;
    while((n_obj = fread(&size, sizeof(char), 1, out)) != 0){
        fread(str, size + sizeof(char) + sizeof(int), 1, out);
        for (int i = 0; i < size + sizeof(char) + sizeof(int); ++i)
            printf("%c", str[i]);
        printf("\n");
    }
    fclose(out);
    return 0;
}

