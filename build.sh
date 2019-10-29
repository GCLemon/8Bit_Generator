g++ -std=c++17 -O -o product/mmltofc `find ./source -name "*.cpp"`

cd product
./mmltofc sample.mml
cd ..