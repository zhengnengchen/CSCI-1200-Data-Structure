clang++ *.cpp -o hw2 -Wall

./hw2 example.txt o_example.txt standard
./hw2 no_strikes_or_spares.txt o_no_strikes_or_spares.txt standard
./hw2 simple_tenth.txt o_simple_tenth.txt standard

diff out_example.txt o_example.txt
diff out_no_strikes_or_spares.txt o_no_strikes_or_spares.txt
diff out_simple_tenth.txt o_simple_tenth.txt

rm o_example.txt
rm o_no_strikes_or_spares.txt
rm o_simple_tenth.txt
rm hw2
