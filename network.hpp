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
	
	std::array<Neuron, Const::NB_NEURONS> neurons; //! array of all the neurons of the network 
	std::vector<int> numberSpikes_;  //! number of spikes for each time step
	
	public: 
	
 /*! 
 * @brief constructor, create random connections between the neurons of the network
 */	
	Network(); 
	~Network() = default;    //! Destructor
	
	
/****************************************************************************************************************
 *                                             GETTERS
 * *************************************************************************************************************/	
	
 /*!
 * @return  the local clock of neuron i
 * @param i the index of a neuron
 */	
	int getNeuronClock(int i) const;

 /*!
 * @return  the neuron i of the list of neurons 
 * @param i the index of a neuron
 */	
	Neuron getNeuron(int i) const;
	
/****************************************************************************************************************
 *                                             GENERAL METHODS
 * *************************************************************************************************************/	
	
 /*! 
 * @brief main update function, transmit the spikes, update the attributs of the class
 * @param I the current
 * @param steps the duration of the update 
 */	
	void update(double I, int steps);

 /*! 
 * @brief Save spikes time in a file 
 */	
	void save(); 
};

#endif
