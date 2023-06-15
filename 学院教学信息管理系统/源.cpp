#define _CRT_SECURE_NO_WARNINGS 1
/*Ԥ������*/
#include<stdio.h>	/*��׼��������������ļ�*/	
#include<stdlib.h>	/*��׼�������ļ�*/
#include<string.h>	/*�ַ����������ļ�*/

/*���������*/
#define HEADER1 "   |----------------------------------------------��ʦ����������-----------------------------------------------------|\n"//1
#define HEADER2 "   |ְ����     |����           |ְ��           |�Ա�|�γ�1          |�γ�2          |�γ�3          |��ѧЧ���ۺ�����|\n"//2
#define HEADER3 "   |-----------|---------------|---------------|----|---------------|---------------|---------------|----------------|\n"//3
#define FORMAT  "   |%-11s|%-15s|%-15s|%-4s|%-15s|%-15s|%-15s|%16.2f|\n"//4.1
#define DATA p->data.num, p->data.name, p->data.title , p->data.sex , p->data.lesson[0] , p->data.lesson[1] , p->data.lesson[2] , p->data.score//4.2
#define END     "   |---------------------------------������ԣ����Գ��裻���绯�꣬���˲��롱----------------------------------------|\n"//5

/*���ݽṹ��Ʋ���*/
/*��ʦ��Ϣ�ṹ������*/
struct teacher {
	char num[10];//��ʦְ����
	char name[15];//��ʦ����
	char title[15];//��ʦְ��
	char sex[3];//�Ա�
	char lesson[3][15];//3�ſγ�
	double score;//��ѧЧ���ۺ�����
};
/*������ṹ������*/
typedef struct node {
	struct teacher data;		//������
	struct node* next;		//ָ����
}Node, * Link;//�ṹ��������ṹ�����ָ��

/*������������*/
	/*һ������*/
void menu();//һ���˵���ʾ���û�����
void Disp(Link l);//������ʾ
void Add(Link l);//�������
void Qur(Link l);//�ġ���ѯ
void Sort(Link l);//�塢����
	/*�ӹ���*/
void Save(Link l);//1.�浵
void stringinput(char* t, int lens, const char* notice);//2.�ַ���У������
double numberinput(const char* notice);//3.��ֵУ������
Node** Locate(Link l, char findmess[], const int select);//4.��λ
	/*��װ�������*/
void printheader();//1.��ӡ��ͷ
void printdata(Node* pp);//2.��ӡ����
void Wrong();//3.������ʾ
void Nofind();//4.δƥ����ʾ

/*ȫ�ֱ�������*/
int saveflag = 0;/*���浽Ӳ�̵ı�־*/

/*�������岿��*/
/*������*/
int main()
{
	Link l;						//��������l��ͷָ��
	FILE* fp;					//�����ļ�ָ��
	int select;					//�����û������ѡ��0-9��
	char ch;					//�����û������ѡ��y,Y,n,N��
	int count = 0;			//�����ļ��еļ�¼���������������
	Node* p, * r;			//p��newָ�룬r��βָ��

	/*����ͷ��㣬������*/
	l = (Node*)malloc(sizeof(Node));	//�����ڴ棨1����ͬʱ��ͷָ�붨��ͷ��㣨3�����ýڵ�������򲻴洢���ݣ�����ǣͷ���ã�����ʡȥ��������ѭ���ڵı�ͷ�жϣ�������Ҳ�а���
	/*������*/
	if (!l) {
		printf("\n ����ռ�ʧ�ܣ� ");
		return 0;//�˳�����
	}
	l->next = NULL;								//ͷ���ָ�����ʼ����2��
	r = l;													//�ź�βָ�루4��

	/*������е��ļ���ȡ���ݵ��ڴ��еĵ�����*/
	fp = fopen("teacher", "ab+");			//���ļ����ɶ�д������ա������ڻ��½�
	/*�ļ��򿪼��*/
	if (fp == NULL) {
		printf("\n=====>��ʧ�ܣ�\n");
		exit(0);//��ֹ��ִ�г���
	}
	/*��ȡ����*/
	printf("������ȡ�ļ��У����Ժ�...\n");//������ʾ
	while (!feof(fp)) {//�ļ������˳�ѭ��
		p = (Node*)malloc(sizeof(Node));			/*���������㣬�����ļ����ݣ�1��*/
		/*������*/
		if (!p) {
			printf("�ռ�����ʧ�ܣ�");
			exit(0);
		}
		if (fread(p, sizeof(Node), 1, fp) == 1) {		//���ļ��ж�ȡ����д�뵽���������
			p->next = NULL;								//��ʼ���½ڵ�ָ����2��
			r->next = p;										//���ӵ���һ��㣨3��
			r = p;													//β�����Ƶ��½�㣨4��
			count++;											//��¼������
		}
	}
	fclose(fp);											//�ر��ļ�
	printf("=====>���ļ��ɹ�������ȡ�� %d ����¼\n\n\n\n=====>��¼�ҵ��˺ţ�\n", count);
	system("pause");
	/*�˵�����*/
	menu();
	while (1)//���ϵķ��ز˵�
	{
		system("cls");//����
		menu();//��ʾ�˵�
		p = r;//?

		/*����ѡ��*/
		printf("\n��ѡ������Ҫ�Ĺ��ܣ�0-9����");
		scanf("%d", &select);

		/*���ж��˳�*/
		if (select == 0) {//�˳�ѡ��
				/*����ȷ��*/
			if (saveflag == 1) {
				getchar();
				printf("\n=====>�Ƿ���Ҫ�����޸ģ���y/n)��");
				scanf("%c", &ch);
				if (ch == 'Y' || ch == 'y')
					Save(l);
			}
			/*������*/
			printf("\n\n\n\n=====>��л����ʹ�ã�ף��������죡\n\n\n\n");
			getchar();
			break;//��������ѭ���Ĳ˵�������mian��������0������ϵͳ����������
		}

		/*���ж�����*/
		switch (select)
		{
		case 1:Add(l); break;//1.��Ӽ�¼
		case 2:system("cls"); Disp(l); break;//2.��ʾ��¼
		case 3:Qur(l);  break;//3.��Ϣ��ѯ
		case 4:Sort(l); break;//4.��¼����
		case 7:
			if (saveflag == 1)
				Save(l);
			else
				printf("\n\n\=====>��δ���κ��޸ģ������ظ�����Ŷ.\n��������������˵�...");
			getchar();
			getchar();
			break;//5.�������棬����ǰ���ж�
		default:Wrong(); getchar(); break;
		}

	}//while(l)�Ľ�β
	return 0;
}

/*һ������*/
	/*һ���˵���ʾ����*/
void menu() {
	system("cls");
	system("color 0A");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *      ��ʦ��Ϣ����ϵͳ      *\n");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   ������������������������������������������������������������\n");
	printf("\t\t\t\t\t   �� 1. �����Ϣ    2. ��ʾȫ�� ��\n");
	printf("\t\t\t\t\t   ��                            ��\n");
	printf("\t\t\t\t\t   �� 3. ��ѯ��Ϣ    4. ������Ϣ ��\n");
	printf("\t\t\t\t\t   ��                            ��\n");
	printf("\t\t\t\t\t   �� 5. �޸���Ϣ    6. ɾ����Ϣ ��\n");
	printf("\t\t\t\t\t   ��                            ��\n");
	printf("\t\t\t\t\t   �� 7. ��������    0. �˳����� ��\n");
	printf("\t\t\t\t\t   ������������������������������������������������������������\n");
	printf("\t\t\t\t\t   ��������������������ӭ����ʹ�é�����������������\n");
}

/*������ʾ����*/
void Disp(Link l) {
	Node* p;//�����ڲ�ָ��
	p = l->next;//�����ͷ���ſ�ʼ������
	if (!p) {
		printf("\n=====>��ǰ�ļ����޽�ʦ��¼\n");
		system("pause");
		getchar();
		return;//�˳��˺�����������������
	}
	printf("\n\n");
	//printheader();//������
	printf(HEADER1);//1
	printf(HEADER2);//2
	while (p) {//�����������Ļ
		//printf(HEADER3);//3,û�и�����
		printdata(p);//4
		p = p->next;
	}
	printf(END);
	system("pause");
	getchar();//?������
}

/*������Ӻ���*/
void Add(Link l) {
	Node* p, * r, * s;					//p���½��ָ�룩��r��βָ�룩���ڴ�������s�����ָ�룩���ڱ������ְ����
	char ch, flag = 0, num[10]; //flag�����������־��num��ְ���ţ�ch�������û�ѡ��

	r = l;//βָ��ָ���ͷ
	s = l->next;//���ָ���ʵ�����ݿ�ʼ��һ��ʼָ��NULL

	system("cls");
	Disp(l);									//����������ӡ������Ϣ
	printf("\n������ϵͳԭ����Ϣ.\n");
	while (r->next != NULL)
		r = r->next;//��βָ�붨λ����β��׼����Ӽ�¼

	while (1) //����ѭ�����������¼��ֱ���û���num����0ʱ�������˵�
	{
		/*ְ����������*/
		while (1) {//��Ϊ0�����ظ��ſ�ͨ����飬����һֱ����򷵻����˵�
			stringinput(num, 10, "������ְ���š���0�������˵�����");//�ַ���У������
			flag = 0;//ÿ��ѭ����ͷ����flag
			/*ְ������0*/
			if (strcmp(num, "0") == 0) {//�������Ϊ0
				return;//�������˵�
			}
			/*ְ���Ų���*/
			s = l->next;//���ü��ָ�뵽��ͷ
			while (s) {//��������β
				if (strcmp(s->data.num, num) == 0) {
					flag = 1;
					break;
				}
				s = s->next;//ָ�����
			}
			if (flag == 1)//ְ�����ظ�
			{
				getchar();
				printf("=====>��ְ���� %s �Ѵ��ڣ��Ƿ��������룿��y/n����\n", num);
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return;//�������˵�
			}
			else
			{
				break;//��Ϊ0�����ظ���ͨ�����
			}
		}//ְ���ż�����

		/*���������㣬�����ļ����ݣ�1��*/
		p = (Node*)malloc(sizeof(Node));
		/*�ռ�������*/
		if (!p) {
			printf("�ռ�����ʧ�ܣ�");
			return;//�������˵�
		}
		//�Խ�㸳ֵ��2��
		strcpy(p->data.num, num);			//�ռ���ֵ��ְ����
		stringinput(p->data.name, 15, "������");
		stringinput(p->data.title, 15, "ְ�ƣ�");
		stringinput(p->data.sex, 2, "�Ա�");
		stringinput(p->data.lesson[0], 15, "�γ�1��");
		stringinput(p->data.lesson[1], 15, "�γ�2��");
		stringinput(p->data.lesson[2], 15, "�γ�3��");
		p->data.score = numberinput("��ѧЧ���ۺ����֣�");
		p->next = NULL;							//ָ����ֵ

		r->next = p;									//������һ����㣺r=l�ʼΪ��ͷ��ֻ��ǣͷ���õı�ͷ��3��
		r = p;											//βָ��ָ���½ڵ㣨4��

		saveflag = 1;//ȫ�ֱ�����������
	}//���벿�ֽ���������0��ȡ�����䣺return;		����Add�������������˵�
	return;//Ӧ�ò�������return; �������г���
}

/*�ġ���ѯ����*/
void Qur(Link l) {
	int select;//��ʽѡ��1-��ְ���ţ�2-��������3-���γ������������˳��������������˵�
	char ch;//�˳�ѡ��y,!y
	char searchinput[20];//�����û���ѯ����
	Node** p;//����Ŀ���¼�Ķ�λ��������Ҫ����Locate�����������ӹ���,�����ڿγ̻����ظ������������õ���ָ������,����һ������ָ�������ܶ�����ĵ�ַ

	if (!l->next)//������Ϊ�գ�l��ͷָ��
	{
		system("cls");
		printf("=====>��ǰ�ļ��޽�ʦ��¼\n");
		getchar();//��ͣ������
		system("pause");
		return;//�˳��������������˵�
	}

	while (1)
	{
		system("cls");
		printf("\n=====>1����ְ��������		=====>2������������		=====>3�����γ�������\n");
		printf("��ѡ�����������ʽ��");
		scanf("%d", &select);
		if (select == 1)//��ְ����,Ψһ
		{
			stringinput(searchinput, 10, "������Ҫ��ѯ�Ľ�ʦְ����:");
			p = Locate(l, searchinput, 1);//�ҵ�ְ����Ϊsearchinput�Ľ�㣬�������ַ

			if (p[0])//p[0]���Ƿ��ϵĽ���ַ
			{
				printheader();//������123
				printdata(p[0]);//4
				printf(END);//5
				printf("��������˳�");
				getchar();
				system("pause");
				break;
			}
			else//���p[0]=NULL,û��ƥ���
			{
				Nofind();
				system("pause");
			}
			//getchar();
		}//��ѯ���

		else if (select == 2)//��������Ψһ
		{
			stringinput(searchinput, 15, "������Ҫ��ѯ�Ľ�ʦ������");
			p = Locate(l, searchinput, 2);//�ҵ�����Ϊsearchinput�Ľ�㣬�������ַ
			if (p[0])//�����ΪNULL
			{
				printheader();//������123
				printdata(p[0]);//4
				printf(END);//5
				printf("��������˳�...");
				getchar();
			}
			else//���NULL
			{
				Nofind();
				system("pause");
				getchar();
			}
		}//��ѯ���

		else if (select == 3)//���γ���,���ǲ�Ψһ
		{
			int flag = 0;//�ж��Ƿ��ҵ�
			int count = 0;//��¼����
			stringinput(searchinput, 15, "������Ҫ��ѯ�Ŀγ�����");
			p = Locate(l, searchinput, 3);//�ҵ�����Ϊsearchinput�Ľ�㣬�������ַ
			printf(HEADER1);//��ͷ1
			printf(HEADER2);//��ͷ2
			for (int i = 0; p[i] != NULL; i++)//����������з��Ͻ��
			{
				getchar();//��һ�δ�ӡһ��
				if (p[i])//�����ΪNULL
				{
					flag = 1;//����ƥ���
					count++;//������
					printf(HEADER3);//��ͷ3
					printdata(p[i]);//����4
				}
			}
			printf(END);//��β5
			printf("=====>��Ϊ���ҵ� %d λ�װ��Ľ�ʦ.\n", count);//���ͳ��
			system("pause");
			//���p=NULL
			if (flag != 1) {//������ƥ���
				Nofind();
				system("pause");
			}
		}//��ѯ���

		else//����ѡ��
		{
			Wrong();//�������룻	//��־���˴����Ľ������Ըĳɣ���������Ƿ�����������˳�->�ѸĽ�
			system("pause");
			getchar();				//��־��getchar();������Ҫ��
		}//��ʾ���

		printf("\n=====>�Ƿ������ѯ��y/!y����\n");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y') {
			continue;
		}
		else
			return;//�������˵�
	}
}

/*�塢������*/
void Sort(Link l) {
	/*�ý���������ķ�ʽ��ʹ�������򣬶�������ԭ�������ϸĶ�������˳��*/
	int select;//ѡ���������ݣ�1�������֣�!1����ְ����
	printf("\n=====>����Ҫ�����ַ�ʽ����=====>1��������	!1����ְ����\n");
	scanf("%d", &select);

	Link ll;//�������ͷ
	Node* p, * rr, * s;//rr��������βָ�룻s���¾���������ݴ��������㣻p��ԭ������ƶ�ָ��

	/*�ж�ԭ����ձ�*/
	if (l->next == NULL)//û�������κ����ݽ�㣬Ϊ������
	{
		system("cls");
		printf("\n\n=====>��ǰ�ļ������޽�ʦ��Ϣ��һ����ʦ����·��~\n");
		getchar();
		system("pause");
		return;//�������˵�
	}

	/*һ������һ���������ͷ*/
	ll = (Node*)malloc(sizeof(Node));//�����ڴ�(1)������ͷ��λ��3��
	/*������*/
	if (!ll) {
		printf("\n ����ռ�ʧ�ܣ� ");
		return;//�������˵�
	}
	ll->next = NULL;//ָ���򸳿գ���������(2)

	system("cls");
	printf("����ǰ��\n");
	Disp(l);//��ʾ����ǰ����

	/*�����ӳ���������������������*/
	p = l->next;//����ԭ�����ͷ���
	while (p)//����ԭ��������ʵ�ʽ��
	{
		/*2.1		����s���ڴ�*/
		s = (Node*)malloc(sizeof(Node));//���ݴ��������㣬�൱���������new����p���
		/*������*/
		if (!s) {
			printf("\n ����ռ�ʧ�ܣ� ");
			return;//�������˵�
		}

		/*2.2		���s�½��*/
		/*���θ���ԭ����ÿ����������*/
		s->data = p->data;//����ԭ����������
		s->next = NULL;//ָ���򸳿�

		/*2.3		���ӣ����룩s�½��*/
		/*�������򷨶������������ӵĸĶ��������棺*/
		/*����㲻��ԭ���ı�β�ˣ�ԭ������������ʱ��βָ����ÿ���һ���ڵ�󣬶�Ҫ���¶��ڱ�β��
		������Ҫ�������������ӣ�βָ��Ͳ���ÿ�ζ����ڱ�β�ˣ����ǵ�һ�� ������ݱ���С���� ���ǰ��*/

		/*2.3.1Ѱ�Ҳ���λ��*/
		/*������Ѱ�Ҳ���λ�õĹ���*/
		rr = ll;//ѭ��ǰ���ض�λ���ܶ������Ĳ��������磺flag=0;��sum=0;�ȵ�

		/*����Ǽ򵥵Ľ���������ָ�ź��������βָ�룬��������s�½�㣬�ӳ�������ll��4����
		����������ָ����rr���ض�λ��ÿ�ζ�Ҫ�ӱ�ͷ��ʼ�ң�ȷ�������ѭ���ܱ������������н��
		ÿ����һ������Ҫ��������֮ǰ�Ľ�㣬�ҵ�����λ��*/
		if (select == 1) {
			while (rr->next != NULL && rr->next->data.score >= p->data.score) {//��������
				rr = rr->next;//��������ڼ򵥵Ľ�����һ����Ҫ�����ѭ�����ɴΣ��Ա�ѧϰ��
			}//��λ���
		}
		else {
			while (rr->next != NULL && strcmp(rr->next->data.num, p->data.num) > 0) {//��������
				rr = rr->next;//��������ڼ򵥵Ľ�����һ����Ҫ�����ѭ�����ɴΣ��Ա�ѧϰ��
			}//��λ���
		}

		/*2.3.2����*/
		if (rr->next == NULL)//˵���������е��������ݶ��ȴ�����Ľ��󣬻���������Ϊ�գ���Ϊ�ǽ������У����������p����s�����뵽��β����βrr����������ȥ����~��
			rr->next = s;
		else//rr����Ľ����ֱ�pС�������ȡ��һ������p���뵽�������ǰ�棺����rr�����G����磬������ǰ�棬�ٺ٣���
		{
			s->next = rr->next;//��Ҫ��������rr�ĺ�һ����ַ��
			rr->next = s;//���������Լ��ĵ�ֱַ�Ӿ͸���rr��ָ���򣬷���ԭ����һ����һϵ�У��Ľ�㽫��ʧ�������޷��һ�
			/*���൱�ڣ�һ������ָ����һ��ֻ�ܷ�һ��ָ�룬ֻ�ܷ�һ�����ӣ�Ҫ���µ����ӣ������Ƚ�ԭ�������ӷ���һ������ȡ���ĵط������򣬱����ǽ���ʧ*/
		}
		/*2.4���β���*/
		p = p->next;//������ԭ����l����һ�������뵽������ll��
	}//�µ��������������!
	/*����������*/
	l->next = ll->next;

	/*������*/
	printf("�����\n");
	Disp(l);//��ʾ�������
	saveflag = 1;//������
	printf("\n=====>������ɣ�\n");
	getchar();
	system("pause");
	return;
}

/*�ӹ���*/
	/*1.�浵�ӹ��ܺ���*/
void Save(Link l) {
	FILE* fp;
	Node* p;
	int count = 0;
	fp = fopen("teacher", "wb");//��д��û�����½�
	/*�ļ��򿪼��*/
	if (fp == NULL) {
		printf("\n=====>��ʧ�ܣ�\n");
		getchar();
		return;
	}

	p = l->next;
	while (p) {
		if (fwrite(p, sizeof(Node), 1, fp) == 1)//ÿ��д��һ�������Ϣ���ļ�
		{
			p = p->next;//��һ�����
			count++;//����
		}
		else
			break;
	}
	if (count > 0) {
		getchar();
		printf("\n\n\n\n\n=====>�ļ�������ɣ�����%d����¼.\n�밴���������...", count);
		getchar();
		saveflag = 0;
	}
	else
	{
		system("cls");
		printf("��ǰ����Ϊ�գ�û�м�¼������.\n");
		getchar();
	}
	fclose(fp);
}

/*2.�ַ���У�������ӹ��ܺ���*/
void stringinput(char* t, int lens, const char* notice) {
	char n[255] = { 0 };
	do {
		printf(notice);
		scanf("%s", n);//���ģ���Ҫ��scanf
		if (strlen(n) > lens)
			printf("\n̫�࿴��������������˼\n");
	} while (strlen(n) > lens);
	strcpy(t, n);//һ������ѹأ���Ч����Ÿ��Ƶ�������Ҫ���ַ�����
}

/*3.��ֵУ�������ӹ��ܺ���*/
double numberinput(const char* notice) {
	double t = 0.0;
	do {
		printf(notice);
		scanf("%lf", &t);//����dd����ѭ��
		if (t > 100.0 || t < 0.0)
			printf("\n����Ӧ�ڡ�0-100����\n");
	} while (t > 100.0 || t < 0.0);
	return t;//������ƣ����ݺ���Ÿ�����
}

/*4.��λ�ӹ��ܺ���*/
Node** Locate(Link l, char findmess[], const int select) {
	Node* r[100] = { NULL };//����Ŀ�����ַ���γ����ظ�����

	/*��ͬ�Ĳ�ѯ��ʽ*/
	/*�����ַ����ȽϺ����жϣ��û�ѡ��ķ�ʽ*/

	/*1����ְ����*/
	if (select == 1)
	{
		r[0] = l->next;//��λ����һ����㣬��ֻ��һ��ָ�뱣��Ŀ����ĵ�ַ����
		while (r[0]) {//����������������н��
			if (strcmp(r[0]->data.num, findmess) == 0)//����ƥ��ɹ�
				return r;//ֱ�ӷ��أ�r[0]���ѱ��棬����r���У������Ƿ��أ�����ֻ���棬��ƥ���ֱ�ӷ��أ����������
			r[0] = r[0]->next;//û�ҵ���һֱ���ƣ�ֱ��r[0]==NULL
		}//������ϣ����û�У����ﲻ��return r;r[0]==NULL�˳�ѭ��
		return r;//��ʱr[0]==NULL
	}//ְ���Ų�ѯ���

	/*2��������*/
	else	if (select == 2)
	{
		r[0] = l->next;//��λ����һ��
		while (r[0]) {//��������
			if (strcmp(r[0]->data.name, findmess) == 0)//����ƥ��ɹ�
				return r;//���ؽ��
			r[0] = r[0]->next;//û�ҵ���һֱ���ƣ�ֱ����β
		}//�������
		return r;//��ʱr[0]==NULL
	}//������ѯ���

	/*3�����γ���*/
	else	if (select == 3)
	{
		Node* t;//�м�������������ַ
		t = l->next;//�ӵ�һ����㿪ʼ�ж�
		int i = 0;//����������ƶ�
		while (t) {//������������
			if (strcmp(t->data.lesson[0], findmess) == 0)//��һ��������ƥ��ɹ�
				r[i] = t;//�ɹ��򱣴浽r������
			else if (strcmp(t->data.lesson[1], findmess) == 0)//��һ��������ƥ��ɹ�
				r[i] = t;//�ɹ��򱣴浽r������
			else if (strcmp(t->data.lesson[2], findmess) == 0)//��һ��������ƥ��ɹ�
				r[i] = t;//�ɹ��򱣴浽r������
			else
				i--;//����������ƥ��ʧ�ܣ�ʧ�����ֹ�������,��������ĺ���
			/*�����������ƶ�����*/
			t = t->next;//���н�㶼Ҫ��
			i++;//������ƣ�������Ӧ��1
		}
		return r;//���һ����û��r����ȫNULL��״̬���ѳ�ʼ��
	}//�γ�����ѯ���
}

/*������װ�������Ļ����ʾ����*/
	/*1.��ӡ��ͷ*/
void printheader() {
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
/*2.��ӡ��������*/
void printdata(Node* pp) {
	Node* p;
	p = pp;
	printf(FORMAT, DATA);//���滻
}
/*3.������ʾ*/
void Wrong() {
	printf("\n\n\n\n\n***********Error�����������Ŷ���밴���������***********\n");
	getchar();
}
/*4.δƥ����ʾ*/
void Nofind() {
	printf("\n=====>����û�У���������·���أ�\n");
	getchar();
}