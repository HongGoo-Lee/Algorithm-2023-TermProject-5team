#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int test_ui(void) {

    int i, category;
    // 네모박스 안의 카테고리를 동적으로 설정하기 위한 배열을 설정 

    char categories[9][20] = {
        "전체",
        "과자",
        "음료수",
        "간편식품",
        "요리",
        "아이스크림",
        "생활잡화",
        "컵라면",
        "택배"
    };

    printf("%20s", "");
    printf("┌");
    for (i = 0; i < 50; i++) {
        printf("─");
    }
    printf("┐\n");
    printf("%20s", "");
    printf("│%50s│\n", "");
    printf("%20s", "");
    printf("│%33s", "      	－O－ 편의점 프로그램－O－");
    printf("%13s│", "");
    printf("%20s", "\n");
    printf("%20s", "");
    printf("├");
    for (i = 0; i < 50; i++) {
        printf("─");
    }
    printf("┤\n");

    printf("%20s", "");
    printf("│");

    printf("%5s", "");
    printf("┌");
    for (i = 0; i < 7; i++) {
        printf("─");
    }
    printf("┬");
    for (i = 0; i < 33; i++) {
        printf("─");
    }
    printf("┐");

    printf("%2s", "");

    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%5s", "");
    printf("│ 입  력  │");
    printf("%33s", "");
    printf("│");


    printf("%2s", "");

    printf("│\n");

    printf("%20s", "");
    printf("│");

    printf("%5s", "");
    printf("└");
    for (i = 0; i < 7; i++) {
        printf("─");
    }
    printf("┴");
    for (i = 0; i < 33; i++) {
        printf("─");
    }
    printf("┘");
    printf("%2s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%50s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%4s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");
    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");


    printf("%4s", "");
    printf("│   %s", categories[0]);
    printf("%3s", "");
    printf("│");
    printf("%3s", "");
    printf("│   %s", categories[1]);
    printf("%3s", "");
    printf("│");
    printf("%3s", "");
    printf("│  %s", categories[2]);
    printf("%2s", "");
    printf("│");
    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");
    printf("%4s", "");
    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");
    printf("%50s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%4s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");
    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");


    printf("%4s", "");
    printf("│   %s", categories[3]);
    printf("%1s", "");
    printf("│");
    printf("%3s", "");
    printf("│   %s", categories[4]);
    printf("%3s", "");
    printf("│");
    printf("%3s", "");
    printf("│ %s", categories[5]);
    printf("%s", "");
    printf("│");
    printf("%4s", "");
    printf("│\n");


    printf("%20s", "");
    printf("│");
    printf("%4s", "");
    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");
    printf("%50s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%4s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%3s", "");

    printf("┌");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┐");

    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");


    printf("%4s", "");
    printf("│   %s", categories[6]);
    printf("%3s", "");
    printf("│");
    printf("%3s", "");
    printf("│ %s", categories[7]);
    printf("%3s", "");
    printf("│");
    printf("%3s", "");
    printf("│ %s", categories[8]);
    printf("%2s", "");
    printf("│");
    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");
    printf("%4s", "");
    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%3s", "");

    printf("└");
    for (i = 0; i < 10; i++) {
        printf("─");
    }
    printf("┘");

    printf("%4s", "");
    printf("│\n");

    printf("%20s", "");
    printf("│");
    printf("%50s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│");
    printf("%50s", "");
    printf("│\n");
    printf("%20s", "");
    printf("│%50s│\n", "");
    printf("%20s", "");
    printf("└");
    for (i = 0; i < 50; i++) {
        printf("─");
    }
    printf("┘\n");



    GotoXY(36, 5);
    scanf_s("%d", &category);

    system("cls");
    print_items(category - 1);

    return 0;
}