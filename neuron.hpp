#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath> 
#include <vector>
#include <array>
#include "Constants.hpp"

class Neuron {
	
	private: 
	
	double c1;   ///constant of integration1
	double c2;   ///constant of integration1
	double memPot_;   ///membrane potential 
	int numSpikes_;   ///number of spikes
	std::vector<double> historicalPot_;   ///stores all the membrane potentials 
	std::vector<double> timeSpikes_;   ///stores the spikes time 
	long clock_;   ///internal clock for a neuron 
	double I_ext;   ///external current 
	double delay_;   ///synaptic delay in ms
	unsigned long delay_steps_;   ///delay in steps
	std::vector<double> buffer_;   ///buffer for spikes 
	
	bool isExcitatory; ///checks is the neuron is excitatory(true) or not(false)
	
	public: 
	
	Neuron(); 
	virtual ~Neuron() = default; 
	double getMemPot() const; 
	double getNumSpikes() const; 
	double getLastSpike() const; 
	int getTimesOccured() const;
	long getClock() const; 
	double getIext() const;
	bool getIsExcitatory() const; 
	
	void receive(double J, int steps); 
	
	bool spiked(); 
	bool isRefractory() const; 
	
	void setMemPot(double x);
	void setIext(double i);
	void setExcitatory(bool b);
	
	void update(int steps); 
	
	void addConnetion(int i); ///add a connexion to the neuron 
	
};

#endif
	
