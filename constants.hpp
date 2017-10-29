#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

namespace Const {
	const double TAU = 20.0;   ///membrane time constant 
	
	const int C=1;   ///membrane capacity
	
	const double R=20.0;   ///membrane resistance
	
	const double H=0.1;   ///integration stepsize
	
	const int V_THR=20;   ///spike threshold
	
	const int V_RESET = 10; 

	const double REFTIME =2;   ///refractory time
	
	const double J =10; 
	
	const int DELAY = 15;

	const int NB_EXCITATORY = 10000;    ///number of excitatory neurons (0.8*NB_NEURONS)
	const int NB_INIBITORY = 2500;    ///number of inhibitory neurons (0.25*NB_EXCITATORY)
    const int NB_NEURONS = NB_EXCITATORY+NB_INIBITORY;    /// total number of neurons (inhibitory + excitatory) 
    
    const double RATIO=NB_EXCITATORY/NB_INIBITORY;    ///ratio of excitatory neurons over inhibitory neurons 
    
    const double J_EXCITATORY = 0.1; 	///weight of excitment 		
	const double J_INHIBITORY = -RATIO * J_EXCITATORY;   ///weight of inhibition 
    

	constexpr double E = 0.1;    ///constant epsilon 

	const int C_EXCITATORY = (E * NB_EXCITATORY);   ///number of excitatory connections that one neuron receives
	const int C_INIBITORY =  (E * NB_INIBITORY);    ///number of inhibitory connections that one neuron receives
	const int C_TOTAL = C_EXCITATORY + C_INIBITORY;    ///total number of connections received by a neuron 
	
	const double V_EXT = V_THR / (C_EXCITATORY * J_EXCITATORY * TAU);   /// value of the external input from the rest of the brain 
}

#endif
