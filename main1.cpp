#include "network.hpp"
#include <fstream>
#include "constants.hpp"

int main () {
	

	int Tstop(10000); //total simulation time
	
	Network n;	

for (int t(0); t<Tstop; ++t)
{	
		n.update(0.0, t); 
		n.save(); 
}

	return 0;
}

