set( TESTS
     cst-test0
     cst-test1
     cst-test2
     psp-test
     endec-test
     )

foreach( test ${TESTS} )
  add_executable( ${test} ${test}.cpp )
  target_link_libraries( ${test} fe ${Boost_LIBRARIES} )
endforeach( test )
