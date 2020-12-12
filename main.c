/*\8-я лаба
#include <stdio.h>
#include <locale.h>
#include <string.h>

void comrade(FILE *);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE* trash = fopen("a.txt", "r");
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
#include <stdio.h>
#include <locale.h>

char txt_to_bin(FILE *, FILE *);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE *out = fopen("a.txt", "r");
    FILE *in = fopen("a.bin", "wb");
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
#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Russian_Russia.1251");
    FILE *out = fopen("a.bin", "rb");
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
#include <stdio.h>
#include <locale.h>

void fill_CfW(char *);
char ICoW(unsigned char);
char fill_with_whitespaces(char *, unsigned);

int main(){
    setlocale(LC_ALL, "Russian_Russia.1251");
    const size_t rec_size = 60;
    FILE *in = fopen("a.txt", "r");
    FILE *out = fopen("b.txt", "w");
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
#include <stdio.h>
#include <locale.h>

void reverse(char *, short);
void change_str(char *);

int main(){
    setlocale(LC_ALL, "RUSSIAN");
    char str[257];
    FILE *in = fopen("a.txt", "r");
    FILE *tmpf = tmpfile();
    while (fgets(str, 257, in) != 0){
        change_str(str);
        fputs(str, tmpf);
        if (fgets(str, 257, in) != 0)
            fputs(str, tmpf);
    }
    fclose(in);
    rewind(tmpf);
    in = fopen("a.txt", "w");
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

/*\12-ая лаба
#include <stdio.h>
#include <math.h>
//double fact(unsigned short); //факториал
double f(double); //функция, вычисляющая значение функции
double sum(double, unsigned); //сумма n слагаемых для x
unsigned NQoT(double, double); //функция, вычисляющая сколько нужно слагаемых

int main(){
    double e = 1e-6, x; //e - точность
    int a = 5, m = 6;
    unsigned n = (NQoT(10, e) > NQoT(15, e))? NQoT(10, e) : NQoT(15, e);
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

/*\13 лаба, 1 часть
#include <stdio.h>
#include <math.h>

double f(double);
double find_root(double, double, double);

int main(){
    double eps = 0.001;
    double a = 1.7, b = 2.7;
    double ans = find_root(a, b, eps);
    printf("Root is %lf\n", ans);
    return 0;
}

double f(double x){
    return x*x - 1.3*log(x+0.5) - 2.8*x + 2.35;
}

double find_root(double a, double b, double eps){
    double x = a;
    if (f(a) * f(b) > 0)
        return NAN;
    while (fabs(b - a) >= eps && fabs(f(x)) > eps){
        x = (a*f(b) - b*f(a)) / (f(b) - f(a));
        if (f(b) * f(x) < 0)
            a = x;
        else
            b = x;
    }
    return x;
}
/*\*/

/*\13 лаба, часть 2
#include <stdio.h>
#include <math.h>

double f(double);
double integral(double, double, double);

const int kek = 160;

int main(){
    double eps = 0.0005;
    double a = 0, b = 5, ans;
    ans = integral(a, b, eps);
    printf("Integral is %lf\n", ans);
    return 0;
}

double f(double x){
    return exp(x) * sin(x)*sin(x);
}

double integral(double a, double b, double eps){
    double square = f((a + b) / 2) * (b - a), prev_sq = 0;
    for (unsigned n = 10; n <= kek; n += 5){ //fabs(square - prev_sq) > eps
        prev_sq = square;
        square = 0;
        for (unsigned i = 0; i < n; ++i)
            square += f(a + (b-a)/n * (2*i+1)/2) * (b-a)/n;
    }
    return square;
}
/*\*/

/*\14-ая лаба
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

double f(double);
double min_on(double, double);
double max_on(double, double);
void output_gist(double, double, double, double);

int width = 800, height = 733;
double a, b, y_min, y_max;

void draw_num(double, double, double);
void display(void);
void reshape(int, int);

int main(int argc, char *argv[]){
    a = -3, b = 2.5; //можно ли избавиться от глобальных переменных?
    y_min = -pow(16, 1/3.);
    y_max = pow(16, 1/3.);
    output_gist(a, b, y_min, y_max);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //Два буфера и картинка определяется палитрой RGB
    glutInitWindowSize(width, height); //инициализация окна с размерами width x height
    glutCreateWindow("График функции y = (x+2)^(2/3) - (x-2)^(2/3)"); //Название окна
    
    glutDisplayFunc(display); //функция, отвечающая за отрисовку
    glutReshapeFunc(reshape);
    glPointSize(3);
    glClearColor(1, 1, 1, 0); //Заполняем задний фон белым цветом
    
    glutMainLoop(); //цикл состоящий из функций
    return 0;
}

void output_gist(double a, double b, double y_min, double y_max){
    FILE* out = fopen("Гистограмма.txt", "w");
    if (out == NULL) {
        printf("Файл для вывода гистограммы не может быть создан!\n");
        exit(0);
    }
    fprintf(out, "Гистограмма y = (x+2)^(2/3) - (x-2)^(2/3):\n\n");
    unsigned i = 0;
    for (double x = a, y = y_max; x <= b; ++i, x = a + i/4.0){
        for (int i = -25; i <= 25; ++i){
            if (i * f(x) > 0 && fabs(f(x)) * 25 / y > abs(i))
                fputc('#', out);
            else if (i == 0)
                fputc('|', out);
            else
                fputc(' ', out);
        }
        if (2 * x == floor(2 * x))
            fprintf(out, " %g", x);
        fputc('\n', out);
    }
    fclose(out);
}

void draw_num(double x, double i, double j){
    char str[10];
    if (x == -0)
        x = 0;
    sprintf(str, "%g", x);
    glColor3f(1, 0.5, 0);
    glRasterPos2f(i + 8. / width, j - 20. / height);
    for (unsigned k = 0; str[k] != '\0'; ++k)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[k]);
    //glFinish();
}

// эта функция управляет всем выводом на экран
void display(void){
    //Рисуем ось ординат
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES); //прорисовка оси ординат
    glColor3f(0, 0, 0);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glEnd();
    glBegin(GL_TRIANGLES); //прорисовка стрелки для оси ординат
    glVertex2f(1 - 12. / width, -6. / height);
    glVertex2f(1, 0);
    glVertex2f(1 - 12. / width, 6. / height);
    glEnd();
    glBegin(GL_POINTS); //прорисовка делений на оси ординат
    double i;
    for (int x = a; x <= b; ++x){
        i = 2 * (x - a) / (b - a) - 1;
        glColor3f(0, 0, 0);
        glVertex2d(i, 0);
    }
    glEnd();
    //прорисовка чиселок для делений
    for (int x = a; x <= b; ++x){
        i = 2 * (x - a) / (b - a) - 1;
        draw_num(x, i, 0);
    }
    
    //Рисуем ось абсцисс
    glBegin(GL_LINES);  //прорисовка оси абсцисс
    glColor3f(0, 0, 0);
    glVertex2f(-(b + a) / (b - a), -1);
    glVertex2f(-(b + a) / (b - a), 1);
    glEnd();
    glBegin(GL_TRIANGLES); //прорисовка стрелки для оси абсцисс
    glVertex2f(-(b + a) / (b - a) - 6. / width, 1 - 12. / height);
    glVertex2f(-(b + a) / (b - a), 1);
    glVertex2f(-(b + a) / (b - a) + 6. / width, 1 - 12. / height);
    glEnd();
    glBegin(GL_POINTS); //прорисовка делений на оси абсцисс
    double j;
    for (int y = ceil(y_min); y <= y_max; ++y){
        j = 2 * y / (b - a);
        glColor3f(0, 0, 0);
        glVertex2d(-(b + a) / (b - a), j);
    }
    glEnd();
    //прорисовка чиселок для делений
    for (int y = ceil(y_min); y <= y_max; ++y){
        j = 2 * y / (b - a);
        draw_num(y, -(b + a) / (b - a), j);
    }
    //Рисуем график функции
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    double x;
    for (unsigned i = 0; i <= 1e4; ++i){
        x = (b - a) * i / 1e4 + a;
        j = 2 * f(x) / (y_max - y_min);
        glVertex2d((2 * i - 1e4) / 1e4, j);
    }
    glEnd();
    
    // Меняем буферы
    glutSwapBuffers();
}

void reshape(int w, int h){
    width = w;
    height = h;
    
    //Устанавливаем размеры области отображения
    glViewport(0, 0, width, height);
}

double f(double x){
    return pow(pow(x+2, 2), 1.0/3) - pow(pow(x-2, 2), 1.0/3);
}
/*\*/
