/*
Danny Foley
CSE 545 - Artificial Intelligence - University of Louisville
Project 2 9/13/2021

Traveling Salesperson Problem - find the shortest route using BFS and DFS
*/

#include <iostream> //basic library
#include <fstream> //used to read files
#include <string> //used for strings
#include <vector> //used for vectors and vector manipulation
#include <algorithm> //used for the next_permutation function
#include <time.h> //used for the execution time
#include <list> //used for list 


using namespace std;



struct node { //structure to hold the city number, the x and y coordinates, the distance from the source city, the list of its edges, the list of cities that came before it.
	int num = -1;
	long double x = 0;
	long double y = 0;
	long double dist = 0;
	vector<int> citybefore = {};
	vector<int> edges_going = {};
};

struct FileInfo { //structure to hold the information from the .tsp files that were given.
	string name;
	string type;
	string comment;
	int dimension = 0;
	string edge;
	vector<node> cities;
};

vector<node> DFS_Cities; //global vector of cities for DFS to use.

int readFile(string filename, FileInfo &Information) { //reads information from the .tsp file into the FileInfo struct.
	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.substr(0, 6) == "NAME: ") {
				line.erase(0, 6);
				Information.name = line;
			}
			else if (line.substr(0, 6) == "TYPE: ") {
				line.erase(0, 6);
				Information.type = line;
			}
			else if (line.substr(0, 9) == "COMMENT: ") {
				line.erase(0, 9);
				if (Information.comment.empty()) {
					Information.comment = line;
				}
				else {
					Information.comment += " ";
					Information.comment += line;
				}
			}
			else if (line.substr(0, 11) == "DIMENSION: ") {
				line.erase(0, 11);
				Information.dimension = stoi(line);
			}
			else if (line.substr(0, 18) == "EDGE_WEIGHT_TYPE: ") {
				line.erase(0, 18);
				Information.edge = line;
			}
			else if (line.substr(0, 18) == "NODE_COORD_SECTION") {
			}
			else {
				string token;
				int num;
				long double x;
				long double y;
				size_t pos = 0;

				pos = line.find(" ");
				token = line.substr(0, pos);
				num = stoi(token);
				line.erase(0, pos + 1);
				pos = line.find(" ");
				token = line.substr(0, pos);
				x = stold(token);
				line.erase(0, pos + 1);
				y = stold(line);
				node newCity;
				newCity.num = num - 1;
				newCity.x = x;
				newCity.y = y;
				Information.cities.push_back(newCity);
			}
			
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

void DFS(list<int>* queue) {//implements the DFS approach 
	node frontier;
	if (queue->empty()) {
		queue->push_back(DFS_Cities[0].num);
		frontier = DFS_Cities[0];
		DFS_Cities[0].citybefore.push_back(0);
	}
	else {
		int num = queue->back();
		frontier = DFS_Cities[num];
	}
	for (int i = 0; i < (int)frontier.edges_going.size(); i++) { //checks the edges and updates information for the cities if the new distance is less than the previous distance via a route.
		long double edge_distance = sqrtl((DFS_Cities[frontier.edges_going[i]].x - frontier.x) * (DFS_Cities[frontier.edges_going[i]].x - frontier.x) + (DFS_Cities[frontier.edges_going[i]].y - frontier.y) * (DFS_Cities[frontier.edges_going[i]].y - frontier.y));
		if (DFS_Cities[frontier.edges_going[i]].dist > (frontier.dist + edge_distance)) {
			DFS_Cities[frontier.edges_going[i]].dist = (frontier.dist + edge_distance);
			DFS_Cities[frontier.edges_going[i]].citybefore.clear();
			DFS_Cities[frontier.edges_going[i]].citybefore.insert(DFS_Cities[frontier.edges_going[i]].citybefore.end(), frontier.citybefore.begin(), frontier.citybefore.end());
			DFS_Cities[frontier.edges_going[i]].citybefore.push_back(frontier.num);
		}
		queue->push_back(frontier.edges_going[i]); //pushes back the edge
		DFS(queue); //calls DFS again
		queue->remove(frontier.num);
	}
}

void BFS(vector<node> vCity, list<int> queue, string* bfs_path) { //implements the BFS algorithm
	node frontier;
	if (queue.empty()) {
		frontier = vCity[0];
		vCity[0].citybefore.push_back(0);
	}
	else {
		
		int num = queue.front();
		frontier = vCity[num];
		if (queue.size() == 1) {
			queue.erase(queue.begin());
		}
		else {
			queue.pop_front();
		}
		
	}
	if (frontier.edges_going.size() != 0) {
		for (int i = 0; i < (int)frontier.edges_going.size(); i++) { //checks the edges and updates information for the cities if the new distance is less than the previous distance via a route.
			list<int>::iterator c = find(queue.begin(), queue.end(), frontier.edges_going[i]);
			if (c == queue.end()) {
				queue.push_back(frontier.edges_going[i]);
			}
			long double edge_distance = sqrtl((vCity[frontier.edges_going[i]].x - frontier.x) * (vCity[frontier.edges_going[i]].x - frontier.x) + (vCity[frontier.edges_going[i]].y - frontier.y) * (vCity[frontier.edges_going[i]].y - frontier.y));
			if (vCity[frontier.edges_going[i]].dist > (frontier.dist + edge_distance)) {
				vCity[frontier.edges_going[i]].dist = (frontier.dist + edge_distance);
				vCity[frontier.edges_going[i]].citybefore.clear();
				vCity[frontier.edges_going[i]].citybefore.insert(vCity[frontier.edges_going[i]].citybefore.end(), frontier.citybefore.begin(), frontier.citybefore.end());
				vCity[frontier.edges_going[i]].citybefore.push_back(frontier.num);
			}
		}
	}
	if (queue.size() > 0) {
		BFS(vCity, queue, bfs_path);
	}
	else {
		for (int i = 0; i < (int)vCity[10].citybefore.size(); i++) { //looks at destination city's history and makes path a string
			*bfs_path += to_string(vCity[10].citybefore[i] + 1) + " -> ";
		}
		*bfs_path += "11 | Total Distance: ";
		*bfs_path += to_string(vCity[10].dist);
		return;
	}
}

int main() {
	int cityedges[11][11] = { //shows the relationship of connections between cities (from the project 2 document) we will be using a numbering starting at 0 to make things easier, printing the correct information at the end
		{0,1,1,1,0,0,0,0,0,0,0}, //0
		{0,0,1,0,0,0,0,0,0,0,0}, //1
		{0,0,0,1,1,0,0,0,0,0,0}, //2
		{0,0,0,0,1,1,1,0,0,0,0}, //3
		{0,0,0,0,0,0,1,1,0,0,0}, //4
		{0,0,0,0,0,0,0,1,0,0,0}, //5
		{0,0,0,0,0,0,0,0,1,1,0}, //6
		{0,0,0,0,0,0,0,0,1,1,1}, //7
		{0,0,0,0,0,0,0,0,0,0,1}, //8
		{0,0,0,0,0,0,0,0,0,0,1}, //9
		{0,0,0,0,0,0,0,0,0,0,0}  //10
	};
	//-------------------------------------- creates a file and uses readFile to import data
	string file;
	cout << "FULL FILE PATH: ";
	cin >> file;
	FileInfo Info;
	if (readFile(file, Info) > 0) {
		cout << "Error in reading file\n";
		return 1;
	}
	//------------------------------------- reads the data from cityedges[][] and imports to FileInfo
	for (int i = 0; i < 11; i++) {
		if (i == 0) {
			Info.cities[i].dist = 0;
		}
		else {
			Info.cities[i].dist = LONG_MAX;
		}
		for (int j = 0; j < 11; j++) {
			if (cityedges[i][j] == 1) {
				Info.cities[i].edges_going.push_back(j);
			}
		}
	}
	//------------------------------------ setup the city vectors for the DFS and BFS method as well as the queue for each
	list<int> bfsq;
	list<int> dfsq;
	vector<node> BFS_Cities;
	
	string bfs_path;
	string dfs_path;

	for (int i = 0; i < (int)Info.cities.size(); i++) {
		BFS_Cities.push_back(Info.cities[i]);
		DFS_Cities.push_back(Info.cities[i]);
	}
	//------------------------------------ used to find the time it takes for DFS/BFS to run, outputs the routes and distance.

	clock_t BFSStart = clock();
	BFS(BFS_Cities, bfsq, &bfs_path);
	clock_t BFSEnd = clock();
	printf("BFS Time taken: %.6fs\n", (double)(BFSEnd - (double)BFSStart) / CLOCKS_PER_SEC);
	cout << "BFS Shortest Path: " << bfs_path;
	clock_t DFSStart = clock();
	DFS(&dfsq);
	for (int i = 0; i < (int)DFS_Cities[10].citybefore.size(); i++) { //looks at destination city's history and makes path a string
		dfs_path += to_string(DFS_Cities[10].citybefore[i] + 1) + " -> ";
	}
	dfs_path += "11 | Total Distance: " + to_string(DFS_Cities[10].dist);
	clock_t DFSEnd = clock();
	printf("\nDFS Time taken: %.6fs\n", (double)(DFSEnd - (double)DFSStart) / CLOCKS_PER_SEC);
	cout << "DFS Shortest Path: " << dfs_path;
	return 0;
}

