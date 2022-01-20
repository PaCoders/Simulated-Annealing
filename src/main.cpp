
/*
==================================================================
			MAIN PROGRAM OF THE ASSIGNMENT
				Francisco Chanivet Sanchez
==================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "translatorTSPLIB.h"
#include "SA.h"
#include "cronometro.h"

using namespace std;


double optSolution(string file_,vector<City> coord){
	//We open the optimal opt.tour to compute the absolute and relative error
		ifstream file(file_);
		vector<unsigned int> optimalState;
		vector<City> optimalPath;
		string line;
		unsigned int id_c, origin;
		size_t cont = 0;
		
		while(getline(file,line) && (line != "EOF" && line != "-1")){
			if(sscanf(line.c_str(),"%u",&id_c) == 1){
				optimalState.push_back(id_c);
				if(cont == 0){
					origin = id_c;
					cont++;
				}
			}
		}
		file.close();
		optimalState.push_back(origin);
		
		for(size_t i = 0; i < optimalState.size(); i++){
			City c(optimalState[i]);
			auto it = find(coord.begin(),coord.end(),c);
			optimalPath.push_back(*it);
		}

	//Compute the optimal cost of the path
		return fEval(optimalPath);
}


double absoluteError(vector<double> costs, double optSol){
	vector<double> costsAux = costs;
	vector<double> costs_;
	vector<size_t> frecs;
	double cost;
	
	while(!costsAux.empty()){
		cost = costsAux.front();
		frecs.push_back(count(costsAux.begin(),costsAux.end(),cost));
		costs_.push_back(cost);
		for(size_t i = 0; i < costsAux.size(); i++){
			if(costsAux[i] == cost){
				costsAux.erase(costsAux.begin() + i);
				--i;
			}
		}
	}
	
	double val = 0;
	
	for(size_t i = 0; i < costs_.size(); i++){
		val += (costs_[i]*frecs[i]);
	}
	
	return (val/costs.size()) - optSol;
}

double relativeError(vector<double> costs, double optSol){
	vector<double> costsAux = costs;
	vector<double> costs_;
	vector<size_t> frecs;
	double cost;
	
	while(!costsAux.empty()){
		cost = costsAux.front();
		frecs.push_back(count(costsAux.begin(),costsAux.end(),cost));
		costs_.push_back(cost);
		for(size_t i = 0; i < costsAux.size(); i++){
			if(costsAux[i] == cost){
				costsAux.erase(costsAux.begin() + i);
				--i;
			}
		}
	}
	
	double val = 0;
	
	for(size_t i = 0; i < costs_.size(); i++){
		val += (costs_[i]*frecs[i]);
	}
	
	return optSol/(val/costs.size());
}

int main(){
	vector<City> cities;
	string name = "eil51";
	
	int option;
	cout<<"Choose one option: \n"<<"1. Run one time.\n"<<"2. Check run time and absolute/relative error.\n";
	cin>>option;

	cities = translatorTSP(name);
	
	City originCity(1); //Nodo origen
	
	auto it = find(cities.begin(),cities.end(), originCity);
	
	cout<<"We beginning in the city: "<<(*it).id()<<"("<<(*it).coord_x()<<", "<<(*it).coord_y()<<")"<<endl;
	if(option == 1){
		vector<City> final = SimulatedAnnealing(cities,(*it));

		cout<<"Number of cities: "<<cities.size()<<endl;
		cout<<"Cost: "<<fEval(final)<<endl;
	}
	else{
		cronometro c;
		double e_abs_t = 1e-6, e_rel_t = 1e-4;
	
		vector<double> costs;
	
		size_t r = 0;
		string file = "optimal_solutions/" + name + ".opt.tour";
		double optCost = optSolution(file,cities);
	
		c.activar();
		do{
			vector<City> final = SimulatedAnnealing(cities,*it);
			costs.push_back(fEval(final));
			//cout<<"The cost for the instance "<<name<<".tsp is: "<<fEval(final)<<endl;
			++r;
		}while(c.tiempo() < e_abs_t/e_abs_t + e_rel_t);
		c.parar();

		cout<<"Time: "<<c.tiempo()/r<<", Absolute error: "<<absoluteError(costs,optCost)<<", Relative error: "<<relativeError(costs,optCost)<<endl;
	}
	return 0;
}
