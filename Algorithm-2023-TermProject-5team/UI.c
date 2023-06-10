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
		printf("<< 편의점 프로그램 관리자 모드 >>\n");
		printf(" \n");
		printf("%20s", "");
		printf("┌");
		for (i = 0; i < 50; i++)
		{
			printf("─");
		}
		printf("┐\n");

		printf("%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%30s", "1. 물건 관리");
		printf("%20s│", "");

		printf("\n%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%30s", "2. 지역 관리");
		printf("%20s│", "");

		printf("\n%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%30s", "3. 도로 관리");
		printf("%20s│", "");

		printf("\n%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%35s", "4. 판매 내역 확인");
		printf("%15s│", "");

		printf("\n%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%35s", "5. 관리자 키 변경");
		printf("%15s│", "");

		printf("\n%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("└");
		for (i = 0; i < 50; i++)
		{
			printf("─");
		}
		printf("┘\n");

		printf("%20s", "");
		printf("┌");
		for (i = 0; i < 50; i++)
		{
			printf("─");
		}
		printf("┐\n");
		printf("%20s", "");
		printf("│%50s│\n", "");
		printf("%20s", "");
		printf("│%15s", "");
		printf("입력:");
		printf("%30s│", "");
		printf("\n%20s", "");
		printf("│%50s│", "");
		printf("\n%20s", "");
		printf("└");
		for (i = 0; i < 50; i++)
		{
			printf("─");
		}
		printf("┘");
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
	printf("<< 물건 관리 >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");

	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "1. 물건 등록");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "2. 물건 수정");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "3. 물건 삭제");
	printf("%20s│", "");


	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘\n");

	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");
	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%15s", "");
	printf("입력:");
	printf("%30s│", "");
	printf("\n%20s", "");
	printf("│%50s│", "");
	printf("\n%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘");
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
	printf("<< 지역 관리 >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");

	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "1. 지역 등록");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "2. 지역 수정");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "3. 지역 삭제");
	printf("%20s│", "");


	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘\n");

	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");
	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%15s", "");
	printf("입력:");
	printf("%30s│", "");
	printf("\n%20s", "");
	printf("│%50s│", "");
	printf("\n%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘");
	GotoXY(42, 14);
	scanf("%d", &menu_num);
}

void road_menu() {
	int i, menu_num;
	system("cls");
	printf(" \n");
	printf("%38s", "");
	printf("<< 도로 관리 >>\n");
	printf(" \n");
	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");

	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "1. 도로 등록");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "2. 도로 수정");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "3. 도로 삭제");
	printf("%20s│", "");


	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘\n");

	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");
	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%15s", "");
	printf("입력:");
	printf("%30s│", "");
	printf("\n%20s", "");
	printf("│%50s│", "");
	printf("\n%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘");
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
	printf("%41s<< 등록 >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("카테고리: ");
	scanf("%s", category);
	system("cls");
	printf(" \n");
	printf("%41s<< 등록 >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("상품이름: ");
	scanf("%s", stuff_name);
	system("cls");
	printf(" \n");
	printf("%41s<< 등록 >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("가격: ");
	scanf("%s", price);


}

void Rec() {
	int i;
	printf("%20s", "");
	printf("┌");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┐\n");
	printf("%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%50s│", "");
	printf("\n%20s", "");
	printf("│%50s│", "");
	printf("\n%20s", "");
	printf("└");
	for (i = 0; i < 50; i++)
	{
		printf("─");
	}
	printf("┘");
}