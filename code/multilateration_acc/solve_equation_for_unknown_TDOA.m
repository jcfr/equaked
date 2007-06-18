%try to solve

%location of receiver 1
x1 = 0; 
y1 = 10; 

%location of receiver 2, [center]
x2 = 0; 
y2 = 0;  

%location of receiver 3
x3 = 10; 
y3 = 0;

%declare symbolic objects
syms x y R12 R32; 

%time difference between receiver 1 and receiver 2
f12 = ((x-x1)^2+(y-y1)^2)^(1/2) - ((x-x2)^2+(y-y2)^2)^(1/2) - R12;

%time difference between receiver 3 and receiver 2
f32 = ((x-x3)^2+(y-y3)^2)^(1/2) - ((x-x2)^2+(y-y2)^2)^(1/2) - R32;


[X, Y] = solve(f12, f32, x, y)
