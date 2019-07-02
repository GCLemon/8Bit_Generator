source=`find source -name "*.cpp"`

g++ -O -o product/8bit ${source[@]}
cd product
./8bit test.mml
cd ..