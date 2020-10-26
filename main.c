#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <errno.h>

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

/*\10-я лаба
void fill_CfW(char *);
char ICoW(unsigned char);
char fill_with_whitespaces(char *, unsigned);

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
    char str[(rec_size + 2 > 257)? rec_size + 2: 257], *p;
    size_t SoW; //size of word
    short QoW, i, CQ, ISoE; //quantity of words
    while (fgets(str, 257, in) != 0){
        //fill_with_whitespaces(str, rec_size);
        //fputs(str, out);
        p = str;
        ISoE = (str[strlen(str) - 1] == '\n');
        for (QoW = 0; (p = strpbrk(p, CfW)) != NULL; ++QoW)
            p += strspn(p, CfW);
        if (QoW < 2 && rec_size != strlen(str) - ISoE || rec_size < strlen(str) - ISoE){
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
                short QoWS = (CQ - 1 + rec_size - strlen(str) + ISoE) / (QoW - 1);
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

char ICoW(unsigned char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 192 && c <= 255) || c == '-' || (c >= '0' && c <= '9'));
}

char fill_with_whitespaces(char *str, unsigned rec_size){
    short size = strlen(str);
    short ISoE = (str[size - 1] == '\n');
    for (short i = size; i < rec_size + ISoE; ++i)
        str[i] = ' ';
    str[rec_size + ISoE] = '\0';
    char flag = 0;
    for (short i = size - 1; i >= 0; --i){
        if (ICoW(str[i]) && flag == 0)
            flag = 1;
        if (!ICoW(str[i]) && flag == 1)
            flag = 2;
        if (ICoW(str[i]) && flag == 2){
            short j = i + rec_size - size + ISoE;
            for (++i, ++j; !ICoW(str[i]); ++i, ++j) {}
            for (; str[j] != '\0'; ++i, ++j){
                char t = str[i];
                str[i] = str[j];
                str[j] = t;
            }
            return 1;
        }
    }
    return 0;
}
/*\*/

/*\11-ая лаба
void reverse(char *, short);
void change_str(char *);

int main(){
    setlocale(LC_ALL, "RUSSIAN");
    char str[257];
    FILE *in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "r");
    FILE *tmpf = tmpfile();
    while (fgets(str, 257, in) != 0){
        change_str(str);
        fputs(str, tmpf);
        if (fgets(str, 257, in) != 0)
            fputs(str, tmpf);
    }
    fclose(in);
    rewind(tmpf);
    in = fopen("/Users/michaelduzhenko/Documents/Code on XCode/прогание наяву/прогание наяву/a.txt", "w");
    while (fgets(str, 257, tmpf) != 0){
        fputs(str, in);
        if (fgets(str, 257, tmpf) != 0)
            fputs(str, in);
    }
    fclose(in);
    return 0;
}

void change_str(char *str){
    for (short i = 0; str[i] != '\0'; ++i){
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);
    }
    short i_prev = -1, j_prev = -1;
    for (short i = 0, j = strlen(str) - 1; i < j;){
        if (!isalnum(str[i]))
            ++i;
        if (!isalnum(str[j]))
            --j;
        if (isalnum(str[i]) && isalnum(str[j])) {
            reverse(&(str[i]), j - i + 1);
            i_prev = i, j_prev = j;
            for (; isalnum(str[i]); ++i);
            for (; isalnum(str[j]); --j);
            reverse(&(str[j + 1]), j_prev - j);
            if (i <= j) {
                reverse(&(str[i_prev]), i - i_prev);
                reverse(&(str[i]), j - i + 1);
            }
        }
    }
}

void reverse(char *str, short n){
    for (short i = 0, j = n - 1; i < j; ++i, --j){
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
    }
}
/*\*/

/*\12-ая лаба*/
//double fact(unsigned short); //факториал
double f(double); //функция, вычисляющая значение функции
double sum(double, unsigned); //сумма n слагаемых для x
unsigned NQoT(double, double); //функция, вычисляющая сколько нужно слагаемых

int main(){
    double e = 1e-6, x; //e - точность
    int a = 5, m = 6;
    unsigned n = 0;
    for (unsigned i = 0; i <= a * 10; ++i){
        x = (double)i / 10;
        n = (n < NQoT(x, e)) ? NQoT(x, e) : n;
    }
    for (unsigned i = 0; i <= a * 10; ++i){
        x = (double)i / 10;
        printf("%lf\t", sum(x, n));
        if ((i + 1) % ((a * 10 + m - 1) / m) == 0 || i == a * 10)
            printf("\n");
    }
    return 0;
}

double f(double x){
    double ans = sin(x) / x;
    if (ans == NAN)
        ans = 1;
    return ans;
}

/*double fact(unsigned short n){
    double ans = 1;
    for (short i = 1; i <= n; ++i)
        ans *= i;
    return ans;
}*/

double sum(double x, unsigned n){
    double ans = 0, fact = 1;
    for (unsigned i = 0; i < n; ++i, fact *= (2 * i) * (2 * i + 1)){
        ans += pow(-x*x, i) / fact;
    }
    return ans;
}

unsigned NQoT(double x, double e){
    unsigned nq = 0;
    for (double y = 0; fabs(f(x) - y) >= e; ++nq){
        y = sum(x, nq);
    }
    return nq;
}
/*\*/
