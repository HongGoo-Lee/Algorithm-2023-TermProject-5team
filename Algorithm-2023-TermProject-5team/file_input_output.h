#pragma once
#include "floyd.h"

int get_file_line(char* fname);
int get_product_count(char* category);
Product get_struct_product(char* name, char* category, int price, int count);
Product* get_product_list(char* category);
int check_Product(Product product);
int add_new_Product(Product new_p);
int modify_Product(Product old, Product new_p);
int delete_Product(Product old);
int get_City_count(void);
City* get_City_list(void);
int check_City(City city);
int add_new_City(City new_c);
int modifyCity(City old, City new_c);
int deleteCity(City old);
Road get_Road(char* start, char* arrival);
int check_Road(Road road);
int get_Road_count(char* start);
Road make_struct_Road(char* start, char* arrival, int km, int cost, int time);
Road* get_Road_list(char* start);
int add_new_Road(Road new_r);
int modifyRoad(Road old, Road new_r);
int deleteRoad(Road delRoad);
void add_new_SoldData(SoldData new_s);
Date make_struct_Date(int year, int month, int day);
SoldData make_struct_SoldData(char* name, char* category, int count, int year, int month, int day, int money, int delivery, char del);
SoldData* get_soldData_list(void);
int check_manager_key(char* key);
void reset_manager_key(char* key);
int get_Category_count(void);
Category* get_Category_list(void);
int check_Category(Category c);
int cal_money(char* name, int count);
int get_City_num(char* c);
void buy_product(char* name, char* category, int count, int price, int delivery);
Product* search_Product(char* str);
int search_Product_count(char* str);