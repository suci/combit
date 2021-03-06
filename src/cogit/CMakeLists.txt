set (COGIT_VERSION_MAJOR 0)
set (COGIT_VERSION_MINOR 1)
set (COGIT_VERSION_RELEASE 1)
set (COGIT_VERSION "${COGIT_VERSION_MAJOR}.${COGIT_VERSION_MINOR}.${COGIT_VERSION_RELEASE}" )

include_directories (
	${VERSION_HEAD_INCLUDES}
	)

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/version_cogit.h.cmake"
	"${VERSION_HEAD_INCLUDES}/version_cogit.h"
	)

add_definitions(-DCOGIT_LIBRARY)

set(cogit_SRCS
	coactor.cpp
	coblob.cpp
	cocommit.cpp
	codiff.cpp
	coerrors.cpp
	cogit.cpp
	cohead.cpp
	coobject.cpp
	coprocess.cpp
	coref.cpp
	corepo.cpp
	costats.cpp
	cotag.cpp
	cotree.cpp
	coutils.cpp
	)
set(cogit_HEADERS
	coactor.h
	coblob.h
	cocommit.h
	codiff.h
	coerrors.h
	cogit.h
	cohead.h
	coobject.h
	coprocess.h
	corepo.h
	coref.h
	costats.h
	cotag.h
	cotree.h
	coutils.h
	)

qt4_wrap_cpp(cogit_HEADERS_MOC ${cogit_HEADERS})

add_library(CoGit ${LIBRARY_TYPE} ${cogit_SRCS} ${cogit_HEADERS_MOC})
target_link_libraries(CoGit ${QT_LIBRARIES})
