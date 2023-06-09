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
    char del;//ȯ�ҿ���
}SoldData;

//typedef struct_category

//2���� ���� ����� ������ִ� �Լ�
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

// ���� �Ÿ��� ª�� ��Ʈ ã�� �Լ�
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

// ���� ����� �� ��� ��Ʈ ã�� �Լ�
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

// ���� ���� ����ϴ� ��Ʈ�� ã�� �Լ�
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

//������ ���ڵ� ���� ��ȯ�ϴ� �Լ�
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

//���� ��ϵ� ������ ������ ���� ��ȯ�ϴ� �Լ�
int get_product_count(char* category)
{
    FILE* fp = fopen("���Ǹ��.txt", "r");
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

// �Էµ� �����͸� Product ����ü�� ������ִ� �Լ�
Product get_struct_product(char* name, char* category, int price, int count)
{
    Product res;
    strcpy(res.category, category);
    strcpy(res.name, name);
    res.count = count;
    res.price = price;

    return res;
}

// ���� ����� 1���� �迭�� ����� ��ȯ�ϴ� �Լ�
Product* get_product_list(char* category)
{
    FILE* fp = fopen("���Ǹ��.txt", "r");
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


// ��ϵ� ������ 1���� �迭�� ��ȯ�ϴ� �Լ�
City* get_City_list(void)
{
    FILE* fp = fopen("�������.txt", "r");
    int i=0, size = get_file_line("�������.txt"),tmp=0;
    City* res = (City*)calloc(size, sizeof(City));
    while (!feof(fp))
    {
        fscanf(fp, "%s&%d\n", res[i].city, &tmp);
    }

    return res;
}


// �Էµ� �����͸� Date ����ü�� ������ִ� �Լ�
Date make_struct_Date(int year, int month, int day)
{
    Date res;
    res.day = day;
    res.month = month;
    res.year = year;

    return res;
}

// �Էµ� �����͸� SoldData ����ü�� ������ִ� �Լ�
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


// �Ǹ� ����� 1���� �迭�� ���� ��ȯ�ϴ� �Լ�
SoldData* get_soldData_list(void)
{
    int size = get_file_line("�Ǹų���.txt");
    SoldData* res = (SoldData*)calloc(size, sizeof(SoldData));
    char name[41], category[41], del;
    int count, year, month, day, money, delivery, i = 0;
    FILE* fp = fopen("�Ǹų���.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d%d%d%d%d%c\n", name, category, &count, &year, &month, &day, &money, &delivery, &del);
        res[i++] = make_struct_SoldData(name, category, count, year, month, day, money, delivery, del);
    }
    return res;
}


//��ϵ� ������ ������ ��ȯ�ϴ� �Լ�
int get_Road_count(char* start)
{
    int res = 0;
    if (strcmp(start, "all") == 0)
    {
        res = get_file_line("���θ��.txt");
    }
    else
    {
        FILE* fp = fopen("���θ��.txt", "r");
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

// �Էµ� �����͸� Road����ü�� ������ִ� �Լ�
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


// ���θ���� 1���� �迭�� ���� ��ȯ�ϴ� �Լ�
Road* get_Road_list(char* start)
{
    int size = get_Road_count(start);
    Road* res = (Road*)calloc(size, sizeof(Road));
    char fstart[11], arrival[11];
    int km, cost, time, del;
    int i = 0;
    FILE* fp = fopen("���θ��.txt","r");
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

// ������ Ű Ȯ���ϴ� �Լ�
int check_manager_key(char* key)
{
    char fkey[20];
    FILE* fp = fopen("����������.txt", "r");
    fscanf(fp, "%s", fkey);
    return strcmp(key, fkey);
}

//������ Ű �����ϴ� �Լ�
void reset_manager_key(char* key)
{
    FILE* fp = fopen("����������.txt", "w");
    fprintf(fp, "%s", key);
}

//�̹� ���� ���ΰ� �ִ��� üũ ���� ���ΰ� ������ 1�� ��ȯ ������ 0
int check_Road(Road road)
{
    FILE* fp = fopen("���θ��.txt", "r");
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

//���ο� ���θ� ����ϴ� �Լ�
//��������� ���� ���γ��� ���ӵǰ� ������
//������ ������ ����
int add_new_Road(Road new)
{
    FILE* fp1 = NULL;
    FILE* tmp = NULL;
    if (check_Road(new) == 0)
    {
        fp1 = fopen("���θ��.txt", "r");
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
        fp1 = fopen("���θ��.txt", "w");
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

// ������ �̹� �ִ� �������� Ȯ���ϴ� �Լ� ������ 1 ������ 0�� ��ȯ
int check_City(City city)
{
    FILE* fp = fopen("�������.txt", "r");
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
    FILE* fp = fopen("�������.txt", "a");
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
    FILE* fp = fopen("�ǸŸ��.txt", "a");
    fprintf(fp, "%s&%s&%d&%d%d%d%d%d%c\n", new.name, new.category, new.count, new.soldDate.year, new.soldDate.month, new.soldDate.day, new.money, new.delivery, new.del);
}

int check_Product(Product product)
{
    FILE* fp = fopen("��ǰ���.txt", "r");
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
    FILE* fp = fopen("��ǰ���.txt", "a");
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
    FILE* file = fopen("���θ��.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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
        res = 0;//���������� ������
    }
    else if (check_Road(new))
    {
        res = 2;//���� ���ΰ� �̹� �־ ���� �Ұ���
    }
    else
    {
        res = 1;//�����Ϸ��� ���ΰ� ����
    }
    fclose(file);

    return res;
}

int deleteRoad(Road delRoad)
{
    int res = 0;
    if (check_Road(delRoad) == 1)
    {
        FILE* fp = fopen("���θ��.txt", "r+");
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
            res = 0;//����
        }
        else
            res = 2;//�̹� ����
    }
    else
    {
        res = 1;// �Է��� ������ ���ΰ� ����
    }
}

int modifyCity(City old, City new)
{
    FILE* file = fopen("�������.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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
            res = 0;// �����۵�
        }
        fclose(file);
    }
    else if (check_City(new) == 1)
        res = 1;//�̹� �Ȱ��� ������ �־ ���� �Ұ���
    else
        res = 2;//�ٲٷ��� ���������� �߸���

    return res;
}

int deleteCity(City old)
{
    FILE* file = fopen("�������.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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
            res = 1;//�̹� ����
        }
    }
    else
    {
        res = 2;//�����Ϸ��� ������ ����
    }

    fclose(file);

    return res;
}

void modifyProduct(Product old, Product new)
{
    FILE* file = fopen("��ǰ���.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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
        res = 1;//�̹� �Ȱ��� ��ǰ�� ����
    else
        res = 2;//������ �߸� �Է���

    fclose(file);

    return res;
}