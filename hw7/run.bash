clang++ main.cpp -o hw7 -Wall

./hw7 simple_test1.txt o_simple_test1.txt
./hw7 simple_test2.txt o_simple_test2.txt
./hw7 small_test1.txt o_small_test1.txt
./hw7 small_test2.txt o_small_test2.txt

diff o_simple_test1.txt out_simple_test1.txt
diff o_simple_test2.txt out_simple_test2.txt
diff o_small_test1.txt out_small_test1.txt
diff o_small_test2.txt out_small_test2.txt

rm hw7
rm o_simple_test1.txt
rm o_simple_test2.txt
rm o_small_test1.txt
rm o_small_test2.txt
