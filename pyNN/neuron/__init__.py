# encoding: utf-8
"""
nrnpython implementation of the PyNN API.

:copyright: Copyright 2006-2024 by the PyNN team, see AUTHORS.
:license: CeCILL, see LICENSE for details.

"""

from __future__ import absolute_import

import sys, os
try:
    import music.config
except ImportError:
    pass
else:
    if music.config.predictRank() >= 0:
        # launched by MPI
        os.environ['NEURON_INIT_MPI'] = '1'
        music.config.supersedeArgv(['music'] + sys.argv)

import warnings
try:
    from mpi4py import MPI                                          # noqa: F401
except ImportError:
    warnings.warn("mpi4py not available")
from .. import errors, random, space                                # noqa: F401
from ..network import Network                                       # noqa: F401
from ..standardmodels import StandardCellType
from ..random import NumpyRNG, GSLRNG, RandomDistribution           # noqa: F401
from .random import NativeRNG                                       # noqa: F401
from .standardmodels.cells import *                                 # noqa: F403, F401
from .connectors import *                                           # noqa: F403, F401
from .standardmodels.synapses import *                              # noqa: F403, F401
from .standardmodels.electrodes import *                            # noqa: F403, F401
from .standardmodels.ion_channels import *                          # noqa: F403, F401
from .standardmodels.receptors import *                             # noqa: F403, F401
from .populations import Population, PopulationView, Assembly       # noqa: F401
from .projections import Projection                                 # noqa: F401
from .cells import NativeCellType, IntFire1, IntFire2, IntFire4     # noqa: F401
from .control import (                                              # noqa: F401
    setup,
    run,
    run_until,
    run_for,
    reset,
    initialize,
    get_current_time,
    get_time_step,
    get_min_delay,
    get_max_delay,
    num_processes,
    rank,
)
from .procedural_api import create, connect, record, record_v, record_gsyn, set  # noqa: F401
from . import morphology
from .music import music_end
try:
    from . import nineml                                            # noqa: F401
except ImportError:
    pass  # nineml is an optional dependency


def list_standard_models():
    """Return a list of all the StandardCellType classes available for this simulator."""
    return [obj.__name__ for obj in globals().values() if (isinstance(obj, type) and
                                                           issubclass(obj, StandardCellType) and
                                                           obj is not StandardCellType)]


def end(compatible_output=True):
    """Do any necessary cleaning up before exiting."""
    for (population, variables, filename) in simulator.state.write_on_end:
        io = get_io(filename)
        population.write_data(io, variables)
    simulator.state.write_on_end = []
    #simulator.state.finalize()
    music_end() # not necessary once simulator.finalize is implemented


