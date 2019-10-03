#include <stdio.h>
#include <stdlib.h>

typedef int NODE_DATA_TYPE;

typedef struct _node {		// 트리의 노드
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
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

// 전위 순회
void preorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		printf("%c", node->info);
		preorder(node->left);
		preorder(node->right);
	}
}

// 중위 순회
void inorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%c", node->info);
		inorder(node->right);
	}
}

// 후위 순회
void postorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%c", node->info); 
	}
}

// 삽입
TREE_NODE_PTR addData_BSTree(TREE_NODE_PTR node, int data)
{
	if (node == NULL) {
		return createBNode(data, NULL, NULL);
	}

	if (node->info == data)
		return node;
	else if (node->info > data)
		node->left = addData_BSTree(node->left, data);
	else
		node->right = addData_BSTree(node->right, data);

	return node;
}

// 검색
TREE_NODE_PTR search_BSTree(TREE_NODE_PTR node, int data)
{
	if (node == NULL)
		return NULL;

	if (node->info == data)
		return node;
	else if (node->info > data)
		return search_BSTree(node->left, data);
	else
		return search_BSTree(node->right, data);
}

TREE_NODE_PTR firstNode_inorder(TREE_NODE_PTR node)
{
	if (node == NULL)
		return NULL;

	while (node->left != NULL)
		node = node->left;

	return node;
}

// 삭제
TREE_NODE_PTR deleteData_BSTree(TREE_NODE_PTR node, int data)
{
	TREE_NODE_PTR del_Node = search_BSTree(node, data); 
	TREE_NODE_PTR temp_Node = NULL;

	if (del_Node == NULL)
		return NULL;

	if (del_Node->left != NULL && del_Node->right != NULL) {
		temp_Node = firstNode_inorder(del_Node->right);
		del_Node->info = temp_Node->info;
		del_Node->right = deleteData_BSTree(del_Node->right, temp_Node->info);
	} else {
		temp_Node = (del_Node->right == NULL) ? del_Node->left : del_Node->right;

		if (temp_Node != NULL) {
			del_Node->info = temp_Node->info;
			temp_Node = deleteData_BSTree(temp_Node, temp_Node->info);
		}
		else {
			deleteBNode(del_Node);
			return NULL;
		}
	}

	return del_Node;
}

int main()
{
	return 0;
}