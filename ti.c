/*
* A = 5
* R7 = 40H
* R0 = 30H
* [31H] = 14H
* [30H] = 5
* R0++ => 31H
* R7 = 14H
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
    int val;
    Node* next;
};

Node* node_init(int val){
    Node* head = malloc(sizeof(Node*));
    head->val = val;
    head->next = NULL;
    return head;
}

void print_ll(Node* head){
    Node* temp = head;

    while(temp){
        printf("%d ",temp->val);
        temp = temp->next;
    }
}
size_t get_size(Node* head){
    size_t s = 0;
    Node* temp = head;
    while(temp){
        s++;
        temp = temp->next;
    }
    return s;
}

Node* insert(Node* head, int pos, int val){
    Node* temp = node_init(val);    
    // at start, pos = 1
    if(pos == 1){
        temp->next = head;
        return temp;
    }
    // in middle
    size_t s = get_size(head);
    if(s < pos){
        Node* itr = head;
        while(pos--){
            itr=itr->next;
        }
        temp->next = itr->next;
        itr->next = temp;
        // 1 2 4 5
        // 2 -> 3 - > 4
    }
    
    // in the end

}
int main(){    
    Node* myLL = node_init(1);
    
    myLL = insert(myLL,1,2);
    myLL = insert(myLL,1,3);
    myLL = insert(myLL,1,4);
    print_ll(myLL);



    return 0;
}
