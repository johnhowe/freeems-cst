set( TESTS
     cst-test0
     cst-test2
     encoder-test
     decoder-test
     )

foreach( test ${TESTS} )
  add_executable( ${test} ${test}.cpp )
  target_link_libraries( ${test} ${LIBS} )
endforeach( test )
