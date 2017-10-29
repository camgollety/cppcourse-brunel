#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include "Constants.hpp"
#include <random>

class Network {
	
	private: 
	
	std::array<Neuron*, Const::NB_NEURONS> neurons; ///array of all the neurons of the network 
	std::array<std::array<int, Const::NB_NEURONS>, Const::NB_NEURONS> connections_; ///matrix of connections
	double backGroundNoise_; ///additional potential from the rest of the brain 
	
	
	public: 
	
	Network(); 
	~Network();
	
	int getNeuronClock(int i) const;
	double getBackGroundNoise() const; ///returns the value of Vext from the rest of the brain 
	
	void update(double I, int steps);
};

#endif
