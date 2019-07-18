cd object
for i in `find ../source -name "*.cpp"`
do g++ -std=c++17 -O -c $i
done
cd ..
ar rcs ./product/rational.a `find ./object -name "*.o"`