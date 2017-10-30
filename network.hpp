#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include "constants.hpp"
#include <random>

class Network {
	
	private: 
	
	std::array<Neuron, Const::NB_NEURONS> neurons; ///array of all the neurons of the network 
	std::vector<int> numberSpikes_;  ///number of spikes for each time step
	
	public: 
	
	Network(); 
	~Network() = default;
	
	int getNeuronClock(int i) const;
	
	void update(double I, int steps);
};

#endif
