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
		neuron.updateNoNoise(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
	EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
	
	///Test without input 
	neuron.setIext(0.0); 
	for (int i(0); i<2000; ++i) {
		neuron.updateNoNoise(i);
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
		neuron.updateNoNoise(i);
	}
	EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
	EXPECT_GT(1E-3, std::fabs(-19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
	
	///Test without input 
	neuron.setIext(0.0); 
	for (int i(0); i<2000; ++i) {
		neuron.updateNoNoise(i);
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

TEST (NeuronTest, StandAloneSimulation) {
	Neuron neuron;
	neuron.setIext(1.01); 
	
	for (int i(0); i<4000; ++i) {
	neuron.updateNoNoise(i); }
	
	EXPECT_EQ(4, neuron.getNumSpikes()); 
} 

TEST (TwoNeurons, NoPSSpike){
	Neuron neuron1, neuron2; 
	int delay (Const::DELAY);
	neuron1.setIext(1.01);
	//we wait for the first spike and see the impact on neuron2
	for(auto i(0); i<925+delay; i++){
		neuron1.update(1); 
		 if(neuron1.spiked()){
			neuron2.receive(i + static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getMemPot());
		}
		neuron2.update(1);
		neuron2.spiked(); 
	
	EXPECT_EQ(0.1, neuron2.getMemPot()); 
}
}

/*TEST (TwoNeurons, WithPSSpike){
	Neuron neuron1, neuron2; 
	neuron1.setExtCurrent(1.01);
	neuron2.setExtCurrent(1.0);
	int delay (DELAY);
	//neurons did not have time to reach the treshold 
	for (auto i(0); i<1869+delay; i++){
		if(neuron1.update(1)){
			neuron2.receiveSpike(i+static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane()); 
		}
		neuron2.update(1); 
	}
	
	//just before neuron2 spikes 
	EXPECT_EQ(0, neuron2.getNbrSpikes()); 
	neuron2.update(1);
	EXPECT_EQ(0, neuron2.getPotentialMembrane());
	///on veut que des que spiker retourne a 0
	EXPECT_EQ(1, neuron2.getNbrSpikes()); 
}*/

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
	
}

