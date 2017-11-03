#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath> 
#include <vector>
#include <array>
#include <random>
#include "constants.hpp"

class Neuron {
	
/*! @class Neuron 
 * @brief class representing a neuron
 */
	
	private: 
	
	double c1;   //! constant of integration1
	double c2;   //! constant of integration1
	double memPot_;   //! membrane potential 
	int numSpikes_;   //! number of spikes
	std::vector<double> historicalPot_;   //! stores all the membrane potentials 
	std::vector<double> timeSpikes_;   //! stores the spikes time 
	long clock_;   //! internal clock for a neuron 
	double I_ext;   //! external current 
	double delay_;   //! synaptic delay in ms
	unsigned long delay_steps_;   //! delay in steps
	std::vector<double> buffer_;   //! buffer for spikes 
	
	bool isExcitatory; //! checks is the neuron is excitatory(true) or not(false)
	
	std::vector<int> connections_; //! connections of a neuron that are its targets, the int represents a neuron  
	
	public: 
	
	
 /*! 
 * @brief constructor, init a neuron the attributs of the neuron
 */	
	Neuron(); 
	
	virtual ~Neuron() = default; //! destructor 

/****************************************************************************************************************
 *                                             GETTERS
 * *************************************************************************************************************/	
 	
 /*!
 * @return  the membrane potential of the neuron
 */	
	double getMemPot() const; 	
	
 /*!
 * @return  the number of spikes of the neuron during a simulation
 */	
	double getNumSpikes() const;
	
 /*!
 * @return  the last spike of the neuron
 */	
	double getLastSpike() const; 
	
 /*!
 * @return  the local clock of the neuron 
 */	
	long getClock() const; 
	
 /*!
 * @return  the external current that the neuron receives
 */	
	double getIext() const;

 /*!
 * @return  true if the neuron is excitatory, false if it is inhibitory
 */	
	bool getIsExcitatory() const;

 /*!
 * @return  a list of all the connection targets
 */	
	std::vector<int> getConnection() const; 
	
 /*!
 * @return  the list of the spike times of the neuron
 */	
	std::vector<double> getSpikesTime() const;
  
 
/****************************************************************************************************************
 *                                             SETTERS
 * *************************************************************************************************************/	
 
  /*! 
 * @brief assignes the value of the membrane potential of the neuron with the value x
 * @param x value of the new membrane potential
 */	
	void setMemPot(double x);
	
 /*! 
 * @brief assignes the value of the external current with i
 * @param i value of the new external current
 */	
	void setIext(double i);
	
 /*! 
 * @brief modifies the state of the neuron 
 * @param b true is the neuron is excitatory and false instead
 */	
	void setExcitatory(bool b);
	

/****************************************************************************************************************
 *                                             GENERAL METHODS
 * *************************************************************************************************************/	

/*! 
 * @brief receives a spike from an other neuron
 * @param J the potential transmitted by a neuron that spikes
 * @param steps the time in steps of arrival of the spike
 */	
	void receive(double J, int steps); 

 /*! 
 * @return true if the neuron just spiked, false if not
 */	
	bool spiked(); 

 /*! 
 * @return true if the neuron is refractory
 */	
	bool isRefractory() const; 

 /*! 
 * @brief updates the neuron's membrane potential with the general formula
 * adds the potential due to incoming spikes
 * adds the background noise from the res of the brain
 * @param steps the absolute time of the simulation
 */	
	void update(int steps); 

 /*! 
 * @brief updates the neuron's membrane potential with the general formula
 * adds the potential due to incoming spikes
 * no background noise added, used for the google tests
 * @param steps the absolute time of the simulation
 */	
	void updateNoNoise(int steps); 

 /*! 
 * @brief adds a connexion to the neuron
 * @param i the index of the neuron we want to connect to
 */	
	void addConnection(int i); 
	
};

#endif
	
