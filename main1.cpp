#include <iostream>
#include "NEURON.CC"

int main () {
	Neuron n1; 
	double Tstart(0.0);
	double Tstop(0.0);
	double simtime(Tstart);
	double a(0.0);
	double b(0.0);
	double Iext(0.0); 
	
	cout << "How long do you want the simulation to last? " << endl;
	cin >> Tstop; 
	
	cout << "What is the time interval (a,b) for the external current? " << endl; 
	cin >> a;
	cin >> b;
	
	cout << "What is the value for the external current? " << endl; 
	cin >> Iext; 
	
	while (simtime < Tstop) 
	{
		if( simtime>a and simtime<b) 
		{
			n1.update(simtime, Iext);
			
		} else {
			n1.update(simtime, 0.0);
		}
		simtime += h;
	}
	
	return 0;
}

