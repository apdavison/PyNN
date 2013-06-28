# encoding: utf8
"""
Implementation of the "low-level" functionality used by the common
implementation of the API, for the MOOSE simulator.

Functions and classes useable by the common implementation:
    run()


All other functions and classes are private, and should not be used by other
modules.

:copyright: Copyright 2006-2013 by the PyNN team, see AUTHORS.
:license: CeCILL, see LICENSE for details.

"""

import moose
from pyNN import common, core

name = "MOOSE"

ms = 1e-3
in_ms = 1.0/ms
mV = 1e-3
nA = 1e-9
uS = 1e-6
nF = 1e-9

INIT_CLOCK = 0
INTEGRATION_CLOCK = 1
RECORDING_CLOCK = 2

class ID(int, common.IDMixin):
    
    def __init__(self, n):
        """Create an ID object with numerical value `n`."""
        int.__init__(n)
        common.IDMixin.__init__(self)
        
    def _build_cell(self, cell_model, cell_parameters):
        """
        Instantiate a cell in MOOSE.
        
        `cell_model` -- one of the cell classes defined in the
                        `moose.cells` module (more generally, any class that
                        implements a certain interface, but I haven't
                        explicitly described that yet).
        `cell_parameters` -- a dictionary containing the parameters used to
                             initialise the cell model.
        """
        id = int(self)
        self._cell = cell_model("neuron%d" % id, **cell_parameters)  # create the cell object
        

class State(common.control.BaseState):
    """Represent the simulator state."""

    def __init__(self):
        self.clock = moose.element('/clock')
        common.control.BaseState.__init__(self)
        self.mpi_rank = 0
        self.num_processes = 1
        self.clear()

    def run(self, simtime):
        if not self.running:
            moose.reinit()
            self.running = True
        moose.start(simtime*ms)

    def clear(self):
        self.recorders = set([])
        self.gid_counter = 0
        self.segment_counter = -1
        self.reset()
        # CLEAR MOOSE?

    def reset(self):
        """Reset the state of the current network to time t = 0."""
        self.running = False
        self.t_start = 0
        self.segment_counter += 1
        moose.reinit()

    def __get_dt(self):
        return self.clock.tick[0].dt*in_ms
    def __set_dt(self, dt):
        print "setting dt to %g ms" % dt
        moose.setClock(INIT_CLOCK, dt*ms)
        moose.setClock(INTEGRATION_CLOCK, dt*ms)
        moose.setClock(RECORDING_CLOCK, dt*ms)
    dt = property(fget=__get_dt, fset=__set_dt)

    @property
    def t(self):
        return self.clock.currentTime*in_ms


state = State()
