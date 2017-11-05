#include <iostream>
#include <vector>
#include <array>
#include "neuron.hpp"
#include "network.hpp"
#include "gtest/gtest.h"

/*********** check the value of the mem potential at different moment in the simulation for a positive current  **********/
TEST (TEST1, IPOSITIVE) {
Neuron neuron;
neuron.setIext(1.0);
//First update test
for (int i(0); i<1; ++i) {
neuron.updateNoNoise(1);
}
EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
    //Test for a lot of steps
for (int i(0); i<10000; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_EQ(0, neuron.getNumSpikes()); //the neuron should never spike
EXPECT_GT(1E-3, std::fabs(19.999 - neuron.getMemPot())); //the mem pot should tend to 20 but never reach it 
//Test without input 
neuron.setIext(0.0); 
for (int i(0); i<2000; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_NEAR(0, neuron.getMemPot(), 1e-3); //I=0 so the mem pot should tend to 0
}

/*********** check the value of the mem potential for a negative current at different moment in the simulation   **********/
TEST (TEST2, INEGATIVE) {
Neuron neuron;
neuron.setIext(-1.0);
//First update test
for (int i(0); i<1; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_EQ(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
//Test for a lot of steps
for (int i(0); i<10000; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_EQ(0, neuron.getNumSpikes()); ///the neuron should never spike
EXPECT_GT(1E-3, std::fabs(-19.999 - neuron.getMemPot())); ///the mem pot should tend to 20
//Test without input 
neuron.setIext(0.0); 
for (int i(0); i<2000; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_NEAR(0, neuron.getMemPot(), 1e-3); ///I=0 so the mem pot should tend to 0
}


/*********** check the number of spikes knowing the spike times of one neuron  **********/
TEST (NeuronTest, SpikeTimes)
{
Neuron n1;
double I=1.01;
n1.setIext(1.01); 
//waiting for one spike 
//we know that the first spike time is 92.4ms 
for(int i(0); i<924; ++i)
{
n1.updateNoNoise(i);
}
EXPECT_EQ(1, n1.getNumSpikes());
n1.updateNoNoise(1);
EXPECT_EQ(1, n1.getNumSpikes());
EXPECT_EQ(0.0, n1.getMemPot());
Neuron n2; 
n2.setIext(1.01); 
    //waiting for two spikes
    for(int i(0); i<1850; ++i)
    {
n2.updateNoNoise(i);
}
EXPECT_EQ(2,n2.getNumSpikes());
}


/*********** check number of spikes during a simulation  **********/
TEST (NeuronTest, StandAloneSimulation) {
Neuron neuron;
neuron.setIext(10.1); 
for (int i(0); i<110; ++i) {
neuron.updateNoNoise(i);
}
EXPECT_EQ(5, neuron.getNumSpikes()); //we expect 5 spikes after 110 time steps
} 

/************* test to check that a neuron doesn't spike at a moment in the simulation ************/
TEST (NeuronTest, NoSpikes) {
Neuron neuron; 
neuron.setIext(1.01);
neuron.updateNoNoise(4000);
EXPECT_EQ(0, neuron.getNumSpikes());
}

/*********** we check that we have the good number of connections in the network  **********/
TEST (NetworkTest, NumConnections) //test to check if we have the right number of connections in the network
{
int num_neurons(Const::NB_NEURONS);
Network network; 
int nb_connections(0);
for (int i(0) ; i < Const::NB_NEURONS ; ++i)
{
   assert (!(network.getNeuron(i).getConnection()).empty());
nb_connections += (network.getNeuron(i).getConnection()).size(); 
nb_connections /=2; //we don't want to count the connections twice
}
EXPECT_NEAR(50, nb_connections , Const::C_TOTAL); //we expect to have 1250 connections, 0.1*NB_NEURONS
} 


int main(int argc, char **argv) 
{
::testing::InitGoogleTest(&argc, argv);

return RUN_ALL_TESTS();
}




