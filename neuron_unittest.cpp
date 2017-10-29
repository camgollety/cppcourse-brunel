#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

TEST (TEST1, IPOSITIVE) {
	Neuron neuron;
	neuron.setIext(1.0);
	
	///First update test
	for (int i(0); i<1; ++i) {
		neuron.update(i);
	}
	
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
	
    ///Test for a lot of steps
	for (int i(0); i<10000; ++i) {
		neuron.update(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
	EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
	
	///Test without input 
	neuron.setIext(0.0); 
	for (int i(0); i<2000; ++i) {
		neuron.update(i);
	}
	EXPECT_NEAR(0, neuron.getMemPot(), 1e-3); ///I=0 so the mem pot should tend to 0
}

TEST (TEST2, INEGATIVE) {
	Neuron neuron;
	neuron.setIext(-1.0);
	
	///First update test
	for (int i(0); i<1; ++i) {
		neuron.update(i);
	}
	
	EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
	
	///Test for a lot of steps
	for (int i(0); i<10000; ++i) {
		neuron.update(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
	EXPECT_GT(1E-3, std::fabs(-19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
	
	///Test without input 
	neuron.setIext(0.0); 
	for (int i(0); i<2000; ++i) {
		neuron.update(i);
	}
	EXPECT_NEAR(0, neuron.getMemPot(), 1e-3); ///I=0 so the mem pot should tend to 0
}

/*TEST (TEST3, GoodSpikes) {
	Neuron neuron;
	neuron.setIext(1.01);
	
	///First update test
	for (int i(0); i<1; ++i) {
		neuron.update(i);
	}
	
	EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
	
	///Test for a lot of steps
	for (int i(0); i<10000; ++i) {
		neuron.update(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
	EXPECT_GT(1E-3, std::fabs(-19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
	
	///Test without input 
	neuron.setIext(0.0); 
	for (int i(0); i<2000; ++i) {
		neuron.update(i);
	}
	EXPECT_NEAR(0, neuron.getMemPot(), 1e-3); ///I=0 so the mem pot should tend to 0
} */

TEST (NeuronTest, StandaloneSimulation) {
	Neuron neuron;
	neuron.setIext(1.01); 
	
	for (int i(0); i<4000; ++i) {
	neuron.update(i); }
	
	EXPECT_EQ(4, neuron.getNumSpikes()); 
}

