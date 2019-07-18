cd library/rational
sh build.sh
cd ../..
g++ -std=c++17 -O -o product/8bit \
    `find ./source -name "*.cpp"` \
    ./library/rational/product/rational.a
cd product
./8bit -o test.wav sample.mml
cd ..