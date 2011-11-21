# Locate LUA library
# This module defines
# LUA_FOUND, if false, do not try to link to LUA
# LUA_LIBRARY, the name of the librarys to link against
# LUA_INCLUDE_DIR, where to find LUA headers
#
# By default this script will link to the shared-nondebug version of LUA
# You can change this by define this variables befor calling FIND_PACKAGE
#
# LUA_DEBUG - If defined it will link to the debug version of LUA
# LUA_STATIC - If defined it will link to the static version of LUA
#
# For example:
# SET(LUA_STATIC true)
# FIND_PACKAGE(LUA REQUIRED COMPONENTS System Window)
#
# Created by Nils Hasenbanck. Based on the FindSDL_*.cmake modules,
# created by Eric Wing, which were influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).
#
# Changelog:
# 2010-04-04 - Add support for visual studio 2008 (9.0)
# 2010-04-09 - Add support for visual studio 2005 (8.0)
#            - Now the test for the requested components is also implemented.
#            - It also will only link to the requested components
#            - You can chose wich debug/nondebug static/shared versions of the librarys you want to link to

SET(LUA_LIBRARY "")
SET(LUA_INCLUDE_DIR "")

SET( LUADIR $ENV{LUADIR} )
IF(WIN32 AND NOT(CYGWIN))
   # Convert backslashes to slashes
    STRING(REGEX REPLACE "\\\\" "/" LUADIR "${LUADIR}")
ENDIF(WIN32 AND NOT(CYGWIN))

SET(LUA_INCLUDE_COMPONENTS
  lua
  lualib
  lauxlib
)

SET(LUA_LIB_COMPONENTS
  lua
)

SET(LUA_INCLUDE_SEARCH_DIR
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include/lua
    /usr/include/lua
    /usr/local/include
    /usr/include
    /sw/includelua # Fink
    /sw/include
    /opt/local/include/lua # DarwinPorts
    /opt/local/include
    /opt/csw/include/lua # Blastwave
    /opt/csw/include
    /opt/include/lua
    /opt/include
    ${LUADIR}
    ${LUADIR}/include
)

SET(LUA_LIBRARY_SEARCH_DIR
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr/local/lib
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    ${LUADIR}
    ${LUADIR}/lib/vc2008
    ${LUADIR}/lib/vc2005
)

#looking for the include files
FOREACH(COMPONENT ${LUA_INCLUDE_COMPONENTS})
   STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT)
   STRING(TOLOWER ${COMPONENT} LOWERCOMPONENT)

   FIND_PATH(LUA_${UPPERCOMPONENT}_INCLUDE_DIR
      ${COMPONENT}.h
      PATH_SUFFIXES include lua
      PATHS ${LUA_INCLUDE_SEARCH_DIR}
   )

   IF(LUA_${UPPERCOMPONENT}_INCLUDE_DIR)
      IF(WIN32)
         # In wxWIN we need the root include directory without the "/LUA" at the end... so we have to remove it.
         # This is a oversized "remove 5 chars at the right end of the string" function:
         string(LENGTH ${LUA_${UPPERCOMPONENT}_INCLUDE_DIR} STRING_SIZE)
         math(EXPR STRING_SIZE ${STRING_SIZE}-5)
         string(SUBSTRING "${LUA_${UPPERCOMPONENT}_INCLUDE_DIR}" 0 ${STRING_SIZE} LUA_${UPPERCOMPONENT}_INCLUDE_DIR)
      ENDIF(WIN32)

      LIST(APPEND LUA_INCLUDE_DIR ${LUA_${UPPERCOMPONENT}_INCLUDE_DIR})
      LIST(REMOVE_DUPLICATES LUA_INCLUDE_DIR)
   ENDIF(LUA_${UPPERCOMPONENT}_INCLUDE_DIR)
ENDFOREACH(COMPONENT)

#looking for the librarys
FOREACH(COMPONENT ${LUA_LIB_COMPONENTS})
  STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT)
  STRING(TOLOWER ${COMPONENT} LOWERCOMPONENT)

  FIND_LIBRARY(LUA_${UPPERCOMPONENT}_LIBRARY
    ${COMPONENT}
    PATHS ${LUA_LIBRARY_SEARCH_DIR}
    )

  IF (LUA_${UPPERCOMPONENT}_LIBRARY)
    LIST(APPEND LUA_LIBRARY ${LUA_${UPPERCOMPONENT}_LIBRARY})
    LIST(REMOVE_DUPLICATES LUA_LIBRARY)
  ENDIF(LUA_${UPPERCOMPONENT}_LIBRARY)

ENDFOREACH(COMPONENT)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LUA DEFAULT_MSG LUA_LIBRARY LUA_INCLUDE_DIR)

