#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "floyd.h"

//같은 카테고리가 파일에 있는지 확인하는 함수
int check_Category(Category c)
{
    char str[21];
    int res = 0;
    FILE* fp = fopen("카테고리목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", str);
        if (strcmp(c.category, str) == 0)
        {
            res = 1;// 있으면 1
            break;
        }
    }
    return res;
}

//카테고리의 수를 반환하는 함수
int get_Category_count(void)
{
    char str[41];
    int res = 0;
    FILE* fp = fopen("카테고리목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", str);
        res++;
    }
    return res;
}

//새로운 카테고리를 추가하는 함수
int add_new_Category(Category c)
{
    if (check_Category(c) == 0)
    {
        FILE* fp = fopen("카테고리목록.txt", "a");
        fprintf(fp, "%s\n", c.category);
        fclose(fp);
        return 0;//정상작동
    }
    else
        return 1;//이미 같은그게 있음
}

//카테고리 목록을 배열로 반환하는 함수
Category* get_Category_list(void)
{
    int i = 0, size = get_Category_count();
    Category* res = (Category*)calloc(size, sizeof(Category));
    FILE* fp = fopen("카테고리목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", res[i++].category);
    }
    return res;
}

// 물건의 이름을 입력하면 그 물건의 모든 정보를 구조체로 만들어서 반환하는 함수
Product get_Product(char* name)
{
    Product p;
    int soldCount, del;
    FILE* fp = fopen("물건목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(p.name, name) == 0)
        {
            break;
        }
    }
    return p;
}

//물건 재고를 반환하는 함수
int get_product_stock(char* name)
{
    FILE* fp = fopen("물건목록.txt", "r");
    Product p;
    int soldCount, del, res = -1;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(name, p.name) == 0)
        {
            res = p.count;
            break;
        }
    }
    return res;
}

//현재 등록된 편의점 물건의 수를 반환하는 함수
int get_product_count(char* category)
{
    FILE* fp = fopen("물건목록.txt", "r");
    char name[41], category1[21];
    int price, count, soldCount, del=1, size = 0;
    if (strcmp(category, "전체") == 0)
    {
        printf("전체\n");
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", name, category1, &price, &count, &soldCount, &del);
            printf("name = %s, del = %d\n", name, del);
            if (del == 0)
                size++;
        }
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", name, category1, &price, &count, &soldCount, &del);
            if (strcmp(category, category1) == 0 && del == 0)
                size++;
        }
    }
    
    fclose(fp);
    return size;
}

// 입력된 데이터를 Product 구조체로 만들어주는 함수
Product get_struct_product(char* name, char* category, int price, int count)
{
    Product res;
    strcpy(res.category, category);
    strcpy(res.name, name);
    res.count = count;
    res.price = price;

    return res;
}

// 물건 목록을 1차원 배열로 만들어 반환하는 함수
Product* get_product_list(char* category)
{
    FILE* fp = fopen("물건목록.txt", "r");
    char name[41], category1[21];
    int price, count, soldCount, del, size, i = 0;
    size = get_product_count(category);
    Product* res = (Product*)calloc(size, sizeof(Product));
    if (strcmp(category, "전체") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", name, category1, &price, &count, &soldCount, &del);
            if (del == 0)
                res[i++] = get_struct_product(name, category1, price, count);
        }
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", name, category1, &price, &count, &soldCount, &del);
            if (strcmp(category, category1) == 0 && del == 0)
            {
                res[i++] = get_struct_product(name, category1, price, count);
            }
        }
    }

    fclose(fp);
    return res;
}

// 같은 제품이 있는지 확인하는 함수
int check_Product(Product product)
{
    FILE* fp = fopen("물건목록.txt", "r");
    Product p;
    int soldCount, del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(p.name, product.name) == 0)
        {
            res = 1;// 같은 제품이 있음
            break;
        }
    }
    fclose(fp);
    return res;
}

//새로운 제품을 추가하는 함수
int add_new_Product(Product new_p)
{
    int soldCount = 0, del = 0;
    if (check_Product(new_p) == 0)
    {
        FILE* fp = fopen("물건목록.txt", "a");
        fprintf(fp, "%s %s %d %d %d %d\n", new_p.name, new_p.category, new_p.price, new_p.count, soldCount, del);
        fclose(fp);
        Category c;
        strcpy(c.category, new_p.category);
        add_new_Category(c);
        return 0;// 정상작동
    }
    else
    {
        return 1;//이미 같은 제품이 있음
    }
}

//제품 정보 수정하는 함수
int modify_Product(Product old, Product new_p)
{
    FILE* file = fopen("물건목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return 3;
    }

    Product product;
    long int pos;
    int found = 0, del, soldCount, res = 0;

    if (check_Product(old) == 1 && (check_Product(new_p) == 0 || strcmp(old.name,new_p.name)==0))
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s %s %d %d %d %d\n", product.name, product.category, &product.price, &product.count, &soldCount, &del);
            if (strcmp(old.name, product.name) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s %s %d %d %d %d\n", product.name, product.category, product.price, product.count, soldCount, del);
            res = 0;// 정상적으로 수정함
        }
    }
    else if (check_Product(new_p) == 1)
        res = 1;//이미 똑같은 물품이 있음
    else
        res = 2;//정보를 잘못 입력함

    fclose(file);

    return res;
}

//제품을 삭제하는 함수
int delete_Product(Product old)
{
    FILE* file = fopen("물품목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return 3;
    }

    Product p;
    long int pos;
    int found = 0, soldCount = 0, del = 0, res = 0;
    if (check_Product(old) == 1)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
            if (strcmp(old.name, p.name) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos - strlen(p.name) - 1, SEEK_SET);
            fprintf(file, "%s&%s&%d&%d&%d&%d\n", p.name, p.category, p.price, p.count, soldCount, del);
            res = 0;//정상작동
        }
        else
        {
            res = 1;//이미 지워짐
        }
    }
    else
    {
        res = 2;//잘못된 정보를 입력함
    }

    fclose(file);

    return res;
}

// 검색하려는 단어가 포함된 물건의 수를 반환하는 함수
int search_Product_count(char* str)
{
    FILE* fp = fopen("물건목록.txt", "r");
    int res = 0,soldCount,del;
    Product p;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if ((strstr(p.name, str) != NULL) && del == 0)
            res++;
    }
    return res;
}

//검색하려는 단어가 포함된 물건들을 배열로 만들어서 반환하는 함수
Product* search_Product(char* str)
{
    int size = search_Product_count(str), i = 0, soldCount, del;
    Product p;
    Product* res = (Product*)calloc(size, sizeof(Product));
    FILE* fp = fopen("물건목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if ((strstr(p.name, str) != NULL) && del == 0)
        {
            res[i++] = p;
        }
    }
    return res;
}


//지역이 배열에서 몇번째인지 반환하는 함수
int get_City_num(char* c)
{
    FILE* fp = fopen("지역목록.txt", "r");
    int res = 0, del;
    City tmp, c1;
    strcpy(c1.city, c);
    while (!feof(fp))
    {
        fscanf(fp, "%s %d\n", tmp.city, &del);
        if (strcmp(c1.city, tmp.city) == 0)
            break;
        res++;
    }
    fclose(fp);
    return res;
}

//등록된 지역의 수를 반환하는 함수
int get_City_count(void)
{
    FILE* fp = fopen("지역목록.txt", "r");
    City tmp;
    int del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %d\n", tmp.city, &del);
        if (del == 0)
            res++;
    }
    fclose(fp);
    return res;
}

// 등록된 지역을 1차원 배열로 반환하는 함수
City* get_City_list(void)
{
    FILE* fp = fopen("지역목록.txt", "r");
    int i = 0, size = get_City_count(), del = 0;
    City* res = (City*)calloc(size, sizeof(City));
    City tmp;
    while (!feof(fp))
    {
        fscanf(fp, "%s %d\n", tmp.city, &del);
        if (del == 0)
            strcpy(res[i++].city, tmp.city);
    }
    fclose(fp);
    return res;
}

// 지역이 이미 있는 지역인지 확인하는 함수 있으면 1 없으면 0을 반환
int check_City(City city)
{
    FILE* fp = fopen("지역목록.txt", "r");
    City c;
    int del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %d\n", c.city, &del);
        if (strcmp(c.city, city.city) == 0)
        {
            res = 1;
            break;
        }
    }
    fclose(fp);
    return res;
}

//새로운 지역 추가하는 함수
int add_new_City(City new_c)
{
    if (check_City(new_c) == 0)
    {
        FILE* fp = fopen("지역목록.txt", "a");
        fprintf(fp, "%s %d\n", new_c.city, 0);
        fclose(fp);
        return 0;// 정상작동
    }
    else
    {
        return 1; // 이미 같은 지역이 있음
    }
}

//지역 정보 수정하는 함수 조건문에서 조건 수정해야함
int modifyCity(City old, City new_c)
{
    FILE* file = fopen("지역목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return 3;
    }
    City city;
    long int pos;
    int found = 0, del = 0, res = 1;
    if (check_City(old) == 1 && check_City(new_c) == 0)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s %d\n", city.city, &del);
            if (strcmp(old.city, city.city) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s %d\n", new_c.city, del);
            res = 0;// 정상작동
        }
        fclose(file);
    }
    else if (check_City(new_c) == 1)
        res = 1;//이미 똑같은 지역이 있어서 수정 불가능
    else
        res = 2;//바꾸려는 지역정보가 잘못됨

    return res;
}

//지역을 삭제하는 함수
int deleteCity(City old)
{
    FILE* file = fopen("지역목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return 3;
    }

    City city;
    long int pos;
    int found = 0, del = 0, res;

    if (check_City(old) == 1)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s %d\n", city.city, &del);
            if (strcmp(old.city, city.city) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s %d\n", old.city, 1);
            res = 0;
        }
        else
        {
            res = 1;//이미 지움
        }
    }
    else
    {
        res = 2;//삭제하려는 지역이 없음
    }

    fclose(file);

    return res;
}



// 입력받은 정보의 도로 찾아서 반환하는 함수
Road get_Road(char* start, char* arrival)
{
    FILE* fp = fopen("도로목록.txt", "r");
    Road res;
    int del = 0, state = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", res.start, res.arrival, &res.km, &res.cost, &res.time, &del);
        if (strcmp(start, res.start) == 0 && strcmp(arrival, res.arrival) == 0 && del == 0)
        {
            state = 1;
            break;
        }
    }
    if (state == 0)
    {
        strcpy(res.start, start);
        strcpy(res.arrival, arrival);
        res.cost = INF;
        res.km = INF;
        res.time = INF;
    }
    return res;
}

//이미 같은 도로가 있는지 체크 같은 도로가 있으면 1을 반환 없으면 0
int check_Road(Road road)
{
    FILE* fp = fopen("도로목록.txt", "r");
    char start[11], arrival[11];
    int km, cost, time, del;
    int res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", start, arrival, &km, &cost, &time, &del);
        if (strcmp(start, road.start) == 0 && strcmp(arrival, road.arrival) == 0)
        {
            res = 1;
            break;
        }
    }
    fclose(fp);
    return res;
}

//등록된 도로의 개수를 반환하는 함수
int get_Road_count(char* start)
{
    FILE* fp = fopen("도로목록.txt", "r");
    char fstart[11], arrival[11];
    int km, cost, time, del, res = 0;
    if (strcmp(start, "전체") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", fstart, arrival, &km, &cost, &time, &del);
            if (del == 0)
                res++;
        }
        fclose(fp);
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0 && del == 0)
                res++;
        }
        fclose(fp);
    }
    return res;
}

// 입력된 데이터를 Road구조체로 만들어주는 함수
Road make_struct_Road(char* start, char* arrival, int km, int cost, int time)
{
    Road res;
    strcpy(res.start, start);
    strcpy(res.arrival, arrival);
    res.km = km;
    res.time = time;
    res.cost = cost;

    return res;
}

// 도로목록을 1차원 배열로 만들어서 반환하는 함수
Road* get_Road_list(char* start)
{
    int size = get_Road_count(start);
    Road* res = (Road*)calloc(size, sizeof(Road));
    char fstart[11], arrival[11];
    int km, cost, time, del;
    int i = 0;
    FILE* fp = fopen("도로목록.txt", "r");
    if (strcmp(start, "전체") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", fstart, arrival, &km, &cost, &time, &del);
            if (del == 0)
                res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
        }
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s %d %d %d %d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0 && del == 0)
            {
                res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
            }
        }
    }
    fclose(fp);
    return res;
}

//새로운 도로를 등록하는 함수
//출발지점이 같은 도로끼리 연속되게 저장함
//가나다 정렬은 못함
int add_new_Road(Road new_r)
{
    FILE* fp1 = NULL;
    FILE* tmp = NULL;
    City c1,c2;
    strcpy(c1.city, new_r.start);
    strcpy(c2.city, new_r.arrival);
    if (check_City(c1) == 1 && check_City(c2) == 1)
    {
        if (check_Road(new_r) == 0)
        {
            fp1 = fopen("도로목록.txt", "r");
            tmp = fopen("temp.txt", "w");
            char start[11], arrival[11];
            int km, cost, time, del = 0, new_del = 0;
            while (!feof(fp1))
            {
                fscanf(fp1, "%s %s %d %d %d %d\n", start, arrival, &km, &cost, &time, &del);
                fprintf(tmp, "%s %s %d %d %d %d\n", start, arrival, km, cost, time, del);
            }
            fclose(fp1);
            fclose(tmp);
            int state = 0;
            fp1 = fopen("도로목록.txt", "w");
            tmp = fopen("temp.txt", "r");
            while (!feof(tmp))
            {
                fscanf(tmp, "%s %s %d %d %d %d\n", start, arrival, &km, &cost, &time, &del);
                if (strcmp(start, new_r.start) == 0 && state == 0)
                {
                    fprintf(fp1, "%s %s %d %d %d %d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, new_del);
                    state = 1;
                }
                fprintf(fp1, "%s %s %d %d %d %d\n", start, arrival, km, cost, time, del);
            }
            if (state == 0)
                fprintf(fp1, "%s %s %d %d %d %d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, new_del);
            fclose(fp1);
            fclose(tmp);

            return 0;//정상작동
        }
        else
            return 1;// 이미 같은정보의 도로가 있음
    }
    else
        return 2;// 없는 지역임
}

// 도로 수정하는 함수
int modifyRoad(Road old, Road new_r) {
    FILE* file = fopen("도로목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return 3;
    }

    Road edge;
    long pos;
    int del = 0, res = 0;
    if (check_Road(old) == 1 && ((strcmp(old.start, new_r.start) == 0 && strcmp(old.arrival, new_r.arrival) == 0) || (check_Road(new_r) == 0)))
    {
        while (!feof(file)) {
            pos = ftell(file);
            fscanf(file, "%s %s %d %d %d %d\n", edge.start, edge.arrival, &edge.km, &edge.cost, &edge.time, &del);
            if (strcmp(old.start, edge.start) == 0 && strcmp(old.arrival, edge.arrival) == 0 && del == 0) {
                fseek(file, pos, SEEK_SET);
                fprintf(file, "%s %s %d %d %d %d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, 0);
                break;
            }
        }
        res = 0;//정상적으로 수정함
    }
    else if (check_Road(new_r))
    {
        res = 2;//같은 도로가 이미 있어서 수정 불가능
    }
    else
    {
        res = 1;//수정하려는 도로가 없음
    }
    fclose(file);

    return res;
}

//도로 삭제하는 함수 del값만 1로 바꿈
int deleteRoad(Road delRoad)
{
    int res = 0;
    if (check_Road(delRoad) == 1)
    {
        FILE* fp = fopen("도로목록.txt", "r+");
        Road edge;
        long pos;
        int del, found = 0;
        while (!feof(fp))
        {
            pos = ftell(fp);
            fscanf(fp, "%s %s %d %d %d %d\n", edge.start, edge.arrival, &edge.km, &edge.cost, &edge.time, &del);
            if (strcmp(delRoad.start, edge.start) == 0 && strcmp(delRoad.arrival, edge.arrival) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%s %s %d %d %d %d\n", delRoad.start, delRoad.arrival, delRoad.km, delRoad.cost, delRoad.time, 1);
            res = 0;//정상
        }
        else
            res = 2;//이미 지움
        fclose(fp);
    }
    else
    {
        res = 1;// 입력한 정보의 도로가 없음
    }

    return res;
}



// 판매내역 기록하는 함수
void add_new_SoldData(SoldData new_s)
{
    FILE* fp = fopen("판매내역.txt", "a");
    fprintf(fp, "%s %s %d %d %d %d %d %d %d\n", new_s.name, new_s.category, new_s.count, new_s.soldDate.year, new_s.soldDate.month, new_s.soldDate.day, new_s.money, new_s.delivery, new_s.del);
    fclose(fp);
}

// 입력된 데이터를 Date 구조체로 만들어주는 함수
Date make_struct_Date(int year, int month, int day)
{
    Date res;
    res.day = day;
    res.month = month;
    res.year = year;

    return res;
}

// 입력된 데이터를 SoldData 구조체로 만들어주는 함수
SoldData make_struct_SoldData(char* name, char* category, int count, int year, int month, int day, int money, int delivery, int del)
{
    SoldData res;
    res.soldDate = make_struct_Date(year, month, day);
    strcpy(res.category, category);
    strcpy(res.name, name);
    res.del = del;
    res.delivery = delivery;
    res.count = count;
    res.money = money;

    return res;
}

// 판매내역의 수를 반환하는 함수
int get_soldData_count(void)
{
    char name[41], category[21];
    int count, year, month, day, money, delivery,res = 0, del;
    FILE* fp = fopen("판매내역.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d %d %d %d\n", name, category, &count, &year, &month, &day, &money, &delivery, &del);
        res++;
    }
    fclose(fp);
    return res;
}

// 판매 목록을 1차원 배열로 만들어서 반환하는 함수
SoldData* get_soldData_list(void)
{
    int size = get_soldData_count();
    SoldData* res = (SoldData*)calloc(size, sizeof(SoldData));
    char name[41], category[21];
    int count, year, month, day, money, delivery, del,i = 0;
    FILE* fp = fopen("판매내역.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d %d %d %d\n", name, category, &count, &year, &month, &day, &money, &delivery, &del);
        res[i++] = make_struct_SoldData(name, category, count, year, month, day, money, delivery, del);
    }
    fclose(fp);
    return res;
}

//제품과 구매하는 수를 입력받아 지불해야하는 가격을 구해주는 함수
int cal_money(char* name, int count)
{
    Product p;
    int soldCount, del, res = 0;
    FILE* fp = fopen("물건목록.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d %d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(p.name, name) == 0)
        {
            res = p.price * count;
            break;
        }
    }
    return res;
}

//제품구매
void buy_product(char* name, char* category, int count, int price, int delivery)
{
    time_t timer;
    struct tm* t;
    timer = time(NULL); // 1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초
    t = localtime(&timer);
    SoldData s;
    s = make_struct_SoldData(name, category, count, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, price, delivery, 0);
    add_new_SoldData(s);
    Product p = get_Product(name), p2;
    p2 = p;
    p2.count -= count;
    modify_Product(p, p2);
}



// 관리자 키 확인하는 함수
int check_manager_key(char* key)
{
    char fkey[20];
    FILE* fp = fopen("관리자파일.txt", "r");
    fscanf(fp, "%s", fkey);
    fclose(fp);
    return strcmp(key, fkey);
}

//관리자 키 수정하는 함수
void reset_manager_key(char* key)
{
    FILE* fp = fopen("관리자파일.txt", "w");
    fprintf(fp, "%s", key);
    fclose(fp);
}