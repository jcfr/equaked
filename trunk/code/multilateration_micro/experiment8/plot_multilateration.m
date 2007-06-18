
close all; 

%wave velocity in air at 24°C (m/s)
velocity = 34600; 

%sampling frequency
f = 200*10^3;

%area limits
xmin = -3; 
xmax = 29.7 + 21 + 3; 
ymin = -5; 
ymax = 29.7 + 21; 

%center
x2 = 0; 
y2 = 0;
b=[x2 y2]; 

%location of receiver A
x1 = 0; 
y1 = 29.7 + 21 - 5; 
a = [x1 y1];  

%location of receiver C
x3 = 29.7 + 21; 
y3 = 0;
c = [x3 y3];

[t12, t32, t13] = compute_tdoa();

R12 = t12 * ( velocity / f );
R21 = -R12;
R32 = t32 * ( velocity / f );
R23 = -R32;
R13 =  t13 * ( velocity / f );
R31 = -R13;

%declare symbolic objects
syms x y; 

%time difference between receiver A and receiver B
f12 = ((x-x1)^2+(y-y1)^2)^(1/2) - ((x-x2)^2+(y-y2)^2)^(1/2) - R12;

%time difference between receiver C and receiver B
f32 = ((x-x3)^2+(y-y3)^2)^(1/2) - ((x-x2)^2+(y-y2)^2)^(1/2) - R32;

%time difference between receiver A and receiver C
f13 = ((x-x1)^2+(y-y1)^2)^(1/2) - ((x-x3)^2+(y-y3)^2)^(1/2) - R13;

%plot all contour
% figure(1);
% hold on; 
% ezcontour(fab, [xmin, xmax, ymin, ymax]);
% ezcontour(fcb, [xmin, xmax, ymin, ymax]);
% ezcontour(fac, [xmin, xmax, ymin, ymax]);

%plot 3D representation
% figure(2);
% hold on; 
% ezsurf(fab, [xmin, xmax, ymin, ymax]);
% ezsurf(fcb, [xmin, xmax, ymin, ymax]);
% ezsurf(fac, [xmin, xmax, ymin, ymax]);

% --------- 2D plotting -----------

figure(3);
xlabel('X location (cm)');
ylabel('Y location (cm)');
title({'Localization of epicenter', 'Graphical Solution'});
xlim([xmin xmax]);
ylim([ymin ymax]);
hold on;

%plot the receiver locations
plot(x1, y1, 'x');
text(x1, y1,'Station 1','HorizontalAlignment','left', 'VerticalAlignment', 'top');

plot(x2, y2, 'x');
text(x2, y2,'Station 2','HorizontalAlignment','left', 'VerticalAlignment', 'top');

plot(x3, y3, 'x');
text(x3, y3, 'Station 3','HorizontalAlignment','left', 'VerticalAlignment', 'top');

%plot only the interesting contour on the plan 

[X1,Y1]= meshgrid(xmin:.2:xmax,ymin:.2:ymax);

zfun1 = @(x, y) eval(vectorize(f12));
zfun2 = @(x, y) eval(vectorize(f32));
zfun3 = @(x, y) eval(vectorize(f13));
Z1=zfun1(X1,Y1);
Z2=zfun2(X1,Y1);
Z3=zfun3(X1,Y1);

contour(X1, Y1, Z1, [0 0], 'r');
contour(X1, Y1, Z2, [0 0], 'b');
contour(X1, Y1, Z3, [0 0], 'y');






