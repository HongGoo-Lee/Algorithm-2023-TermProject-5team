#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999

typedef struct _date {
    int year;
    int month;
    int day;
}Date;

typedef struct _road {
    char start[11];
    char arrival[11];
    int km;
    int cost;
    int time;
}Road;

typedef struct _product {
    char name[41];
    char category[41];
    int price;
    int count;
}Product;

typedef struct _city {
    char city[11];
}City;

typedef struct _soldData {
    char name[41];
    char category[41];
    int count;
    Date soldDate;
    int money;
    int delivery;
    char del;//환불여부
}SoldData;

//typedef struct_category

//2차원 인접 행렬을 만들어주는 함수
Road** create_Road_array(int size)
{
    Road** res = (Road**)calloc(size, sizeof(Road*));
    for (int i = 0; i < size; i++)
    {
        res[i] = (Road*)calloc(size, sizeof(Road));
        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                res[i][j].km = INF;
            }
        }
    }
}

// 가장 거리가 짧은 루트 찾는 함수
void get_min_dis_array(Road** array, int size)
{
    for (int k = 1; k <= size; k++)
    {
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
            {
                array[i][j].km = min(array[i][j].km, array[i][k].km + array[k][j].km);
            }
        }
    }
}

// 가장 비용이 덜 드는 루트 찾는 함수
void get_min_cost_array(Road** array, int size)
{
    for (int k = 1; k <= size; k++)
    {
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
            {
                array[i][j].cost = min(array[i][j].cost, array[i][k].cost + array[k][j].cost);
            }
        }
    }
}

// 가장 빨리 배송하는 루트를 찾는 함수
void get_min_time_array(Road** array, int size)
{
    for (int k = 1; k <= size; k++)
    {
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
            {
                array[i][j].time = min(array[i][j].time, array[i][k].time + array[k][j].time);
            }
        }
    }
}

//파일의 레코드 수를 반환하는 함수
int get_file_line(char* fname)
{
    FILE* fp = fopen(fname, "r");
    int res = 0;
    char tmp[500];
    while (!feof(fp))
    {
        fgets(tmp,500,fp);
        res++;
    }
    return res;
}

//현재 등록된 편의점 물건의 수를 반환하는 함수
int get_product_count(char* category)
{
    FILE* fp = fopen("물건목록.txt", "r");
    char name[41], category1[41];
    int price, count, soldCount, del, size = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", name, category1, &price, &count, &soldCount, &del);
        if (strcmp(category, category1) == 0)
            size++;
    }
    return size;
}

// 입력된 데이터를 Product 구조체로 만들어주느 함수
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
    char name[41], category1[41];
    int price, count, soldCount, del, size, i = 0;
    size = get_product_count(category);
    Product* res = (Product*)calloc(size, sizeof(Product));
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", name, category1, &price, &count, &soldCount, &del);
        if (strcmp(category, category1) == 0)
        {
            res[i++] = get_struct_product(name, category1, price, count);
        }
    }

    return res;
}


// 등록된 지역을 1차원 배열로 반환하는 함수
City* get_City_list(void)
{
    FILE* fp = fopen("지역목록.txt", "r");
    int i=0, size = get_file_line("지역목록.txt"),tmp=0;
    City* res = (City*)calloc(size, sizeof(City));
    while (!feof(fp))
    {
        fscanf(fp, "%s&%d\n", res[i].city, &tmp);
    }

    return res;
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
SoldData make_struct_SoldData(char* name, char* category, int count, int year, int month, int day, int money, int delivery, char del)
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


// 판매 목록을 1차원 배열로 만들어서 반환하는 함수
SoldData* get_soldData_list(void)
{
    int size = get_file_line("판매내역.txt");
    SoldData* res = (SoldData*)calloc(size, sizeof(SoldData));
    char name[41], category[41], del;
    int count, year, month, day, money, delivery, i = 0;
    FILE* fp = fopen("판매내역.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d%d%d%d%d%c\n", name, category, &count, &year, &month, &day, &money, &delivery, &del);
        res[i++] = make_struct_SoldData(name, category, count, year, month, day, money, delivery, del);
    }
    return res;
}


//등록된 도로의 개수를 반환하는 함수
int get_Road_count(char* start)
{
    int res = 0;
    if (strcmp(start, "all") == 0)
    {
        res = get_file_line("도로목록.txt");
    }
    else
    {
        FILE* fp = fopen("도로목록.txt", "r");
        char fstart[11], arrival[11];
        int km, cost, time,del;
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0)
                res++;
        }
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
    FILE* fp = fopen("도로목록.txt","r");
    if (strcmp(start, "all") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time,&del);
            res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
        }
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0)
            {
                res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
            }
        }
    }
    return res;
}

// 관리자 키 확인하는 함수
int check_manager_key(char* key)
{
    char fkey[20];
    FILE* fp = fopen("관리자파일.txt", "r");
    fscanf(fp, "%s", fkey);
    return strcmp(key, fkey);
}

//관리자 키 수정하는 함수
void reset_manager_key(char* key)
{
    FILE* fp = fopen("관리자파일.txt", "w");
    fprintf(fp, "%s", key);
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
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", start, arrival, &km, &cost, &time, &del);
        if (strcmp(start, road.start) == 0 && strcmp(arrival, road.arrival) == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

//새로운 도로를 등록하는 함수
//출발지점이 같은 도로끼리 연속되게 저장함
//가나다 정렬은 못함
int add_new_Road(Road new)
{
    FILE* fp1 = NULL;
    FILE* tmp = NULL;
    if (check_Road(new) == 0)
    {
        fp1 = fopen("도로목록.txt", "r");
        tmp = fopen("temp.txt", "w");
        char start[11], arrival[11];
        int km, cost, time, del = 0, new_del = 0;
        while (!feof(fp1))
        {
            fscanf(fp1, "%s&%s&%d&%d&%d&%d\n", start, arrival, &km, &cost, &time, &del);
            fprintf(tmp, "%s&%s&%d&%d&%d&%d\n", start, arrival, km, cost, time, del);
        }
        fclose(fp1);
        fclose(tmp);
        int state = 0;
        fp1 = fopen("도로목록.txt", "w");
        tmp = fopen("temp.txt", "r");
        while (!feof(tmp))
        {
            fscanf(tmp, "%s&%s&%d&%d&%d&%d\n", start, arrival, &km, &cost, &time, &del);
            if (strcmp(start, new.start) == 0 && state == 0)
            {
                fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", new.start, new.arrival, new.km, new.cost, new.time, new_del);
                state = 1;
            }
            fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", start, arrival, km, cost, time, del);
        }
        if (state == 0)
            fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", new.start, new.arrival, new.km, new.cost, new.time, new_del);
        fclose(fp1);
        fclose(tmp);

        return 0;
    }
    else
        return 1;
}

// 지역이 이미 있는 지역인지 확인하는 함수 있으면 1 없으면 0을 반환
int check_City(City city)
{
    FILE* fp = fopen("지역목록.txt", "r");
    City c;
    int del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%d\n", c.city, &del);
        if (strcmp(c.city, city.city) == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

int add_new_City(City new)
{
    FILE* fp = fopen("지역목록.txt", "a");
    if (check_City(new) == 0)
    {
        fprintf(fp, "%s&%d\n", new.city, 0);
        return 0;
    }
    else
    {
        return 1;
    }
}

void add_new_SoldData(SoldData new)
{
    FILE* fp = fopen("판매목록.txt", "a");
    fprintf(fp, "%s&%s&%d&%d%d%d%d%d%c\n", new.name, new.category, new.count, new.soldDate.year, new.soldDate.month, new.soldDate.day, new.money, new.delivery, new.del);
}

int check_Product(Product product)
{
    FILE* fp = fopen("물품목록.txt", "r");
    Product p;
    int soldCount,del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(p.name, product.name) == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

int add_new_Product(Product new)
{
    FILE* fp = fopen("물품목록.txt", "a");
    int soldCount = 0, del = 0;
    if (check_Product(new) == 0)
    {
        fprintf(fp, "%s&%s&%d&%d&%d&%d\n", new.name, new.category, new.price, new.count, soldCount, del);
        return 0;
    }
    else
    {
        return 1;
    }
}

int modifyRoad(Road old, Road new) {
    FILE* file = fopen("도로목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return;
    }

    Road edge;
    long pos;
    int del=0, res = 0;
    if (check_Road(old)==1 && check_Road(new)==0)
    {
        while (!feof(file)) {
            pos = ftell(file);
            fscanf(file, "%s&%s&%d&%d&%d&%d\n", edge.start, edge.arrival, &edge.km, &edge.cost, &edge.time, &del);
            if (strcmp(old.start, edge.start) == 0 && strcmp(old.arrival, edge.arrival) == 0 && del == 0) {
                fseek(file, pos, SEEK_SET);
                fprintf(file, "%s&%s&%d&%d&%d&%d\n", new.start, new.arrival, new.km, new.cost, new.time, 0);
                break;
            }
        }
        res = 0;//정상적으로 수정함
    }
    else if (check_Road(new))
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

int deleteRoad(Road delRoad)
{
    int res = 0;
    if (check_Road(delRoad) == 1)
    {
        FILE* fp = fopen("도로목록.txt", "r+");
        Road edge;
        long pos;
        int del, found=0;
        while (!feof(fp))
        {
            pos = ftell(fp);
            fscanf(fp, "%s&%s&%d&%d&%d&%d\n", edge.start, edge.arrival, &edge.km, &edge.cost, &edge.time, &del);
            if (strcmp(delRoad.start, edge.start) == 0 && strcmp(delRoad.arrival, edge.arrival) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%s&%s&%d&%d&%d&%d\n", delRoad.start, delRoad.arrival, delRoad.km, delRoad.cost, delRoad.time, 1);
            res = 0;//정상
        }
        else
            res = 2;//이미 지움
    }
    else
    {
        res = 1;// 입력한 정보의 도로가 없음
    }
}

int modifyCity(City old, City new)
{
    FILE* file = fopen("지역목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return;
    }
    City city;
    long int pos;
    int found = 0, del = 0, res = 1;
    if (check_City(old) == 1 && check_City(new) == 0)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s&%d\n", city.city, &del);
            if (strcmp(old.city, city.city) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s&%d\n", new.city, del);
            res = 0;// 정상작동
        }
        fclose(file);
    }
    else if (check_City(new) == 1)
        res = 1;//이미 똑같은 지역이 있어서 수정 불가능
    else
        res = 2;//바꾸려는 지역정보가 잘못됨

    return res;
}

int deleteCity(City old)
{
    FILE* file = fopen("지역목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return;
    }

    City city;
    long int pos;
    int found = 0,del=0, res;

    if (check_City(old) == 1)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s&%d\n", city.city, &del);
            if (strcmp(old.city, city.city) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s&%d\n", old.city, 1);
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

void modifyProduct(Product old, Product new)
{
    FILE* file = fopen("물품목록.txt", "r+");
    if (file == NULL) {
        printf("파일을 여는 도중 오류 발생!\n");
        return;
    }

    Product product;
    long int pos;
    int found = 0, del, soldCount, res = 0;

    if (check_Product(old) == 1 && check_Product(new) == 0)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s&%s&%d&%d&%d&%d\n", product.name, product.category, &product.price, &product.count, &soldCount, &del);
            if (strcmp(old.name, product.name) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s&%s&%d&%d&%d&%d\n", product.name, product.category, product.price, product.count, soldCount, del);
            res = 0;
        }
    }
    else if (check_Product(new) == 1)
        res = 1;//이미 똑같은 물품이 있음
    else
        res = 2;//정보를 잘못 입력함

    fclose(file);

    return res;
}