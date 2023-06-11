#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "file_input_output.h"
#include "floyd.h"

//좌표이동 함수
void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 카테고리출력 화면의 틀
void print_category_screen_frame(void)
{
	system("cls");
	int i;
	printf("%20s┌", "");
	for (i = 0; i < 50; i++) {
		printf("─");
	}
	printf("┐\n");
	for (i = 0; i < 2; i++)
		printf("%20s│%50s│\n", "", "");

	printf("%20s├", "");
	for (i = 0; i < 50; i++) {
		printf("─");
	}
	printf("┤\n");
	for(i=0;i<20;i++)
		printf("%20s│%50s│\n", "", "");
	printf("%20s└","");
	for (i = 0; i < 50; i++) {
		printf("─");
	}
	printf("┘\n");
}

// 사각형과 그 사각형 안에 문자열을 넣어 출력하는 함수
void print_square(int x, int y, char* msg)
{
	GotoXY(x, y);
	printf("┌");
	for (int i = 0; i < 10; i++)
		printf("─");
	printf("┐");
	GotoXY(x, y + 1);
	printf("│%10s│", msg);
	GotoXY(x, y + 2);
	printf("└");
	for (int i = 0; i < 10; i++)
		printf("─");
	printf("┘");
}

//입력창을 출력하는 함수
void print_input_square(int x, int y)
{
	GotoXY(x, y );
	printf("┌");
	for (int i = 0; i < 8; i++)
		printf("─");
	printf("┬");
	for (int i = 0; i < 31; i++)
		printf("─");
	printf("┐");
	GotoXY(x, y + 1);
	printf("│  입 력 │%31s│","");
	GotoXY(x, y + 2);
	printf("└");
	for (int i = 0; i < 8; i++)
		printf("─");
	printf("┴");
	for (int i = 0; i < 31; i++)
		printf("─");
	printf("┘");
	GotoXY(x+12, y+1);
}

// 카테고리 출력하는 함수
void print_category_screen()
{
	system("cls");
	print_category_screen_frame();

	GotoXY(40, 1);
	printf("<<물건 구매>>");

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

// 프로그램 초기화면
void print_user_ui()
{
	int i = 0;
	printf(" \n");
	printf("%36s", "");
	printf("<< 편의점 프로그램 >>\n");
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
	printf("│%30s", "1. 물건 구매");
	printf("%20s│", "");

	printf("\n%20s", "");
	printf("│%50s│\n", "");
	printf("%20s", "");
	printf("│%30s", "2. 물건 검색");
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
	GotoXY(42, 12);
}

//물건 목록을 출력하는 함수
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
		printf("제품명: %s, 카테고리: %s, 가격: %d원 재고: %d\n", p[i].name, p[i].category, p[i].price, p[i].count);
	}
	print_input_square(25, 19);
}

// 구매 확인 화면
void print_buy_check_screen(char* name, int count, int price)
{
	print_category_screen_frame();
	GotoXY(40, 1);
	printf("<<물건 구매>>");
	GotoXY(30, 5);
	printf("제품명: %s", name);
	GotoXY(30, 7);
	printf("개 수: %d", count);
	GotoXY(30, 9);
	printf("가 격: %d", price);
	print_square(30, 13,"구매");
	print_square(42, 13, "취소");
	print_input_square(25, 18);
} 

// 배달여부 출력하는 함수
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
	printf("1. 최단경로 거리: %d, 비용: %d, 시간: %d시간 %d분 %d초\n", min_dis.km, min_dis.cost, hour, min, sec);
	
	hour = min_dis.cost / 3600;
	min = (min_dis.cost % 3600) / 60;
	sec = (min_dis.cost % 3600) % 60;
	printf("2. 최단비용 거리: %d, 비용: %d, 시간: %d시간 %d분 %d초\n", min_cost.km, min_cost.cost, hour, min, sec);
	
	hour = min_time.time / 3600;
	min = (min_time.time % 3600) / 60;
	sec = (min_time.time % 3600) % 60;
	printf("3. 최단시간 거리: %d, 비용: %d, 시간: %d시간 %d분 %d초\n", min_time.km, min_time.cost, hour, min, sec);
}

// 물건구매 함수
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
	if (strcmp(tmp, "구매") == 0)
	{
		system("cls");
		printf("1. 택배로 받기(추가비용 발생 평균 2만원)\n");
		printf("2. 직접 가져가기\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			printf("본인의 지역을 입력해주세요: ");
			scanf("%s", c.city);
			if (check_City(c) == 0)
				printf("배송이 불가능한 지역입니다.\n구매가 취소됩니다.\n");
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
				printf("구매가 완료 되었습니다.\n");
			}
			break;
		case 2:
			buy_product(name, category.category, count, price, 0);
			printf("구매가 완료 되었습니다.\n");
			break;
		}
	}
	else
	{
		printf("구매를 취소하셨습니다.\n");
	}
}

// 검색한 단어가 들어있는 물건들을 출력하는 함수
void print_search_list(void)
{
	char str[41];
	system("cls");
	print_category_screen_frame();

	GotoXY(40, 1);
	printf("<<물건 검색>>");

	print_input_square(25, 5);
	scanf("%s", str);
	Product* p = search_Product(str);
	system("cls");

	GotoXY(40, 1);
	printf("<<%s 검색결과>>", str);
	GotoXY(35, 2);
	printf("구매할시 제품명, 카테고리, 개수를 적을것");
	for (int i = 0; i < search_Product_count(str); i++)
	{
		GotoXY(25, 5 + i * 2);
		printf("제품명: %s, 카테고리: %s, 가격: %d원 재고: %d\n", p[i].name, p[i].category, p[i].price, p[i].count);
	}
	print_input_square(25, 19);
}

// 물건 검색 함수
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
	if (strcmp(tmp, "구매") == 0)
	{
		system("cls");
		printf("1. 택배로 받기(추가비용 발생 평균 2만원)\n");
		printf("2. 직접 가져가기\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			system("cls");
			printf("본인의 지역을 입력해주세요: ");
			scanf("%s", c.city);
			if (check_City(c) == 0)
				printf("배송이 불가능한 지역입니다.\n구매가 취소됩니다.\n");
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
				printf("구매가 완료 되었습니다.\n");
			}
			break;
		case 2:
			buy_product(name, category.category, count, price, 0);
			printf("구매가 완료 되었습니다.\n");
			break;
		}
	}
	else
	{
		printf("구매를 취소하셨습니다.\n");
	}
}

// 아마 사각형의 틀을 출력하는 함수
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

// 관리자 키 변경 메뉴
void key_menu()
{
	char key[20];

	system("cls");
	printf(" \n");
	printf("%41s<<관리자 키 변경 >>\n", "");
	Rec();
	GotoXY(30, 4);
	printf("관리자 키를 입력하시오: ");
	scanf("%s", key);
	reset_manager_key(key);
	system("cls");
	printf(" \n");
}

// 물건의 정보를 입력받는 함수
Product resist(char* str)
{
	Product res;

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("카테고리: ");
	scanf("%s", res.category);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("상품이름: ");
	scanf("%s", res.name);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("가격: ");
	scanf("%d", &res.price);

	system("cls");
	printf(" \n");
	printf("%41s<< %s >>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("재고: ");
	scanf("%d", &res.count);
	return res;
}

// 물건 관리 메뉴
void stuff_menu()
{
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
		Product new_p = resist("물건 등록");
		if (add_new_Product(new_p) == 0)
			printf("물건이 정상적으로 등록 되었습니다.\n");
		else
			printf("이미 같은 물건이 있습니다.\n");
	}
	else if (menu_num == 2)
	{
		Product old = resist("수정할 물건");
		Product new_p = resist("새로운 물건");
		if (modify_Product(old, new_p) == 0)
			printf("정상적으로 수정되었습니다.\n");
		else
			printf("같은 물건이 있거나 잘못된 정보입니다.\n");
	}
	else if (menu_num == 3)
	{
		Product del_p = resist("물건 삭제");
		if (delete_Product(del_p) == 0)
			printf("정상적으로 삭제되었습니다.\n");
		else
			printf("이미 삭제 되었거나 없는 물건입니다.\n");
	}
}

// 도로의 정보를 입력받는 함수
Road road_resist(char* str) {
	Road res;

	system("cls");
	printf(" \n");
	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("출발 지역: ");
	scanf("%s", res.start);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("도착 지역: ");
	scanf("%s", res.arrival);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("거리: ");
	scanf("%d", &res.km);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("비용: ");
	scanf("%d", &res.cost);

	printf("%41s<<%s>>\n", "",str);
	Rec();
	GotoXY(30, 4);
	printf("시간: ");
	scanf("%d", &res.time);
	system("cls");
	return res;
}

// 도로관리 메뉴
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

	if (menu_num == 1) {
		Road r = road_resist("물건등록");
		if (add_new_Road(r) == 0)
			printf("정상적으로 등록 되었습니다.\n");
		else
			printf("이미 같은 도로가 있습니다.\n");
	}
	else if (menu_num == 2) {
		Road old = road_resist("수정할도로");
		Road new_p = road_resist("새로운도로");
		if (modifyRoad(old, new_p) == 0)
			printf("정상적으로 도로가 수정되었습니다.\n");
		else
			printf("도로를 수정하지 못했습니다.\n");
	}
	else if (menu_num == 3)
	{
		Road del_p = road_resist("새로운도로");
		if (deleteRoad(del_p) == 0)
			printf("정상적으로 도로가 삭제되었습니다.\n");
		else
			printf("도로를 삭제하지 못했습니다.\n");
	}
}

// 지역의 정보를 입력받는 함수
City city_resist(char* str) {
	City res;

	system("cls");
	printf(" \n");
	printf("%41s<<%s>>\n", "", str);
	Rec();
	GotoXY(30, 4);
	printf("지역 이름: ");
	scanf("%s", res.city);

	system("cls");
	return res;
}

// 지역관리 메뉴
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

	if (menu_num == 1)
	{
		City c = city_resist("지역등록");
		if (add_new_City(c) == 0)
			printf("정상적으로 등록 되었습니다.\n");
		else
			printf("등록에 실패하였습니다.\n");
	}
	if (menu_num == 2)
	{
		City c = city_resist("수정할지역");
		City c2 = city_resist("바꿀 이름");
		if (modifyCity(c,c2) == 0)
			printf("정상적으로 수정 되었습니다.\n");
		else
			printf("수정에 실패하였습니다.\n");
	}
	if (menu_num == 3)
	{
		City c = city_resist("지역삭제");
		if (deleteCity(c) == 0)
			printf("정상적으로 삭제 되었습니다.\n");
		else
			printf("삭제에 실패하였습니다.\n");
	}
}

//관리자 메뉴
void admin_menu()
{
	int i, menu_num;

	while (1)
	{
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
		printf("│%25s", "6. 종료");
		printf("%25s│", "");

		printf("\n%20s", "");
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
			printf("종료합니다.\n");
			break;
		}
		_getch();
	}
}

//관리자 비밀번호 체크하는 화면
static void menu_maneger()
{
	char key[20];
	int res = 0;
	system("cls");
	printf("비밀번호를 입력하세요: ");
	scanf("%s", key);
	if (check_manager_key(key) == 0)
	{
		admin_menu();
	}
	else
	{
		printf("비밀번호가 틀렸습니다.\n");
	}
}

//하나의 프로그램으로 합친 함수
void store_program(void)
{
	int menu = 0;
	
	print_user_ui();
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:// 물건 구매
		menu_1();
		break;
	case 2:// 물건 검색
		menu_2();
		break;
	case 4://관리자 들어가는거
		menu_maneger();
		break;
	default:
		break;
	}
}