add_executable( cst main.cpp )
target_link_libraries ( cst ${LIBS} )

add_library( fe endec.cpp
                wsp.cpp
                psp.cpp
                )
target_link_libraries( fe ${Boost_LIBRARIES} )
