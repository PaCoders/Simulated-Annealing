
/*
=====================================================================
				TRANSLATOR OF TSPLIB FORMAT
				Francisco Chanivet Sanchez
=====================================================================
*/

#ifndef _TRANSLATORTSPLIB_H
#define _TRANSLATORTSPLIB_H

#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

class City{
	public:
		City(unsigned int i, double cx = 0, double cy = 0):id_(i), x_(cx), y_(cy){}
		inline unsigned int id() const{return id_;}
		inline double coord_x() const{return x_;}
		inline double coord_y() const{return y_;}
	private:
		unsigned int id_;
		double x_,y_;
};

bool operator==(const City& c1, const City& c2){
	return c1.id() == c2.id();
}

bool operator!=(const City& c1, const City& c2){
	return !(c1.id() == c2.id());
}

bool operator<(const City& c1, const City& c2){
	return (c1 != c2) && (c1.id() < c2.id());
}

vector<City> translatorTSP(string file_name){

	string path = "file_instances/";
	file_name += ".tsp";
	path += file_name;
	
	ifstream file(path);
	string line;
	vector<City> cities;
	unsigned int id_c;
	double x, y;
	while(getline(file,line) && line != "EOF"){
		if(sscanf(line.c_str(),"%u %lf %lf",&id_c,&x,&y) == 3 || sscanf(line.c_str(),"\t%u %lf %lf",&id_c,&x,&y) == 3){
			cities.push_back(City(id_c,x,y));
		}
	}
	
	file.close();
	
	return cities;
}

#endif
