add_library(IOC indexOfCoincidence.cpp)
add_library(IOCO indexOfCoincidenceOptimal.cpp)
add_library(NGram NGram.cpp)
target_link_libraries(NGram PUBLIC
	Boost::headers
	Boost::serialization
)
target_link_libraries(IOCO PUBLIC IOC)