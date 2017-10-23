#include "network.hpp"

using namespace std; 

int main () {
	
	int i_start(1000); ///start the step current
	int i_stop(4000); ///stop the step current 
	int Tstop(4000); ///total simulation time
	//double simtime(Tstart);
	double I_ext(1.01); ///amplitude of current 
	
	Network n;	
	
	n.addNeuron(); 
	n.addNeuron();
	
	n.connect(0, 1);
	n.connect(1, 0);
	
for (int t(0); t<Tstop; ++t)
{
	if(t>= i_start and t<i_stop)
	{
		n.update(I_ext);
	}
	else {
		n.update(0.0);
	}
}
	return 0;
}

