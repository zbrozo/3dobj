cmake --build build
./generator --v --t cube 50 
./generator --v --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 50 --f 0 0 50
./generator --v --t cube-ext --c Pyramid --p 50 --f 0 0 50
./generator --v --t thorus 4 3 
./generator --v --t thorus 4 4
./generator --v --t thorus 6 8
./generator --v --t thorus 20 20 100 130
./generator --v --t cuboid --c0 Pyramid --p0 50 50 --f0 0 0 20 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 20 0 180 0 --c2 Rectangle --p2 20 50 --f2 0 0 50 0 90 0 --c3 Rectangle --p3 20 50 --f3 0 0 50 0 270 0 --c4 Rectangle --p4 50 20 --f4 0 0 50 90 0 0 --c5 Rectangle --p5 50 20 --f5 0 0 50 270 0 0
./generator --v --o cuboid2 --t cuboid --c0 Pyramid --p0 50 50 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 0 0 180 0
./generator --v --o taper1 --t cuboid --c0 Taper --p0 3 50 50 --c1 Taper --p1 3 50 -50
./generator --v --o taper2 --t cuboid --c0 Taper --p0 6 50 50 --c1 Taper --p1 6 50 -50
./viewer cube cube-ext_SquareHolePart1_SquareHolePart2_50 cube-ext_Pyramid_50 thorus_4_3 thorus_4_4 thorus_6_8 thorus_20_20_100_130 cuboid cuboid2 taper1 taper2
