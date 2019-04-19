#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Vertex {
public:
	int id;
	vector<int> nr; ///adjanency list implementation, nr stands for neighbour
	vector<int>::iterator nritr;

	Vertex() {}

	Vertex(int x) {
		id = x;
	};

	void cid(int x) {
		id = x;
	};

	void del_nr(int x, bool must) {
		nritr = find(nr.begin(), nr.end(), x);
		if (nritr != nr.end())
			nr.erase(nritr);
		else
			if (must)
				cout << "No such edge." << endl;
	}

	vector<int> show_nr() {
		sort(nr.begin(), nr.end());
		return nr;
	}

	friend bool operator == (const Vertex& lhs, const Vertex& rhs) {
		return lhs.id == rhs.id;
	}
};

class Graph {
public:
	Graph() {
	};

	Vertex findv(int x) {
		Vertex temp(x);
		return temp;
	}

	void InsertNode(int x) {
		Vertex temp(x);
		itr = find(maze.begin(), maze.end(), temp);
		if (itr == maze.end()) {
			maze.push_back(temp);
		}
		else
			cout << "ID exists.";
	};

	void InsertEdge(int x, int y) {
		itr = find(maze.begin(), maze.end(), findv(x)); //itr will be pointing at the node that is x
		itr2 = find(maze.begin(), maze.end(), findv(y));
		if (itr != maze.end() and itr2 != maze.end())
			itr->nr.push_back(y);
		else
			cout << "No such node." << endl;
	};

	void DeleteNode(int x) {
		itr = find(maze.begin(), maze.end(), findv(x));
		if (itr != maze.end()) {
			maze.erase(itr);
			for (itr = maze.begin(); itr != maze.end(); itr++)
				itr->del_nr(x, false);
		}
		else
			cout << "No such node." << endl;
	};

	void DeleteEdge(int x, int y) {
		itr = find(maze.begin(), maze.end(), findv(x));
		itr2 = find(maze.begin(), maze.end(), findv(y));
		if (itr != maze.end() and itr2 != maze.end())
			itr->del_nr(y, true);
		else
			cout << "No such node." << endl;
	};

	void CommonNeighbor(int x, int y) {
		vector<int> intera, interb, intersection;
		itr = find(maze.begin(), maze.end(), x);
		itr2 = find(maze.begin(), maze.end(), y);
		if (itr != maze.end() and itr2 != maze.end()) {
			intera = itr->show_nr();
			interb = itr2->show_nr();
			set_intersection(intera.begin(), intera.end(), interb.begin(), interb.end(), back_inserter(intersection));
			if (!intersection.empty()) {
				for (int n : intersection) //for each of the element
					cout << n << endl;
			}
			else
				cout << "No common neighbor." << endl;
		}
		else
			cout << "No such node." << endl;
	};

	void ShortestPath(int source, int destination) {
		vector<vector<Vertex>::iterator> q;
		vector<int> visited, neighbor, path;
		vector<int>::iterator found;
		map<int, int> previous;
		Vertex v(source);
		bool found_des = false;

		itr = find(maze.begin(), maze.end(), v);
		q.push_back(itr);
		visited.push_back(itr->id);
		while (!q.empty() and !found_des) {
			itr = *(q.begin());
			q.erase(q.begin());
			visited.push_back(itr->id);
			neighbor = itr->show_nr();
			for (int node : neighbor) {
				v.cid(node);
				found = find(visited.begin(), visited.end(), v.id);
				if (found != visited.end()) continue;
				itr = find(maze.begin(), maze.end(), v);
				q.push_back(itr);
				previous.insert(pair<int, int>(v.id, itr->id));
				if (node == destination) {
					found_des = true;
					break;
				}
			}
		}

		if (found_des) {
			int n = destination;
			path.push_back(n);
			while (n != source) {
				n = previous[n];
				path.push_back(n);
			}
			reverse(path.begin(), path.end());
			for (int n : path) {
				cout << n << endl;
			}
		}
		else
			cout << "No path found." << endl;
	}

	void ShowNeighbor(int x) {
		itr = find(maze.begin(), maze.end(), findv(x));
		if (itr != maze.end()) {
			vector<int> temp;
			vector<int>::iterator tempitr;
			itr = find(maze.begin(), maze.end(), findv(x));
			temp = itr->show_nr();
			if (!temp.empty()) {
				for (tempitr = temp.begin(); tempitr != temp.end(); tempitr++)
					cout << *(tempitr) << endl;
			}
			else
				cout << "No neighbor found." << endl;
		}
		else
			cout << "No node found" << endl;
	}
private:
	vector<Vertex> maze;
	vector<Vertex>::iterator itr;
	vector<Vertex>::iterator itr2;
};


int main() {
	Graph g;
	string command;
	int id1, id2;
	while (cin >> command) {
		if (command == "InsertNode") {
			cin >> id1;
			g.InsertNode(id1);
		}
		else if (command == "InsertEdge") {
			cin >> id1 >> id2;
			g.InsertEdge(id1, id2);
		}
		else if (command == "ShowNeighbor") {
			cin >> id1;
			g.ShowNeighbor(id1);
		}
		else if (command == "CommonNeighbor") {
			cin >> id1 >> id2;
			g.CommonNeighbor(id1, id2);
		}
		else if (command == "DeleteNode") {
			cin >> id1;
			g.DeleteNode(id1);
		}
		else if (command == "DeleteEdge") {
			cin >> id1 >> id2;
			g.DeleteEdge(id1, id2);
		}
		else if (command == "ShortestPath") {
			cin >> id1 >> id2;
			g.ShortestPath(id1, id2);
		}
		else if (command == "Exit") {
			break;
		}
	}
	return 0;
}