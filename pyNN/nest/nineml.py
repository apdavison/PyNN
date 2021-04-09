"""
Support cell types defined in 9ML with NEST.

Requires the 9ml nestbuilder script to be on the import path.

Classes:
    NineMLCellType    - base class for cell types, not used directly
    NineMLSynapseType - base class for synapse types

Functions:
    nineml_cell_type_from_model - return a new NineMLCellType subclass
    nineml_synapse_type_from_model - return a new NineMLSynapseType subclass

Constants:
    NEST_DIR        - subdirectory to which NEST mechanisms will be written (TODO: not implemented)

:copyright: Copyright 2006-2020 by the PyNN team, see AUTHORS.
:license: CeCILL, see LICENSE for details.

"""

from __future__ import absolute_import  # Not compatible with Python 2.4
import logging
import os
from datetime import datetime

from pyNN.nest.cells import NativeCellType
# from pyNN.models import BaseSynapseType
from pyNN.nest.synapses import NativeSynapseType
from pyNN.nest.simulator import Connection

logger = logging.getLogger("PyNN")

# TODO: This should go to a evironment variable, like PYNN_9ML_DIR
# and then a sub-dir for nest, neuron, etc.
# but default to ~/.pyNN or something to that regard.
# NEST_DIR = "nest_models"
NEST_DIR = os.path.join(os.getcwd(), "NEST_nineml_models")

class NineMLCellType(NativeCellType):

    def __init__(self, parameters):
        NativeCellType.__init__(self, parameters)


def nineml_celltype_from_model(name, nineml_model, synapse_components):
    """
    Return a new NineMLCellType subclass from a NineML model.
    """

    dct = {'nineml_model': nineml_model,
           'synapse_components': synapse_components}
    return _nest_build_nineml_celltype(name, (NineMLCellType,), dct)


class _nest_build_nineml_celltype(type):
    """
    Metaclass for building NineMLCellType subclasses
    Called by nineml_celltype_from_model
    """
    def __new__(cls, name, bases, dct):

        import nineml.abstraction as al
        from nineml.abstraction import flattening, writers, component_modifiers
        import nest

        # Extract Parameters Back out from Dict:
        nineml_model = dct['nineml_model']
        synapse_components = dct['synapse_components']

        # Flatten the model:
        assert isinstance(nineml_model, al.ComponentClass)
        if nineml_model.is_flat():
            flat_component = nineml_model
        else:
            flat_component = flattening.flatten(nineml_model, name)

        # Make the substitutions:
        flat_component.backsub_all()
        #flat_component.backsub_aliases()
        #flat_component.backsub_equations()

        # Close any open reduce ports:
        component_modifiers.ComponentModifier.close_all_reduce_ports(component=flat_component)

        flat_component.short_description = "Auto-generated 9ML neuron model for PyNN.nest"
        flat_component.long_description = "Auto-generated 9ML neuron model for PyNN.nest"

        # Close any open reduce ports:
        component_modifiers.ComponentModifier.close_all_reduce_ports(component=flat_component)

        # synapse ports:
        synapse_ports = []
        for syn in synapse_components:
            # get recv event ports
            # TODO: model namespace look
            #syn_component = nineml_model[syn.namespace]
            syn_component = nineml_model.subnodes[syn.namespace]
            recv_event_ports = list(syn_component.query.event_recv_ports)
            # check there's only one
            if len(recv_event_ports) != 1:
                raise ValueError("A synapse component has multiple recv ports.  Cannot dis-ambiguate")
            synapse_ports.append(syn.namespace + '_' + recv_event_ports[0].name)

        # New:
        dct["combined_model"] = flat_component
        # TODO: Override this with user layer
        #default_values = ModelToSingleComponentReducer.flatten_namespace_dict( parameters )
        dct["default_parameters"] = dict((p.name, 1.0) for p in flat_component.parameters)
        dct["default_initial_values"] = dict((s.name, 0.0) for s in flat_component.state_variables)
        dct["synapse_types"] = [syn.namespace for syn in synapse_components]
        dct["standard_receptor_type"] = (dct["synapse_types"] == ('excitatory', 'inhibitory'))
        dct["injectable"] = True  # need to determine this. How??
        dct["conductance_based"] = True  # how to determine this??
        dct["model_name"] = name
        dct["nest_model"] = name

        # Recording from bindings:
        dct["recordable"] = [port.name for port in flat_component.analog_ports] + ['spikes', 'regime']
        # TODO bindings -> alias and support recording of them in nest template
        #+ [binding.name for binding in flat_component.bindings]

        dct["weight_variables"] = dict([(syn.namespace, syn.namespace + '_' + syn.weight_connector)
                                        for syn in synapse_components])

        logger.debug("Creating class '%s' with bases %s and dictionary %s" % (name, bases, dct))

        # TODO: UL configuration of initial regime.
        initial_regime = flat_component.regimes_map.keys()[0]

        from nestbuilder import NestFileBuilder
        nfb = NestFileBuilder(nest_classname=name,
                              component=flat_component,
                              synapse_ports=synapse_ports,
                              initial_regime=initial_regime,
                              initial_values=dct["default_initial_values"],
                              default_values=dct["default_parameters"],
                              )
        nfb.compile_files()
        nest.Install('mymodule')

        return type.__new__(cls, name, bases, dct)


class NineMLSynapseType(NativeSynapseType):

    connection_type = Connection
    presynaptic_type = None
    #postsynaptic_variable = "spikes"

    @property
    def native_parameters(self):
        return self.parameter_space

    def get_native_names(self, *names):
        return names

    def _get_minimum_delay(self):
        return state.min_delay

def nineml_synapse_type(name, nineml_model):
    """

    """
    return _nest_build_nineml_synapsetype(name, (NineMLSynapseType,), {'nineml_model': nineml_model, 'nest_name': nineml_model.name})

class _nest_build_nineml_synapsetype(type):
    """
    Metaclass for building NineMLSynapseType subclasses.
    """
    def __new__(cls, name, bases, dct):

        import pype9
        from pype9.simulate.nest import CodeGenerator
        from pype9.simulate.nest.units import UnitHandler

        builder = CodeGenerator()

        # Extract attributes from dct:
        model = dct['nineml_model']

        # Calculate attributes of the new class
        dct["default_parameters"] = {
            "weight": 0.0, "delay": None,
            "dendritic_delay_fraction": 1.0
        }
        dct["default_parameters"].update((param.name, 1.0) for param in model.parameters)
        dct["default_initial_values"] = dict((statevar.name, 0.0) for statevar in model.state_variables)
        dct["postsynaptic_variable"] = "spikes"
        dct["model"] = name

        logger.debug("Creating class '%s' with bases %s and dictionary %s" % (name, bases, dct))

        # Now generate and compile the NEST model
        all_triggers = []
        for regime in model.regimes:
            for on_condition in regime.on_conditions:
                if on_condition.trigger.rhs not in all_triggers:
                    all_triggers.append(on_condition.trigger.rhs)

        context = {
            'component_class': model,
            'all_triggers': all_triggers,
            'component_name': model.name,
            'version': pype9.__version__,
            'timestamp': datetime.now().strftime('%a %d %b %y %I:%M:%S%p'),
            'unit_handler': UnitHandler(model),
            'regime_varname': builder.REGIME_VARNAME,
            'code_gen': builder,
        }

        # Render source files
        nest_model_dir=os.path.join(NEST_DIR, name)
        src_dir=os.path.join(nest_model_dir, 'src')
        builder.clean_src_dir(src_dir=src_dir, name=name)
        builder.generate_source_files(component_class=model, src_dir=src_dir)

        # Generate Makefile if it is not present
        compile_dir=os.path.join(nest_model_dir,'compile')
        install_dir=os.path.join(nest_model_dir,'install')
        builder.clean_compile_dir(compile_dir=compile_dir)
        builder.configure_build_files(name=model.name, src_dir=src_dir,
                                        compile_dir=compile_dir,
                                        install_dir=install_dir)

        # Compile C++ header file
        builder.clean_install_dir(install_dir)
        builder.compile_source_files(compile_dir=compile_dir,
                                        component_name = model.name)

        # Load the libraries into the Python namespace
        builder.load_libraries(name=model.name, url=install_dir)

        return type.__new__(cls, name, bases, dct)
