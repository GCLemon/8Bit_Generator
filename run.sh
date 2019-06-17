cd object

source=`find ../source -name "*.cpp"`

for s in ${source[@]}
do
    g++ -O -c $s
done

g++ -O -o ../product/8bit ${source[@]}
cd ../product
./8bit test.mml
cd ..