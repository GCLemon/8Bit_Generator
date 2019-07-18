cp library/rational.dylib product
g++ -std=c++17 -O -o product/8bit `find ./source -name "*.cpp"` -lm product/rational.dylib
cd product
./8bit
cd ..
