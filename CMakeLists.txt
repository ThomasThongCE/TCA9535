cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(TCA9535)
SET(LICENSE "TBD")

######## Build and include settings ########
include_directories(
	inc
)

link_directories(
	${LINK_DIRECTORIES}
)


file(GLOB SOURCES
	"src/*.cpp"
)

add_executable(
	TCA9535

	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	TCA9535
)

######## Install targets ########
INSTALL(TARGETS TCA9535
	RUNTIME DESTINATION usr/bin
)
