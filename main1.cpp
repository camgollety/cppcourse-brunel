#include "network.hpp"

using namespace std; 

int main () {
	
	int i_start(1000); ///start the step current
	int i_stop(4000); ///stop the step current 
	int Tstop(5); ///total simulation time
	double I_ext(1.01); ///amplitude of current 
	
	
	
	Network n;	

for (int t(0); t<Tstop; ++t)
{
	int comp(0); 
	if(t>= i_start and t<i_stop)
	{
		n.update(0.0, t); 
	}
	else {
		n.update(0.0, t);
	}
	++comp; 
cout << comp << endl;
}

	return 0;
}

