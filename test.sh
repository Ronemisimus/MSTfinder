g++ -g edge.cpp Node.cpp NodeTest.cpp -o NodeTest
valgrind ./NodeTest 2> NodeTest.res

g++ -g edge.cpp Node.cpp list.cpp ListTest.cpp -o ListTest
valgrind ./ListTest 2> ListTest.res

g++ -g edge.cpp EdgeTest.cpp -o EdgeTest
valgrind ./EdgeTest 2> EdgeTest.res

g++ -g edge.cpp Node.cpp list.cpp graph.cpp GraphTest.cpp -o GraphTest
valgrind ./GraphTest 2> GraphTest.res

g++ -g hashMap.cpp heap.cpp heapTest.cpp -o heapTest
valgrind ./heapTest 2> heapTest.res

g++ -g unionFind.cpp unionFindTest.cpp -o unionFindTest
valgrind ./unionFindTest 2> unionFindTest.res

g++ -g hashMap.cpp hashMapTest.cpp -o hashMapTest
valgrind ./hashMapTest 2> hashMapTest.res

g++ -g hashMap.cpp unionFind.cpp heap.cpp Node.cpp edge.cpp graph.cpp list.cpp main.cpp -o mainTests/mainTest
valgrind mainTests/mainTest 2> mainTests/mainTest.res 

for f in $(ls -1 tests)
do
    valgrind --leak-check=full mainTests/mainTest tests/$f 2> mainTests/mainTest$f.res
done

