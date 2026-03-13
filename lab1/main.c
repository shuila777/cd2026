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

/* 印出結果：按輸入順序並用逗號隔開 */
void printList(Node* head, const char* input){
    int first = 1;
    int len = strlen(input);

    for(int i = 0; i < len; i++){
        char ch = input[i];

        // 找到該字元在linked list裡第一次出現
        Node* exist = find(head, ch);

        if(exist != NULL){
            if(!first)
                printf(",");
            printf("%c", ch);
            first = 0;

            // 標記這個字元已經輸出過
            exist->count = 0; 
        }
    }
    printf("\n");
}

int main(){

    Node* head = NULL;

    char input[1000];
    scanf("%[^\n]", input); // 讀取整行包含空格

    int len = strlen(input);

    for(int i = 0; i < len; i++){

        char ch = input[i];

        Node* exist = find(head, ch);

        if(exist != NULL){
            exist->count++;
        }
        else{
            insert(&head, ch);
        }
    }

    printList(head, input);

    return 0;
}