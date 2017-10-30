#include <iostream>
#include <cmath> 
#include <vector>
#include <cassert>
#include "network.hpp"

using namespace std; 

Network::Network() 
{
	neurons = {};
	//connections_={}; 
	

	/// the first 10 000 neurons are excitatory and the others are inhibitory
	for (int j=0; j<Const::NB_EXCITATORY; ++j) {
		neurons[j].setExcitatory(true);
	} 
	
	///generating connections using uniformly distributed random numbers 
    std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<int> excitatory(0, Const::NB_EXCITATORY-1); 
	std::uniform_int_distribution<int> inhibitory(Const::NB_EXCITATORY, Const::NB_NEURONS-1); 
	
	
	for (size_t n=0; n<Const::NB_NEURONS; ++n) 
	{
		cout << "Etape " << n << " /12500" << endl;
		for (size_t i=0; i<Const::C_EXCITATORY; ++i) 
		{
			auto source = excitatory(gen);
			
			neurons[source].addConnection(n); 
		}
		for (size_t i=0; i<Const::C_INIBITORY; ++i) 
		{
			auto source = inhibitory(gen);
			
			neurons[source].addConnection(n);   ///neurone n devient une target de source 
		}
	}
}


void Network::update(double I, int steps) 
{
	for (size_t i(0); i< neurons.size(); ++i) 
	{
		neurons[i].setIext(I);
		neurons[i].update(steps);		
		
		if (neurons[i].spiked()) {
			cout << "The neuron spiked at : " << steps*Const::H << "ms: " << neurons[i].getMemPot() << "mV"<< endl; 
			
			double J = i < Const::NB_EXCITATORY ? Const::J_EXCITATORY : Const::J_INHIBITORY;
			
			///transmission of the spike to other neurons    ///we go through the connexions of neuron i to transmit the signal to the targets
			for(auto connection: neurons[i].getConnection()) {
				neurons[connection].receive(J, steps);
			}
		}
	}
}


int Network::getNeuronClock(int i) const 
{
	return neurons[i].getClock(); 
}

	
