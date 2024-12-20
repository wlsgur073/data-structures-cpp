#include <iostream>

#include "../shared/BinaryTree.h"

using namespace std;

/*
[용어]
- 선형 자료구조 vs 비선형 자료구조
- 트리(tree), 서브트리(subtree)
- 노드(node), 루트(root) 노드,
- 부모 노드, 자식 노드, 형제(sibling) 노드, 조상(ancestor) 노드, 후손(descendent) 노드
- 단말 노드(terminal node, leaf node), 비단말 노드(nonterminal node)
- 노드의 차수(degree): 자식 노드의 개수
- 트리의 차수: 노드들의 차수 중 가장 큰 차수
- 레벨(루트의 레벨은 1), 깊이, 높이 https://stackoverflow.com/questions/2603692/what-is-the-difference-between-tree-depth-and-height
- 높이: 최대 레벨
- 간선(edge)
- 이진 트리: 모든 노드의 차수가 2 이하 (최대 2개의 자식 노드)
- 포화 이진 트리(full binary tree): 모든 노드가 가득 차 있는 트리
- 완전 이진 트리(complete binary tree): 마지막 레벨 외에는 모두 다 차있고 마지막 레벨은 왼쪽부터 차있는 트리 (중간 빈곳 X)
*/

int main()
{
	// 배열로도 구현 가능

	using Node = BinaryTree<int>::Node;

	Node* n1 = new Node{ 1, nullptr, nullptr };
	Node* n2 = new Node{ 2, n1, nullptr };
	Node* n3 = new Node{ 3, nullptr, nullptr };
	Node* n4 = new Node{ 4, nullptr, nullptr };
	Node* n5 = new Node{ 5, nullptr, n4 };
	Node* n6 = new Node{ 6, n2, n5 };

	n1->right = n3; // <- 연결관계 변경

	BinaryTree<int> tree(n6); // <- n6의 주소를 root node로 

	tree.Print2D();

	cout << "Sum: " << tree.Sum() << endl; //Sum: 21
	cout << "Height: " << tree.Height() << endl; //Height : 4


	// Tree traversal methods

	cout << "Preorder" << endl; // 6 2 1 3 5 4
	tree.Preorder(); // root 이후 왼쪽 기준으로 단말노드까지 가고 나서 오른쪽으로 이동
	cout << endl;

	cout << "Inorder" << endl; // 1 3 2 6 5 4
	tree.Inorder(); // 왼쪽 단말노드부터 시작해서 있으면 계속 visit, 오른쪽
	cout << endl;

	cout << "Postorder" << endl; // 3 1 2 4 5 6
	tree.Postorder();
	cout << endl;

	cout << "LevelOrder" << endl; // 6 2 5 1 4 3
	tree.LevelOrder(); // 재귀 사용하지 마셈.
	cout << endl;

	cout << "Iterative Preorder" << endl; // 6 2 1 3 5 4
	tree.IterPreorder();
	cout << endl;

	cout << "Iterative Inorder" << endl; // 1 3 2 6 5 4
	tree.IterInorder();
	cout << endl;

	cout << "Iterative Postorder" << endl; // 3 1 2 4 5 6
	tree.IterPostorder();
	cout << endl;

	return 0;
}
