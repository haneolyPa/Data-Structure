#include <stdio.h>
#include <stdlib.h>

typedef char NODE_DATA_TYPE;

typedef struct _node {		// 트리의 노드
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
	bool isThread;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// 이중 연결 리스트의 헤드 노드 구조 정의
	TREE_NODE_PTR root;
} BIN_TREE;
typedef BIN_TREE * BIN_TREE_PTR;

// 이진트리 노드 생성
TREE_NODE_PTR createBNode(NODE_DATA_TYPE data, TREE_NODE_PTR left, TREE_NODE_PTR right)
{
	TREE_NODE_PTR newBNode = (TREE_NODE_PTR)malloc(sizeof(TREE_NODE));

	newBNode->info = data;
	newBNode->left = left;
	newBNode->right = right;
	newBNode->isThread = false;

	return newBNode;
}

// 이진트리 노드 제거
void deleteBNode(TREE_NODE_PTR node)
{
	if (node == NULL)
		return;

	deleteBNode(node->left);
	deleteBNode(node->right);
	free(node);
}

// 트리 생성
BIN_TREE_PTR createBTree()
{
	BIN_TREE_PTR newTree = (BIN_TREE_PTR)malloc(sizeof(BIN_TREE));
	newTree->root = NULL;
	return newTree;
}

// 트리 제거
void deleteBTree(BIN_TREE_PTR tree)
{
	deleteBNode(tree->root);
	free(tree);
}

// 스레드 노드 여부
bool isThreadNode(const TREE_NODE_PTR node)
{
	return node->isThread;
}

// 스레드 노드 셋팅
void setThreadNode(TREE_NODE_PTR node)
{
	node->isThread = true;
}

// 전위 순회
void preorder(TREE_NODE_PTR node)
{
	while (node) {
		printf("%c", node->info);

		if (node->left != NULL)
			node = node->left;
		else
			node = node->right;
	}
}

TREE_NODE_PTR nextNode_inorder(TREE_NODE_PTR node)
{
	TREE_NODE_PTR next_Node = node->right;

	if (next_Node == NULL || isThreadNode(node))
		return next_Node;

	while (next_Node->left != NULL)
		next_Node = next_Node->left;

	return next_Node;
}

void inorder(TREE_NODE_PTR node)
{
	TREE_NODE_PTR tempNode = node;
	while (tempNode->left != NULL)
		tempNode = tempNode->left;

	do {
		printf("%c", tempNode->info);
		tempNode = nextNode_inorder(tempNode);
	} while (tempNode != NULL);
}




int main()
{
	BIN_TREE_PTR pBTree = createBTree();

	// 그림 7-14 사칙연산
	TREE_NODE_PTR pNode_A = createBNode('A', NULL, NULL);
	TREE_NODE_PTR pNode_B = createBNode('B', NULL, NULL);
	TREE_NODE_PTR pNode_C = createBNode('C', NULL, NULL);
	TREE_NODE_PTR pNode_D = createBNode('D', NULL, NULL);
	TREE_NODE_PTR pNode_E = createBNode('E', NULL, NULL);

	TREE_NODE_PTR pNode_Div = createBNode('/', NULL, NULL);
	TREE_NODE_PTR pNode_Sub = createBNode('-', NULL, NULL);
	TREE_NODE_PTR pNode_Plus = createBNode('+', NULL, NULL);
	TREE_NODE_PTR pNode_Mul = createBNode('*', NULL, NULL);

	pBTree->root = pNode_Mul;
	pNode_Mul->left = pNode_Sub;
	pNode_Mul->right = pNode_D;

	pNode_Sub->left = pNode_Div;
	pNode_Sub->right = pNode_C;

	pNode_Div->left = pNode_E;
	pNode_Div->right = pNode_Plus;

	pNode_Plus->left = pNode_A;
	pNode_Plus->right = pNode_B;

	// 스레드 노드 셋팅
	setThreadNode(pNode_E);
	setThreadNode(pNode_A);
	setThreadNode(pNode_B);
	setThreadNode(pNode_C);
	setThreadNode(pNode_D);

	// 전위 순회 스레드 셋팅
	pNode_E->right = pNode_Plus;
	pNode_A->right = pNode_B;
	pNode_B->right = pNode_C;
	pNode_C->right = pNode_D;

	// 전위 순회
	preorder(pBTree->root);
	printf("\n");

	// 중위 순회 스레드 셋팅
	pNode_E->right = pNode_Div;
	pNode_A->right = pNode_Plus;
	pNode_B->right = pNode_Sub;
	pNode_C->right = pNode_Mul;

	// 중위 순회
	inorder(pBTree->root);
	printf("\n");


	return 0;
}