/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

    printf("----길동현 2022041025----\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); //h가 비어있지 않으면 h노드 메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //h의 오른쪽 노드를 h로 설정
	(*h)->key = -9999;

	top = -1; //변수 초기화

	front = rear = -1; //변수 초기화

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left) 
			push(node); //왼쪽 자식 노드로 이동하여 스택에 현재 노드 저장
		node = pop(); //스택에서 노드를 꺼냄.

		if(!node) break; //노드가 비어있으면 반복 종료
		printf(" [%d] ", node->key); //현재 노드의 키값 출력

		node = node->right; //오른쪽 자식 노드로 이동
	} 
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //루트 노드를 큐에 넣음

	for(;;)
	{
		ptr = deQueue(); //큐에서 노드를 꺼냄
		if(ptr) {
			printf(" [%d] ", ptr->key); //현재 노드의 키값을 출력

			if(ptr->left) 
				enQueue(ptr->left); //왼쪽 자식 노드를 큐에 넣음
			if(ptr->right)
				enQueue(ptr->right); //오른쪽 자식 노드를 큐에 넣음
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key; //newNode를 초기화한다.
	newNode->left = NULL; //노드를 비운다
	newNode->right = NULL; //노드를 비운다

	if (head->left == NULL) {
		head->left = newNode; //헤드의 왼쪽 노들르 newNode로 설정한다.
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1; //해당 키를 가진 노드가 존재하면 반환한다.

		parentNode = ptr; //부모노드를 찾는다

		if(ptr->key < key) //현재 노드의 키가 입력키보다 크다면
			ptr = ptr->right; //새 노드는 오른쪽 노드에 삽입
		else //아니라면
			ptr = ptr->left; //새 노드는 왼쪽 노드에 삽입
	}

	if(parentNode->key > key)
		parentNode->left = newNode; //새 노드를 부모 왼쪽에 연결
	else
		parentNode->right = newNode; //새 노드를 부모 오른쪽에 연결
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left; //헤드의 왼쪽 노드는 루트



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr; //부모노드 저장

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	if(ptr == NULL) 
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	if(ptr->left == NULL && ptr->right == NULL) //노드가 비어있는 경우
	{
		if(parent != NULL) { //부모가 존재할때
			if(parent->left == ptr) //노드가 부모의 왼쪽노드일때
				parent->left = NULL; //부모의 왼쪽노드를 비움
			else
				parent->right = NULL; //부모의 오른쪽 노드를 비움
		} else {
			//부모가 존재하지 않으면 헤드의 왼쪽노드를 비움
			head->left = NULL;

		}

		free(ptr); //노드 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //노드의 왼쪽이 비어있거나 오른쪽이 비어있을때
	{
		Node* child;
		if (ptr->left != NULL) //왼쪽노드가 비어있지 않을때
			child = ptr->left; 
		else
			child = ptr->right;

		if(parent != NULL) //부모가 비어있지 않을때
		{
			if(parent->left == ptr)
				parent->left = child; //부모의 왼쪽노드를 자식노드로
			else
				parent->right = child; //부모의 오른쪽노드를 자식으로
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //자식은 루트
		}

		free(ptr); //노드 메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL) //candidate의 왼쪽 노드가 비어있지 않을때
	{
		parent = candidate; //candidate를 부모로
		candidate = candidate->left; //cadidate의 왼쪽노드를 candidate로 저장
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //candidate가 부모의 오른쪽 노드일때
		parent->right = candidate->right; //candidate의 오른쪽 노드는 부모의 오른쪽 노드
	else
		parent->left = candidate->right; //부모의 왼쪽 노드는 candidate의 오른쪽 노드

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //candidate의 key를 ptr의 key값으로 저장

	free(candidate); //candidate 메모리 해제
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //ptr의 왼쪽노드 메모리 해제
 		freeNode(ptr->right); //ptr의 오른쪽 노드 메모리 해제
		free(ptr); //ptr메모리 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//헤드의 왼쪽노드가 헤드일때
	{
		free(head); //헤드 메모리 해제
		return 1;
	}

	Node* p = head->left; 

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL; //스택이 비어있으면 NULL 리턴
	return stack[top--]; //스택이 가장 위에 있는 노드 반환하고 top 감소
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top 증가, 스택에 노드 추가
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; //큐가 비어있으면 NULL 반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front를 한칸 앞으로 이동시킴
	return queue[front]; //큐에서 front 다음 위치에 있는 노드 반환

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear를 한칸 뒤로 이동
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return; //큐가 가득 차면 함수를 종료
	}

	queue[rear] = aNode; //큐의 rear다음 위치에 노드를 추가
}




