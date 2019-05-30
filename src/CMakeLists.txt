find_package(Qt4 REQUIRED QtDBus)

SET(SRCS
	Base.cpp
	Process.cpp
)

SET(INCS
	../include/qdbusdaemon/Base.h
	../include/qdbusdaemon/Process.h
)

#	add_definitions(-DMILEVERSION_IMPL_WIN32)
#	LIST(APPEND SRCS mileversionimpl_WIN32.cpp)
#	LIST(APPEND INCS ../include/mileversion/mileversionimpl_WIN32.h)

ADD_LIBRARY(qdbusdaemon STATIC ${SRCS} ${INCS} )

target_link_libraries(qdbusdaemon Qt4::QtDBus)
