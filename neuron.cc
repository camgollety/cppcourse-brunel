
#include "neuron.hpp"

using namespace std; 

Neuron::Neuron(): 
    memPot_(0.0), 
    numSpikes_(0), 
    clock_(0), 
    I_ext(0.0), 
    delay_(1.5), 
    buffer()
{
	c1 = exp(-h/tau);
	c2=(tau/C)*(1.0-c1);
	delay_steps_=static_cast<unsigned long>(ceil(delay_/h));
	buffer.resize(delay_steps_+1, 0.0);
	
}

double Neuron::getMemPot() const 
{
	return memPot_;
} /** @return current value of the membrane **/

double Neuron::getNumSpikes() const
{ 
	return (!timeSpikes_.empty() and timeSpikes_.size());
} /** @return number of spikes **/

long Neuron::getClock() const 
{ 
	return clock_;
} /** @return current value of the internal clock of the neuron **/

double Neuron::getIext() const
{
	return I_ext;
} /** @return the external current **/

void Neuron::setMemPot(double x) 
{
	memPot_=x; 
} 

void Neuron::setIext(double i)
{
	I_ext=i;
}

void Neuron::update() 
{	
	if (isRefractory()) 
	{
		memPot_=0.0;
	}
	else {
		memPot_ = c1*memPot_+ I_ext*c2 + buffer[clock_%buffer.size()];
		if(spiked()) 
		{
			timeSpikes_.push_back(clock_);
			++numSpikes_;
		}
	}
	++clock_;
} ///update the state of the neuron from state t to t+h, update the value of membrane potential 

bool Neuron::spiked()
{
	return (getMemPot()>= V_thr);
} /// check if the neuron spiked or not 

bool Neuron::isRefractory() const
{
	return (!historicalPot_.empty() and clock_ - timeSpikes_[timeSpikes_.size()] < refTime); 
}

double Neuron::getLastSpike() const {
	if (!historicalPot_.empty()) 
	{
		return historicalPot_.back();
	}
	else 
	{
		return 0;
	}
} /** @return the value of the membrane for the last spike **/

void Neuron::receive(double J, int d) 
{
	if (!isRefractory())
	{
		buffer[(clock_+d)%buffer.size()] += J;
	}
} /**the neuron receives a spike with weight J 
@éJ: weight of the spike
@d: delay of the spike **/ 
	
