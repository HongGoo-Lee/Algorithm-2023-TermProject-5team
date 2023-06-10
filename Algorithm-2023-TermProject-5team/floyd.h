#pragma once
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

Road** create_Road_array(int size);
void set_Road_array(Road** array, City* citys, int city_size);
void get_min_dis_array(Road** array, int size);
void get_min_cost_array(Road** array, int size);
void get_min_time_array(Road** array, int size);