"""
PyNN (pronounced 'pine' ) is a Python package for simulator-independent
specification of neuronal network models. 

In other words, you can write the code for a model once, using the PyNN API, and
then run it without modification on any simulator that PyNN supports. 

To use PyNN, import the particular simulator module you wish to use, e.g.
    import pyNN.neuron as sim
all subsequent code in the `sim` namespace will then have the same behaviour
independent of simulator.

Functions for simulation set-up and control:
    setup()
    run()
    end()
    get_time_step()
    get_current_time()
    get_min_delay()
    get_max_delay()
    rank()
    num_processes()
    list_standard_models()
    
Functions for creating, connecting, modifying and recording from neurons
(low-level interface):
    create()
    connect()
    set()
    record()
    record_v()
    record_gsyn()
    
Classes for creating, connecting, modifying and recording from neurons
(high-level interface):
    Population
    Projection
    Connectors: AllToAllConnector, OneToOneConnector, FixedProbabilityConnector,
                DistanceDependentProbabilityConnector, FixedNumberPreConnector,
                FixedNumberPostConnector, FromListConnector, FromFileConnector
    Standard cell types: IF_curr_exp, IF_curr_alpha, IF_cond_exp, IF_cond_alpha,
                IF_cond_exp_gsfa_grr, IF_facets_hardware1, HH_cond_exp,
                EIF_cond_alpha_isfa_ista, EIF_cond_exp_isfa_ista,
                SpikeSourcePoisson, SpikeSourceArray, SpikeSourceInhGamma
                (not all cell types are available for all simulator backends).
    Synaptic plasticity: SynapseDynamics, TsodyksMarkramMechanism, STDPMechanism,
                AdditiveWeightDependence, MultiplicativeWeightDependence,
                AdditivePotentiationMultiplicativeDepression,
                GutigWeightDependence, SpikePairRule
                (not all combinations area available for all simulator backends).
    Current injection: DCSource, StepCurrentSource, NoisyCurrentSource.

Available simulator modules:
    nest
    neuron
    pcsim
    brian

Other modules:
    utility
    random

"""

__version__ = '0.5 ( $Rev$)'.replace(' $','')
__all__ = ["common", "random", "nest", "neuron", "pcsim", 'brian' ]

