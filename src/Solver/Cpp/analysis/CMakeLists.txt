set(BOOST_ROOT = "C:/Boost/boost_1_81_0")
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.81.0 REQUIRED COMPONENTS serialization)
add_library(IOC indexOfCoincidence.cpp)
add_library(IOCO indexOfCoincidenceOptimal.cpp)
add_library(NGram NGram.cpp)
target_link_libraries(NGram PUBLIC
	Boost::headers
	Boost::serialization
)
target_link_libraries(IOCO PUBLIC IOC)