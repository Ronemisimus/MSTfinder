g++ Node.cpp NodeTest.cpp -o NodeTest
valgrind ./NodeTest > NodeTest.res

g++ Node.cpp list.cpp ListTest.cpp -o ListTest
valgrind ./ListTest > ListTest.res


