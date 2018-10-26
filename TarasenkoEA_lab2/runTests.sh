echo "Test1 input: (a (b c) d)"
./list < ./Tests/test1.txt

echo "Test1 input: ()"
./list < ./Tests/test2.txt

echo "Test1 input: "
./list < ./Tests/test3.txt

echo "Test1 input: ab"
./list < ./Tests/test4.txt

echo "Test1 input: (a b c(d e f(g)) h(i) j(k l) m n o(p))"
./list < ./Tests/test5.txt

echo "Test1 input: (a b(c)))"
./list < ./Tests/test6.txt