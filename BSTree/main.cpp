#include <stdio.h>
#include <stdlib.h>

typedef int NODE_DATA_TYPE;

typedef struct _node {		// 트리의 노드
	struct _node * left;
	struct _node * right;
	NODE_DATA_TYPE info;
} TREE_NODE;
typedef TREE_NODE * TREE_NODE_PTR;

typedef struct _Tree {			// 트리 구조체
	TREE_NODE_PTR root;			// 루트 노드 포인터
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
		printf("%d", node->info);
		preorder(node->left);
		preorder(node->right);
	}
}

// 중위 순회
void inorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		inorder(node->left);
		printf("%d", node->info);
		inorder(node->right);
	}
}

// 후위 순회
void postorder(TREE_NODE_PTR node)
{
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%d", node->info);
	}
}
 
// 검색
TREE_NODE_PTR search(TREE_NODE_PTR node, NODE_DATA_TYPE data)
{
	if (node == NULL)
		return NULL;
		
	if (node->info > data)
		return search(node->left, data);
	else if (node->info < data)
		return search(node->right, data);

	return node;
}


// 트리에 node 추가
TREE_NODE_PTR add_Node(TREE_NODE_PTR node, NODE_DATA_TYPE data)
{	
	if (node == NULL)
		return createBNode(data, NULL, NULL);

	if (node->info > data) {
		node->left = add_Node(node->left, data);
	}
	else if (node->info < data) {
		node->right = add_Node(node->left, data);
	}

	return node;
}

TREE_NODE_PTR inorder_first_Node(TREE_NODE_PTR node)
{
	TREE_NODE_PTR res_node = node;
	if (node == NULL)
		return node;

	while (res_node->left != NULL)
		res_node = res_node->left;

	return res_node;
}

TREE_NODE_PTR inorder_last_Node(TREE_NODE_PTR node)
{
	TREE_NODE_PTR res_node = node;
	if (node == NULL)
		return node;

	while (res_node->right != NULL)
		res_node = res_node->right;

	return res_node;
}

// 트리에서 node 제거
void delete_Node(TREE_NODE_PTR node, NODE_DATA_TYPE data) // 트리에서 data 가 값인 node 를 찾아 제거
{
	TREE_NODE_PTR del_Node = search(node, data);		// 제거하려는 node
	TREE_NODE_PTR chage_Node = NULL;
	
	if (del_Node == NULL)
		return;

	// 오른쪽 서브 트리에서 중위 순회 첫번째 node 검색
	if ((chage_Node = inorder_first_Node(del_Node->right)) == NULL) {
		// 왼쪽 트리의 중위 순회 마지막 node 검색
		chage_Node = inorder_last_Node;
	}

	// 자식 노드가 없는 경우 그냥 삭제
	if (chage_Node == NULL)
		deleteBNode(del_Node);

	
}




int main()
{


	return 0;
}