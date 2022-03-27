/*
//
// Created by Administrator on 2022/3/10.
//
typedef struct {
    int n;
    pthread_mutex_t lock1;
    pthread_mutex_t lock2;
} FooBar;

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;

    pthread_mutex_init(&obj->lock1, NULL);
    pthread_mutex_init(&obj->lock2, NULL);

    pthread_mutex_lock(&obj->lock2);

    return obj;
}

void foo(FooBar* obj) {

    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->lock1);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        pthread_mutex_unlock(&obj->lock2);
    }
}

void bar(FooBar* obj) {

    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->lock2);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        pthread_mutex_unlock(&obj->lock1);
    }
}

void fooBarFree(FooBar* obj) {
    free(obj);
}
*/
