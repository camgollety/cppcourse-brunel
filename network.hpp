#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.hpp"
#include "constants.hpp"
#include <random>
#include <fstream>
 
 /*! @class Network 
 * @brief Network of neurons connected and interracting together
 */

class Network {
	
	private: 
	
	std::array<Neuron, Const::NB_NEURONS> neurons; ///array of all the neurons of the network 
	std::vector<int> numberSpikes_;  ///number of spikes for each time step
	
	public: 
	
	Network();    /**< Constructor*/
	~Network() = default;    /**< Destructor*/
	
	int getNeuronClock(int i) const;
	
	void update(double I, int steps);
	void save(); 
};

#endif
