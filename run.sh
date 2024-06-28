cmake --build build

mkdir -p ./objects
mkdir -p ./objects_small

cd ./objects_small

# small objects
../generator --v --o cube1 --t cube 50
../generator --v --o cube2 --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 50 --f 0 0 50
../generator --v --o cube3 --t cube-ext --c Pyramid --p 50 --f 0 0 50
../generator --v --o thorus1 --t thorus 4 3 
../generator --v --o thorus2 --t thorus 4 4
../generator --v --o thorus3 --t thorus 6 8
../generator --v --o taper1 --t composite --c0 Taper --p0 3 50 50 --c1 Taper --p1 3 50 -50
../generator --v --o taper2 --t composite --c0 Taper --p0 6 50 50 --c1 Taper --p1 6 50 -50
../generator --v --o composite1 --t composite --c0 Pyramid --p0 50 50 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 0 0 180 0
../generator --v --o composite2 --t composite --c0 Pyramid --p0 50 50 --f0 0 0 20 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 20 0 180 0 --c2 Rectangle --p2 20 50 --f2 0 0 50 0 90 0 --c3 Rectangle --p3 20 50 --f3 0 0 50 0 270 0 --c4 Rectangle --p4 50 20 --f4 0 0 50 90 0 0 --c5 Rectangle --p5 50 20 --f5 0 0 50 270 0 0
../generator --v --o composite3 --t composite --c0 Taper --p0 6 50 50 --f0 0 0 25 --c1 Taper --p1 6 50 -50 --f1 0 0 -25 --c2 Cylinder --p2 6 50 50 --f2 0 0 25

cd ..
cd ./objects

# normal objects
../generator --v --o cube1 --t cube 100
../generator --v --o cube2 --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 100 --f 0 0 100
../generator --v --o cube3 --t cube-ext --c Pyramid --p 100 --f 0 0 100
../generator --v --o thorus1 --t thorus 20 40 30 100
../generator --v --o thorus2 --t thorus 20 40 30 100 0 0 6 10 0 0
../generator --v --o thorus3 --t thorus 20 20 30 100 0 0 3 5 0 0 0 0 1 20 0 0
../generator --v --o taper1 --t composite --c0 Taper --p0 3 100 100 --c1 Taper --p1 3 100 -100
../generator --v --o taper2 --t composite --c0 Taper --p0 6 100 100 --c1 Taper --p1 6 100 -100
../generator --v --o composite1 --t composite --c0 Pyramid --p0 100 100 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 100 100 --f1 0 0 0 0 180 0
../generator --v --o composite2 --t composite --c0 Pyramid --p0 100 100 --f0 0 0 20 0 0 0 --c1 Pyramid --p1 100 100 --f1 0 0 20 0 180 0 --c2 Rectangle --p2 20 100 --f2 0 0 100 0 90 0 --c3 Rectangle --p3 20 100 --f3 0 0 100 0 270 0 --c4 Rectangle --p4 100 20 --f4 0 0 100 90 0 0 --c5 Rectangle --p5 100 20 --f5 0 0 100 270 0 0
../generator --v --o composite3 --t composite --c0 Taper --p0 6 100 100 --f0 0 0 50 --c1 Taper --p1 6 100 -100 --f1 0 0 -50 --c2 Cylinder --p2 6 100 100 --f2 0 0 50

cd ..

./viewer objects cube1 cube2 cube3 thorus1 thorus2 thorus3 taper1 taper2 composite1 composite2 composite3
