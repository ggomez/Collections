/* 
 * File:   ConcurrentLinkedList.h
 * Author: memo
 *
 * Created on February 13, 2014, 10:35 AM
 */

#ifndef CONCURRENTLINKEDLIST_H
#define	CONCURRENTLINKEDLIST_H

#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>

typedef struct ConcurrentLinkedList_s ConcurrentLinkedList;
typedef struct ListNode_s ListNode;
struct ConcurrentLinkedList_s{
    pthread_mutex_t lock;
    int size;
    ListNode * head;
};

struct ListNode_s{
    void * Element;
    ListNode * nextNode;
};

ConcurrentLinkedList * getNewList();
void addElement(ConcurrentLinkedList * list, void * E);
void removeElement(ConcurrentLinkedList * list, void * E);
void * getElement(ConcurrentLinkedList * list, int index);
int getSize(ConcurrentLinkedList * list);
void destroyList(ConcurrentLinkedList * list);

#endif	/* CONCURRENTLINKEDLIST_H */

