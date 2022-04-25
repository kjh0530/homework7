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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;
/* key ���� ������ int�� ������
   link�� �ּҸ� ������ ������ ����
   �� ���� ���� Node ����ü ���� */



typedef struct Head {
	struct Node* first;
}headNode;
/* Node ����ü�� ����Ű�� ������ ������
   ���� Head ����ü ����
   (ù ��° ��带 ����Ű�� ���� ����ü) */



/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h); //nodelist�� �ʱ�ȭ�ϴ� �Լ�

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h); //nodelist�� �Ҵ�� �޸𸮸� free��Ű�� �Լ�
int insertNode(headNode* h, int key);
//key ���� ���� ��带 �����ϴ� �Լ�(key ���� ũ�⿡ ���� )
int insertLast(headNode* h, int key);
//nodelist�� �������� key ���� ���� ��带 �����ϴ� �Լ�
int insertFirst(headNode* h, int key);
//nodelist�� ó���� key ���� ���� ��带 �����ϴ� �Լ�
int deleteNode(headNode* h, int key);
//key ���� ���� ��带 �����ϴ� �Լ�
int deleteLast(headNode* h);
//nodelist�� �������� �ִ� ��带 �����ϴ� �Լ�
int deleteFirst(headNode* h);
//nodelist�� ó���� �ִ� ��带 �����ϴ� �Լ�
int invertList(headNode* h);
//nodelist�� ������ �ݴ�� �ٲٴ� �Լ�

void printList(headNode* h);
//nodelist�� ���� ���¸� ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- ������ 2020039027 -----]\n\n");//�̸� �й� ���
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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

	if(h == NULL) { //nodelist�� ���������
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { //ó������ ������
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) //nodelist�� ���������
	{
		h->first = node; //ù ��° ��忡 ����
		return 0;
	}

	listNode* n = h->first; //n�� headnode �Ҵ�
	while(n->rlink != NULL) {
		n = n->rlink;
	}//n�� ������ ��带 ����Ŵ
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL) //nodelist�� ���������
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
 * list�� ù��° ��� ����
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
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //nodelist�� ���������
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL; //���� ��� ������ ����
	listNode *middle = NULL; //���� ��� ������ ����

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle; //������ ���� ù ��° ���� ��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { //headnode�� key���� �Ű������� ����

	listNode* node = (listNode*)malloc(sizeof(listNode));
	//��� ����
	node->key = key;
	//key �� �Ҵ�
	node->llink = node->rlink = NULL;
	//����� link�� �ʱ�ȭ(NULL)
	if (h->first == NULL) //nodelist�� ���������
	{
		h->first = node; //ù ��° ��忡 ����
		return 0;
	}

	listNode* n = h->first; //n�� ù ����� �ּ� �Ҵ�

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				insertFirst(h, key);
				//insertFirst �Լ��� ù ��° ��忡 ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;
				//������ ����� ���� ��ũ�� n ����� �ּҸ� �Ҵ�
				node->llink = n->llink;
				//������ ����� �� ��ũ�� n�� �� ��ũ �Ҵ�
				n->llink->rlink = node;
				//n�� �� ����� ���� ��ũ�� ������ ����� �ּ� �Ҵ�
			}
			return 0;
		}

		n = n->rlink; //���� ���� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //nodelist�� ���������
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;
	//n�� ù ��° ����� link ���� �Ҵ�

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; 
				//�� ����� ���� ��ũ�� ���� ����� ���� ��ũ �Ҵ�
				n->rlink->llink = n->llink;
				//���� ����� �� ��ũ�� ��������� �� ��ũ �Ҵ�
				free(n); //n�� free ��Ų��.
			}
			return 1;
		}

		n = n->rlink;
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


