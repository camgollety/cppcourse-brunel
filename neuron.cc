
#include "neuron.hpp"

using namespace std; 

Neuron::Neuron(): 
    memPot_(0.0), 
    numSpikes_(0), 
    clock_(0), 
    I_ext(0.0), 
    delay_(1.5), 
    buffer_(), 
    isExcitatory(false)
{
	c1 = exp(-Const::H/Const::TAU);
	c2=(Const::TAU/Const::C)*(1.0-c1);
	delay_steps_=static_cast<unsigned long>(ceil(delay_/Const::H));
	buffer_.resize(delay_steps_+1, 0.0);
	
	buffer_ = {}; ///initilisation of the buffer
	
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

bool Neuron::getIsExcitatory() const
{
	return isExcitatory;
} /** @return the value of the boolean isExcitatory **/


void Neuron::setMemPot(double x) 
{
	memPot_=x; 
} 

void Neuron::setIext(double i)
{
	I_ext=i;
}

void Neuron::setExcitatory(bool b) 
{
	isExcitatory=b;
} 

void Neuron::update(int steps) 
{	
	
	if (isRefractory()) 
	{
		memPot_=0.0;
	}
	else {
		memPot_ = c1*memPot_+ I_ext*c2 + buffer_[steps%buffer_.size()];
		buffer_[clock_%buffer_.size()]=0.0;
		if(spiked()) 
		{
			timeSpikes_.push_back(steps);
			++numSpikes_;
			isRefractory();
		}
	}
	++clock_;
} ///update the state of the neuron from state t to t+h, update the value of membrane potential 

bool Neuron::spiked()
{
	return (getMemPot()>= Const::V_THR);
} /// check if the neuron spiked or not 

bool Neuron::isRefractory() const
{
	return (!timeSpikes_.empty() and clock_ - timeSpikes_[timeSpikes_.size()-1] < Const::REFTIME); 
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

void Neuron::receive(double J, int steps) 
{

		buffer_[(steps+delay_steps_)%buffer_.size()] += J; 
	
} /**the neuron receives a spike with weight J 
@J: weight of the spike **/ 



