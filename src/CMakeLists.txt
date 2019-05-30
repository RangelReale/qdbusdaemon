find_package(Qt4 REQUIRED QtDBus)

SET(SRCS
	qdbusdaemon.cpp
	daemon.cpp
)

SET(INCS
	../include/qdbusdaemon/qdbusdaemon.h
	../include/qdbusdaemon/daemon.h
)

#	add_definitions(-DMILEVERSION_IMPL_WIN32)
#	LIST(APPEND SRCS mileversionimpl_WIN32.cpp)
#	LIST(APPEND INCS ../include/mileversion/mileversionimpl_WIN32.h)

ADD_LIBRARY(qdbusdaemon STATIC ${SRCS} ${INCS} )

target_link_libraries(qdbusdaemon Qt4::QtDBus)
