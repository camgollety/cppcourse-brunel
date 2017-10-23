#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"

using namespace std;



class Network {
	
	private: 
	
	vector<Neuron*> neurons; 
	vector<vector<unsigned int>> connexions; ///connexions between neurons 
	
	public: 
	
	Network(); 
	virtual ~Network();
	void addNeuron(); 
	void connect(unsigned int n1, unsigned int n2); ///x/= y et ils existent et et x et y plus petits que la taille du tableau neurones 
	
	int getNeuronClock(int i) const;
	
	void update(double I);
};

#endif
