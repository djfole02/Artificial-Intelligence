/*
Danny Foley
CSE 545 - Artificial Intelligence - University of Louisville
Project 4 10/23/2021

Traveling Salesperson Problem - find the shortest route using GA
*/

#include <iostream> //basic library
#include <fstream> //used to read files
#include <string> //used for strings
#include <vector> //used for vectors and vector manipulation
#include <algorithm> //used for the next_permutation function
#include <chrono> //used for the execution time
#include <list> //used for list
#include <windows.h>
#include <cstdlib>
#include <plot_client interface/plot.h>
#include <plot_client interface/plot_exception.h>

const wchar_t *dir = L"C:\\Users\\mathe\\source\\repos\\TSP\\TSP\\graph";

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
	long double dist;

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
	void tour() {
		string route = "";
		cities_tour.push_back(cities_in[0]);
		while (cities_tour.size() < all_cities.size()) {
			for (int i = 0; i < all_edges.size(); i++) {
				if (all_edges[i].city1.num == cities_tour.back().num) {
					cities_tour.push_back(all_edges[i].city2);
				}
			}
		}
	}
	void print_tour() {
		string route = "";
		for (int i = 0; i < cities_tour.size(); i++) {
			if (i != cities_tour.size() - 1) {
				route += to_string(cities_tour[i].num + 1) + "->";
			}
			else {
				route += to_string(cities_tour[i].num + 1);
			}
		}
		cout << route << endl;
	}
	void insertion(FileInfo I) { //used to insert the information from FileInfo into a graph.
		for (int i = 0; i < I.cities.size(); i++) {
			cities_out.push_back(I.cities[i]);
			all_cities.push_back(I.cities[i]);
		}
		while (cities_out.size() != 0) {
			int index = rand() % cities_out.size();
			in_out(cities_out[index]);
		}
		for (int i = 0; i < cities_in.size() - 1; i++) {
			create_edge(cities_in[i], cities_in[i + 1]);
		}
		create_edge(cities_in[cities_in.size() - 1], cities_in[0]);
		tour();
		dist = totalDistance();
	}
	bool check(int num) { //see if a city number is not contained in the cities_out vector, if it is = return false;
		for (int i = 0; i < cities_out.size(); i++) {
			if (num == cities_out[i].num) {
				return false;
			}
		}
		return true;
	}

	void afterCrossover() { //used to make sure that everything is setup once a child has been produced from crossover
		while (cities_out.size() != 0) {
			all_cities.push_back(cities_out.front());
			in_out(cities_out.front());
		}
		for (int i = 0; i < cities_in.size() - 1; i++) {
			create_edge(cities_in[i], cities_in[i + 1]);
		}
		create_edge(cities_in[cities_in.size() - 1], cities_in[0]);
		tour();
		dist = totalDistance();
	}

	void afterMutation() {
		all_edges.clear();
		cities_tour.clear();
		for (int i = 0; i < cities_in.size() - 1; i++) {
			create_edge(cities_in[i], cities_in[i + 1]);
		}
		create_edge(cities_in[cities_in.size() - 1], cities_in[0]);
		tour();
		dist = totalDistance();
	}
};

struct dna_results {
	vector<graph> pop;
	int generation;
	vector<graph> best;

	void rank_tours() {
		int i, j;
		graph key;
		for (i = 1; i < pop.size(); i++) {
			key = pop[i];
			j = i - 1;
			while (j >= 0 && pop[j].dist > key.dist) {
				pop[j + 1] = pop[j];
				j = j - 1;
			}
			pop[j + 1] = key;
		}
	}
	vector<graph> order_crossover(graph p1, graph p2) {//returns two children after performing an order crossover.
		vector<graph> c;
		graph c1;
		graph c2;
		int size = p1.all_cities.size();
		//---------------------------------------------- create two crossover points
		int rdp1 = (rand() % size);
		int rdp2 = rdp1 + (rand() % (size-rdp1));
		//---------------------------------------------- use the crossover algorithm OX1
		for (int i = rdp1; i <= rdp2; i++) {
			c1.cities_out.push_back(p1.cities_in[i]);
			c2.cities_out.push_back(p2.cities_in[i]);
		}
		for (int i = rdp2; i < size; i++) {
			if (c1.check(p2.cities_in[i].num)) {
				c1.cities_out.push_back(p2.cities_in[i]);
			}
			if (c2.check(p1.cities_in[i].num)) {
				c2.cities_out.push_back(p1.cities_in[i]);
			}
		}
		for (int i = 0; i < rdp2; i++) {
			if (c1.check(p2.cities_in[i].num)) {
				c1.cities_out.insert(c1.cities_out.begin(), p2.cities_in[i]);
			}
			if (c2.check(p1.cities_in[i].num)) {
				c2.cities_out.insert(c2.cities_out.begin(), p1.cities_in[i]);
			}
		}
		//--------------------------------------------- make sure the children have everything else they need and ship them off
		c1.afterCrossover();
		c2.afterCrossover();
		c.push_back(c1);
		c.push_back(c2);
		return c;
	}
	vector<graph> swap_mutation() {//goes through population and swaps two cities
		vector<graph> m;
		for (int i = 0; i < pop.size(); i++) {
			m.push_back(pop[i]);
		}
		for (int i = 0; i < m.size(); i++) {
			int rate = rand() % 2; //there is a 50% mutation rate
			if (rate == 1) {
				//cout << "MUTATING" << endl;
				int m1 = rand() % (int)(m[i].all_cities.size()-1);
				int m2 = rand() % (int)(m[i].all_cities.size());
				node mut;
				if (m1 == m2) {
					m2 += 1;
				}
				mut = m[i].cities_in[m2];
				m[i].cities_in[m2] = m[i].cities_in[m1];
				m[i].cities_in[m1] = mut;
				m[i].afterMutation();
			}
		}
		return m;
	}

	vector<graph> inverse_mutation() {//takes a section of link 5 in the tour and reveres
		vector<graph> m;
		for (int i = 0; i < pop.size(); i++) {
			m.push_back(pop[i]);
		}
		for (int i = 0; i < m.size(); i++) {
			int rate = rand() % 2; //50% mutation rate
			if (rate == 1) {
				//cout << "MUTATING" << endl;
				int m1 = rand() % (int)(m[i].all_cities.size()-5);
				int m2 = m1 + 5;
				
				for (int i = 0; i < m.size(); i++) {
					vector<node> muts;
					for (int j = m2; j > m1; j--) {
						muts.push_back(m[i].cities_in[j]);
					}
					int index = 0;
					for (int j = m1; j < m2; j++) {
						m[i].cities_in[j] = muts[index];
						index++;
					}
				}
			}
		}
		return m;
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

void makeGraph(struct graph g, int gen, string savefile) {
	
	if (gen != -1) {
		//to make the savefile name
		wstring widestr = wstring(savefile.begin(), savefile.end());
		const wchar_t* plotname = widestr.c_str();
		//to make the title of the graph have gen number and distance
		string dist = "Generation: " + to_string(gen) + "\n" + "Distance: " + to_string(g.dist);
		wstring widestr_dist = wstring(dist.begin(), dist.end());
		const wchar_t* title = widestr_dist.c_str();
		auto numlines = g.all_edges.size();
		auto plot = plotclient::plot::create(plotname);
		plot->begin_lines2d(numlines);

		for (int i = 0; i < numlines; i++) {
			plot->add_line2d(g.all_edges[i].city1.x, g.all_edges[i].city1.y, g.all_edges[i].city2.x, g.all_edges[i].city2.y);
		}
		plot->set_title(title);
		plot->set_white_background();
		plot->set_window_size(800, 600);
		plot->set_line_thickness(1.0f);
		plot->set_point_size(6.0f);
		plot->set_write_file(2, dir);
		plot->build();
	}
	else {
		wstring widestr = wstring(savefile.begin(), savefile.end());
		const wchar_t* plotname = widestr.c_str();
		//to make the title of the graph have gen number and distance
		string dist = "Generation vs Cost";
		wstring widestr_dist = wstring(dist.begin(), dist.end());
		const wchar_t* title = widestr_dist.c_str();
		auto numpoints = g.all_cities.size();
		auto plot = plotclient::plot::create(plotname);
		plot->begin_points2d(numpoints);
		for (int i = 0; i < numpoints; i++) {
			plot->add_point2d(g.all_cities[i].x, g.all_cities[i].y);
		}
		plot->set_title(title);
		plot->set_white_background();
		plot->set_window_size(800, 600);
		plot->set_point_size(3.0f);
		plot->set_axis_labels(L"Generation", L"Cost/Distance", L"");
		plot->set_write_file(2, dir);
		plot->build();
	}
	
}

dna_results crossover_method(dna_results dna, string crossover) { //returns two children populations from two parent populations.
	dna_results children;
	while (1) {
		int c1 = rand() % (int)(dna.pop.size() * .1); //takes from the top 10%
		int c2 = rand() % (int)(dna.pop.size() * .5); //takes from the top 50%
		if (crossover == "order_crossover") {
			//cout << "CROSSING" << endl;
			vector<graph> c = dna.order_crossover(dna.pop[c1], dna.pop[c2]);
			children.pop.push_back(c[0]);
			children.pop.push_back(c[1]);
		}
		if (children.pop.size() == 100) {
			break;
		}
	}
	children.rank_tours();
	return children;
}

dna_results mutation_method(dna_results dna, string mutation) {
	dna_results mutants;
	if (mutation == "swap_mutation") {
		vector<graph> m = dna.swap_mutation();
		for (int i = 0; i < m.size(); i++) {
			mutants.pop.push_back(m[i]);
		}
	}
	if (mutation == "inverse_mutation") {
		vector<graph> m = dna.inverse_mutation();
		for (int i = 0; i < m.size(); i++) {
			mutants.pop.push_back(m[i]);
		}
	}
	return mutants;
}

vector<dna_results> dna(FileInfo I, string mutate, string crossover, int iterations, int pop_size) {
	int gen = 0;
	int index = 0;
	long double best_dist = LLONG_MAX;
	vector<dna_results> dna;
	dna_results d;
	//-------------------------------------- creates a population (of pop_size) of routes. 
	for (int i = 0; i < pop_size; i++) {
		graph g;
		g.insertion(I);
		d.pop.push_back(g);
	}
	d.rank_tours();
	//-------------------------------------- create new generations with a crossover and mutation until no progress is made for x generations
	while (index < iterations) {
		gen++;
		//cout << "Gen: " << gen << endl;
		index++;
		dna_results new_generation_c = crossover_method(d, crossover);
		dna_results new_generation = mutation_method(new_generation_c, mutate);
		d.pop.clear();
		d.pop.insert(d.pop.begin(), new_generation_c.pop.begin(), new_generation_c.pop.end());
		d.generation = gen;
		if (d.pop[0].dist < best_dist) {
			index = 0;
			best_dist = d.pop[0].dist;
		}
		dna.push_back(d);
	}
	return dna;
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
	auto dnaStart = chrono::steady_clock::now();
	srand((unsigned)time(NULL));
	string cross = "order_crossover"; //crossover method
	string mut = "inverse_mutation"; //mutation method (can either be "inverse_mutation" or "swap_mutation")
	int iterations = 100; //number of iterations to do until no progress is made.
	int population_size = 100;
	vector<dna_results> best_results;
	vector<dna_results> results = dna(Info, mut, cross, iterations, population_size);
	auto dnaEnd = chrono::steady_clock::now();

	//-------------------------------------- used to create the graphs and output the final tour/distance/generation
	long double best = LLONG_MAX;
	for (int i = 0; i < results.size(); i++) {
		if (results[i].pop[0].dist < best) {
			best_results.push_back(results[i]);
			best = results[i].pop[0].dist;
		}
	}
	for (int i = 0; i < best_results.size(); i++) {
		makeGraph(best_results[i].pop[0], best_results[i].generation, "graph" + to_string(i));
		Sleep(500);
		if (i % 10 == 0 && i != 0) {
			system("taskkill /F /IM plot.exe >nul 2>&1");
		}
	}

	graph g;
	for (int i = 0; i < results.size(); i++) {
		node value;
		value.num = i;
		value.x = results[i].generation;
		value.y = results[i].pop[0].dist;
		g.all_cities.push_back(value);
	}
	printf("Elapsed Time in seconds: %.2f\n", (double)chrono::duration_cast<chrono::seconds>(dnaEnd - dnaStart).count());
	cout << "Total Generations: " << results.back().generation << endl;
	cout << "Best Generation: " << best_results.back().generation << endl;
	cout << "Best Distance: " << best_results.back().pop[0].dist << endl;
	cout << "Best Route: " << endl;
	best_results.back().pop[0].print_tour();
	
	system("taskkill /F /IM plot.exe >nul 2>&1");

	//shows the best route found and the cost to generation graph as well as opening a gif that is made after running a python code.
	makeGraph(g, -1, "cost_vs_generation");
	makeGraph(best_results.back().pop[0], best_results.back().generation, "graphfinal");
	cout << "Run the Python Code to Create a Gif, Once Created Then: " << endl;
	system("pause");
	system("C:\\Users\\mathe\\source\\repos\\GUIGifMaker\\GUIGifMaker\\project4.gif");
		
	
	return 0;
}

