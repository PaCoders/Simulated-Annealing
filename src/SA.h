
/*
=====================================================================
			SIMULATED ANNEALING ALGORITHM
				Francisco Chanivet Sanchez
=====================================================================
*/

#ifndef _SA_H
#define _SA_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <climits>

#include "translatorTSPLIB.h"

using namespace std;

vector<City> genInitial(const vector<City>& nodeCities, City origin){
	
	vector<City> initial = nodeCities;
	
	auto it = find(initial.begin(),initial.end(),origin);
	
	initial.erase(it);
		
	random_shuffle(initial.begin(),initial.end());
		
	initial[0] = origin;
	initial.push_back(origin);
	
	return initial;
}

vector<City> genSuc(vector<City> currentState, size_t posCity){
	vector<City> newState = currentState;
	size_t pos;
	int direccion = rand() % 2;
	
	if(posCity == currentState.size() - 2 || (direccion == 0 && posCity > 7)){
		pos = 1 + rand() % (posCity - 1);
	}
	else{
		pos = (posCity + 1) + rand() % (currentState.size() - 2 - posCity);
	}
	
	newState[posCity] = currentState[pos];
	newState[pos] = currentState[posCity];
	
	return newState;
}

double d_euclid2D(const City& c1, const City& c2){
	return sqrt(pow(c2.coord_x() - c1.coord_x(),2) + pow(c2.coord_y() - c1.coord_y(),2));
}
double fEval(vector<City> currentState){
	double val = 0;
	
	for(size_t i = 1; i < currentState.size(); i++){
		val += d_euclid2D(currentState[i-1],currentState[i]); 
	}
	
	return val;
}

double cool(double t){
	return t *0.8;
}

vector<City> SimulatedAnnealing(vector<City> cities, City origin){
	
	double T = 9.32, T_min = 0.543;
	size_t city = 1, maxAttemps = 0; //With the counter, we can check if we have the same value almost N times
	double deltaE,p;
	
	srand(time(NULL));
	
	vector<City> currentState = genInitial(cities,origin); //We generate the initial state
	vector<City> newState;
	double deltaEaux = numeric_limits<double>::max();
	
	while(T > T_min && maxAttemps < 1000){
		newState = genSuc(currentState,city); 
		deltaE = fEval(newState) - fEval(currentState);
		
		if(deltaE < 0){
			if(deltaE < deltaEaux){ 
				currentState = newState;
				deltaEaux = deltaE;
			}
			
			++city;
		}
		else{
			p = exp(-deltaE/T);
			if(p > (double)rand()){
				currentState = newState;
				deltaEaux = deltaE;
			}
		}

		T = cool(T);
		++maxAttemps;
		
		if(city == currentState.size() - 1){
			city = 1;
		}
	}

	return currentState;
}

#endif
