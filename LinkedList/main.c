#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

struct Student{
    int id;
    char Name[10];
};

struct Node{
    struct Student S;
    struct Node *pPrev;
    struct Node *pNext;
};

struct Node *pHead;
struct Node *pTail;

void PrintStudent(struct Student s);
struct Student Fill(void);

void printScreen(void);

struct Node *creatNode(struct Student s);
int addNode (struct Student s);
int insertNode (struct Student s, int loc);
struct Student searchNodeID(int id);
struct Student searchNodeName(char Name[]);
int deletNode(int loc);
void freeList(void);
void showList(void);

int main()
{
    struct Student s;
    char x;
    char name[10];
    int ret, loc, id;

    while(x != '8')
    {
        system("cls");
        printScreen();
        x=getch();
        system("cls");

        switch(x)
        {
        case '1':
            {
                s = Fill();
                ret = addNode(s);
                break;
            }
        case '2':
            {
                printf("Please, enter the location: ");
                scanf("%d",&loc);
                s = Fill();
                ret = insertNode(s, loc);
                if(ret==0)
                    printf("the student has not been added");
                else
                    printf("the student has been added successfully");
                getch();
                break;
            }
        case '3':
            {
                printf("Please enter the id: ");
                scanf("%d",&id);
                s = searchNodeID(id);
                if(s.id!=-1)
                    PrintStudent(s);
                else
                    printf("there is no student with this id");

                getch();
                break;
            }
        case '4':
            {
                printf("Please, enter the name: ");
                scanf("%s",name);
                s = searchNodeName(name);
                if(s.id!=-1)
                    PrintStudent(s);
                else
                    printf("there is no student with this name");

                getch();
                break;
            }
        case '5':
            {
                printf("Please, enter the location: ");
                scanf("%d",&loc);
                ret = deletNode(loc);
                if(ret==0)
                    printf("no node has been deleted");
                else
                    printf("the node has been deleted");
                getch();
                break;
            }
        case '6':
            {
                showList();
                getch();
                break;
            }
        case '7':
            {
                freeList();
                printf("list has been deleted");
                getch();
                break;
            }
        }

    }
    return 0;
}

void PrintStudent(struct Student s)
{
    int i;

    printf("\n");
    printf("The student ID is: %d\n", s.id);
    printf("The student name is: %s\n", s.Name);
}

struct Student Fill(void)
{
    struct Student s;
    int i;

    printf("Please, Enter the student ID: ");
    scanf("%d", &s.id);

    printf("Please, Enter the student Name: ");
    scanf("%s", s.Name);

    printf("\n");
    return s;
}

void printScreen(void)
{
    printf("1- Add node\n");
    printf("2- Insert node\n");
    printf("3- Search by ID\n");
    printf("4- Search by name\n");
    printf("5- Delete node\n");
    printf("6- Print list\n");
    printf("7- free list\n");
    printf("8- exit\n");
}

struct Node *creatNode(struct Student s)
{
    struct Node *ptr;
    ptr = (struct Node*)malloc(sizeof(struct Node));

    if(ptr)
    {
        ptr->S = s;
        ptr->pPrev = NULL;
        ptr->pNext = NULL;
    }
    return ptr;
}

int addNode(struct Student s)
{
    int retval=0;
    struct Node *ptr;
    ptr = creatNode(s);

    if(ptr)
    {
        if(!pHead)
            pHead = pTail = ptr;

        else
        {
            ptr->pPrev = pTail;
            pTail->pNext = ptr;
            pTail = ptr;
        }
        retval = 1;
    }
    return retval;
}

struct Student searchNodeID(int id)
{
    struct Node *ptr;
    struct Student s;

    s.id = -1;
    ptr = pHead;

    while((ptr->S.id != id) && ptr)
        ptr = ptr->pNext;

    if(ptr)
        s = ptr->S;

    return s;
}

struct Student searchNodeName(char Name[])
{
    struct Node *ptr;
    struct Student s;

    s.id = -1;
    ptr = pHead;

    while(strcmp(ptr->S.Name, Name) && ptr)
        ptr = ptr->pNext;

    if(ptr)
        s = ptr->S;

    return s;
};

void freeList(void)
{
    struct Node *ptr;
    while(pHead)
    {
        ptr = pHead;
        pHead = pHead->pNext;
        free(ptr);
    }
    pTail = NULL;
}

void showList(void)
{
    struct Node *ptr;
    int count=0;
    ptr = pHead;

    if(ptr==NULL)
        printf("There is no data to show");

    else
    {
        while(ptr)
        {
            count++;
            PrintStudent(ptr->S);
            ptr = ptr->pNext;
        }
    }
}

int insertNode(struct Student s, int loc)
{
    int retval=0;
    int i;
    struct Node *ptr, *pcur;

    ptr = creatNode(s);

    if(ptr)
    {
        if(!pHead)
            pHead = pTail = ptr;

        else
        {
            if(loc == 0)
            {
                ptr->pNext = pHead;
                pHead->pPrev = ptr;
                pHead = ptr;
            }

            else
            {
                pcur = pHead;

                for(i=0;i<(loc-1)&&(pcur);i++)
                    pcur = pcur->pNext;

                if((pcur==pTail)||(pcur==NULL))
                {
                    ptr->pPrev = pTail;
                    pTail->pNext = ptr;
                    pTail = ptr;
                }

                else
                {
                    ptr->pNext = pcur->pNext;
                    pcur->pNext->pPrev = ptr;
                    pcur->pNext = ptr;
                    ptr->pPrev = pcur;
                }
            }
        }
        retval = 1;
    }
    return retval;
}

int deletNode(int loc)
{
    int retval=0;
    int i;
    struct Node *pcur;

    if(pHead)
    {
        pcur = pHead;

        if(loc==0)
        {
            if(pHead->pNext==NULL)
            {
                freeList();
            }
            else
            {
                pHead = pcur->pNext;
                pcur->pNext->pPrev = NULL;
                free(pcur);
            }

            retval = 1;
        }
        else
        {
            for(i=0;i<(loc)&&(pcur);i++)
                pcur = pcur->pNext;

            if(pcur==pTail)
            {
                pTail = pcur->pPrev;
                pcur->pPrev->pNext = NULL;
                free(pcur);

                retval = 1;

                return retval;
            }

            else if(pcur)
            {
                pcur->pNext->pPrev = pcur->pPrev;
                pcur->pPrev->pNext = pcur->pNext;
                free(pcur);

                retval = 1;
            }
        }
    }

    return retval;
}
