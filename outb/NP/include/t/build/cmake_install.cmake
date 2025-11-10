# Install script for directory: /work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooFitUnfold.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldBayes.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldBinByBin.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldErrors.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldFitHelpers.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldGP.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldHelpers.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldIds.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldInvert.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldParms.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldPoisson.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldResponse.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldSvd.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldTH1Helpers.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfoldTUnfold.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold_LinkDef.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfold.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfoldBinning.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfoldBinningXML.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfoldDensity.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfoldIterativeEM.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/TUnfoldSys.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/RooUnfold/TUnfold" TYPE FILE FILES
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfold.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfoldBinning.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfoldBinningXML.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfoldDensity.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfoldIterativeEM.h"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src/RooUnfold/TUnfold/TUnfoldSys.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libraries" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/build/libRooUnfold.rootmap"
    "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/build/libRooUnfold_rdict.pcm"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libraries" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/build/libRooUnfold.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so"
         OLD_RPATH "/cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/almalinux9-gcc11/local/root/6.30.04/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRooUnfold.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libraries" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
