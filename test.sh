g++ Node.cpp NodeTest.cpp -o NodeTest
valgrind ./NodeTest 2> NodeTest.res

g++ Node.cpp list.cpp ListTest.cpp -o ListTest
valgrind ./ListTest 2> ListTest.res


