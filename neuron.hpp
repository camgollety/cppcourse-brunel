#include <iostream>
#include <cmath> 
#include <vector>

using namespace std;

const unsigned int tau = 20;
const int C=1;
const int h=1; 
const int V_thr=20;
const int V_reset = 10; 
const double refTime =1.0;

class Neuron {
	
	private: 
	double memPot_; 
	int numSpikes_; 
	vector<double> timeSpikes;
	vector<double> historicalPot;
	
	public: 
	Neuron(double m, double n, int t);
	Neuron(); 
	~Neuron();
	double getMemPot() const;
	double getNumSpikes() const;
	int getTimesOccured() const;
	bool spikes();
	bool isRefractory(double time);
	
	void setMemPot(double x);
	/*void setNumSpikes(int x);
	void setTimesOccured(int x);*/
	
	void update(double simtime, double I);
	
};


	
/*void Neuron::setNumSpikes(int x) 
{
	numSpikes_=x;
} */

