#include <stdio.h>
#include <string.h>

// 自定义结构体
struct Student {
    char name[20];
    int age;
    float score;
};

// 返回结构体对象的函数
struct Student createStudent() {
    struct Student s = {"Tom", 20, 89.5};
    return s;
}

int main() {
    struct Student s = createStudent();
    printf("Name: %s, Age: %d, Score: %f\n", s.name, s.age, s.score);
    return 0;
}
