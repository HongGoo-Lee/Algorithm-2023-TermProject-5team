#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_input_output.h"

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
                res[i][j].cost = INF;
                res[i][j].time = INF;
            }
        }
    }

    return res;
}

// 인접행렬 초기값으로 설정하는 함수
void set_Road_array(Road** array, City* citys, int city_size)
{
    for (int i = 0; i < city_size; i++)
    {
        for (int j = 0; j < city_size; j++)
        {
            if (i != j)
            {
                array[i][j] = get_Road(citys[i].city, citys[j].city);
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

//편의점으로부터 특정 지역까지 최단거리를 찾아서 그 정보를 반환하는 함수
Road get_min_dis_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_dis_array(res, c_size);
    return res[0][num];
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

//편의점으로부터 특정 지역까지 비용이 제일 저렴한 길을 찾아서 그 정보를 반환하는 함수
Road get_min_cost_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_cost_array(res, c_size);
    return res[0][num];
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

//편의점으로부터 특정 지역까지 시간이 제일 빠른 길을 찾아서 그 정보를 반환하는 함수
Road get_min_time_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_time_array(res, c_size);
    return res[0][num];
}