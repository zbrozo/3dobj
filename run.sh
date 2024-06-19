cmake --build build
./generator -t cube 50 
./generator -t cube-ext -c 1 2 -p 100 
./generator -t cube-ext -c 3 -p 50
./generator -t thorus 4 3 
./generator -t thorus 4 4
./generator -t thorus 6 8
./generator -t thorus 20 20 
./viewer cube cube-ext_1_2_100 cube-ext_3_50 thorus_4_3 thorus_4_4 thorus_6_8 thorus_20_20
