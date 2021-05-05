//
///  Дуженко Михаил, М3О-219Бк-19, 10-ый вариант
//
///  Руководство по использованию программы:
//  Сначала предлагается ввести границы отрезка и шаг деления. Затем для каждой границы
//  нужно ввести граничные условия.
//
///  Вывод программы:
//  Вывод табличных значений функции осуществляется в консоли/терминале.
//  Вывод графика появляется в отдельном окне. При зажатии ЛКМ отображаются координаты
//  точки, находящейся на месте курсора.
//
//  Вводимые данные в программу для 10-ого варианта находятся в комментариях
//  под основным кодом программы
//

#include <iostream>
#include <vector>
#include <valarray>
#include <algorithm>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>

#define MSoN 20

using namespace std;

valarray<double> Runthrough(vector<valarray<double>> matrix){
    unsigned size = matrix.size();
    vector <double> p(size+1), q(size+1);
    p[0] = 0;
    q[0] = 0;
    unsigned step = 0;
    double a = 0, b, c;
    for (unsigned i = 0; i < size; ++i){
        if (i != 0)
            a = matrix[i][i-1];
        b = matrix[i][i];
        c = matrix[i][i+1];
        if (i + 1 == size)
            c = 0;
        p[i+1] = -c / (b + a * p[i]);
        q[i+1] = (matrix[i][size] - a * q[i]) / (b + a * p[i]);
    }
    valarray<double> x(size);
    x[size - 1] = q[size];
    for (unsigned i = size - 1; i > 0; --i){
        x[i - 1] = q[i] + p[i] * x[i];
    }
    return x;
}

double Lagrange(const valarray<double>& X, const valarray<double>& Y, double x) {
    double tmp, ans = 0;
    unsigned long size = X.size();
    for (unsigned i = 0; i < size; ++i) {
        tmp = Y[i];
        for (unsigned k = 0; k < size; ++k) {
            if (k == i) continue;
            tmp *= (x - X[k]) / (X[i] - X[k]);
        }
        ans += tmp;
    }
    return ans;
}

double k(double x){
    return 1;
}

double l(double x){
    return 1.5;
}

double m(double x){
    return -x;
}

double f(double x){
    return 0.5;
}

double y_max, y_min;
double a, b;
char LBP = 0;
valarray <double> X, Y;

void draw_num(double, double, double, int, int);
void CountStreak(bool, int, double&);
void DrawGraph(GLFWwindow*, int, int);
void Reshape(GLFWwindow*, int, int);
void MButtonPress(GLFWwindow*, int, int, int);
unsigned length(double);

int main(){
    double step, corr;
    int w, h;
    cout << "Enter borders of segment: ";
    cin >> a >> b;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << "Enter length of step: ";
    cin >> step;
    if (!cin || step <= 0 || fmod(b - a, step) > (b - a) * 1e-10) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl;
    
    unsigned size = (b - a) / step + 1;
    vector<valarray<double>> coef(size);
    X.resize(size);
    unsigned i = 0;
    for (; i < size; ++i)
        coef[i].resize(size + 1);
    i = 0;
    X[i] = a;
    {
        double l, m, f;
        cout << "Enter left boundary condition: ";
        cin >> l >> m >> f;
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        //y'
        coef[i][i] = -l / step;
        coef[i][i+1] = l / step;
        //y
        coef[i][i] += m;
        //free coef
        coef[i][size] = f;
    }
    coef[0][0] = 12; coef[0][1] = -10; coef[0][size] = 1;
    for (i = 1; i + 1 < size; ++i){
        X[i] = a + step * i;
        //y"
        coef[i][i-1] = k(X[i]) * pow(step, -2);
        coef[i][i] = -2 * k(X[i]) * pow(step, -2);
        coef[i][i+1] = k(X[i]) * pow(step, -2);
        //y'
        coef[i][i-1] -= l(X[i]) / (2 * step);
        coef[i][i+1] += l(X[i]) / (2 * step);
        //y
        coef[i][i] += m(X[i]);
        //free coef
        coef[i][size] = f(X[i]);
    }
    X[i] = b;
    {
        double l, m, f;
        cout << "Enter right boundary condition: ";
        cin >> l >> m >> f;
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        //y'
        coef[i][i-1] = -l / step;
        coef[i][i] = l / step;
        //y
        coef[i][i] += m;
        //free coef
        coef[i][size] = f;
    }
    cout << endl;
    
    Y = Runthrough(coef);
    for (i = 0; i < size; ++i){
        printf("y(%lg) = %lg\n", X[i], Y[i]);
    }
    y_max = Y.max();
    y_min = Y.min();
    corr = 0.1 * (y_max - y_min);
    y_max += corr; y_min -= corr;
    corr = 0.1 * (b - a);
    b += corr; a -= corr;
    
    if (glfwInit() == GLFW_FALSE) {
        cout << endl << "Something bad happened..." << endl;
        return 0;
    }
    // Создаём курсор в виде круга
    unsigned char pixels[9 * 9 * 4];
    memset(pixels, 0xff, sizeof(pixels));
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            corr = round(hypot(i - 4, j - 4));
            if (corr < 3)
                memset(pixels + (9 * i + j) * 4, 0x00, 3);
            else if (corr >= 4)
                memset(pixels + (9 * i + j) * 4 + 3, 0x00, 1);
        }
    }
    GLFWimage image;
    image.width = 9;
    image.height = 9;
    image.pixels = pixels;
    GLFWcursor* cursor = glfwCreateCursor(&image, 4, 4);
    
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(1, 1, "График функции, полученной из дифференциального уравнения y\" + 1.5y' - xy = 0.5", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        cout << endl << "Window didn't create!" << endl;
        return 0;
    }
    glfwSetCursor(window, cursor);
    glfwSetWindowSizeLimits(window, 300, 300, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(window);
    glClearColor(1, 1, 1, 0);           // Заполняем задний фон белым цветом
    glMatrixMode(GL_PROJECTION);        // Матрица проекции
    glLoadIdentity;                     // задание единичной матрицы
    gluOrtho2D(a, b, y_min, y_max);
    glMatrixMode(GL_MODELVIEW);
    glfwSetFramebufferSizeCallback(window, Reshape);
    glfwSetMouseButtonCallback(window, MButtonPress);
    glfwGetWindowSize(window, &w, &h);
    DrawGraph(window, w, h);
    glfwSwapBuffers(window);
    double xpos, ypos, realx, realy;
    char str[40];
    while (!glfwWindowShouldClose(window)) {
        if (LBP & 1) {
            glfwGetWindowSize(window, &w, &h);
            glfwGetCursorPos(window, &xpos, &ypos);
            DrawGraph(window, w, h);
            realx = xpos;
            realx = a + (b - a) * realx / w;
            realy = h - ypos;
            realy = y_min + (y_max - y_min) * realy / h;
            glColor3f(0, 0, 0);
            glPointSize(3);
            sprintf(str, "(%g, %g)", realx, realy);
            glRasterPos2f(realx + 6 * (b - a) / w, realy - 15 * (y_max - y_min) / h);
            for (unsigned k = 0; str[k] != '\0'; ++k)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[k]);
            glfwSwapBuffers(window);
            glFinish();
        } else if (LBP & 2) {
            DrawGraph(window, w, h);
            glfwSwapBuffers(window);
            LBP = 0;
        }
        glfwPollEvents();               // Получение и обработка событий
    }
    glfwTerminate();
    return 0;
}

unsigned length(double x){
    char str[20];
    sprintf(str, "%lg", x);
    return strlen(str);
}

//функция отрисовки чисел
void draw_num(double x, double i, double j, int width, int height){
    char str[15];
    if (x == -0)
        x = 0;
    sprintf(str, "%g", x);
    glRasterPos2f(i + 6 * (b - a) / width, j - 15 * (y_max - y_min) / height);
    for (unsigned k = 0; str[k] != '\0'; ++k)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[k]);
}

//функция подсчёта делений
void CountStreak(bool wh, int len, double realen, double& streak){
    char flag = 0;
    unsigned l = 1;
    streak = 1;
    while (streak * len > l * MSoN * realen){
        if (!flag) {
            streak /= 2;
            flag = 1;
        } else if (flag & 1) {
            streak *= 2;
            streak /= 5;
            flag = 2;
        } else {
            streak /= 2;
            flag = 0;
        }
        l = pow(0.6 * length(streak), wh);
    }
    if (flag)
        flag = 3 - flag;
    while (streak * len < l * MSoN * realen){
        if (!flag) {
            streak *= 2;
            flag = 1;
        } else if (flag & 1) {
            streak /= 2;
            streak *= 5;
            flag = 2;
        } else {
            streak *= 2;
            flag = 0;
        }
        l = pow(0.6 * length(streak), wh);
    }
}

//функция управлящая выводом в окно
void DrawGraph(GLFWwindow* window, int width, int height){
    double streak, x, y, corr;
    glPointSize(3);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Рисуем ось ординат
    CountStreak(1, width, b - a, streak);
    if (y_min > MSoN * (y_max - y_min) / height) {
        corr = y_min + MSoN * (y_max - y_min) / height;
    } else if (y_max < -MSoN * (y_max - y_min) / height) {
        corr = y_max - MSoN * (y_max - y_min) / height;
    } else {
        corr = 0;
    }
    // Прорисовка оси ординат
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(a, corr);
    glVertex2f(b, corr);
    glEnd();
    // Прорисовка стрелки для оси ординат
    glBegin(GL_TRIANGLES);
    glVertex2f(b - 8 * (b - a) / width, corr - 4 * (y_max - y_min) / height);
    glVertex2f(b, corr);
    glVertex2f(b - 8 * (b - a) / width, corr + 4 * (y_max - y_min) / height);
    glEnd();
    // Прорисовка делений на оси ординат
    glBegin(GL_POINTS);
    glColor3f(0.1, 0.1, 0.1);
    for (x = floor((b - (b - a) * length(streak) * 0.6 * MSoN / width) / streak) * streak; x >= a; x -= streak){
        glVertex2d(x, corr);
    }
    glEnd();
    // Прорисовка чисел для делений
    glColor3f(0.9, 0.5, 0);
    for (x = floor((b - (b - a) * length(streak) * 0.6 * MSoN / width) / streak) * streak; x >= a; x -= streak){
        x = round(x / streak) * streak;
        draw_num(x, x, corr, width, height);
    }
    
    // Рисуем ось абсцисс
    CountStreak(0, height, y_max - y_min, streak);
    if (a > MSoN * (b - a) / width) {
        corr = a + MSoN * (b - a) / width;
    } else if (b < -length(streak) * MSoN * (b - a) / width) {
        corr = b - length(streak) * MSoN * (b - a) / width;
    } else {
        corr = 0;
    }
    // Прорисовка оси абсцисс
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2d(corr, y_min);
    glVertex2d(corr, y_max);
    glEnd();
    glBegin(GL_TRIANGLES); //прорисовка стрелки для оси абсцисс
    glVertex2f(corr - 4 * (b - a) / width, y_max - 8 * (y_max - y_min) / height);
    glVertex2f(corr, y_max);
    glVertex2f(corr + 4 * (b - a) / width, y_max - 8 * (y_max - y_min) / height);
    glEnd();
    // Прорисовка делений на оси абсцисс
    glBegin(GL_POINTS);
    glColor3f(0.1, 0.1, 0.1);
    for (y = ceil((y_min + (y_max - y_min) * MSoN / height) / streak) * streak; y <= y_max; y += streak){
        glVertex2d(corr, y);
    }
    glEnd();
    // Прорисовка чисел для делений
    glColor3f(0.9, 0.5, 0);
    for (y = ceil((y_min + (y_max - y_min) * MSoN / height) / streak) * streak; y <= y_max; y += streak){
        y = round(y / streak) * streak;
        draw_num(y, corr, y, width, height);
    }
    
    // Рисуем график функции
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    for (unsigned i = 0; i <= width; ++i){
        x = a + (b - a) * i / width;
        y = Lagrange(X, Y, x);
        glVertex2d(x, y);
    }
    glEnd();
    // Рисуем точки, по которым строили график
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0, 0.9, 0);
    for (unsigned i = 0; i < X.size(); ++i){
        glVertex2d(X[i], Y[i]);
    }
    glEnd();
    glFinish();
}

void Reshape(GLFWwindow* window, int w, int h){
    glfwMakeContextCurrent(window);
    glViewport(0, 0, w, h);    // Устанавливаем размеры области отображения
    DrawGraph(window, w, h);
    glfwSwapBuffers(window);
}

//обработка нажатия или спуска ЛКМ
void MButtonPress(GLFWwindow* window, int button, int action, int mod){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        LBP = 1;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        LBP = 2;
    }
}

/*\
 Границы отрезка: 1.3 1.6
 Шаг: 0.1
 Условие для левой границы (2y' - y = 1): 2 -1 1
 Условие для правой границы (y = 3): 0 1 3
\*/
