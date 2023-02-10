# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/src;/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/compile")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/home/pedroernesto/anaconda3/lib/python3.7/site-packages/cmake/data/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "StdpSongAbbottmodule built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/compile;StdpSongAbbottmodule;ALL;/")
set(CPACK_INSTALL_PREFIX "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/install")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "StdpSongAbbottmodule 1.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "StdpSongAbbottmodule 1.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/compile/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/home/pedroernesto/anaconda3/lib/python3.7/site-packages/cmake/data/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NEST Module StdpSongAbbottmodule")
set(CPACK_PACKAGE_FILE_NAME "StdpSongAbbottmodule-1.0-Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "StdpSongAbbottmodule 1.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "StdpSongAbbottmodule 1.0")
set(CPACK_PACKAGE_NAME "StdpSongAbbottmodule")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "NEST Initiative (http://www.nest-initiative.org/)")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "/home/pedroernesto/anaconda3/lib/python3.7/site-packages/cmake/data/share/cmake-3.18/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/home/pedroernesto/anaconda3/lib/python3.7/site-packages/cmake/data/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/home/pedroernesto/anaconda3/lib/python3.7/site-packages/cmake/data/share/cmake-3.18/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "\\.gitignore;\\.git/;\\.travis\\.yml;/build/;/_CPack_Packages/;CMakeFiles/;cmake_install\\.cmake;Makefile.*;CMakeCache\\.txt;CPackConfig\\.cmake;CPackSourceConfig\\.cmake")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/compile/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "StdpSongAbbottmodule")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott/compile/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
