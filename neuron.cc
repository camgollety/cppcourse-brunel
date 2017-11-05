
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
	
	buffer_ = {}; ///initilisation of the buffer
	for (size_t i(0); i<delay_steps_+1; ++i) 
	{
		buffer_.push_back(0.0); 
	}
	
	connections_ = {};  ///initilisation of the connections of a neuron
	
}

/********************************************** GETTERS **************************************************/

double Neuron::getMemPot() const 
{
	return memPot_;
} 

double Neuron::getNumSpikes() const
{ 
	return numSpikes_;
} 

long Neuron::getClock() const 
{ 
	return clock_;
} 

double Neuron::getIext() const
{
	return I_ext;
} 

bool Neuron::getIsExcitatory() const
{
	return isExcitatory;
} 

vector<int> Neuron::getConnection() const 
{
	return connections_; 
}

vector<double> Neuron::getSpikesTime() const
{
	return timeSpikes_; 
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
} 

/********************************************** SETTERS ******************************************/

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

/********************************************** GEERAL METHODS ******************************************/

void Neuron::update(int steps) 
{		
	if (isRefractory()) 
	{
		memPot_=0.0;
	}
	else {
		//creating a random noise that is a current from the rest of the brain 
		//static: variable that exists only once 
		static random_device rd; //creation of a random device 
		static mt19937 gen(rd()); //initializing random generator
		static poisson_distribution<> noise(Const::V_EXT * Const::C_EXCITATORY * Const::H * Const::J_EXCITATORY); //initializing a poisson distribution
		
		memPot_ = c1*memPot_+ I_ext*c2 + buffer_[steps%buffer_.size()]+noise(gen);
		buffer_[clock_%buffer_.size()]=0.0;
		if(spiked()) 
		{
			timeSpikes_.push_back(steps);
			++numSpikes_;
			isRefractory();
		}
	}
	++clock_; 
} //update the state of the neuron from state t to t+h, update the value of membrane potential 

void Neuron::updateNoNoise(int steps) 
{		
	if (isRefractory()) 
	{
		memPot_=0.0;
	}
	else {
		//creating a random noise that is a current from the rest of the brain 
		//static: variable that exists only once 
		static random_device rd; //creation of a random device 
		static mt19937 gen(rd()); //initializing random generator
		static poisson_distribution<> noise(Const::V_EXT * Const::C_EXCITATORY * Const::H * Const::J_EXCITATORY); ///initializing a poisson distribution
		
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
}

bool Neuron::spiked()
{
	return (getMemPot()>= Const::V_THR);
} // check if the neuron spiked or not 

bool Neuron::isRefractory() const
{
	return (!timeSpikes_.empty() and clock_ - timeSpikes_[timeSpikes_.size()-1] < Const::REFTIME); 
}

void Neuron::receive(double J, int steps) 
{

		buffer_[(steps+delay_steps_)%buffer_.size()] += J; 
	
}

void Neuron::addConnection(int i) {
	connections_.push_back(i);
	
}




