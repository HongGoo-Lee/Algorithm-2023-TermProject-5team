#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floyd.h"


//������ ���ڵ� ���� ��ȯ�ϴ� �Լ�
int get_file_line(char* fname)
{
    FILE* fp = fopen(fname, "r");
    int res = 0;
    char tmp[500];
    while (!feof(fp))
    {
        fgets(tmp, 500, fp);
        res++;
    }
    fclose(fp);
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
        if (strcmp(category, category1) == 0 && del == 0)
            size++;
    }
    fclose(fp);
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
        if (strcmp(category, category1) == 0 && del == 0)
        {
            res[i++] = get_struct_product(name, category1, price, count);
        }
    }
    fclose(fp);
    return res;
}

// ���� ��ǰ�� �ִ��� Ȯ���ϴ� �Լ�
int check_Product(Product product)
{
    FILE* fp = fopen("��ǰ���.txt", "r");
    Product p;
    int soldCount, del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", p.name, p.category, &p.price, &p.count, &soldCount, &del);
        if (strcmp(p.name, product.name) == 0)
        {
            res = 1;// ���� ��ǰ�� ����
            break;
        }
    }
    fclose(fp);
    return res;
}

//���ο� ��ǰ�� �߰��ϴ� �Լ�
int add_new_Product(Product new_p)
{
    int soldCount = 0, del = 0;
    if (check_Product(new_p) == 0)
    {
        FILE* fp = fopen("��ǰ���.txt", "a");
        fprintf(fp, "%s&%s&%d&%d&%d&%d\n", new_p.name, new_p.category, new_p.price, new_p.count, soldCount, del);
        fclose(fp);
        return 0;// �����۵�
    }
    else
    {
        return 1;//�̹� ���� ��ǰ�� ����
    }
}

//��ǰ ���� �����ϴ� �Լ� ���ǹ����� ���� �����ؾ���
int modify_Product(Product old, Product new_p)
{
    FILE* file = fopen("��ǰ���.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
        return 3;
    }

    Product product;
    long int pos;
    int found = 0, del, soldCount, res = 0;

    if (check_Product(old) == 1 && check_Product(new_p) == 0)
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
            res = 0;// ���������� ������
        }
    }
    else if (check_Product(new_p) == 1)
        res = 1;//�̹� �Ȱ��� ��ǰ�� ����
    else
        res = 2;//������ �߸� �Է���

    fclose(file);

    return res;
}

//��ǰ�� �����ϴ� �Լ�
int delete_Product(Product old)
{
    FILE* file = fopen("��ǰ���.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
        return 3;
    }

    Product item;
    long int pos;
    int found = 0, soldCount = 0, del = 0, res = 0;
    if (check_Product(old) == 1)
    {
        while (!feof(file))
        {
            pos = ftell(file);
            fscanf(file, "%s&%s&%d&%d&%d&%d\n", item.name, item.category, &item.price, &item.count, &soldCount, &del);
            if (strcmp(old.name, item.name) == 0 && del == 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            fseek(file, pos - strlen(item.name) - 1, SEEK_SET);
            fprintf(file, "%s&%s&%d&%d&%d&%d\n", item.name, item.category, item.price, item.count, soldCount, del);
            res = 0;//�����۵�
        }
        else
        {
            res = 1;//�̹� ������
        }
    }
    else
    {
        res = 2;//�߸��� ������ �Է���
    }

    fclose(file);

    return res;
}



//��ϵ� ������ ���� ��ȯ�ϴ� �Լ�
int get_City_count(void)
{
    FILE* fp = fopen("�������.txt", "r");
    City tmp;
    int del, res = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%d\n", tmp.city, &del);
        if (del == 0)
            res++;
    }
    return res;
}

// ��ϵ� ������ 1���� �迭�� ��ȯ�ϴ� �Լ�
City* get_City_list(void)
{
    FILE* fp = fopen("�������.txt", "r");
    int i = 0, size = get_City_count(), del = 0;
    City* res = (City*)calloc(size, sizeof(City));
    City tmp;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%d\n", tmp.city, &del);
        if (del == 0)
            strcpy(res[i++].city, tmp.city);
    }
    fclose(fp);
    return res;
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
    fclose(fp);
    return res;
}

//���ο� ���� �߰��ϴ� �Լ�
int add_new_City(City new_c)
{
    if (check_City(new_c) == 0)
    {
        FILE* fp = fopen("�������.txt", "a");
        fprintf(fp, "%s&%d\n", new_c.city, 0);
        fclose(fp);
        return 0;// �����۵�
    }
    else
    {
        return 1; // �̹� ���� ������ ����
    }
}

//���� ���� �����ϴ� �Լ� ���ǹ����� ���� �����ؾ���
int modifyCity(City old, City new_c)
{
    FILE* file = fopen("�������.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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
            fprintf(file, "%s&%d\n", new_c.city, del);
            res = 0;// �����۵�
        }
        fclose(file);
    }
    else if (check_City(new_c) == 1)
        res = 1;//�̹� �Ȱ��� ������ �־ ���� �Ұ���
    else
        res = 2;//�ٲٷ��� ���������� �߸���

    return res;
}

//������ �����ϴ� �Լ�
int deleteCity(City old)
{
    FILE* file = fopen("�������.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
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



// �Է¹��� ������ ���� ã�Ƽ� ��ȯ�ϴ� �Լ�
Road get_Road(char* start, char* arrival)
{
    FILE* fp = fopen("���θ��.txt", "r");
    Road res;
    int del = 0, state = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s&%s&%d&%d&%d&%d\n", res.start, res.arrival, &res.km, &res.cost, &res.time, &del);
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
    fclose(fp);
    return res;
}

//��ϵ� ������ ������ ��ȯ�ϴ� �Լ�
int get_Road_count(char* start)
{
    FILE* fp = fopen("���θ��.txt", "r");
    char fstart[11], arrival[11];
    int km, cost, time, del, res = 0;
    if (strcmp(start, "all") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (del == 0)
                res++;
        }
        fclose(fp);
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0 && del == 0)
                res++;
        }
        fclose(fp);
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
    FILE* fp = fopen("���θ��.txt", "r");
    if (strcmp(start, "all") == 0)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (del == 0)
                res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
        }
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s&%s&%d&%d&%d%d\n", fstart, arrival, &km, &cost, &time, &del);
            if (strcmp(start, fstart) == 0 && del == 0)
            {
                res[i++] = make_struct_Road(fstart, arrival, km, cost, time);
            }
        }
    }
    fclose(fp);
    return res;
}

//���ο� ���θ� ����ϴ� �Լ�
//��������� ���� ���γ��� ���ӵǰ� ������
//������ ������ ����
int add_new_Road(Road new_r)
{
    FILE* fp1 = NULL;
    FILE* tmp = NULL;
    if (check_Road(new_r) == 0)
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
            if (strcmp(start, new_r.start) == 0 && state == 0)
            {
                fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, new_del);
                state = 1;
            }
            fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", start, arrival, km, cost, time, del);
        }
        if (state == 0)
            fprintf(fp1, "%s&%s&%d&%d&%d&%d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, new_del);
        fclose(fp1);
        fclose(tmp);

        return 0;
    }
    else
        return 1;
}

// ���� �����ϴ� �Լ�
int modifyRoad(Road old, Road new_r) {
    FILE* file = fopen("���θ��.txt", "r+");
    if (file == NULL) {
        printf("������ ���� ���� ���� �߻�!\n");
        return 3;
    }

    Road edge;
    long pos;
    int del = 0, res = 0;
    if (check_Road(old) == 1 && ((strcmp(old.start, new_r.start) == 0 && strcmp(old.arrival, new_r.arrival) == 0) || (check_Road(new_r) == 0)))
    {
        while (!feof(file)) {
            pos = ftell(file);
            fscanf(file, "%s&%s&%d&%d&%d&%d\n", edge.start, edge.arrival, &edge.km, &edge.cost, &edge.time, &del);
            if (strcmp(old.start, edge.start) == 0 && strcmp(old.arrival, edge.arrival) == 0 && del == 0) {
                fseek(file, pos, SEEK_SET);
                fprintf(file, "%s&%s&%d&%d&%d&%d\n", new_r.start, new_r.arrival, new_r.km, new_r.cost, new_r.time, 0);
                break;
            }
        }
        res = 0;//���������� ������
    }
    else if (check_Road(new_r))
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

//���� �����ϴ� �Լ� del���� 1�� �ٲ�
int deleteRoad(Road delRoad)
{
    int res = 0;
    if (check_Road(delRoad) == 1)
    {
        FILE* fp = fopen("���θ��.txt", "r+");
        Road edge;
        long pos;
        int del, found = 0;
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
        fclose(fp);
    }
    else
    {
        res = 1;// �Է��� ������ ���ΰ� ����
    }

    return res;
}



// �Ǹų��� ����ϴ� �Լ�
void add_new_SoldData(SoldData new_s)
{
    FILE* fp = fopen("�ǸŸ��.txt", "a");
    fprintf(fp, "%s&%s&%d&%d%d%d%d%d%c\n", new_s.name, new_s.category, new_s.count, new_s.soldDate.year, new_s.soldDate.month, new_s.soldDate.day, new_s.money, new_s.delivery, new_s.del);
    fclose(fp);
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
    fclose(fp);
    return res;
}





// ������ Ű Ȯ���ϴ� �Լ�
int check_manager_key(char* key)
{
    char fkey[20];
    FILE* fp = fopen("����������.txt", "r");
    fscanf(fp, "%s", fkey);
    fclose(fp);
    return strcmp(key, fkey);
}

//������ Ű �����ϴ� �Լ�
void reset_manager_key(char* key)
{
    FILE* fp = fopen("����������.txt", "w");
    fprintf(fp, "%s", key);
    fclose(fp);
}