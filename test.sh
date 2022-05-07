g++ edge.cpp Node.cpp NodeTest.cpp -o NodeTest
valgrind ./NodeTest 2> NodeTest.res

g++ edge.cpp Node.cpp list.cpp ListTest.cpp -o ListTest
valgrind ./ListTest 2> ListTest.res

g++ edge.cpp EdgeTest.cpp -o EdgeTest
valgrind ./EdgeTest 2> EdgeTest.res

g++ edge.cpp Node.cpp list.cpp graph.cpp GraphTest.cpp -o GraphTest
valgrind ./GraphTest 2> GraphTest.res

