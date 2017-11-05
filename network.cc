#include <iostream>
#include <cmath> 
#include <vector>
#include <cassert>
#include "network.hpp"

using namespace std; 

Network::Network() 
{
	neurons = {};
	
	// the first 10 000 neurons are excitatory and the others are inhibitory
	for (int j=0; j<Const::NB_EXCITATORY; ++j) {
		neurons[j].setExcitatory(true);
	} 
	
	//generating connections using uniformly distributed random numbers 
    std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<int> excitatory(0, Const::NB_EXCITATORY-1); 
	std::uniform_int_distribution<int> inhibitory(Const::NB_EXCITATORY, Const::NB_NEURONS-1); 
	
	for (size_t n=0; n<Const::NB_NEURONS; ++n) 
	{
		//generate excitatory connections
		for (size_t i=0; i<Const::C_EXCITATORY; ++i) 
		{
			auto source = excitatory(gen);
			
			neurons[source].addConnection(n); 
		}
		//generate excitatory connections
		for (size_t i=0; i<Const::C_INIBITORY; ++i) 
		{
			auto source = inhibitory(gen);
			
			neurons[source].addConnection(n);   //neuron n becomes a target of the neuron source
		}
	}
}

void Network::update(double I, int steps) 
{
	
	int spikes(0);
	for (size_t i(0); i< neurons.size(); ++i) 
	{	
		neurons[i].setIext(I);  //set the external current
		neurons[i].update(steps);	//calls the update method of all the neurons of the network	
		
		if (neurons[i].spiked()) {
			cout << "The neuron " << i << " spiked at : " << steps*Const::H << "ms: " << neurons[i].getMemPot() << "mV"<< endl; 
			++spikes; 
			
			double J = i < Const::NB_EXCITATORY ? Const::J_EXCITATORY : Const::J_INHIBITORY;
			
			//transmission of the spike to other neurons    
			for(auto connection: neurons[i].getConnection()) {  //we go through the connexions of neuron i to transmit the signal to the targets
				neurons[connection].receive(J, steps);
			}
		}
	}
	numberSpikes_.push_back(spikes); 
	spikes = 0;
}

void Network::save() 
{
	ofstream out; 
	out.open("../spikes.gdf"); //opening a file to save the results
	
	for (long i(0); i<neurons.size(); ++i) 
	{
		for (int j(0); j<neurons[i].getSpikesTime().size(); ++j) //we store the spikes time of every neurons
		{
		out << neurons[i].getSpikesTime()[j] << '\t' << i << '\n';  //writes the results in the file
		}
	}
		
	out.close(); 
}

int Network::getNeuronClock(int i) const 
{
	return neurons[i].getClock(); 
}

Neuron Network::getNeuron(int i) const 
{
	return neurons[i];
}

	
