Neuron Project:

This project is a neural network simulation from the paper « Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons » written by Nicolas Brunel.

The network consists of 12500 integrate and fire neurons with 10’000 excitatory neurons and 2’500 inhibitory neurons.
Each neuron receives C randomly chosen connections from other neurons in the network.
Every neuron also receives an additional random input from the rest of the brain.
The neurons spike and interact with each other and the aim of the program is to observe their comportment.

The main program can be run from the main with the command: ./neuron, it will display the neurons that spiked and the times corresponded.
Tests can be made with the command: ./neuron_unittest

I commented my code in a special way so that it was compatible with doxygen. The command make doc is useful to compile and update all the comments.
 
A file called spikes.gdf stores the values of all the spikes from all the neurons from the network and is useful to generate the plots on Jupyter. 
