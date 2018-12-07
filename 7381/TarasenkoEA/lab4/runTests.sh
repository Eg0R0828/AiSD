echo "Test1 input: (a#(b(c)#))"
./main < ./Tests/test1.txt

echo "Test2 input: (a)"
./main < ./Tests/test2.txt

echo "Test3 input: (a(b#(d))(c(e(g)(h))(f(i)#)))"
./main < ./Tests/test3.txt

echo "Test4 input: ()"
./main < ./Tests/test4.txt

echo "Test5 input: "
./main < ./Tests/test5.txt

echo "Test6 input: a"
./main < ./Tests/test6.txt

echo "Test7 input: (a(b)(c))))"
./main < ./Tests/test7.txt

echo "Test8 input: (abc)"
./main < ./Tests/test7.txt