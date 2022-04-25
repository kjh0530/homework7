/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;
/* key 값을 저장할 int형 변수와
   link할 주소를 저장할 포인터 변수
   두 개를 가진 Node 구조체 정의 */



typedef struct Head {
	struct Node* first;
}headNode;
/* Node 구조체를 가리키는 포인터 변수를
   가진 Head 구조체 정의
   (첫 번째 노드를 가리키기 위한 구조체) */



/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); //nodelist를 초기화하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //nodelist에 할당된 메모리를 free시키는 함수
int insertNode(headNode* h, int key);
//key 값을 가진 노드를 삽입하는 함수(key 값에 크기에 따라 )
int insertLast(headNode* h, int key);
//nodelist의 마지막에 key 값을 가진 노드를 삽입하는 함수
int insertFirst(headNode* h, int key);
//nodelist의 처음에 key 값을 가진 노드를 삽입하는 함수
int deleteNode(headNode* h, int key);
//key 값을 가진 노드를 삭제하는 함수
int deleteLast(headNode* h);
//nodelist의 마지막에 있는 노드를 삭제하는 함수
int deleteFirst(headNode* h);
//nodelist의 처음에 있는 노드를 삭제하는 함수
int invertList(headNode* h);
//nodelist의 순서를 반대로 바꾸는 함수

void printList(headNode* h);
//nodelist의 현재 상태를 출력하는 함수


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- 김주훈 2020039027 -----]\n\n");//이름 학번 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //nodelist가 비어있으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { //처음부터 끝까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) //nodelist가 비어있으면
	{
		h->first = node; //첫 번째 노드에 삽입
		return 0;
	}

	listNode* n = h->first; //n에 headnode 할당
	while(n->rlink != NULL) {
		n = n->rlink;
	}//n이 마지막 노드를 가리킴
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL) //nodelist가 비어있으면
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //nodelist가 비어있으면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL; //이전 노드 저장할 변수
	listNode *middle = NULL; //현재 노드 저장할 변수

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle; //마지막 값이 첫 번째 값이 됨

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //headnode와 key값을 매개변수로 받음

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//노드 생성
	node->key = key;
	//key 값 할당
	node->llink = node->rlink = NULL;
	//노드의 link값 초기화(NULL)
	if (h->first == NULL) //nodelist가 비어있으면
	{
		h->first = node; //첫 번째 노드에 삽입
		return 0;
	}

	listNode* n = h->first; //n에 첫 노드의 주소 할당

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
				//insertFirst 함수로 첫 번째 노드에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				//삽입할 노드의 다음 링크에 n 노드의 주소를 할당
				node->llink = n->llink;
				//삽입할 노드의 전 링크에 n의 전 링크 할당
				n->llink->rlink = node;
				//n의 전 노드의 다음 링크에 삽입할 노드의 주소 할당
			}
			return 0;
		}

		n = n->rlink; //다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //nodelist가 비어있으면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;
	//n에 첫 번째 노드의 link 값을 할당

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; 
				//전 노드의 다음 링크에 현재 노드의 다음 링크 할당
				n->rlink->llink = n->llink;
				//다음 노드의 전 링크에 현제노드의 전 링크 할당
				free(n); //n을 free 시킨다.
			}
			return 1;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


