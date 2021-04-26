# Install script for directory: /home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE MODULE FILES "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/compile/StdpSongAbbottmodule.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/StdpSongAbbottmodule.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/compile/libStdpSongAbbottmodule.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libStdpSongAbbottmodule.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/src/StdpSongAbbottmodule.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE DIRECTORY FILES "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/src/sli")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/install/share/doc/StdpSongAbbottmodule/help")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/install/share/doc/StdpSongAbbottmodule" TYPE DIRECTORY FILES "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/compile/doc/help")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(
      COMMAND /home/pedroernesto/anaconda3/envs/PyNN-branch-nineml_pype9-branch-plasticiy-NEST/bin/python -B generate_helpindex.py "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/install/share/doc/StdpSongAbbottmodule"
      WORKING_DIRECTORY "/home/pedroernesto/anaconda3/build/NEST/share/nest/help_generator"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/pedroernesto/Documents/Project/Code/Models_RepresentationSharing/TASKS_PyNN-branch-nineml/PyNN-branch-nineml_from-apdavisonGitHub/examples/NEST_nineml_models/StdpSongAbbott_latest/compile/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
