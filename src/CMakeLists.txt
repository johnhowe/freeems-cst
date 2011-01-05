add_executable( cst main.cpp )
target_link_libraries ( cst ${LIBS} )

add_library( fe encoder.cpp
                decoder.cpp
                )
target_link_libraries( fe ${Boost_LIBRARIES} )
