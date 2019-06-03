set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if (VQTVERSION STREQUAL QT5)
	find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
elseif (VQTVERSION STREQUAL QT4)
	find_package(Qt4 REQUIRED QtGui QtDBus)
endif()
SET( TARGET_BASE_NAME qdbusdaemon${VQTVERSION_SUFFIX}_sample )

add_executable(${TARGET_BASE_NAME}
	main.cpp
	MainWindow.h
	MainWindow.cpp
)

target_link_libraries(${TARGET_BASE_NAME}
	qdbusdaemon${VQTVERSION_SUFFIX}
	Qt4::QtGui
	Qt4::QtDBus
)

if (VQTVERSION STREQUAL QT5)
	target_link_libraries(${TARGET_BASE_NAME} Qt5::Widgets Qt5::DBus)
elseif (VQTVERSION STREQUAL QT4)
	target_link_libraries(${TARGET_BASE_NAME} Qt4::QtGui Qt4::QtDBus)
endif()
