cmake --build build
./generator -t cube 50 
./generator -t cube-ext -c SquareHolePart1 SquareHolePart2 -p 100 
./generator -t cube-ext -c Pyramid -p 50
./generator -t thorus 4 3 
./generator -t thorus 4 4
./generator -t thorus 6 8
./generator -t thorus 20 20 100 130 
./generator -t cuboid -v --c0 Pyramid --p0 50 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 50 --f1 0 0 0 0 180 0 --c2 Pyramid --p2 50 --f2 0 0 0 0 90 0 --c3 Pyramid --p3 50 --f3 0 0 0 0 270 0 --c4 Square --p4 50 --f4 0 0 0 90 0 0 --c5 Square --p5 50 --f5 0 0 0 270 0 0
./viewer cube cube-ext_SquareHolePart1_SquareHolePart2_100 cube-ext_Pyramid_50 thorus_4_3 thorus_4_4 thorus_6_8 thorus_20_20_100_130 cuboid
