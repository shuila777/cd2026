#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char c;
    int count;
    struct Node* next;
} Node;

/* 找字元是否已存在 */
Node* find(Node* head, char ch){
    Node* temp = head;

    while(temp != NULL){
        if(temp->c == ch)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/* 新增node */
void insert(Node** head, char ch){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->c = ch;
    newNode->count = 1;
    newNode->next = *head;
    *head = newNode;
}

/* 印出結果 */
void printList(Node* head){
    Node* temp = head;

    while(temp != NULL){
        printf("%c : %d\n", temp->c, temp->count);
        temp = temp->next;
    }
}

int main(){

    Node* head = NULL;

    char input[1000];
    scanf("%s", input);

    int len = strlen(input);

    for(int i=0;i<len;i++){

        char ch = input[i];

        if(ch==' ' || ch=='\n')
            continue;

        Node* exist = find(head, ch);

        if(exist != NULL){
            exist->count++;
        }
        else{
            insert(&head, ch);
        }
    }

    printList(head);

    return 0;
}