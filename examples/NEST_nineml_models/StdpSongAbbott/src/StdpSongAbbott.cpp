/*
  This file was generated by PyPe9 version 0.2 on Mon 10 May 21 12:03:45PM
  Based on stdp_connection_hom.cpp, which is part of NEST
  First Version of Jinja template: April 2021
  Author: Pedro Garcia-Rodriguez, ICN, CNRS, France
*/

/*
 *  stdp_connection_StdpSongAbbott.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdpSongAbbott.h"

// Includes from nestkernel:
#include "common_synapse_properties.h"
#include "connector_model.h"
#include "event.h"

// Includes from sli:
#include "dictdatum.h"