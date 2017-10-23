#include <iostream>
#include <cmath> 
#include <vector>
#include <cassert>
#include "network.hpp"

using namespace std; 


Network::Network() 
{}

Network::~Network() {
	for (auto& neuron : neurons) {
		delete neuron;
		neuron = nullptr;
	}
}

void Network::update(double I) 
{
	for (size_t i(0); i< neurons.size(); ++i) 
	{
		neurons[i]->setIext(I);
		neurons[i]->update();
		
		if (neurons[i]->spiked()) {
			cout << "The neuron spiked at : " << getNeuronClock(i)*h << "ms: " << neurons[i]->getMemPot() << "mV"<< endl; 
			
			///transmission of the spike to other neurons 
			for(auto connected: connexions[i]) ///we go through the connexions of neuron i to transmit the signal 
			{ neurons[connected]->receive(J, delay); }
		}
		
	}
}

void Network::addNeuron()
{
	neurons.push_back(new Neuron());
	connexions.push_back(vector<unsigned int>());
}

int Network::getNeuronClock(int i) const 
{
	return neurons[i]->getClock(); 
}

void Network::connect(unsigned int n1, unsigned int n2) 
{
	assert(n1!=n2);
	assert(n1<neurons.size());
	assert(n2<neurons.size());

	connexions[n1].push_back(n2);
}
	
	
