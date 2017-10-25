#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, PositiveInput) {
	Neuron neuron;
	neuron.setIext(1.0);
	
	///First update test
	for (int i(0); i<1; ++i) {
		neuron.update(i);
	}
	
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
	
	///Test after numerous updates
	for (int i(0); i<10000; ++i) {
		neuron.update(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes());
	EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getMemPot()));
	
	
	neuron.setIext(0.0);
	for (int i(0); i<2000; ++i) {
		neuron.update(i);
	}
	EXPECT_NEAR(0, neuron.getMemPot(), 1e-3);
}

