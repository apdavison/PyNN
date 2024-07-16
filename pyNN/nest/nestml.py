# -*- coding: utf-8 -*-
"""
Support cell types defined in NESTML.


Classes:
    NESTMLCellType   - base class for cell types, not used directly

Functions:
    nestml_cell_type - return a new NESTMLCellType subclass


:copyright: Copyright 2006-2024 by the PyNN team, see AUTHORS.
:license: CeCILL, see LICENSE for details.
"""

import logging
import os.path
import shutil
import tempfile

from pyNN.nest.cells import NativeCellType, native_cell_type


logger = logging.getLogger("PyNN")



def nestml_cell_type(name, nestml_description):
    """
    Return a new NESTMLCellType subclass from a NESTML description.
    """

    from pynestml.frontend.pynestml_frontend import generate_nest_target
    import nest

    module_name = "pynnnestmlmodule"  # todo: customize this
    if os.path.exists(nestml_description):
        # description is a file path
        input_path = nestml_description
    else:
        # assume description is a string containing nestml code
        input_path = tempfile.mkdtemp()
        with open(os.path.join(input_path, "tmp.nestml"), "w") as fp:
            fp.write(nestml_description)
    generate_nest_target(
        input_path=input_path,
        target_path=None,  # "/tmp/nestml_target",
        install_path=None,
        module_name=module_name,
    )
    shutil.rmtree(input_path)

    nest.Install(module_name)

    # todo: get units information from nestml_description, provide to "native_cell_type()"
    return native_cell_type(name)
