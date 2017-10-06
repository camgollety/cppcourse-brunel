#include <iostream>
#include <cmath> 
#include <vector>
#include "NEURON.HPP"

using namespace std; 

Neuron::Neuron(double m, double n, int t): memPot_(m), numSpikes_(n)
{}

Neuron::Neuron(): memPot_(0.0), numSpikes_(0)
{}

Neuron::~Neuron() {}


double Neuron::getMemPot() const 
{
	return memPot_;
}

double Neuron::getNumSpikes() const
{ 
	return numSpikes_;
}

void Neuron::setMemPot(double x) 
{
	memPot_=x; 
}
	
/*void Neuron::setNumSpikes(int x) 
{
	numSpikes_=x;
}*/

void Neuron::update(double simtime, double I) 
{
	if (isRefractory(simtime)) 
	{
		setMemPot(0.0);
	}
	else {
		double m(exp(-h/tau)*getMemPot()+I*(tau/C)*(1-exp(-h/tau)));
		this->setMemPot(m);
		if(spikes()) 
		{
			timeSpikes.push_back(simtime);
		}
	}
}

bool Neuron::spikes() 
{
	return (getMemPot()> V_thr);
}

bool Neuron::isRefractory(double time) 
{
	return (time - timeSpikes[timeSpikes.size()] < refTime); 
}

	
