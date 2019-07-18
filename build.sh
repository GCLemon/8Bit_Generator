cd library/rational
sh build.sh
cd ../..
g++ -std=c++17 -O -o product/mmltofc \
    `find ./source -name "*.cpp"` \
    ./library/rational/product/rational.a