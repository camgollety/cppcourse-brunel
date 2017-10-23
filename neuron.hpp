#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath> 
#include <vector>
#include <array>

using namespace std;



const double tau = 20;   ///membrane time constant 
const int C=1;   ///membrane capacity
const double R=1;   ///membrane resistance
const double h=0.1;   ///integration stepsize
const int V_thr=20;   ///spike threshold
const int V_reset = 10; 
const double refTime =20;   ///refractory time
const double J =10; 
const int delay = 15; 

class Neuron {
	
	private: 
	
	double c1;   ///constant of integration1
	double c2;   ///constant of integration1
	double memPot_;   ///membrane potential 
	int numSpikes_;   ///number of spikes
	vector<double> historicalPot_;   ///stores all the membrane potentials 
	vector<double> timeSpikes_;   ///stores the spikes time 
	long clock_;   ///internal clock for a neuron 
	double I_ext;   ///external current 
	double delay_;   ///synaptic delay in ms
	unsigned long delay_steps_;   ///delay in steps
	vector<double> buffer;   ///buffer for spikes 
	
	public: 
	
	Neuron(); 
	virtual ~Neuron() = default; 
	double getMemPot() const; 
	double getNumSpikes() const; 
	double getLastSpike() const; 
	int getTimesOccured() const;
	long getClock() const; 
	double getIext() const;
	void receive(double J, int d); 
	
	bool spiked(); 
	bool isRefractory() const; 
	
	void setMemPot(double x);
	void setIext(double i);
	
	void update(); 
	
};

#endif
	
