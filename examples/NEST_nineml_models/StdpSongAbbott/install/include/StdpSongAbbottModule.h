/* This file was generated by PyPe9 version 0.2 on Fri 09 Apr 21 12:09:06PM */

#ifndef STDPSONGABBOTT_MODULE_H
#define STDPSONGABBOTT_MODULE_H

#include "slimodule.h"
#include "slifunction.h"

namespace nest {
  class Network;
}

// Put your stuff into your own namespace.
namespace nineml {

/**
 * Class defining your model.
 * @note For each model, you must define one such class, with a unique name.
 */
class StdpSongAbbottModule : public SLIModule {
 public:

  // Interface functions ------------------------------------------

  /**
   * @note The constructor registers the module with the dynamic loader.
   *       Initialization proper is performed by the init() method.
   */
  StdpSongAbbottModule();

  /**
   * @note The destructor does not do much in modules.
   */
  ~StdpSongAbbottModule();

  /**
   * Initialize module by registering models with the network.
   * @param SLIInterpreter* SLI interpreter
   */
  void init( SLIInterpreter* );

  /**
   * Return the name of your model.
   */
  const std::string name( void ) const;

  /**
   * Return the name of a sli file to execute when StdpSongAbbottModule is loaded.
   * This mechanism can be used to define SLI commands associated with your
   * module, in particular, set up type tries for functions you have defined.
   */
  const std::string commandstring( void ) const;

};

}  // nineml namespace

#endif  // STDPSONGABBOTT_MODULE_H