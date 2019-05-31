set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt4 REQUIRED QtGui QtDBus)

add_executable(qdbusdaemon_sample
	main.cpp
	MainWindow.h
	MainWindow.cpp
)

target_link_libraries(qdbusdaemon_sample
	qdbusdaemon
	Qt4::QtGui
	Qt4::QtDBus
)
