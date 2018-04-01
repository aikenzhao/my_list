/**********************************************************
 * Author        : Aiken.zhao
 * Email         : 
 * Last modified : 2018-03-30 16:37
 * Filename      : my_list.h
 * Description   : 
 * *******************************************************/
#ifndef _MY_LIST_H_
#define _MY_LIST_H_
#include<pthread.h>
#define POINTER_DATA unsigned long int  

using namespace std;

struct DataElement{
    char *data;
    int data_len;
    DataElement *prev;
    DataElement *next;
};

class MyList{
private:
    DataElement *first;
    DataElement *last;
    int element_num;   //链表中元素的个数
    const int element_num_max;//链表中最多允许的元素个数
    const int element_num_min;//链表中最少允许的元素个数

    pthread_mutex_t *pth_lock;

protected:    
    MyList();
    MyList(pthread_mutex_t *p_clock);
    ~MyList();

public:
    //获取初始化list
    static MyList *get_list(pthread_mutex_t *p_lock);
    //释放list
    void release();

    //往链表中写数据
    //data的内存在外部开辟和注销，
    //data_len:为数据的长度，单位byte
    int write_data(char* data, int data_len);

    //读取链表中的数据，data为外部存储的指针的指针，
    //返回值为数据的长度
    int read_data(char** data);
    

    void print_list();
    int cheack_list();
    int is_full();
    int is_empty();
    void print_data();
    //MyList();
    //~MyList();

private:
    //int is_full();
    //int is_empty();
    void delete_first();
    void add_last(DataElement *ele);
    DataElement *creat_element();
    //print_list();
};

#endif
