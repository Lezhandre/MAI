#include <stdio.h>
#include <locale.h>

/*\*/
void comrade(FILE*);

int main() {
    FILE* trash = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    comrade(trash);
    return 0;
}

void comrade(FILE* file){
    if (file != NULL) {
        long long sum;
        unsigned i = 0;
        int c = 1, f;
        while (c != EOF){
            ++i;
            sum = 0;
            f = -1;
            while ((c = getc(file)) != EOF && c != '\n'){
                sum += c * f;
                f = -f;
                printf("%c", c);
            }
            printf("\nКонтрольная сумма %d-ой строки: %lld\n", i, sum);
        }
    }
    else
        printf("Файл не открылся\n");
}
/*\*/

/*\
int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE *out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    FILE *in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "wb");
    u_char str[257];
    if (out != NULL && in != NULL) {
        while (fgets(str, 257, out) != NULL){
            unsigned char i = 0;
            int sum = 0;
            unsigned char num_of_let = 0;
            for (i; str[i] != '\n' && str[i] != '\0'; ++i){
                if ((str[i] >= 'a' && str[i] <= 'z') || str[i] >= 'A' && str[i] <= 'Z' ||
                    str[i] >= '\xe0' && str[i] <= '\xff' || str[i] >= '\xco' && str[i] <= '\xdf')
                    ++num_of_let;
                sum += str[i];
            }
            short f = fwrite(&(i), sizeof(char), 1, in);
            if (f < 0) {
                printf("Неправильно присунули в бинарник!");
                return 0;
            }
            f = fwrite(&(num_of_let), sizeof(char), 1, in);
            if (f < 0) {
                printf("Неправильно присунули в бинарник!");
                return 0;
            }
            f = fwrite(&(sum), sizeof(int), 1, in);
            if (f < 0) {
                printf("Неправильно присунули в бинарник!");
                return 0;
            }
            f = fwrite(str, i, 1, in);
            if (f < 0) {
                printf("Неправильно присунули в бинарник!");
                return 0;
            }
        }
    }
    fclose(in);
    fclose(out);
    out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "rb");
    size_t n_obj;
    while((n_obj = fread(str, sizeof(char), 40, out)) != 0){
    for (unsigned i = 0; i < n_obj; ++i){
        if (16 > str[i])
            printf("0");
        printf("%X", str[i]);
    }
    printf("\n");
    }
    fclose(out);
    return 0;
}
/*\*/
