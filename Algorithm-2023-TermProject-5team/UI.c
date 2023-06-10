#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void print_admin_menu();
void stuff_menu();
void location_menu();
void road_menu();
void sales_menu();
void key_menu();
void Rec();
void resist();

void print_admin_menu()
{
	int i, menu_num;

	while (1) {
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
		GotoXY(42, 18);
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
			sales_menu();
		}
		else if (menu_num == 5) {
			key_menu();
		}
		else {
			continue;
		}
	}
}

void stuff_menu() {
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
		resist();
	}
}

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
}

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
}

void sales_menu() {


}

void key_menu() {

}

void resist() {
	char category[20];
	char stuff_name[20];
	char price[20];

	system("cls");
	printf(" \n");
	printf("%41s<< ��� >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("ī�װ�: ");
	scanf("%s", category);
	system("cls");
	printf(" \n");
	printf("%41s<< ��� >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("��ǰ�̸�: ");
	scanf("%s", stuff_name);
	system("cls");
	printf(" \n");
	printf("%41s<< ��� >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("����: ");
	scanf("%s", price);


}

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