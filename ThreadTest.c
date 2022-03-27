 //
 // Created by Administrator on 2022/3/8.
 //

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include "student.h"

 #define STU_SIZE 2

 int g_num = 1;
 pthread_mutex_t mutex;
 pthread_cond_t cond1,cond2;

 struct node {
 	int _data;
 	struct node* _pnext;
 };

 typedef struct sList {
 	struct node* _phead;
 } sList;

 void sListInit(sList* s) {
 	s->_phead = NULL;
 }

 struct node* wrappNode(int data) {
 	struct node* nd = malloc(sizeof(struct node));
 	nd->_data = data;
 	nd->_pnext = NULL;
 	return nd;
 }

 //与wrappNode区别
 struct node wrappNode2(int data) {
 	struct node nd;
 	nd._data = data;
 	nd._pnext = NULL;
 	return nd;
 }

 void sListPushBack(sList* s, int data) {
 	if (s==NULL) return;
 	struct node *newNode = wrappNode(data);

 	if (s->_phead==NULL) {
 		s->_phead = newNode;
 		return;
 	}

 	struct node* start = s->_phead;
 	while (start->_pnext) {
 		start = start->_pnext;
 	}
 	start->_pnext = newNode;
 }

 void sListPushBack2(sList* s, struct node* newNode) {
 	if (s == NULL) return;
 	if (s->_phead == NULL) {
 		s->_phead = newNode;
 		newNode->_pnext = NULL;
 		return;
 	}

 	struct node* start = s->_phead;
 	while (start->_pnext) {
 		start = start->_pnext;
 	}
 	start->_pnext = newNode;
 	newNode->_pnext = NULL;
 }

 //2 3
 sList initList(int *a, int size) {
 	sList* list = malloc(sizeof(sList));
 	sListInit(list);
 	for (int i = 0; i < size; i++) {
 		sListPushBack(list, *a++);
 	}
 	return *list;
 }

 void printList(sList* s) {
 	if (s->_phead == NULL) return;
 	struct node* start = s->_phead;
 	printf("链表元素如下：\n");
 	while (start) {
 		printf("%d ", start->_data);
 		start = start->_pnext;
 	}
 }

 //合并两个链表，链表都是从小到大顺排
 struct sList* mergeTwoLists(struct sList* list1, struct sList* list2) {
 	sList* s = malloc(sizeof(s));
 	sListInit(s);
 	if (list1->_phead == NULL && list2->_phead!=NULL) return list2;
 	if (list2->_phead == NULL && list1->_phead != NULL) return list1;
 	//if (list1->_phead = NULL && list2->_phead == NULL) return s;

 	struct node* s1 = list1->_phead;
 	struct node* sTmp;
 	struct node* s2 = list2->_phead;
 	while (1) {
 		if (s1->_data <= s2->_data) {
 			sTmp = s1->_pnext;
 			sListPushBack2(s, s1);
 			s1 = sTmp;
 		} else {
 			sTmp = s2->_pnext;
 			sListPushBack2(s, s2);
 			s2 = sTmp;
 		}
 		if (s1 == NULL || s2 == NULL) break;
 	}
 	struct node* ss = s1 == NULL ? s2 : s1;
 	while (ss) {
 		sListPushBack(s, ss->_data);
 		ss = ss->_pnext;
 	}

 	printf("\n");
 	printList(s);
 }

 /**
  * Note: The returned array must be malloced, assume caller calls free().
  */
 int *twoSum(int* nums, int numsSize, int target, int* returnSize) {
 	int* rs = malloc(2*sizeof(int));
 	int i = 0, flag = 0;
 	int *nums2 = nums;
 	for (i = 0; i < numsSize; nums++,i++) {
 		if (i == numsSize - 1) break;

 		int v1 = *nums;
 		int v2 = target - v1;

 		nums2 = nums;
 		++nums2;//指向后续起点元素
 		for (int j = i+1; j < numsSize; j++) {
 			if (*nums2 == v2) {
 				*rs = i;
 				*(rs+1) = j;
 				break;
 			}
 			else if (j<numsSize-1) nums2++;
 		}
 	}
 	return rs;
 }

 int charScan() {
 	char name[64];
 	//memset(name, 0, sizeof(char) * 64);
 	printf("Enter your name: ");
     scanf("qq%s", name);
 	printf("Your name is %s\n", name);
 	return 0;
 }

 //接受键盘输入学生信息，并最后循环打印
 struct student *stulistScanf() {
 	struct student* stu = malloc(STU_SIZE * sizeof(struct student));
 	/*for (int i = 0; i < STU_SIZE; i++)
 	{
 		memset(stu[i].name, 0, sizeof(stu[i].name));
 	}*/
 	//memset(stu, 0, sizeof(stu));

 	for (int i = 0; i < STU_SIZE; i++)
 	{
 		printf("请输入第%d个学生的信息:", i + 1);
 		printf("请输入姓名：");

         scanf("%s", stu[i].name);

 		printf("请输入学号：");
         scanf("%d", &stu[i].id);

 		printf("请输入分数：");
         scanf("%d", &stu[i].score);
 	}

 	for (int i = 0; i < STU_SIZE; ++i) {
 		printf("第%d个学生的信息 姓名：%s 学号：%d 分数：%d \n", (i+1), stu[i].name, stu[i].id, stu[i].score);
 	}
 	return stu;
 }

 //初始化4个学生，并循环打印出来
 void stulist() {
 	struct student stu2[STU_SIZE] = {{"Tom", 9001, 98},{"张三", 9002, 97}};
	 int i;
 	for (i = 0; i < STU_SIZE; i++) {
 		printf("第%d个学生信息:%s %d %d \n", (i+1), stu2[i].name, stu2[i].id, stu2[i].score);
 	}
 	return;
 }

 //测试指针不同写法的值
 void printPoint() {
 	int a = 100;
 	int* ap = &a;
 	printf("%p\n", &a);
 	printf("%p\n", ap);
 	printf("%p\n", &ap);
 	printf("%d\n", *ap);
 	printf("%p\n", &*ap);
 }

//  void writeFile()
//  {
//  	FILE* fp = NULL;

//  	char fname[] = "d:/tmp/whitelist.txt";

//  	fopen_s(&fp, fname, "w+");

//  	fprintf(fp, "This is testing for fprintf...\n");

//  	fputs("This is testing for fputs...\n", fp);

//  	fclose(fp);
//  }

//  void readFile()
//  {
//  	FILE* fp = NULL;
//  	char buffer[20];
//  	char fname[] = "d:/tmp/whitelist.txt";

//  	fopen_s(&fp, fname, "r");//fp指针变量的内存地址

//  	//fscanf_s(fp, "%s", buffer, 6);
//      fscanf(fp, "%s", buffer, 6);

//  	printf("1: %s\n", buffer);

//  	fclose(fp);
//  }

 void* start_routine(void* arg) {
 	char msg[32] = "";
 	snprintf(msg, sizeof(msg) - 1, "thd%d: i am thd%d\n", *((int*)arg), *((int*)arg));
 	while (1) {
 		write(1, msg, strlen(msg));
 		sleep(3);
 	}
 }

 int multiThreadPrint() {
     //启动3个子线程循环打印线程ID，注意：如果主线程结束，那么子线程也就死亡。
 	int th1 = 1;
 	pthread_t tid1;
 	pthread_create(&tid1, NULL, &start_routine, &th1);

 	int th2 = 2;
 	pthread_t tid2;
 	pthread_create(&tid2, NULL, &start_routine, &th2);

 	int th3 = 3;
 	pthread_t tid3;
 	pthread_create(&tid3, NULL, &start_routine, &th3);

 	int i=0;
 	const char* msg = "main: i am main\n";
 	while (i<10) {
 		write(1, msg, strlen(msg));
 		sleep(1);
 		i++;
 	}
 	return 0;
 }

 void* thread1(void* arg)
 {
     while(1)
     {
         pthread_mutex_lock(&mutex);
         //如果需要交替打印一定范围(例如1-10)内的数字，那么可以加上下面两行代码
         if(g_num > 100) {
             exit(1);
         }
         printf("Thread1: %d \n",g_num);
         g_num ++;
         pthread_cond_signal(&cond2);
         pthread_cond_wait(&cond1,&mutex);
         pthread_mutex_unlock(&mutex);
         //sleep(1);
     }
     return NULL;
 }

 void* thread2(void* arg)
 {
     while(1)
     {
         //这个sleep(1)加在前面是因为开启线程时有可能是线程2先打印，
         //导致变成thread2输出奇数，threa1输出偶数。为了避免这种情况，可以在延迟下线程2的打印。
         //sleep(1);//休眠1秒
         pthread_mutex_lock(&mutex);
         if(g_num > 100) {
             exit(1);
         }
         printf("Thread2: %d \n",g_num);
         g_num++;
         pthread_cond_signal(&cond1);
         pthread_cond_wait(&cond2,&mutex);
         pthread_mutex_unlock(&mutex);
     }
     return NULL;
 }

 //2、测试多线程交易打印数字 1-2-3-4-5.。。-100
 int startThreadPrint()
 {
     pthread_t p1,p2;

     pthread_mutex_init(&mutex,NULL);
     pthread_cond_init(&cond1,NULL);
     pthread_cond_init(&cond2,NULL);

     pthread_create(&p1,NULL,thread1,NULL);
     pthread_create(&p2,NULL,thread2,NULL);
     pthread_join(p1,NULL);
     pthread_join(p2,NULL);

     pthread_mutex_destroy(&mutex);
     pthread_cond_destroy(&cond1);
     pthread_cond_destroy(&cond2);

     return 0;
 }


 //交替打印foo、bar
 typedef struct {
     int n;
 } FooBar;

 int fooFlag = 1;

 FooBar* fooBarCreate(int n) {
     FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
     obj->n = n;
     return obj;
 }

 void printFoo(){
     printf("%s", "foo");
     g_num++;
     return;
 }

 void printBar(){
     printf("%s", "bar");
     return;
 }

 void* foo(void * obj1) {
	 FooBar * obj =(FooBar*)obj1;

     while(1)
     {
         // printFoo() outputs "foo". Do not change or remove this line.
         pthread_mutex_lock(&mutex);
         if(g_num > obj->n) {
             exit(1);
         }
         
		 if (fooFlag == 1){
			printFoo();
			pthread_cond_wait(&cond1, &mutex);
			fooFlag = 0;
		}

		 pthread_cond_signal(&cond2);
         pthread_mutex_unlock(&mutex);
     }
 }

 void* bar(void* obj1) {
	 FooBar * obj=(FooBar* ) obj1;
     while(1)
     {
         // printBar() outputs "bar". Do not change or remove this line.
         pthread_mutex_lock(&mutex);
         if (g_num > obj->n) {
             exit(1);
         }
         
        if (fooFlag==0){
			printBar();
			//sleep(1);  //为何添加休眠，程序执行很慢
			pthread_cond_wait(&cond2, &mutex);
			fooFlag = 1;
		}
        
		pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&mutex);
     }
 }

 int fooBarFree(FooBar* obj) {
     pthread_t p1,p2;

     pthread_mutex_init(&mutex, NULL);
     pthread_cond_init(&cond1, NULL);
     pthread_cond_init(&cond2, NULL);

     pthread_create(&p1, NULL, foo, obj);
     pthread_create(&p2, NULL, bar, obj);

     pthread_join(p1,NULL);
     pthread_join(p2,NULL);

     pthread_mutex_destroy(&mutex);
     pthread_cond_destroy(&cond1);
     pthread_cond_destroy(&cond2);

     return 0;
 }

 //TODO 3、创建子进程,父子进程协调同步： 参考 https://blog.csdn.net/weixin_39673704/article/details/110499390
 int testChildPid(){
     pid_t pid;
     printf("Before the fork(),pid=%d\n", getpid());
     pid = fork();
     printf("After the fork(),pid=%d\n", getpid());
     if (pid < 0)
         printf("error in fork!");
     else if (pid == 0)
         printf("i am the child process, my process id is %d\n", getpid());
     else printf("i am the parent process, my process id is %d\n", getpid());

	printf("pid=%d 开始休眠....\n", getpid());
	sleep(5);
	
    return 0;
 }

 int testpipe(){
     int pipefds[2];
     int returnstatus;
     char writemessages[2][20]={"Hi", "Hello"};
     char readmessage[20];
     returnstatus = pipe(pipefds);

     if (returnstatus == -1) {
         printf("Unable to create pipe\n");
         return 1;
     }

     printf("Writing to pipe - Message 1 is %s\n", writemessages[0]);
     write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
     read(pipefds[0], readmessage, sizeof(readmessage));
     printf("Reading from pipe – Message 1 is %s\n", readmessage);
     printf("Writing to pipe - Message 2 is %s\n", writemessages[0]);
     write(pipefds[1], writemessages[1], sizeof(writemessages[0]));
     read(pipefds[0], readmessage, sizeof(readmessage));
     printf("Reading from pipe – Message 2 is %s\n", readmessage);
     return 0;
 }

//字符串全部转化为大写 testa
int swichUpperCase(char str[], int len){
	int i = 0;
	char charVal;
	for (i=0; i<len&&str[i]>='a'&&str[i]<='z'; ++i){
		charVal = str[i] + 'A'-'a';
		str[i] = charVal;
		
	}
	return 1;
}

//字符转换为数字 '987'-->987，如果中途遇到非数字字符，则不继续扫描，直接返回
int srctoInt(const char str[]){
	int i, intVal, result = 0;
	for (i=0; str[i]>='0'&&str[i]<='9'; ++i){
		intVal = str[i] - '0';
		result = result*10 + intVal;
	}
	return result;
}

 int main() {
 	/*1、数组中找出两数字之和为指定数的两个数
 	**/
 	/*int array[] = {2,7,11,15};
 	int* rs = twoSum(array, 4, 9, 1);

 	printf("第1个数字：%d \n第二个数字：%d\n", *(rs++), *rs);*/

 	/*2、班级信息维护(CRUD)：
 		2.1基于数组实现(初始化、打印)
 		2.2基于链表实现(初始化、打印)
 	**/
 	//stulist();
 	//stulistScanf();

 	//charScan();


 	/*3、合并两个顺序链表：
 		3.1 初始化第一个链表
 		3.2 初始化第二个链表
 		3.3 合并两个链表
 	**/
 	/*int a1[1] = {1};
 	sList list1 = initList(a1, 1);
 	printList(&list1);

 	printf("\n");

 	int a2[3] = {2,5,6};
 	sList list2 = initList(a2, 3);
 	printList(&list2);

 	mergeTwoLists(&list1, &list2);*/

 	//writeFile();
 	//readFile();

 	//multiThreadPrint();
    //startThreadPrint();

    // FooBar fooBar = {.n = 100};
    // fooBarFree(&fooBar);

	//testChildPid();

	//字符串转大写
	// char str[]="testa";
	// int result = swichUpperCase(str, 5);
	// printf("str=%s \n", str);

	//字符转数字
	printf("%d \n", srctoInt("987"));
	printf("%d \n", srctoInt("2366677"));
	printf("%d \n", srctoInt("800a"));
	printf("%d \n", srctoInt("8c00a"));
 	return 0;
 }
