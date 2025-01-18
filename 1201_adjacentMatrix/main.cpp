#include <iostream>
#include <cassert>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph(인접 행렬): vertex들끼리 어떻게 연결돼 있는지를 행렬 형태로 표현.
{
public:
	struct Vertex // Node
	{
		T item = T();
	};

	AdjMatGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		matrix_ = new int* [max_vertices_];
		for (int r = 0; r < max_vertices_; r++) {
			matrix_[r] = new int[max_vertices_];
			for (int c = 0; c < max_vertices_; c++)
				matrix_[r][c] = 0;
		}

		vertices_ = new Vertex[max_vertices_];

		n_ = 0;
	}

	~AdjMatGraph()
	{
		delete[] vertices_;

		for (int i = 0; i < max_vertices_; i++)
			delete[] matrix_[i];
		delete[] matrix_;

		if (visited_)
			delete[] visited_;
	}

	void PrintMatrix()
	{
		using namespace std;
		if (n_)
			for (int r = 0; r < n_; r++) {
				for (int c = 0; c < n_; c++)
					cout << matrix_[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		matrix_[u][v] = 1; // u에서 v로 가는 간선이 있다는 의미
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
	}

	void DepthFirstTraversal(int v) // v는 인덱스
	{
		cout << vertices_[v].item << " ";

		visited_[v] = true; // 방문했음

		for (int i = 0; i < n_; i++)
			if (matrix_[v][i] && !visited_[i]) // v에서 i로 가는 간선이 있고, i를 방문하지 않았다면
				DepthFirstTraversal(i);
	}

	void IterDFT()
	{
		ResetVisited();

		Stack<int> s;

		s.Push(0); // 0번에서 시작

		while (!s.IsEmpty())
		{
			int v = s.Top();
			s.Pop();

			if (!visited_[v])
			{
				cout << vertices_[v].item << " ";
				visited_[v] = true;

				// for (int i = 0; i < n_; i++)
				for(int i = n_ - 1; i >= 0; i--) // stack 구조에 맞춰 역순으로 탐색
					if (matrix_[v][i] && !visited_[i])
						s.Push(i);
				
				cout << "Stack: ";
				s.Print();
			}
		}

		cout << endl;
	}

	void BreadthFirstTraversal()
	{
		int v = 0; // 0번에서 시작

		Queue<int> q;

		ResetVisited();

		visited_[v] = true;

		q.Enqueue(v);

		// q.SetDebugFlag(true);
		// q.Print();
		while (!q.IsEmpty())
		{
			v = q.Front();
			q.Dequeue();

			cout << vertices_[v].item << " ";

			for (int i = 0; i < n_; i++)
				if (matrix_[v][i] && !visited_[i])
				{
					// q.Print();
					visited_[i] = true;
					q.Enqueue(i);
				}
			
			cout << "Queue: ";
			q.Print();
		}
	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화 -> 미로찾기 문제 풀 때, 전부 다 0으로 초기화하고 시작했음.
	}

private:
	int** matrix_ = nullptr;
	Vertex* vertices_ = nullptr;
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity

	bool* visited_ = nullptr;
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	/*
	// 위키피디아 버전 // https://en.wikipedia.org/wiki/Depth-first_search
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);
	g.InsertEdge(3, 0);	g.InsertEdge(0, 3);
	g.InsertEdge(4, 0);	g.InsertEdge(0, 4);
	*/

	// 강의 영상 버전 // 대칭 행렬 
	// 자기 자신과 연결 돼 있냐는 것은 0으로 표현
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0); // 양방향
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.PrintMatrix();

	g.DepthFirstTraversal(); // 0 1 3 6 4 2 5 <- Recursive DFS

	g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}

/*
	그래프 예시
	2호선 `사당역 <-> 강남역`을 이용한다고 가정했을때,
	각 역을 정점(vertex)으로, 두 정점을 잇는 간선(edge)을 그래프로 표현할 수 있다.
	또한, 2호선이 아니라, 환승을 거쳐서 `사당역 <-> 강남역`을 이용할수도 있음.
	마찬가지로 인스타 팔로우도 그래프 연결 구조를 이용해서 표현할 수 있음.

	DFT(Depth First Traversal): 깊이 우선 탐색: // `Traversal`라 해도 되고 `Search`라 해도 된다.
	- 0번에서 1번을 간 김에 1번과 연결된 3번이 있다면 거기를 탐색하는 방식

	BFT(Breadth First Traversal): 너비 우선 탐색:
	- 0번에서 1번을 갔는데 아니면 0번으로 다시 돌아와서 2번으로 가는 방식

	Stack-based graph traversal ≠ depth first search
	refer: https://11011110.github.io/blog/2013/12/17/stack-based-graph-traversal.html
*/