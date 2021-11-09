/*
Danny Foley
CSE 545 - Artificial Intelligence - University of Louisville
Project 1 8/28/2021

Traveling Salesperson Problem - find the shortest route using the brute force method.
*/




#include <iostream> //basic library
#include <fstream> //used to read files
#include <string> //used for strings
#include <vector> //used for vectors and vector manipulation
#include <algorithm> //used for the next_permutation function
#include <time.h> //used for the execution time

using namespace std;

struct coordinates { //structure to hold the city number as well as the x and y coordinates
	int num;
	long double x;
	long double y;
};

struct FileInfo { //structure to hold the information from the .tsp files that were given.
	string name;
	string type;
	string comment;
	int dimension = 0;
	string edge;
	vector<coordinates> nodes;
};

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
				coordinates dxy;
				size_t pos = 0;

				pos = line.find(" ");
				token = line.substr(0, pos);
				dxy.num = stoi(token);
				line.erase(0, pos + 1);
				pos = line.find(" ");
				token = line.substr(0, pos);
				dxy.x = stold(token);
				line.erase(0, pos + 1);
				dxy.y = stold(line);
				Information.nodes.push_back(dxy);
			}
			
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

void brute_force(FileInfo I) {
	long double s_dist = LLONG_MAX; //shortest route distance
	int size = I.dimension;
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < size; i++) { //inserts values from 0->size into the vector, these will be used as index to v2
		v1.push_back(i);
	}
	sort(v1.begin(), v1.end()); //sorts v1 by numerical value 

	do {

		long double dist = 0;
		long double x_dist = 0;
		long double y_dist = 0;
		for (int i = 1; i < size; i++) {
			x_dist = I.nodes[v1[i - 1]].x - I.nodes[v1[i]].x;
			y_dist = I.nodes[v1[i - 1]].y - I.nodes[v1[i]].y;
			dist += sqrt(x_dist * x_dist + y_dist * y_dist);
		}

		x_dist = I.nodes[v1[size - 1]].x - I.nodes[v1[0]].x;
		y_dist = I.nodes[v1[size - 1]].y - I.nodes[v1[0]].y;
		dist += sqrt(x_dist * x_dist + y_dist * y_dist);

		if (dist < s_dist) { //if the new total distance of the route is shorter than the previously shortest, make it the new shortest route and save the route in v2
			s_dist = dist;
			v2.assign(v1.begin(), v1.end());
		}
		for (int i = 0; i <= size - 1; i++) { //prints out the full route with its travel distance.
			cout << v1[i] + 1 << " -> ";
		}
		cout << v1[0] + 1 << " DIST: " << dist << endl;
		
	}while(next_permutation(v1.begin(), v1.end()) && v1[0] == 0); //creates a new permutation of the v1 vector so that 1,2,3 becomes 1,3,2 and also limits the permutaiton to only start with a 1.

	cout << "\nBRUTE FORCE SHORTEST ROUTE: \n"; //prints out the shortest route and its travel distance.
	for (int i = 0; i <= size-1; i++) {
		cout << v2[i] + 1 << " -> ";
	}
	cout << v2[0] + 1 << "      DIST: " << s_dist << endl;
}

int main() {
	
	string file;
	cout << "FULL FILE PATH: ";
	cin >> file;
	FileInfo Info;
	if (readFile(file, Info) > 0) {
		cout << "Error in reading file\n";
		return 1;
	}
	clock_t tStart = clock();
	brute_force(Info);
	printf("Time taken: %.6fs\n", (double)(clock() - (double)tStart) / CLOCKS_PER_SEC);
	return 0;
}