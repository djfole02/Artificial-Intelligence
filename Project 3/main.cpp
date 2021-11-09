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
#include <chrono> //used for the execution time
#include <list> //used for list
#include <plot_client interface/plot.h>
#include <plot_client interface/plot_exception.h>

using namespace std;

struct node { //structure to hold the city number, the x and y coordinates, the distance from the source city, the list of its edges, the list of cities that came before it.
	int num = -1;
	long double x = 0;
	long double y = 0;
};

struct edge {
	node city1;
	node city2;
	long double a, b, c; //equation of line 0 = ax+by+c
	long double dist;

	edge(node u, node v) {
		this->city1 = u;
		this->city2 = v;
		long double m = long double((u.y - v.y) / (u.x - v.x));
		long double bcept = long double((u.y) / (m * u.x));
		this->a = m;
		this->b = -1;
		this->c = bcept;
		this->dist = sqrtl((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
	}

	edge() = default;
	
};

struct FileInfo { //structure to hold the information from the .tsp files that were given.
	string name;
	string type;
	string comment;
	int dimension = 0;
	string edge_type;
	vector<node> cities;
};

struct graph {
	vector<edge> all_edges;
	vector<node> cities_in;
	vector<node> cities_out;
	vector<node> all_cities;
	vector<node> cities_tour;

	void in_out(node c) {
		cities_in.push_back(c);
		for (int i = 0; i < (int)cities_out.size(); i++) {
			if (cities_out[i].num == c.num) {
				cities_out.erase(cities_out.begin() + i);
			}
		}
	}
	void create_edge(node u, node v) {
		edge new_edge = edge(u, v);
		all_edges.push_back(new_edge);
	}
	void remove_edge(edge e) {
		for (int i = 0; i < (int)all_edges.size(); i++) {
			if (all_edges[i].city1.num == e.city1.num && all_edges[i].city2.num == e.city2.num) {
				all_edges.erase(all_edges.begin() + i);
			}
		}
	}
	void replace_edge(edge e, node c) {
		remove_edge(e);
		create_edge(e.city1, c);
		create_edge(c, e.city2);
	}
	long double cityDistToEdgePoints(edge e, node c) {
		return sqrtl((e.city1.x - c.x) * (e.city1.x - c.x) + (e.city1.y - c.y) * (e.city1.y - c.y)) + sqrtl((e.city2.x - c.x) * (e.city2.x - c.x) + (e.city2.y - c.y) * (e.city2.y - c.y));
	}
	long double totalDistance() {
		long double dist = 0;
		for (int i = 0; i < all_edges.size(); i++) {
			dist += all_edges[i].dist;
		}
		return dist;
	}
	string tour() {
		string route = "";
		cities_tour.push_back(cities_in[0]);
		while (cities_tour.size() != all_cities.size()) {
			for (int i = 0; i < all_edges.size(); i++) {
				if (all_edges[i].city1.num == cities_tour.back().num) {
					cities_tour.push_back(all_edges[i].city2);
				}
			}
		}
		for (int i = 0; i < cities_tour.size(); i++) {
			route += to_string(cities_tour[i].num + 1) + "->";
		}
		route += to_string(cities_tour[0].num + 1) + "\n";
		return route;
	}
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
				Information.edge_type = line;
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

void makeGraph(struct graph g) {
	auto numlines = g.all_edges.size();

	auto plot = plotclient::plot::create(L"Cities");
	plot->begin_lines2d(numlines);

	for (int i = 0; i < numlines; i++) {
		plot->add_line2d(g.all_edges[i].city1.x, g.all_edges[i].city1.y, g.all_edges[i].city2.x, g.all_edges[i].city2.y);
	}
	plot->set_white_background();
	plot->set_window_size(800, 600);
	plot->set_line_thickness(1.0f);
	plot->set_point_size(6.0f);
	plot->build();
}

struct graph greedy(FileInfo I) {
	struct graph G;
	for (int i = 0; i < (int)I.cities.size(); i++) {
		G.cities_out.push_back(I.cities[i]);
		G.all_cities.push_back(I.cities[i]);
	}
	G.in_out(G.cities_out[0]);
	long double shortest = INT_MAX;
	node city;
	for (int i = 0; i < (int)G.cities_out.size(); i++) {
		long double dist = sqrtl((G.cities_in[0].x - G.cities_out[i].x) * (G.cities_in[0].x - G.cities_out[i].x) + (G.cities_in[0].y - G.cities_out[i].y) * (G.cities_in[0].y - G.cities_out[i].y));
		if (shortest > dist) {
			shortest = dist;
			city = G.cities_out[i];
		}
	}
	G.in_out(city);
	G.create_edge(G.cities_in[0], G.cities_in[1]);
	int count = 0;
	while ((int)G.cities_out.size() > 0) {
		long double close = INT_MAX;
		edge bestedge;
		node bestnode;
		for (int i = 0; i < (int)G.all_edges.size(); i++) {//finds the best node and the best edge, the ones that are the closest to each other.
			for (int j = 0; j < (int)G.cities_out.size(); j++) {
				long double dist = G.cityDistToEdgePoints(G.all_edges[i], G.cities_out[j]);
				if (dist < close) {
					bestedge = G.all_edges[i];
					bestnode = G.cities_out[j];
					close = dist;
				}
			}
		}
		G.replace_edge(bestedge, bestnode);
		G.in_out(bestnode);
		if (G.cities_in.size() == 3) { //sets up a triangle route
			G.create_edge(G.cities_in[1], G.cities_in[0]);
		}
		count++;
	}
	return G;
}


int main() {
	//-------------------------------------- creates a file and uses readFile to import data
	string file;
	cout << "FULL FILE PATH: ";
	cin >> file;
	FileInfo Info;
	if (readFile(file, Info) > 0) {
		cout << "Error in reading file\n";
		return 1;
	}
	//-------------------------------------- used to find the time it takes for DFS/BFS to run, outputs the routes and distance.
	auto greedyStart = chrono::steady_clock::now();
	struct graph g = greedy(Info);
	auto greedyEnd = chrono::steady_clock::now();
	printf("Elapsed Time in microseconds: %.2f\n", (double)chrono::duration_cast<chrono::microseconds>(greedyEnd - greedyStart).count());
	//-------------------------------------- used to create the string for the route taken and the distance of the route
	cout << "Greedy Route: " << g.tour();
	cout << "Total Distance: " << g.totalDistance() << endl;
	makeGraph(g);
	return 0;
}

