#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

/*\8-я лаба
void comrade(FILE *);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
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
            }
            printf("Контрольная сумма %d-ой строки: %lld\n", i, sum);
        }
    }
    else
        printf("Файл не открылся\n");
}
/*\*/

/*\9-я  лаба, часть 1
char txt_to_bin(FILE *, FILE *);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE *out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    FILE *in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "wb");
    if (out != NULL && in != NULL) {
        if (txt_to_bin(out, in) < 0){
            printf("Не удалось перевести текстовый файл в бинарный\n");
            return 0;
        }
    }
    else {
        printf("Один из файлов не открывается или не создаётся\n");
        return 0;
    }
    fclose(in);
    fclose(out);
    return 0;
}

char txt_to_bin(FILE *out, FILE *in) {
    u_char str[257];
    while (fgets(str, 257, out) != NULL){
        unsigned char i = 0;
        int sum = 0;
        unsigned char num_of_let = 0;
        for (i; str[i] != '\n' && str[i] != '\0'; ++i){
            if ((str[i] >= 'a' && str[i] <= 'z') || str[i] >= 'A' && str[i] <= 'Z' ||
                str[i] >= 192 && str[i] <= 255)
                ++num_of_let;
            sum += str[i];
        }
        if (fwrite(&(i), sizeof(char), 1, in) < 0)
            return -1;
        if (fwrite(&(num_of_let), sizeof(char), 1, in) < 0)
            return -1;
        if (fwrite(&(sum), sizeof(int), 1, in) < 0)
            return -1;
        if (fwrite(str, i, 1, in) < 0)
            return -1;
    }
    return 1;
}
/*\*/

/*\9-я лаба, часть 2
int main(){
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE *out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/a.bin", "rb");
    unsigned SoF = 0;
    if (out == NULL) {
        printf("Не удалось открыть файл\n");
        return 0;
    }
    size_t n_obj;
    unsigned char size, QoL;
    int sum;
    unsigned char str[257];
    for (unsigned i = 0; (n_obj = fread(&size, sizeof(char), 1, out)) != 0; ++i){
        printf("Длина %d-ой строки: %d\n", i+1, size);
        fread(&QoL, sizeof(char), 1, out);
        printf("Количество букв в строке: %d\n", QoL);
        fread(&sum, sizeof(int), 1, out);
        printf("Сумма кодов символов в строке: %d\n", sum);
        fread(str, sizeof(char), size, out);
        str[size] = '\0';
        printf("Строка:\n%s\n", str);
        SoF += (size + 2) * sizeof(char) + sizeof(int);
    }
    printf("\nРазмер файла: %u байт\n", SoF);
    fclose(out);
}
/*\*/

/*\10-я лаба*/
void fill_CfW(char *);

int main(){ //int argc, char *argv[]
    const size_t rec_size = 40;
    FILE *in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    FILE *out = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/b.txt", "w");
    if (out == NULL || in == NULL) {
        printf("Один из файлов не может быть открыт\n");
        return 0;
    }
    char CfW[130]; //chars from words
    fill_CfW(CfW);
    char str[rec_size + 1], *p;
    size_t SoW; //size of word
    short QoW, i, CQ; //quantity of words
    while (fgets(str, 257, in) != 0){
        p = str;
        for (QoW = 0; (p = strpbrk(p, CfW)) != NULL; ++QoW)
            p += strspn(p, CfW);
        if (QoW < 2 && rec_size != strlen(str)){
            printf("Во входном файле есть недопустимая строка\n");
            return 0;
        }
        p = str;
        CQ = 0;
        while (p != NULL && *p != '\0'){ //вывод слов
            if (p == strpbrk(p, CfW)){
                SoW = strspn(p, CfW);
                for (i = 0; i < SoW; ++i)
                    fputc(p[i], out);
                p += SoW;
                ++CQ;
            }
            else {
                SoW = strcspn(p, CfW); //вывод неслов
                for (i = 0; i < SoW; ++i)
                    fputc(p[i], out);
                p += SoW;
                short QoWS = (CQ - 1 + rec_size - strlen(str) + (str[strlen(str) - 1] == '\n')) / (QoW - 1);
                if (CQ != 0 && CQ != QoW) {
                    for (i = 0; i < QoWS; ++i)
                        fputc(' ', out);
                }
            }
        }
    }
    fclose(out);
    fclose(in);
    return 0;
}

void fill_CfW(char *str){
    short i = 0, c;
    for (c = 'a'; c <= 'z'; ++i, ++c)
        str[i] = c;
    for (c = 'A'; c <= 'Z'; ++i, ++c)
        str[i] = c;
    for (c = 192; c <= 255; ++i, ++c)
        str[i] = c;
    for (c = '0'; c <= '9'; ++i, ++c)
        str[i] = c;
    str[i] = '-';
    str[i + 1] = '\0';
}
/*\*/
