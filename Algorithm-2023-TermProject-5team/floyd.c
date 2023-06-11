#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_input_output.h"

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
                res[i][j].cost = INF;
                res[i][j].time = INF;
            }
        }
    }

    return res;
}

// ������� �ʱⰪ���� �����ϴ� �Լ�
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

//���������κ��� Ư�� �������� �ִܰŸ��� ã�Ƽ� �� ������ ��ȯ�ϴ� �Լ�
Road get_min_dis_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_dis_array(res, c_size);
    return res[0][num];
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

//���������κ��� Ư�� �������� ����� ���� ������ ���� ã�Ƽ� �� ������ ��ȯ�ϴ� �Լ�
Road get_min_cost_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_cost_array(res, c_size);
    return res[0][num];
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

//���������κ��� Ư�� �������� �ð��� ���� ���� ���� ã�Ƽ� �� ������ ��ȯ�ϴ� �Լ�
Road get_min_time_Road(int num)
{
    City* c_array = get_City_list();
    int c_size = get_City_count();
    Road** res = create_Road_array(c_size);
    set_Road_array(res, c_array, c_size);
    get_min_time_array(res, c_size);
    return res[0][num];
}