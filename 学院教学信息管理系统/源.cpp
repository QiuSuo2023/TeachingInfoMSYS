#define _CRT_SECURE_NO_WARNINGS 1
/*Ԥ������*/
#include<stdio.h>	/*��׼��������������ļ�*/	
#include<stdlib.h>	/*��׼�������ļ�*/
#include<string.h>	/*�ַ����������ļ�*/
//������Ŀ���Ʋ���
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
	struct teacher data;//������
	struct node* next;//ָ����
}Node, * Link;//�ṹ��������ṹ�����ָ��

/*������������*/
	/*һ������*/
Link ReadFile();//�㡢�ļ���ȡ
void Menu(Link l);//һ���˵�ѡ��
void Add(Link l);//�������----------------��ť1
void Disp(Link l);//������ʾ---------------��ť2
int Qur(Link l);//�ġ���ѯ----------------��ť3
void Sort(Link l);//�塢����---------------��ť4
void Modify(Link l);//������鲢�޸�-------��ť5
void Del(Link l);//�ߡ�ɾ��----------------��ť6
void Quit(Link l);//�ˡ��˳���ѡ���Ա���---��ť0
	/*�ӹ���*/
void Save(Link l);//1.�浵-----------------��ť7
void stringinput(char* t, int lens, const char* notice);//2.�ַ���У������
double numberinput(const char* notice);//3.��ֵУ������
Node** Locate(Link l, char findmess[], const int select);//4.��λ
	/*��װ�������*/
void menu();//1.��ӡ�˵����û�����
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
	Link l;//����ָ�룬���ն�ȡ������
/*һ����ȡ�ļ���Ϣ*/
	l = ReadFile();
/*��������˵�����*/
	Menu(l);
	return 0;
}

/*һ������*/
/*�㡢�ļ���ȡ����*/
Link ReadFile() {
	Link l;//��������l��ͷָ�룬�ýڵ�������򲻴洢����
	//����ǣͷ���ã�����ʡȥ��������ѭ���ڵı�ͷ�жϣ�������Ҳ�а���
	FILE* fp;//�����ļ�ָ��
	int count = 0;//�����ļ��еļ�¼��������������
	Node* p, * r;//p��newָ�룬r��βָ��

	/*�����������ͷ���*/
	l = (Node*)malloc(sizeof(Node));//�����ڴ棨1����ͬʱ��ͷָ�붨��ͷ��㣨3����
	if (!l) {
		printf("\n ����ռ�ʧ�ܣ� "); return 0;
	}/*������*/
	l->next = NULL;//ͷ���ָ�����ʼ����2��
	r = l;//�ź�βָ�루4��

	/*��ȡ�ļ����ݣ����������Ƶ�����*/
	fp = fopen("teacher", "ab+");//���ļ����ɶ�д������ա������ڻ��½�
	if (fp == NULL) {
		printf("\n=====>��ʧ�ܣ�\n"); exit(0);/*��ֹ��ִ�г���*/
	}/*������*/
	printf("������ȡ�ļ��У����Ժ�...\n");//������ʾ
	while (!feof(fp)) {//�ļ�����ʱ�˳�ѭ��
		p = (Node*)malloc(sizeof(Node));//���������㣬�����ļ����ݣ�1��
		if (!p) {
			printf("�ռ�����ʧ�ܣ�"); exit(0);/*��ֹ��ִ�г���*/
		}/*������*/
		/*��ȡ�ļ���Ϊ���������ֵ*/
		if (fread(p, sizeof(Node), 1, fp) == 1) {
			p->next = NULL;//ָ����ֵ��2�����ļ��е�ָ����ʧЧ��
			r->next = p;//���ӵ���һ��㣨3��
			r = p;		//β�����Ƶ��½�㣨4��
			count++;	//��¼������
		}
	}
	fclose(fp); //�ر��ļ�
	printf("=====>���ļ��ɹ�������ȡ�� %d ����¼\n\n\n\n=====>��¼�ҵ��˺ţ�\n", count);
	system("pause");
	return l;
}

/*һ���˵�ѡ����*/
void Menu(Link l) {
	int select;			//�����û������ѡ��0-9��

	while (1)//���Բ��ϵط��ز˵�
	{
		system("cls");//����
		menu();//�˵������ӡ
		/*����ѡ��*/
		printf("\n��ѡ������Ҫ�Ĺ��ܡ�0-9����");
		scanf("%d", &select);

		switch (select)
		{
		case 0:Quit(l); return;//0.����main��������main������������
		case 1:Add(l); break;//1.��Ӽ�¼
		case 2:system("cls"); Disp(l); break;//2.��ʾ��¼
		case 3:Qur(l);  break;//3.��ѯ��Ϣ
		case 4:Sort(l); break;//4.�����¼
		case 5:Modify(l); break;//5.�޸���Ϣ
		case 6:Del(l); break;//6.ɾ����Ϣ
		case 7:Save(l); getchar();break;//7.�������棬����ǰ���ж�
		default:Wrong(); getchar();break;//�����������
		}
	}//�˵�while(l)�Ľ�β������main��������main������������
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
	//printf("\n\n");//��ʾ������޸�=>
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          ȫ����¼          *\n");
	printf("\t\t\t\t\t   ******************************\n");
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
	Node* p, * r, * s;//p���½��ָ�룩��r��βָ�룩���ڴ�������s�����ָ�룩���ڱ������ְ����
	char ch, flag = 0, num[10]; //flag��ְ�����ظ���־��num��ְ���ţ�ch�������û�ѡ��

	r = l;//βָ�룬ָ���ͷ
	s = l->next;//���ָ�룬��ʵ�����ݿ�ʼ��һ��ʼָ��NULL

	system("cls");
	/*���ҳ��*/
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          ��Ӽ�¼          *\n");
	printf("\t\t\t\t\t   ******************************\n");
	/*�������������ӡԭ����Ϣ*/
	if (l->next) {
		Disp(l);
		printf("\n������ϵͳԭ����Ϣ.\n");
	}

	/*���벿�ֿ�ʼ*/
	/*��βָ�붨λ����β��׷�ӻ��½���¼*/
	while (r->next != NULL)
		r = r->next;
	while (1) //����ѭ�����������¼��ֱ���û���num����0ʱ�������˵������ظ�ʱѡ���˻����˵�
	{
		/*�����ȷ��*/
		while (1)//ÿ�����ȷ�ϲ���
		{
			/*�˳�������ְ���Ų���*/
			while (1) //��Ϊ0�����ظ��ſ�������Ϣ������һֱ����򷵻����˵�
			{				
				stringinput(num, 10, "������ְ���š���0�������˵�����");//�ַ���У������
				
				/*�˳�����*/
				if (strcmp(num, "0") == 0)
					return;//��0�˻����˵�

				/*ְ���Ų���*/
				s = l->next;//ÿ�β��أ����ü��ָ�룬����ͷ
				flag = 0;//ͬʱ�������ظ�flag=0
				while (s) {
					if (strcmp(s->data.num, num) == 0) {flag = 1;break;}//�����ظ������
					s = s->next;//ָ����ƣ�������ͷ��β
				}

				if (flag == 1){//ְ�����ظ�
					getchar();
					printf("=====>��ְ���� %s �Ѵ��ڣ��Ƿ��������룿��y/n����\n", num);
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')continue;
					else return;//�������˵�
				}
				else break;//���˳���û�ظ���ͨ�����
			}//ְ���ż�����

			/*��������4����*/
			/*���������㣨1��*/
			p = (Node*)malloc(sizeof(Node));
			if (!p) {
				printf("�ռ�����ʧ�ܣ�");
				return;//�������˵�
			}
			/*�����¼����Ϣ��2��*/
			strcpy(p->data.num, num);
			stringinput(p->data.name, 15, "������");
			stringinput(p->data.title, 15, "ְ�ƣ�");
			stringinput(p->data.sex, 2, "�Ա�");
			stringinput(p->data.lesson[0], 15, "�γ�1��");
			stringinput(p->data.lesson[1], 15, "�γ�2��");
			stringinput(p->data.lesson[2], 15, "�γ�3��");
			p->data.score = numberinput("��ѧЧ���ۺ����֣�");//������ֵ
			p->next = NULL;//ָ����ֵ
			/*4���м�Ӹ��жϣ�ȷ���Ƿ�����*/
			int select;
			printf("=====>����0�����䣬����1������\n");
			scanf("%d", &select);
			if (select == 0) {
				free(p);continue;//��ձ������ݣ��ͷŲ�Ҫ���ڴ�
			}
			r->next = p;//������һ����㣻r->nextʼ��Ϊ�գ�r�ʼΪ���������β�����ͷ��lͷ��㲻����Ϣ��3��
			r = p;//βָ��ָ���½ڵ㣨4��
			/*���޸ı��*/
			saveflag = 1;//ȫ�ֱ���
		}
	}//���벿�ֽ���������0ʱ�����˺������������˵�
}

/*�ġ���ѯ����*/
int Qur(Link l) {
	int select;//��ʽѡ��1-��ְ���ţ�2-��������3-���γ������������˳��������������˵�
	int count = 0;//��¼����
	char searchinput[20];//�����û���ѯ����
	Node** p;//����Ŀ���¼�Ķ�λ��������Ҫ����Locate�����������ӹ���,�����ڿγ̻����ظ�������
	//�����õ���ָ������,����һ������ָ�������ܶ�����ĵ�ַ
	/*��������ļ�*/
	if (!l->next)//������Ϊ�գ�l��ͷָ��
	{
		system("cls");
		printf("=====>��ǰ�ļ��޽�ʦ��¼\n");
		getchar();//��ͣ������
		system("pause");
		return count;//�˳��������������˵�
	}
	/*�����ѯ����*/
	while (1)
	{
		/*��ѯ�������*/
		system("cls");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\t\t\t\t\t   *          ��ѯ��Ϣ          *\n");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\n=====>1����ְ��������		=====>2������������		=====>3�����γ�������\n");
		printf("��ѡ�����������ʽ��");//��������ϸ�������������������bug
		scanf("%d", &select);

		if (select == 1)//��ְ����,Ψһ
		{
			stringinput(searchinput, 10, "������Ҫ��ѯ�Ľ�ʦְ����:");
			p = Locate(l, searchinput, 1);//�ҵ�ְ����Ϊsearchinput�Ľ�㣬�������ַ

			if (p[0])//p[0]���Ƿ��ϵĽ���ַ
			{
				count++;
				printheader();//������123
				printdata(p[0]);//4
				printf(END);//5
				getchar();
				system("pause");
			}
			else//���p[0]=NULL,û��ƥ���
			{
				Nofind();
				system("pause");
				getchar();
			}
		}//��ѯ���

		else if (select == 2)//��������Ψһ
		{
			stringinput(searchinput, 15, "������Ҫ��ѯ�Ľ�ʦ������");
			p = Locate(l, searchinput, 2);//�ҵ�����Ϊsearchinput�Ľ�㣬�������ַ
			if (p[0])//�����ΪNULL
			{
				count++;
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
				getchar();
			}
		}//��ѯ���

		else//����ѡ��
		{
			Wrong();//�������룻	//��־���˴����Ľ������Ըĳɣ���������Ƿ�����������˳�->�ѸĽ�
			system("pause");
			getchar();				//��־��getchar();������Ҫ��
		}//��ʾ���

		int ch;//�˳�ѡ����
		printf("\n=====>��1��������ѯ    ��2���˳���ѯ\n");
		scanf("%d", &ch);
		if (ch == 1)
		{
			getchar(); continue;//�ڶ���ѭ��ֱ�ӽ�����������char�����뱻��������\n�����,=>�ĳ�������
		}
		else
			break;//����ѭ��
	}
	return count;//������ڼ�����ѯ���ͷ��ز��ҵ����ܸ���
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
			while (rr->next != NULL && strcmp(rr->next->data.num, p->data.num) < 0) {//��������
				rr = rr->next;//��������ڼ򵥵Ľ�����һ����Ҫ�����ѭ�����ɴΣ��Ա�ѧϰ��
			}//��λ���
		}

		/*2.3.2����*/
		if (rr->next == NULL)//˵���������е��������ݶ��ȴ�����Ľ��󣬻���������Ϊ�գ���Ϊ�ǽ������У����������p����s�����뵽��β����βrr����������ȥ����~��
			rr->next = s;//rr��������һ���ĵ�ַ��s�����ŵ�ǰ������Ľ��λ��
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

/*������鲢�޸ĺ���*/
void Modify(Link l) {
	Node* *p;//��Ž�ʦ��¼��㣬��ֻ��p[0]
	char id[20];//���ְ���ţ��޸���ְ����Ϊ����,��Ϊְ����Ψһ����������������Ψһ������޸Ĵ��ڹ�������
	int select1;//�Ƿ��޸���Ϣ
	if (!l->next) {
		printf("\n=====>��ǰ�ļ����޽�ʦ��¼\n");
		system("pause");
		getchar();
		return;//�˳��˺�����������������
	}

	system("cls");
	printf("\t\t\t\t\t   ******************************\n");
	printf("\t\t\t\t\t   *          ������Ϣ          *\n");
	printf("\t\t\t\t\t   ******************************\n");
	Disp(l);
	printf("=====>������ԭ�н�ʦ��Ϣ.\n");

	printf("=====>��1����ȷ��ѯ ��2������\n");
	int select4;//�Ƿ���Ҫ��ȷ��ѯ
	scanf("%d",&select4);
	//getchar();//�Ƿ���Ҫ����\n?
	if (select4 == 1)
		Qur(l);//�����û��鿴Ҫ�޸Ľ�ʦ�������Ϣ��ȷ���Ƿ��޸�
	/*��ʾ�Ƿ��޸�*/
	printf("�����˲飬�Ƿ��޸ģ���1����Ϣ��������Ҫ�޸�    ��2���˲���ȷ���������˵�\n");
	scanf("%d", &select1);
	if (select1 != 1)
		return;//���ز˵�����������ڽ�һ������ҳ�棬�Ͳ��ط��ز˵�

	/*��ʼ�޸�*/
	while (1)//�����޸�
	{
		/*��ʼ�޸ģ�һ��ֻ���޸�һ��*/
		stringinput(id, 10, "��������Ҫ�޸Ľ�ʦ��ְ���ţ�");
		/*�ҳ��޸Ķ���Ψһ*/
		p = Locate(l, id, 1);//ע�⣺���ﷵ�ص���ָ������,�����ǰ�ְ���Ų��ң����ص�����ֻ����һ��p[0]
		/*�ж��Ƿ���ڸý�ʦ*/
		if (p[0])
		{
			/*�û��޸Ĳ�ȷ��*/
			while (1) 
			{
				int select2;//ѡ���޸�����
				//printf("=====>��Ҫ�޸Ľ�ʦ��ְ���ţ�%s\n", p[0]->data.num);
				printf("=====>����Ҫ�޸ĸ�����ʦ�ģ�\n"
					"\t\t\t\t\   ��   1������     2��ְ��     3���Ա�    ��\n"
					"\t\t\t\t\   ��   4���γ�1    5���γ�2    6���γ�3   ��\n"
					"\t\t\t\t\   ��   7: �������γ�  8����ѧЧ���ۺ����� ��\n"
					"\t\t\t\t\   ��   9��ȫ��     0���˳��޸�            ��\n"
					"\t\t\t\t\   ����ְ����������ɾ��������ʦ������¼�롿\n");
				scanf("%d",&select2);
				switch (select2)
				{
				case 0:return;//���ز˵�
				case 1:printf("�޸�ǰ������%s\n", p[0]->data.name); stringinput(p[0]->data.name, 15, "�޸ĺ�"); break;
				case 2:printf("�޸�ǰְ�ƣ�%s\n", p[0]->data.title); stringinput(p[0]->data.title, 15, "�޸ĺ�"); break;
				case 3:printf("�޸�ǰ�Ա�%s\n", p[0]->data.sex); stringinput(p[0]->data.sex, 3, "�޸ĺ�"); break;
				case 4:printf("�޸�ǰ�γ�1��%s\n", p[0]->data.lesson[0]); stringinput(p[0]->data.lesson[0], 15, "�޸ĺ�"); break;
				case 5:printf("�޸�ǰ�γ�2��%s\n", p[0]->data.lesson[1]); stringinput(p[0]->data.lesson[1], 15, "�޸ĺ�"); break;
				case 6:printf("�޸�ǰ�γ�3��%s\n", p[0]->data.lesson[2]); stringinput(p[0]->data.lesson[2], 15, "�޸ĺ�"); break;
				case 7:for (int i = 0; i < 3; i++) {
					printf("�޸�ǰ�γ�%d��%s\n", i, p[0]->data.lesson[i]); stringinput(p[0]->data.lesson[i], 15, "�޸ĺ�");
				}break;
				case 8:printf("�޸�ǰ���֣�%lf\n", p[0]->data.score); p[0]->data.score = numberinput("�޸ĺ�"); break;
				case 9:
					printf("�޸�ǰ������%s\n", p[0]->data.name); stringinput(p[0]->data.name, 15, "�޸ĺ�");
					printf("�޸�ǰְ�ƣ�%s\n", p[0]->data.title); stringinput(p[0]->data.title, 15, "�޸ĺ�");
					printf("�޸�ǰ�Ա�%s\n", p[0]->data.sex); stringinput(p[0]->data.sex, 3, "�޸ĺ�");
					printf("�޸�ǰ�γ�1��%s\n", p[0]->data.lesson[0]); stringinput(p[0]->data.lesson[0], 15, "�޸ĺ�");
					printf("�޸�ǰ�γ�2��%s\n", p[0]->data.lesson[1]); stringinput(p[0]->data.lesson[1], 15, "�޸ĺ�");
					printf("�޸�ǰ�γ�3��%s\n", p[0]->data.lesson[2]); stringinput(p[0]->data.lesson[2], 15, "�޸ĺ�");
					printf("�޸�ǰ���֣�%lf\n", p[0]->data.score); p[0]->data.score = numberinput("�޸ĺ�"); break;
				}//�����޸Ľ���
				int select3;//ȷ���޸�����
				printf("=====>��1��ȷ���޸�    !1�������޸ġ�\n");
				scanf("%d", &select3);
				//getchar();
				if (select3 == 1)break;//��1ȷ�ϣ����������޸�
			}//ȷ�ϱ����޸�
			printf("=====>�޸ĳɹ�����ʦ %s ����Ϊ��\n", p[0]->data.num);
			saveflag = 1;//��¼�޸ı��
			printdata(p[0]);
		}
		else
			Nofind();
		printf("=====>�Ƿ�����޸ģ���1����  ��2����");
		scanf("%d", &select4);//����̫�࣬��һ��
		if (select4 != 1)return;//�����޸ĵĳ���
	}//�޸Ĳ�������
}

/*�ߡ�ɾ������*/
void Del(Link l) {
	Node** p, * r;//p����Ҫɾ���Ľ�㣬�����ж����p����ָ���������Ԫ�ص�ַ
	char findmess[20];//����û���������
	system("cls");
	/*��������ļ�*/
	if (!l->next) {
		printf("\n=====>��ǰ�ļ������޽�ʦ��¼.\n");
		system("pause");
		getchar();
		return;//�ļ�Ϊ�գ����ز˵�
	}
	/*����ɾ������*/
	while (1) {
		/*ɾ���������*/
		system("cls");
		printf("\t\t\t\t\t   ******************************\n");
		printf("\t\t\t\t\t   *          ɾ����Ϣ          *\n");
		printf("\t\t\t\t\t   ******************************\n");
		Disp(l);
		printf("=====>������ԭ�н�ʦ��Ϣ.\n");

		/*�о�ȷ��ѯ����*/
		int messageNum;//���ݲ�ѯ���ĸ���
		printf("=====>��1����ȷ��ѯ ��2������\n");
		int sel2;//��ȷ��ѯѡ����
		scanf("%d", &sel2);
		if (sel2 == 1)
			messageNum =Qur(l);//�����û��鿴Ҫɾ����ʦ�������Ϣ��ȷ���Ƿ�ɾ��

		/*ɾ��ȷ��*/
		printf("�����˲飬�Ƿ�ɾ������1����Ϣ��������Ҫɾ��    ��2���˲���ȷ���������˵�\n");
		int sel3;//ȷ��ɾ��ѡ����
		scanf("%d", &sel3);
		if (sel3 != 1)
			return;//���ز˵�����������ڽ�һ������ҳ�棬�Ͳ��ط��ز˵�

		/*��ʼɾ��*/
		int sel1;//ɾ����ʽѡ����
		if (sel2==1&&messageNum == 1) {//�����ȷ��ѯ��ֻһ����¼��������ʽѡ�����ʾ��ֱ��ɾ���˼�¼����
			sel1 = 1;//�����֧1
		}
		else {
			printf("=====>��1��������ɾ��    ��2��������ɾ��    ��3�����γ�ɾ��\n");
			scanf("%d", &sel1);
		}
		
		if (sel1 == 1)
		{
			stringinput(findmess, 10, "=====>������Ҫɾ����ʦ�Ĺ��ţ�\n");
			p = Locate(l, findmess, 1);
			if (p[0])//����
			{
				r = l;
				while (r->next != p[0])
					r = r->next;
				r->next = p[0]->next;//�ƹ�p[0]���
				free(p[0]);
				printf("=====>ɾ���ɹ�\n");
				printf("=====>��ɾ�� 1 ����ʦ��Ϣ.\n");//ͳ����ʾ
				getchar();
				saveflag = 1;//���Ϊ���޸�
			}
			else
				Nofind();
			getchar();
		}
		else if (sel1 == 2)
		{
			stringinput(findmess, 15, "=====>������Ҫɾ����ʦ��������\n");
			p = Locate(l, findmess, 2);
			if (p[0])//����
			{
				r = l;
				while (r->next != p[0])
					r = r->next;
				r->next = p[0]->next;//�ƹ�p[0]���
				free(p[0]);
				printf("=====>ɾ���ɹ�\n");
				printf("=====>��ɾ�� 1 ����ʦ��Ϣ.\n");//ͳ����ʾ
				getchar();
				saveflag = 1;//���Ϊ���޸�
			}
			else
				Nofind();
			getchar();
		}
		else if (sel1 == 3)
		{
			stringinput(findmess, 15, "=====>������Ҫɾ����ʦ�Ŀγ�����\n");
			p = Locate(l, findmess, 3);
			int flag = 0;//�ж��Ƿ��ҵ�
			int count = 0;//��¼����
			for (int i = 0; p[i] != NULL; i++)//����ɾ������Ҫɾ�����
			{
				getchar();//��һ�δ�ӡһ��
				if (p[i])//ɾ��Ϊֹ
				{
					/*�õ�Ҫɾ����ǰһ����㣬��Ҫ����ָ����*/
					r = l;
					while (r->next != p[i])
						r = r->next;
					r->next = p[i]->next;//�ƹ�p[i]���
					free(p[i]);//ɾ��
					flag = 1;//�����ҵ���һ��
					count++;//������
				}
			}
			printf("=====>ɾ���ɹ�\n");
			printf("=====>��ɾ�� %d ����ʦ��Ϣ.\n", count);//ͳ����ʾ
			system("pause");
			getchar();
			//���p=NULL
			if (flag != 1) {//������
				Nofind();
				system("pause");
			}
		}//ɾ�����

		else//����ѡ��
		{
			Wrong();//��������
			system("pause");
			getchar();
		}//��ʾ���

		printf("\n=====>�Ƿ����ɾ����y/!y����\n");
		char ch;//ѡ����
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y')
			continue;
		else
			return;//��������������main����
	}//ѭ��ɾ������������main����
	return;
}

/*�ˡ��˳���ѡ�񱣴溯��*/
void Quit(Link l) {
	char ch;//ѡ����
	/*����ȷ��*/
	/*��⵽���޸�*/
	if (saveflag == 1) {
		getchar();
		printf("\n=====>�Ƿ���Ҫ�����޸ģ���y/n����");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y') Save(l);
	}
	/*������*/
	printf("\n=====>��л����ʹ�ã�ף��������죡");
	getchar();
	return;
}

/*�ӹ���*/
/*1.�浵�ӹ��ܺ���*/
void Save(Link l) {
	if (saveflag != 1) {
		printf("\n=====>��ǰ��δ���κ��޸ģ������ظ�����Ŷ.\n");
		system("pause");
		getchar();
		return;//����ǰ��������Ƿ񾭹��Ķ�
	}
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
	p = l->next;//�����ݱ�ͷ��ʼ¼��
	while (p) {
		if (fwrite(p, sizeof(Node), 1, fp) == 1)//ÿ��д��һ�������Ϣ���ļ�
		{
			p = p->next;//��һ�����
			count++;//����
		}
		else break;
	}
	if (count > 0) {
		getchar();
		printf("\n=====>�ļ�������ɣ�����%d����¼.\n�밴���������...", count);
		getchar();
		saveflag = 0;
	}
	else
	{
		system("cls");
		printf("=====>��ǰ����Ϊ��,�ļ���Ϊ��.\n");//��Ϊ��wb��ʽ��д����δд�����ݣ��ļ������ֿ�
		system("pause");
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
			printf("\n̫���˿���������������˼\n");
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

	/*��ͬ�Ķ�λ��ʽ*/
	/*�����ַ����ȽϺ����жϣ��û�ѡ��ķ�ʽ*/

	/*��Ҫ֪����λ���ֳ�Ա*/
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
/*1.��ӡ�˵�*/
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
/*2.��ӡ��ͷ*/
void printheader() {
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
}
/*3.��ӡ��������*/
void printdata(Node* pp) {
	Node* p;
	p = pp;
	printf(FORMAT, DATA);//���滻
}
/*4.������ʾ*/
void Wrong() {
	printf("\n\n\n\n\n***********Error�����������Ŷ���밴���������***********\n");
	getchar();
}
/*5.δƥ����ʾ*/
void Nofind() {
	printf("\n=====>����û�У���������·���أ�\n");
	getchar();
}

/*��־*/
/*
��־��2023 6.16 0:35
Ϊʲô����ѡ0�˳���Ҫ��������һ����֧��
���ԷŽ�switch��ģ�
�ܲ��ܷ�װ��һ���˳�������->ok!
���������������ȡ������Ĺ��ܣ������Ϣ����ˣ�����enter���������ϼ�ʱ�޸ģ�����һ������
��������ʱ�޸ĵĹ��ܣ�������ÿ����һ������¼������ж�ѡ���Ƿ���Ҫ�޸ģ�->ok!
*/

/*
��λ�ӹ��ܺ���
��־��2023 6.15 10��26
����Ϊ�Ƚϵĳ�Ա��һ������Ҫ�ж����֧�ظ���ͬ�����ݣ�����������޸�
�ܷ������������룿
�����ڿγ̿��ظ�����ѧ��Ψһ�������������ѧ��ʱ�Ķ���������
�����ѭ�����ѧ������Ҳֻ���ü򵥵Ĵ����úܸ���->Ҳ���ԣ�if(select==1)return r; r[i]=t;
��������ô�ϲ���������֧��
*/

/*
��־��2023 6.15 22��05
��ʼ��������ͼ֮�󣬷����˲���ģ�黯
��ʼ�������˵�ģ���main�����ж���������ʹ��������ࣻ
����Menu();
*/

/*
��־��2023 6.17 ��ҹ
printf("\n=====>�Ƿ������ѯ��y/!y����\n");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y')
		{
			getchar(); continue;//�ڶ���ѭ��ֱ�ӽ�����===>��Ϊ���ͣ�ok
		}
		Qur()������Ҫ���һ������ֵ����ʾ�ҵ�����===>ok
*/

/*
��־��2023 6.17 9��14
���ļ�ʱ��ɾ�����棬�ͱ�����治����ͣ=>ok
*/

/*
��־��
�ļ���ȡҲ���Է�װ��һ������
*/