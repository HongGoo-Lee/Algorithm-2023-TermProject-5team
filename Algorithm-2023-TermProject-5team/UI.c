#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "file_input_output.h"
#include "floyd.h"

//��ǥ�̵� �Լ�
void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// ī�װ���� ȭ���� Ʋ
void print_category_screen_frame(void)
{
	system("cls");
	int i;
	printf("%20s��", "");
	for (i = 0; i < 50; i++) {
		printf("��");
	}
	printf("��\n");
	for (i = 0; i < 2; i++)
		printf("%20s��%50s��\n", "", "");

	printf("%20s��", "");
	for (i = 0; i < 50; i++) {
		printf("��");
	}
	printf("��\n");
	for(i=0;i<20;i++)
		printf("%20s��%50s��\n", "", "");
	printf("%20s��","");
	for (i = 0; i < 50; i++) {
		printf("��");
	}
	printf("��\n");
}

// �簢���� �� �簢�� �ȿ� ���ڿ��� �־� ����ϴ� �Լ�
void print_square(int x, int y, char* msg)
{
	GotoXY(x, y);
	printf("��");
	for (int i = 0; i < 10; i++)
		printf("��");
	printf("��");
	GotoXY(x, y + 1);
	printf("��%10s��", msg);
	GotoXY(x, y + 2);
	printf("��");
	for (int i = 0; i < 10; i++)
		printf("��");
	printf("��");
}

//�Է�â�� ����ϴ� �Լ�
void print_input_square(int x, int y)
{
	GotoXY(x, y );
	printf("��");
	for (int i = 0; i < 8; i++)
		printf("��");
	printf("��");
	for (int i = 0; i < 31; i++)
		printf("��");
	printf("��");
	GotoXY(x, y + 1);
	printf("��  �� �� ��%31s��","");
	GotoXY(x, y + 2);
	printf("��");
	for (int i = 0; i < 8; i++)
		printf("��");
	printf("��");
	for (int i = 0; i < 31; i++)
		printf("��");
	printf("��");
	GotoXY(x+12, y+1);
}

// ī�װ� ����ϴ� �Լ�
void print_category_screen()
{
	system("cls");
	print_category_screen_frame();

	GotoXY(40, 1);
	printf("<<���� ����>>");

	print_input_square(25, 5);

	int category_size = get_Category_count();
	Category* array = get_Category_list();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i * 3 + j) < category_size)
			{
				GotoXY(25 + j * 15, 10 + i * 4);
				print_square(25 + j * 15, 10 + i * 4, array[(i * 3) + j].category);
			}
		}
	}
	GotoXY(36, 6);
}

// ���α׷� �ʱ�ȭ��
void print_user_ui()
{
	int i = 0;
	printf(" \n");
	printf("%36s", "");
	printf("<< ������ ���α׷� >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "1. ���� ����");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "2. ���� �˻�");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");
	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%15s", "");
	printf("�Է�:");
	printf("%30s��", "");
	printf("\n%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��");
	GotoXY(42, 12);
}

//���� ����� ����ϴ� �Լ�
void print_product_list(char* category)
{
	Product* p = get_product_list(category);
	int i,size = get_product_count(category);
	system("cls");
	GotoXY(40, 1);
	printf("<<%s>>",category);
	for (i = 0; i < size; i++)
	{
		GotoXY(25, 5+i*2);
		printf("��ǰ��: %s, ī�װ�: %s, ����: %d�� ���: %d\n", p[i].name, p[i].category, p[i].price, p[i].count);
	}
	print_input_square(25, 19);
}

// ���� Ȯ�� ȭ��
void print_buy_check_screen(char* name, int count, int price)
{
	print_category_screen_frame();
	GotoXY(40, 1);
	printf("<<���� ����>>");
	GotoXY(30, 5);
	printf("��ǰ��: %s", name);
	GotoXY(30, 7);
	printf("�� ��: %d", count);
	GotoXY(30, 9);
	printf("�� ��: %d", price);
	print_square(30, 13,"����");
	print_square(42, 13, "���");
	print_input_square(25, 18);
} 

// ��޿��� ����ϴ� �Լ�
void print_delivery_screen(char* arrival)
{
	system("cls");
	int num = get_City_num(arrival);

	Road min_dis = get_min_dis_Road(num);
	Road min_cost = get_min_cost_Road(num);
	Road min_time = get_min_time_Road(num);
	
	int hour, min, sec;
	
	hour = min_dis.time / 3600;
	min = (min_dis.time % 3600) / 60;
	sec = (min_dis.time % 3600) % 60;
	printf("1. �ִܰ�� �Ÿ�: %d, ���: %d, �ð�: %d�ð� %d�� %d��\n", min_dis.km, min_dis.cost, hour, min, sec);
	
	hour = min_dis.cost / 3600;
	min = (min_dis.cost % 3600) / 60;
	sec = (min_dis.cost % 3600) % 60;
	printf("2. �ִܺ�� �Ÿ�: %d, ���: %d, �ð�: %d�ð� %d�� %d��\n", min_cost.km, min_cost.cost, hour, min, sec);
	
	hour = min_time.time / 3600;
	min = (min_time.time % 3600) / 60;
	sec = (min_time.time % 3600) % 60;
	printf("3. �ִܽð� �Ÿ�: %d, ���: %d, �ð�: %d�ð� %d�� %d��\n", min_time.km, min_time.cost, hour, min, sec);
}

// ���Ǳ��� �Լ�
void menu_1(void)
{
	int menu, count = 0, price = 0;
	char name[41], tmp[41];
	Category category;
	City c;
	do
	{
		print_category_screen();
		scanf("%s", category.category);
	} while (check_Category(category) == 0);
	print_product_list(category.category);
	scanf("%s %s %d", name, category.category, &count);
	price = cal_money(name, count);
	print_buy_check_screen(name, count, price);
	scanf("%s", tmp);
	if (strcmp(tmp, "����") == 0)
	{
		system("cls");
		printf("1. �ù�� �ޱ�(�߰���� �߻� ��� 2����)\n");
		printf("2. ���� ��������\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			printf("������ ������ �Է����ּ���: ");
			scanf("%s", c.city);
			if (check_City(c) == 0)
				printf("����� �Ұ����� �����Դϴ�.\n���Ű� ��ҵ˴ϴ�.\n");
			else
			{
				print_delivery_screen(c.city);
				getchar();
				scanf("%d", &menu);
				int num = get_City_num(c.city);
				Road tmp;
				switch (menu)
				{
				case 1:
					tmp = get_min_dis_Road(num);
					break;
				case 2:
					tmp = get_min_cost_Road(num);
					break;
				case 3:
					tmp = get_min_time_Road(num);
					break;
				}
				buy_product(name, category.category, count, price + tmp.cost, 1);
				printf("���Ű� �Ϸ� �Ǿ����ϴ�.\n");
			}
			break;
		case 2:
			buy_product(name, category.category, count, price, 0);
			printf("���Ű� �Ϸ� �Ǿ����ϴ�.\n");
			break;
		}
	}
	else
	{
		printf("���Ÿ� ����ϼ̽��ϴ�.\n");
	}
}

// �˻��� �ܾ ����ִ� ���ǵ��� ����ϴ� �Լ�
void print_search_list(void)
{
	char str[41];
	system("cls");
	print_category_screen_frame();

	GotoXY(40, 1);
	printf("<<���� �˻�>>");

	print_input_square(25, 5);
	scanf("%s", str);
	Product* p = search_Product(str);
	system("cls");

	GotoXY(40, 1);
	printf("<<%s �˻����>>", str);
	GotoXY(35, 2);
	printf("�����ҽ� ��ǰ��, ī�װ�, ������ ������");
	for (int i = 0; i < search_Product_count(str); i++)
	{
		GotoXY(25, 5 + i * 2);
		printf("��ǰ��: %s, ī�װ�: %s, ����: %d�� ���: %d\n", p[i].name, p[i].category, p[i].price, p[i].count);
	}
	print_input_square(25, 19);
}

// ���� �˻� �Լ�
void menu_2()
{
	int menu, count = 0, price = 0;
	char name[41], tmp[41];
	Category category;
	City c;
	print_search_list();
	scanf("%s %s %d", name, category.category, &count);
	price = cal_money(name, count);
	print_buy_check_screen(name, count, price);
	scanf("%s", tmp);
	if (strcmp(tmp, "����") == 0)
	{
		system("cls");
		printf("1. �ù�� �ޱ�(�߰���� �߻� ��� 2����)\n");
		printf("2. ���� ��������\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			system("cls");
			printf("������ ������ �Է����ּ���: ");
			scanf("%s", c.city);
			if (check_City(c) == 0)
				printf("����� �Ұ����� �����Դϴ�.\n���Ű� ��ҵ˴ϴ�.\n");
			else
			{
				print_delivery_screen(c.city);
				scanf("%d", &menu);
				int num = get_City_num(c.city);
				Road tmp;
				switch (menu)
				{
				case 1:
					tmp = get_min_dis_Road(num);
					break;
				case 2:
					tmp = get_min_cost_Road(num);
					break;
				case 3:
					tmp = get_min_time_Road(num);
					break;
				}
				buy_product(name, category.category, count, price + tmp.cost, 1);
				printf("���Ű� �Ϸ� �Ǿ����ϴ�.\n");
			}
			break;
		case 2:
			buy_product(name, category.category, count, price, 0);
			printf("���Ű� �Ϸ� �Ǿ����ϴ�.\n");
			break;
		}
	}
	else
	{
		printf("���Ÿ� ����ϼ̽��ϴ�.\n");
	}
}

// �Ƹ� �簢���� Ʋ�� ����ϴ� �Լ�
void Rec() {
	int i;
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");
	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��");
}

// ������ Ű ���� �޴�
void key_menu()
{
	char key[20];

	system("cls");
	printf(" \n");
	printf("%41s<<������ Ű ���� >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("������ Ű�� �Է��Ͻÿ�: ");
	scanf("%s", key);
	reset_manager_key(key);
	system("cls");
	printf(" \n");
}

// ������ ������ �Է¹޴� �Լ�
Product resist(char* str)
{
	Product res;

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("ī�װ�: ");
	scanf("%s", res.category);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("��ǰ�̸�: ");
	scanf("%s", res.name);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("����: ");
	scanf("%d", &res.price);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("���: ");
	scanf("%d", &res.count);
	return res;
}

// ���� ���� �޴�
void stuff_menu()
{
	int i, menu_num;
	system("cls");
	printf(" \n");
	printf("%38s", "");
	printf("<< ���� ���� >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "1. ���� ���");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "2. ���� ����");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "3. ���� ����");
	printf("%20s��", "");


	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");
	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%15s", "");
	printf("�Է�:");
	printf("%30s��", "");
	printf("\n%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��");
	GotoXY(42, 14);
	scanf("%d", &menu_num);

	if (menu_num == 1) {
		Product new_p = resist("���� ���");
		if (add_new_Product(new_p) == 0)
			printf("������ ���������� ��� �Ǿ����ϴ�.\n");
		else
			printf("�̹� ���� ������ �ֽ��ϴ�.\n");
	}
	else if (menu_num == 2)
	{
		Product old = resist("������ ����");
		Product new_p = resist("���ο� ����");
		if (modify_Product(old, new_p) == 0)
			printf("���������� �����Ǿ����ϴ�.\n");
		else
			printf("���� ������ �ְų� �߸��� �����Դϴ�.\n");
	}
	else if (menu_num == 3)
	{
		Product del_p = resist("���� ����");
		if (delete_Product(del_p) == 0)
			printf("���������� �����Ǿ����ϴ�.\n");
		else
			printf("�̹� ���� �Ǿ��ų� ���� �����Դϴ�.\n");
	}
}

// ������ ������ �Է¹޴� �Լ�
Road road_resist(char* str) {
	Road res;

	system("cls");
	printf(" \n");
	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("��� ����: ");
	scanf("%s", res.start);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("���� ����: ");
	scanf("%s", res.arrival);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("�Ÿ�: ");
	scanf("%d", &res.km);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("���: ");
	scanf("%d", &res.cost);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("�ð�: ");
	scanf("%d", &res.time);
	system("cls");
	return res;
}

// ���ΰ��� �޴�
void road_menu() {
	int i, menu_num;
	system("cls");
	printf(" \n");
	printf("%38s", "");
	printf("<< ���� ���� >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "1. ���� ���");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "2. ���� ����");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "3. ���� ����");
	printf("%20s��", "");


	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");
	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%15s", "");
	printf("�Է�:");
	printf("%30s��", "");
	printf("\n%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��");
	GotoXY(42, 14);
	scanf("%d", &menu_num);

	if (menu_num == 1) {
		Road r = road_resist("���ǵ��");
		if (add_new_Road(r) == 0)
			printf("���������� ��� �Ǿ����ϴ�.\n");
		else
			printf("�̹� ���� ���ΰ� �ֽ��ϴ�.\n");
	}
	else if (menu_num == 2) {
		Road old = road_resist("�����ҵ���");
		Road new_p = road_resist("���ο��");
		if (modifyRoad(old, new_p) == 0)
			printf("���������� ���ΰ� �����Ǿ����ϴ�.\n");
		else
			printf("���θ� �������� ���߽��ϴ�.\n");
	}
	else if (menu_num == 3)
	{
		Road del_p = road_resist("���ο��");
		if (deleteRoad(del_p) == 0)
			printf("���������� ���ΰ� �����Ǿ����ϴ�.\n");
		else
			printf("���θ� �������� ���߽��ϴ�.\n");
	}
}

// ������ ������ �Է¹޴� �Լ�
City city_resist(char* str) {
	City res;

	system("cls");
	printf(" \n");
	printf("%41s<<%s>>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("���� �̸�: ");
	scanf("%s", res.city);

	system("cls");
	return res;
}

// �������� �޴�
void location_menu() {
	int i, menu_num;
	system("cls");
	printf(" \n");
	printf("%38s", "");
	printf("<< ���� ���� >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "1. ���� ���");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "2. ���� ����");
	printf("%20s��", "");

	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%30s", "3. ���� ����");
	printf("%20s��", "");


	printf("\n%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");

	printf("%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��\n");
	printf("%20s", "");
	printf("��%50s��\n", "");
	printf("%20s", "");
	printf("��%15s", "");
	printf("�Է�:");
	printf("%30s��", "");
	printf("\n%20s", "");
	printf("��%50s��", "");
	printf("\n%20s", "");
	printf("��");
	for (i = 0; i < 50; i++)
	{
		printf("��");
	}
	printf("��");
	GotoXY(42, 14);
	scanf("%d", &menu_num);

	if (menu_num == 1)
	{
		City c = city_resist("�������");
		if (add_new_City(c) == 0)
			printf("���������� ��� �Ǿ����ϴ�.\n");
		else
			printf("��Ͽ� �����Ͽ����ϴ�.\n");
	}
	if (menu_num == 2)
	{
		City c = city_resist("����������");
		City c2 = city_resist("�ٲ� �̸�");
		if (modifyCity(c,c2) == 0)
			printf("���������� ���� �Ǿ����ϴ�.\n");
		else
			printf("������ �����Ͽ����ϴ�.\n");
	}
	if (menu_num == 3)
	{
		City c = city_resist("��������");
		if (deleteCity(c) == 0)
			printf("���������� ���� �Ǿ����ϴ�.\n");
		else
			printf("������ �����Ͽ����ϴ�.\n");
	}
}

//������ �޴�
void admin_menu()
{
	int i, menu_num;

	while (1)
	{
		system("cls");
		printf(" \n");
		printf("%31s", "");
		printf("<< ������ ���α׷� ������ ��� >>\n");
		printf(" \n");
		printf("%20s", "");
		printf("��");
		for (i = 0; i < 50; i++)
		{
			printf("��");
		}
		printf("��\n");

		printf("%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%30s", "1. ���� ����");
		printf("%20s��", "");

		printf("\n%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%30s", "2. ���� ����");
		printf("%20s��", "");

		printf("\n%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%30s", "3. ���� ����");
		printf("%20s��", "");

		printf("\n%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%35s", "4. �Ǹ� ���� Ȯ��");
		printf("%15s��", "");

		printf("\n%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%35s", "5. ������ Ű ����");
		printf("%15s��", "");

		printf("\n%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%25s", "6. ����");
		printf("%25s��", "");

		printf("\n%20s", "");
		printf("��");
		for (i = 0; i < 50; i++)
		{
			printf("��");
		}
		printf("��\n");

		printf("%20s", "");
		printf("��");
		for (i = 0; i < 50; i++)
		{
			printf("��");
		}
		printf("��\n");
		printf("%20s", "");
		printf("��%50s��\n", "");
		printf("%20s", "");
		printf("��%15s", "");
		printf("�Է�:");
		printf("%30s��", "");
		printf("\n%20s", "");
		printf("��%50s��", "");
		printf("\n%20s", "");
		printf("��");
		for (i = 0; i < 50; i++)
		{
			printf("��");
		}
		printf("��");
		GotoXY(42, 19);
		scanf("%d", &menu_num);

		if (menu_num == 1) {
			stuff_menu();
		}
		else if (menu_num == 2) {
			location_menu();
		}
		else if (menu_num == 3) {
			road_menu();
		}
		else if (menu_num == 4) {
			//sales_menu();
		}
		else if (menu_num == 5) {
			key_menu();
		}
		else if (menu_num == 6)
		{
			system("cls");
			printf("�����մϴ�.\n");
			break;
		}
		_getch();
	}
}

//������ ��й�ȣ üũ�ϴ� ȭ��
static void menu_maneger()
{
	char key[20];
	int res = 0;
	system("cls");
	printf("��й�ȣ�� �Է��ϼ���: ");
	scanf("%s", key);
	if (check_manager_key(key) == 0)
	{
		admin_menu();
	}
	else
	{
		printf("��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
	}
}

//�ϳ��� ���α׷����� ��ģ �Լ�
void store_program(void)
{
	int menu = 0;
	
	print_user_ui();
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:// ���� ����
		menu_1();
		break;
	case 2:// ���� �˻�
		menu_2();
		break;
	case 4://������ ���°�
		menu_maneger();
		break;
	default:
		break;
	}
}