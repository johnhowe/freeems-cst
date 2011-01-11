add_library( fe endec.cpp
                wsp.cpp
                psp.cpp
                )
target_link_libraries( fe ${Boost_LIBRARIES} )
