add_library(IOC indexOfCoincidence.cpp)
add_library(NGram NGram.cpp)
target_link_libraries(NGram PUBLIC
	Boost::headers
	Boost::serialization
)