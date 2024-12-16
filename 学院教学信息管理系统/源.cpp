#define _CRT_SECURE_NO_WARNINGS 1
/*预处理部分*/
#include<stdio.h>	/*标准输入输出函数库文件*/	
#include<stdlib.h>	/*标准函数库文件*/
#include<string.h>	/*字符串函数库文件*/
//更改项目名称测试
/*宏代换部分*/
#define HEADER1 "   |----------------------------------------------老师，您辛苦了-----------------------------------------------------|\n"//1
#define HEADER2 "   |职工号     |姓名           |职称           |性别|课程1          |课程2          |课程3          |教学效果综合评分|\n"//2
#define HEADER3 "   |-----------|---------------|---------------|----|---------------|---------------|---------------|----------------|\n"//3
#define FORMAT  "   |%-11s|%-15s|%-15s|%-4s|%-15s|%-15s|%-15s|%16.2f|\n"//4.1
#define DATA p->data.num, p->data.name, p->data.title , p->data.sex , p->data.lesson[0] , p->data.lesson[1] , p->data.lesson[2] , p->data.score//4.2
#define END     "   |---------------------------------“桃李不言，下自成蹊；春风化雨，诲人不倦”----------------------------------------|\n"//5

/*数据结构设计部分*/
/*教师信息结构体类型*/
struct teacher {
	char num[10];//教师职工号
	char name[15];//教师姓名
	char title[15];//教师职称
	char sex[3];//性别
	char lesson[3][15];//3门课程
	double score;//教学效果综合评分
};
/*链表结点结构体类型*/
typedef struct node {
	struct teacher data;//数据域
	struct node* next;//指针域
}Node, * Link;//结构体变量、结构体变量指针

/*函数声明部分*/
	/*一级功能*/
Link ReadFile();//零、文件读取
void Menu(Link l);//一、菜单选择
void Add(Link l);//二、添加----------------按钮1
void Disp(Link l);//三、显示---------------按钮2
int Qur(Link l);//四、查询----------------按钮3
void Sort(Link l);//五、排序---------------按钮4
void Modify(Link l);//六、检查并修改-------按钮5
void Del(Link l);//七、删除----------------按钮6
void Quit(Link l);//八、退出和选择性保存---按钮0
	/*子功能*/
void Save(Link l);//1.存档-----------------按钮7
void stringinput(char* t, int lens, const char* notice);//2.字符串校验输入
double numberinput(const char* notice);//3.数值校验输入
Node** Locate(Link l, char findmess[], const int select);//4.定位
	/*封装输出功能*/
void menu();//1.打印菜单，用户界面
void printheader();//1.打印表头
void printdata(Node* pp);//2.打印数据
void Wrong();//3.错误提示
void Nofind();//4.未匹配提示

/*全局变量部分*/
int saveflag = 0;/*保存到硬盘的标志*/

/*函数定义部分*/
/*主函数*/
int main()
{
	Link l;//链表指针，接收读取的数据
/*一、读取文件信息*/
	l = ReadFile();
/*二、进入菜单界面*/
	Menu(l);
	return 0;
}

/*一级功能*/
/*零、文件读取函数*/
Link ReadFile() {
	Link l;//定义链表，l是头指针，该节点的数据域不存储数据
	//仅作牵头作用，可以省去创建链表循环内的表头判断，对排序也有帮助
	FILE* fp;//定义文件指针
	int count = 0;//保存文件中的记录条数（结点个数）
	Node* p, * r;//p是new指针，r是尾指针

	/*创建单链表的头结点*/
	l = (Node*)malloc(sizeof(Node));//申请内存（1），同时将头指针定在头结点（3）；
	if (!l) {
		printf("\n 申请空间失败！ "); return 0;
	}/*常规检查*/
	l->next = NULL;//头结点指针域初始化（2）
	r = l;//放好尾指针（4）

	/*读取文件数据，创建并复制单链表*/
	fp = fopen("teacher", "ab+");//打开文件：可读写、不清空、不存在会新建
	if (fp == NULL) {
		printf("\n=====>打开失败！\n"); exit(0);/*终止可执行程序*/
	}/*常规检查*/
	printf("奋力读取文件中，请稍后...\n");//交互提示
	while (!feof(fp)) {//文件结束时退出循环
		p = (Node*)malloc(sizeof(Node));//逐个创建结点，接受文件数据（1）
		if (!p) {
			printf("空间申请失败！"); exit(0);/*终止可执行程序*/
		}/*常规检查*/
		/*读取文件，为结点数据域赋值*/
		if (fread(p, sizeof(Node), 1, fp) == 1) {
			p->next = NULL;//指针域赋值（2），文件中的指针域失效了
			r->next = p;//连接到上一结点（3）
			r = p;		//尾结点后移到新结点（4）
			count++;	//记录结点个数
		}
	}
	fclose(fp); //关闭文件
	printf("=====>打开文件成功！共读取到 %d 条记录\n\n\n\n=====>登录我的账号：\n", count);
	system("pause");
	return l;
}

/*一、菜单选择函数*/
void Menu(Link l) {
	int select;			//保存用户输入的选择（0-9）

	while (1)//可以不断地返回菜单
	{
		system("cls");//清屏
		menu();//菜单界面打印
		/*功能选择*/
		printf("\n请选择你想要的功能【0-9】：");
		scanf("%d", &select);

		switch (select)
		{
		case 0:Quit(l); return;//0.返回main函数，由main函数结束程序
		case 1:Add(l); break;//1.添加记录
		case 2:system("cls"); Disp(l); break;//2.显示记录
		case 3:Qur(l);  break;//3.查询信息
		case 4:Sort(l); break;//4.排序记录
		case 5:Modify(l); break;//5.修改信息
		case 6:Del(l); break;//6.删除信息
		case 7:Save(l); getchar();break;//7.立即保存，保存前做判定
		default:Wrong(); getchar();break;//如果错误输入
		}
	}//菜单while(l)的结尾，返回main函数，由main函数结束程序
}

/*二、显示函数*/
void Disp(Link l) {
	Node* p;//函数内部指针
	p = l->next;//链表次头结点才开始有数据
	if (!p) {
		printf("\n=====>当前文件暂无教师记录\n");
		system("pause");
		getchar();
		return;//退出此函数，返回主调函数
	}
	//printf("\n\n");//显示界面可修改=>
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          全部记录          *\n");
	printf("\t\t\t\t\t   ******************************\n");
	//printheader();//界面表格
	printf(HEADER1);//1
	printf(HEADER2);//2
	while (p) {//逐条输出到屏幕
		//printf(HEADER3);//3,没有更美观
		printdata(p);//4
		p = p->next;
	}
	printf(END);
	system("pause");
	getchar();//?会怎样
}

/*三、添加函数*/
void Add(Link l) {
	Node* p, * r, * s;//p（新结点指针），r（尾指针）用于创建链表；s（检查指针）用于遍历检查职工号
	char ch, flag = 0, num[10]; //flag：职工号重复标志，num：职工号，ch：保存用户选择

	r = l;//尾指针，指向表头
	s = l->next;//检查指针，从实际数据开始，一开始指向NULL

	system("cls");
	/*添加页面*/
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          添加记录          *\n");
	printf("\t\t\t\t\t   ******************************\n");
	/*链表有数据则打印原有信息*/
	if (l->next) {
		Disp(l);
		printf("\n以上是系统原有信息.\n");
	}

	/*输入部分开始*/
	/*将尾指针定位到表尾，追加或新建记录*/
	while (r->next != NULL)
		r = r->next;
	while (1) //可以循环输入多条记录，直到用户向num输入0时返回主菜单，或重复时选择退回主菜单
	{
		/*输入和确认*/
		while (1)//每条添加确认操作
		{
			/*退出操作和职工号查重*/
			while (1) //不为0、不重复才可输入信息，否则一直输入或返回主菜单
			{				
				stringinput(num, 10, "请输入职工号【按0返回主菜单】：");//字符串校验输入
				
				/*退出操作*/
				if (strcmp(num, "0") == 0)
					return;//按0退回主菜单

				/*职工号查重*/
				s = l->next;//每次查重，重置检查指针，到表头
				flag = 0;//同时，重置重复flag=0
				while (s) {
					if (strcmp(s->data.num, num) == 0) {flag = 1;break;}//发现重复，标记
					s = s->next;//指针后移，遍历从头到尾
				}

				if (flag == 1){//职工号重复
					getchar();
					printf("=====>此职工号 %s 已存在，是否重新输入？【y/n】：\n", num);
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')continue;
					else return;//返回主菜单
				}
				else break;//不退出，没重复，通过检查
			}//职工号检查完毕

			/*建立链表（4步）*/
			/*逐个创建结点（1）*/
			p = (Node*)malloc(sizeof(Node));
			if (!p) {
				printf("空间申请失败！");
				return;//返回主菜单
			}
			/*给结点录入信息（2）*/
			strcpy(p->data.num, num);
			stringinput(p->data.name, 15, "姓名：");
			stringinput(p->data.title, 15, "职称：");
			stringinput(p->data.sex, 2, "性别：");
			stringinput(p->data.lesson[0], 15, "课程1：");
			stringinput(p->data.lesson[1], 15, "课程2：");
			stringinput(p->data.lesson[2], 15, "课程3：");
			p->data.score = numberinput("教学效果综合评分：");//数据域赋值
			p->next = NULL;//指针域赋值
			/*4步中间加个判断：确认是否重输*/
			int select;
			printf("=====>按【0】重输，按【1】继续\n");
			scanf("%d", &select);
			if (select == 0) {
				free(p);continue;//清空本次数据，释放不要的内存
			}
			r->next = p;//接入上一个结点；r->next始终为空；r最开始为传入链表的尾结点或表头，l头结点不存信息（3）
			r = p;//尾指针指向新节点（4）
			/*已修改标记*/
			saveflag = 1;//全局变量
		}
	}//输入部分结束；输入0时结束此函数，返回主菜单
}

/*四、查询函数*/
int Qur(Link l) {
	int select;//方式选择：1-按职工号，2-按姓名，3-按课程名，其他：退出函数，返回主菜单
	int count = 0;//记录个数
	char searchinput[20];//保存用户查询内容
	Node** p;//接收目标记录的定位，这里需要调用Locate函数，是其子功能,但对于课程会有重复的现象，
	//所以用到了指针数组,定义一个二级指针来接受多个结点的地址
	/*检查有无文件*/
	if (!l->next)//若链表为空，l是头指针
	{
		system("cls");
		printf("=====>当前文件无教师记录\n");
		getchar();//暂停，滞留
		system("pause");
		return count;//退出函数，返回主菜单
	}
	/*进入查询界面*/
	while (1)
	{
		/*查询界面设计*/
		system("cls");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\t\t\t\t\t   *          查询信息          *\n");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\n=====>1：按职工号搜索		=====>2：按姓名搜索		=====>3：按课程名搜索\n");
		printf("请选择你的搜索方式：");//这里必须严格输入整数，否则会出现bug
		scanf("%d", &select);

		if (select == 1)//按职工号,唯一
		{
			stringinput(searchinput, 10, "请输入要查询的教师职工号:");
			p = Locate(l, searchinput, 1);//找到职工号为searchinput的结点，返回其地址

			if (p[0])//p[0]就是符合的结点地址
			{
				count++;
				printheader();//界面表格123
				printdata(p[0]);//4
				printf(END);//5
				getchar();
				system("pause");
			}
			else//如果p[0]=NULL,没有匹配的
			{
				Nofind();
				system("pause");
				getchar();
			}
		}//查询完毕

		else if (select == 2)//按姓名，唯一
		{
			stringinput(searchinput, 15, "请输入要查询的教师姓名：");
			p = Locate(l, searchinput, 2);//找到姓名为searchinput的结点，返回其地址
			if (p[0])//如果不为NULL
			{
				count++;
				printheader();//界面表格123
				printdata(p[0]);//4
				printf(END);//5
				printf("按任意键退出...");
				getchar();
			}
			else//如果NULL
			{
				Nofind();
				system("pause");
				getchar();
			}
		}//查询完毕

		else if (select == 3)//按课程名,但是不唯一
		{
			int flag = 0;//判断是否找到
			int count = 0;//记录个数
			stringinput(searchinput, 15, "请输入要查询的课程名：");
			p = Locate(l, searchinput, 3);//找到姓名为searchinput的结点，返回其地址
			printf(HEADER1);//表头1
			printf(HEADER2);//表头2
			for (int i = 0; p[i] != NULL; i++)//遍历输出所有符合结点
			{
				getchar();//按一次打印一个
				if (p[i])//如果不为NULL
				{
					flag = 1;//存在匹配的
					count++;//计数器
					printf(HEADER3);//表头3
					printdata(p[i]);//表身4
				}
			}
			printf(END);//表尾5
			printf("=====>共为您找到 %d 位亲爱的教师.\n", count);//表格统计
			system("pause");
			//如果p=NULL
			if (flag != 1) {//不存在匹配的
				Nofind();
				system("pause");
				getchar();
			}
		}//查询完毕

		else//其他选择
		{
			Wrong();//错误输入；	//日志：此处待改进，可以改成，输入错误，是否重新输入或退出->已改进
			system("pause");
			getchar();				//日志：getchar();还蛮重要的
		}//提示完毕

		int ch;//退出选择器
		printf("\n=====>【1】继续查询    【2】退出查询\n");
		scanf("%d", &ch);
		if (ch == 1)
		{
			getchar(); continue;//第二次循环直接结束？可能是char型输入被缓冲区的\n填掉了,=>改成了整型
		}
		else
			break;//结束循环
	}
	return count;//如果不在继续查询，就返回查找到的总个数
}

/*五、排序函数*/
void Sort(Link l) {
	/*用建立新链表的方式来使数据有序，而不是在原来链表上改动其连接顺序*/
	int select;//选择排序依据；1：按评分，!1：按职工号
	printf("\n=====>您想要按何种方式排序？=====>1：按评分	!1：按职工号\n");
	scanf("%d", &select);

	Link ll;//新链表表头
	Node* p, * rr, * s;//rr：新链表尾指针；s：新旧链表的数据传递游离结点；p：原链表的移动指针

	/*判断原链表空表*/
	if (l->next == NULL)//没有连接任何数据结点，为空链表
	{
		system("cls");
		printf("\n\n=====>当前文件中暂无教师信息：一大波老师正在路上~\n");
		getchar();
		system("pause");
		return;//返回主菜单
	}

	/*一、建立一个新链表表头*/
	ll = (Node*)malloc(sizeof(Node));//申请内存(1)，将表头定位（3）
	/*申请检查*/
	if (!ll) {
		printf("\n 申请空间失败！ ");
		return;//返回主菜单
	}
	ll->next = NULL;//指针域赋空，数据域不用(2)

	system("cls");
	printf("排序前：\n");
	Disp(l);//显示排序前数据

	/*二、延长该新链表，数据有序连接*/
	p = l->next;//定好原链表次头结点
	while (p)//遍历原链表所有实际结点
	{
		/*2.1		申请s新内存*/
		s = (Node*)malloc(sizeof(Node));//数据传递游离结点，相当于新链表的new结点或p结点
		/*申请检查*/
		if (!s) {
			printf("\n 申请空间失败！ ");
			return;//返回主菜单
		}

		/*2.2		填充s新结点*/
		/*依次复制原链表每个结点的内容*/
		s->data = p->data;//复制原链表数据域
		s->next = NULL;//指针域赋空

		/*2.3		连接（插入）s新结点*/
		/*插入排序法对链表有序连接的改动就在下面：*/
		/*插入点不是原来的表尾了，原来建立单链表时，尾指针在每添加一个节点后，都要重新定在表尾；
		现在需要将链表有序连接，尾指针就不是每次都定在表尾了，而是第一个 相关数据比它小或大的 结点前面*/

		/*2.3.1寻找插入位置*/
		/*下面是寻找插入位置的功能*/
		rr = ll;//循环前先重定位（很多这样的操作，比如：flag=0;、sum=0;等等

		/*如果是简单的建表，这里是指放好新链表的尾指针，用于连接s新结点，延长新链表ll（4）；
		但在这里是指：对rr的重定位，每次都要从表头开始找，确保下面的循环能遍历新链表所有结点
		每插入一个，就要遍历所有之前的结点，找到插入位置*/
		if (select == 1) {
			while (rr->next != NULL && rr->next->data.score >= p->data.score) {//降序排列
				rr = rr->next;//这里相对于简单的建表，这一句需要视情况循环若干次（对比学习）
			}//定位完毕
		}
		else {
			while (rr->next != NULL && strcmp(rr->next->data.num, p->data.num) < 0) {//升序排列
				rr = rr->next;//这里相对于简单的建表，这一句需要视情况循环若干次（对比学习）
			}//定位完毕
		}

		/*2.3.2插入*/
		if (rr->next == NULL)//说明新链表中的所有数据都比待插入的结点大，或者新链表为空，因为是降序排列，将待插入的p，即s，插入到表尾；表尾rr：“到后面去吧你~”
			rr->next = s;//rr保存着上一结点的地址，s保存着当前待插入的结点位置
		else//rr后面的结点出现比p小的情况，取第一个，将p插入到这个结点的前面：表中rr：“欸，大哥，你在我前面，嘿嘿！”
		{
			s->next = rr->next;//先要保存下来rr的后一个地址，
			rr->next = s;//而不是用自己的地址直接就覆盖rr的指针域，否则原来后一个（一系列）的结点将丢失，并且无法找回
			/*就相当于，一个结点的指针域一次只能放一个指针，只能放一根绳子，要放新的绳子，必须先将原来的绳子放在一个可以取到的地方，否则，被覆盖将消失*/
		}
		/*2.4依次插入*/
		p = p->next;//继续将原链表l的下一个结点插入到新链表ll中
	}//新的有序链表建立完成!
	/*三、重连接*/
	l->next = ll->next;

	/*排序结果*/
	printf("排序后：\n");
	Disp(l);//显示排序后表格
	saveflag = 1;//保存标记
	printf("\n=====>排序完成！\n");
	getchar();
	system("pause");
	return;
}

/*六、检查并修改函数*/
void Modify(Link l) {
	Node* *p;//存放教师记录结点，但只用p[0]
	char id[20];//存放职工号，修改以职工号为索引,因为职工号唯一，按其他的索引不唯一，如此修改存在管理问题
	int select1;//是否修改信息
	if (!l->next) {
		printf("\n=====>当前文件暂无教师记录\n");
		system("pause");
		getchar();
		return;//退出此函数，返回主调函数
	}

	system("cls");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          更改信息          *\n");
	printf("\t\t\t\t\t   ******************************\n");
	Disp(l);
	printf("=====>以上是原有教师信息.\n");

	printf("=====>【1】精确查询 【2】继续\n");
	int select4;//是否需要精确查询
	scanf("%d",&select4);
	//getchar();//是否需要吸收\n?
	if (select4 == 1)
		Qur(l);//先让用户查看要修改教师的相关信息，确认是否修改
	/*提示是否修改*/
	printf("请您核查，是否修改？【1】信息有误，我需要修改    【2】核查正确，返回主菜单\n");
	scanf("%d", &select1);
	if (select1 != 1)
		return;//返回菜单，这里可以在建一个更改页面，就不必返回菜单

	/*开始修改*/
	while (1)//多条修改
	{
		/*开始修改，一次只能修改一条*/
		stringinput(id, 10, "请输入您要修改教师的职工号：");
		/*找出修改对象，唯一*/
		p = Locate(l, id, 1);//注意：这里返回的是指针数组,但是是按职工号查找，返回的数组只存了一个p[0]
		/*判断是否存在该教师*/
		if (p[0])
		{
			/*用户修改并确认*/
			while (1) 
			{
				int select2;//选择修改内容
				//printf("=====>需要修改教师的职工号：%s\n", p[0]->data.num);
				printf("=====>您需要修改该名教师的？\n"
					"\t\t\t\t\   【   1：姓名     2：职称     3：性别    】\n"
					"\t\t\t\t\   【   4：课程1    5：课程2    6：课程3   】\n"
					"\t\t\t\t\   【   7: 仅三名课程  8：教学效果综合评分 】\n"
					"\t\t\t\t\   【   9：全部     0：退出修改            】\n"
					"\t\t\t\t\   【如职工号有误，请删除该名教师后重新录入】\n");
				scanf("%d",&select2);
				switch (select2)
				{
				case 0:return;//返回菜单
				case 1:printf("修改前姓名：%s\n", p[0]->data.name); stringinput(p[0]->data.name, 15, "修改后："); break;
				case 2:printf("修改前职称：%s\n", p[0]->data.title); stringinput(p[0]->data.title, 15, "修改后："); break;
				case 3:printf("修改前性别：%s\n", p[0]->data.sex); stringinput(p[0]->data.sex, 3, "修改后："); break;
				case 4:printf("修改前课程1：%s\n", p[0]->data.lesson[0]); stringinput(p[0]->data.lesson[0], 15, "修改后："); break;
				case 5:printf("修改前课程2：%s\n", p[0]->data.lesson[1]); stringinput(p[0]->data.lesson[1], 15, "修改后："); break;
				case 6:printf("修改前课程3：%s\n", p[0]->data.lesson[2]); stringinput(p[0]->data.lesson[2], 15, "修改后："); break;
				case 7:for (int i = 0; i < 3; i++) {
					printf("修改前课程%d：%s\n", i, p[0]->data.lesson[i]); stringinput(p[0]->data.lesson[i], 15, "修改后：");
				}break;
				case 8:printf("修改前评分：%lf\n", p[0]->data.score); p[0]->data.score = numberinput("修改后："); break;
				case 9:
					printf("修改前姓名：%s\n", p[0]->data.name); stringinput(p[0]->data.name, 15, "修改后：");
					printf("修改前职称：%s\n", p[0]->data.title); stringinput(p[0]->data.title, 15, "修改后：");
					printf("修改前性别：%s\n", p[0]->data.sex); stringinput(p[0]->data.sex, 3, "修改后：");
					printf("修改前课程1：%s\n", p[0]->data.lesson[0]); stringinput(p[0]->data.lesson[0], 15, "修改后：");
					printf("修改前课程2：%s\n", p[0]->data.lesson[1]); stringinput(p[0]->data.lesson[1], 15, "修改后：");
					printf("修改前课程3：%s\n", p[0]->data.lesson[2]); stringinput(p[0]->data.lesson[2], 15, "修改后：");
					printf("修改前评分：%lf\n", p[0]->data.score); p[0]->data.score = numberinput("修改后："); break;
				}//单次修改结束
				int select3;//确认修改无误
				printf("=====>【1：确认修改    !1：重新修改】\n");
				scanf("%d", &select3);
				//getchar();
				if (select3 == 1)break;//按1确认，否则重新修改
			}//确认本次修改
			printf("=====>修改成功！教师 %s 更新为：\n", p[0]->data.num);
			saveflag = 1;//记录修改标记
			printdata(p[0]);
		}
		else
			Nofind();
		printf("=====>是否继续修改？【1】是  【2】否：");
		scanf("%d", &select4);//变量太多，借一个
		if (select4 != 1)return;//多条修改的出口
	}//修改操作结束
}

/*七、删除函数*/
void Del(Link l) {
	Node** p, * r;//p接收要删除的结点，可能有多个，p接收指针数组的首元素地址
	char findmess[20];//存放用户输入内容
	system("cls");
	/*检查有无文件*/
	if (!l->next) {
		printf("\n=====>当前文件夹暂无教师记录.\n");
		system("pause");
		getchar();
		return;//文件为空，返回菜单
	}
	/*进入删除界面*/
	while (1) {
		/*删除界面设计*/
		system("cls");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\t\t\t\t\t   *          删除信息          *\n");
		printf("\t\t\t\t\t   ******************************\n");
		Disp(l);
		printf("=====>以上是原有教师信息.\n");

		/*有精确查询功能*/
		int messageNum;//根据查询到的个数
		printf("=====>【1】精确查询 【2】继续\n");
		int sel2;//精确查询选择器
		scanf("%d", &sel2);
		if (sel2 == 1)
			messageNum =Qur(l);//先让用户查看要删除教师的相关信息，确认是否删除

		/*删除确认*/
		printf("请您核查，是否删除？【1】信息有误，我需要删除    【2】核查正确，返回主菜单\n");
		int sel3;//确认删除选择器
		scanf("%d", &sel3);
		if (sel3 != 1)
			return;//返回菜单，这里可以在建一个更改页面，就不必返回菜单

		/*开始删除*/
		int sel1;//删除方式选择器
		if (sel2==1&&messageNum == 1) {//如果精确查询到只一条记录则跳过方式选择和提示，直接删除此记录即可
			sel1 = 1;//进入分支1
		}
		else {
			printf("=====>【1】按工号删除    【2】按姓名删除    【3】按课程删除\n");
			scanf("%d", &sel1);
		}
		
		if (sel1 == 1)
		{
			stringinput(findmess, 10, "=====>请输入要删除教师的工号：\n");
			p = Locate(l, findmess, 1);
			if (p[0])//存在
			{
				r = l;
				while (r->next != p[0])
					r = r->next;
				r->next = p[0]->next;//绕过p[0]结点
				free(p[0]);
				printf("=====>删除成功\n");
				printf("=====>共删除 1 条教师信息.\n");//统计提示
				getchar();
				saveflag = 1;//标记为已修改
			}
			else
				Nofind();
			getchar();
		}
		else if (sel1 == 2)
		{
			stringinput(findmess, 15, "=====>请输入要删除教师的姓名：\n");
			p = Locate(l, findmess, 2);
			if (p[0])//存在
			{
				r = l;
				while (r->next != p[0])
					r = r->next;
				r->next = p[0]->next;//绕过p[0]结点
				free(p[0]);
				printf("=====>删除成功\n");
				printf("=====>共删除 1 条教师信息.\n");//统计提示
				getchar();
				saveflag = 1;//标记为已修改
			}
			else
				Nofind();
			getchar();
		}
		else if (sel1 == 3)
		{
			stringinput(findmess, 15, "=====>请输入要删除教师的课程名：\n");
			p = Locate(l, findmess, 3);
			int flag = 0;//判断是否找到
			int count = 0;//记录个数
			for (int i = 0; p[i] != NULL; i++)//遍历删除所有要删除结点
			{
				getchar();//按一次打印一个
				if (p[i])//删完为止
				{
					/*得到要删结点的前一个结点，需要它的指针域*/
					r = l;
					while (r->next != p[i])
						r = r->next;
					r->next = p[i]->next;//绕过p[i]结点
					free(p[i]);//删除
					flag = 1;//至少找到了一个
					count++;//计数器
				}
			}
			printf("=====>删除成功\n");
			printf("=====>共删除 %d 条教师信息.\n", count);//统计提示
			system("pause");
			getchar();
			//如果p=NULL
			if (flag != 1) {//不存在
				Nofind();
				system("pause");
			}
		}//删除完毕

		else//其他选择
		{
			Wrong();//错误输入
			system("pause");
			getchar();
		}//提示完毕

		printf("\n=====>是否继续删除【y/!y】：\n");
		char ch;//选择器
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y')
			continue;
		else
			return;//返回主调函数，main函数
	}//循环删除结束，返回main函数
	return;
}

/*八、退出并选择保存函数*/
void Quit(Link l) {
	char ch;//选择器
	/*保存确认*/
	/*检测到有修改*/
	if (saveflag == 1) {
		getchar();
		printf("\n=====>是否需要保存修改？【y/n】：");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y') Save(l);
	}
	/*结束语*/
	printf("\n=====>感谢您的使用！祝您生活愉快！");
	getchar();
	return;
}

/*子功能*/
/*1.存档子功能函数*/
void Save(Link l) {
	if (saveflag != 1) {
		printf("\n=====>当前您未做任何修改，无需重复保存哦.\n");
		system("pause");
		getchar();
		return;//保存前检查数据是否经过改动
	}
	FILE* fp;
	Node* p;
	int count = 0;
	fp = fopen("teacher", "wb");//重写，没有则新建
	/*文件打开检查*/
	if (fp == NULL) {
		printf("\n=====>打开失败！\n");
		getchar();
		return;
	}
	p = l->next;//从数据表头开始录入
	while (p) {
		if (fwrite(p, sizeof(Node), 1, fp) == 1)//每次写入一个结点信息至文件
		{
			p = p->next;//下一个结点
			count++;//计数
		}
		else break;
	}
	if (count > 0) {
		getchar();
		printf("\n=====>文件保存完成，共有%d条记录.\n请按任意键继续...", count);
		getchar();
		saveflag = 0;
	}
	else
	{
		system("cls");
		printf("=====>当前链表为空,文件将为空.\n");//因为以wb方式重写，如未写入数据，文件将保持空
		system("pause");
		getchar();
	}
	fclose(fp);
}

/*2.字符串校验输入子功能函数*/
void stringinput(char* t, int lens, const char* notice) {
	char n[255] = { 0 };
	do {
		printf(notice);
		scanf("%s", n);//核心，主要是scanf
		if (strlen(n) > lens)
			printf("\n太多了看不过来，不好意思\n");
	} while (strlen(n) > lens);
	strcpy(t, n);//一个输入把关，有效输入才复制到后续需要的字符串中
}

/*3.数值校验输入子功能函数*/
double numberinput(const char* notice) {
	double t = 0.0;
	do {
		printf(notice);
		scanf("%lf", &t);//输入dd会死循环
		if (t > 100.0 || t < 0.0)
			printf("\n分数应在【0-100】内\n");
	} while (t > 100.0 || t < 0.0);
	return t;//输入控制，数据合理才给接收
}

/*4.定位子功能函数*/
Node** Locate(Link l, char findmess[], const int select) {
	Node* r[100] = { NULL };//保存目标结点地址，课程有重复现象

	/*不同的定位方式*/
	/*利用字符串比较函数判断：用户选择的方式*/

	/*需要知道定位何种成员*/
	/*1：按职工号*/
	if (select == 1)
	{
		r[0] = l->next;//定位到第一个结点，但只用一个指针保存目标结点的地址就行
		while (r[0]) {//遍历搜索链表的所有结点
			if (strcmp(r[0]->data.num, findmess) == 0)//搜索匹配成功
				return r;//直接返回，r[0]中已保存，返回r就行；这里是返回，不是只保存，有匹配的直接返回，不看后面的
			r[0] = r[0]->next;//没找到就一直后移，直至r[0]==NULL
		}//搜索完毕，如果没有，这里不会return r;r[0]==NULL退出循环
		return r;//此时r[0]==NULL
	}//职工号查询完毕

	/*2：按姓名*/
	else	if (select == 2)
	{
		r[0] = l->next;//定位到第一个
		while (r[0]) {//遍历搜索
			if (strcmp(r[0]->data.name, findmess) == 0)//搜索匹配成功
				return r;//返回结果
			r[0] = r[0]->next;//没找到就一直后移，直至表尾
		}//搜索完毕
		return r;//此时r[0]==NULL
	}//姓名查询完毕

	/*3：按课程名*/
	else	if (select == 3)
	{
		Node* t;//中间变量，保存结点地址
		t = l->next;//从第一个结点开始判断
		int i = 0;//控制数组的移动
		while (t) {//遍历搜索链表
			if (strcmp(t->data.lesson[0], findmess) == 0)//有一个则搜索匹配成功
				r[i] = t;//成功则保存到r数组中
			else if (strcmp(t->data.lesson[1], findmess) == 0)//有一个则搜索匹配成功
				r[i] = t;//成功则保存到r数组中
			else if (strcmp(t->data.lesson[2], findmess) == 0)//有一个则搜索匹配成功
				r[i] = t;//成功则保存到r数组中
			else
				i--;//都不保存则匹配失败，失败则防止数组后移,抵消数组的后移
			/*链表和数组的移动操作*/
			t = t->next;//所有结点都要看
			i++;//链表后移，数组相应加1
		}
		return r;//如果一条都没，r保持全NULL的状态，已初始化
	}//课程名查询完毕
}

/*其他封装输出到屏幕的提示功能*/
/*1.打印菜单*/
void menu() {
	system("cls");
	system("color 0A");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *      教师信息管理系统      *\n");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   ┌────────────────────────────┐\n");
	printf("\t\t\t\t\t   │ 1. 添加信息    2. 显示全部 │\n");
	printf("\t\t\t\t\t   │                            │\n");
	printf("\t\t\t\t\t   │ 3. 查询信息    4. 排序信息 │\n");
	printf("\t\t\t\t\t   │                            │\n");
	printf("\t\t\t\t\t   │ 5. 修改信息    6. 删除信息 │\n");
	printf("\t\t\t\t\t   │                            │\n");
	printf("\t\t\t\t\t   │ 7. 立即保存    0. 退出程序 │\n");
	printf("\t\t\t\t\t   └────────────────────────────┘\n");
	printf("\t\t\t\t\t   │────────欢迎您的使用────────│\n");
}
/*2.打印表头*/
void printheader() {
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
/*3.打印表身数据*/
void printdata(Node* pp) {
	Node* p;
	p = pp;
	printf(FORMAT, DATA);//宏替换
}
/*4.错误提示*/
void Wrong() {
	printf("\n\n\n\n\n***********Error：输入错误了哦，请按任意键继续***********\n");
	getchar();
}
/*5.未匹配提示*/
void Nofind() {
	printf("\n=====>现在没有，或许，正在路上呢？\n");
	getchar();
}

/*日志*/
/*
日志：2023 6.16 0:35
为什么这里选0退出非要独立出来一个分支？
可以放进switch里的；
能不能封装成一个退出函数？->ok!
或者在输入是添加取消输入的功能，如果信息输错了，按了enter，不能马上及时修改，这是一个问题
对于输入时修改的功能：可以在每填完一整个记录后给出判断选择，是否需要修改？->ok!
*/

/*
定位子功能函数
日志：2023 6.15 10：26
就因为比较的成员不一样，就要有多个分支重复相同的内容，这里可以做修改
能否试试条件编译？
但由于课程可重复，而学号唯一，可能造成搜索学号时的多余搜索，
就算对循环针对学号做，也只会让简单的代码变得很复杂->也可以，if(select==1)return r; r[i]=t;
现在是怎么合并这三个分支？
*/

/*
日志：2023 6.15 22：05
开始做数据流图之后，发现了不够模块化
开始决定将菜单模块从main函数中独立出来，使程序更简简洁；
如下Menu();
*/

/*
日志：2023 6.17 半夜
printf("\n=====>是否继续查询【y/!y】：\n");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y')
		{
			getchar(); continue;//第二次循环直接结束？===>改为整型，ok
		}
		Qur()函数需要添加一个返回值，表示找到几个===>ok
*/

/*
日志：2023 6.17 9：14
无文件时，删除界面，和保存界面不会暂停=>ok
*/

/*
日志：
文件读取也可以封装成一个函数
*/