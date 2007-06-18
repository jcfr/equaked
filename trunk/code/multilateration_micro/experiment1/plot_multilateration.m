
%unsigned int max value
uint_max = 65535;


%------- experiment 1 ---------
%counters 
count_idx_s1 = 3;
count_idx_s2 = 3;
count_idx_s3 = 3;

%low granularity counter
count_s1 = 805;
count_s2 = 799;
count_s3 = 797;

%--------- experiment 2 --------
% count_idx_s1 = 4;
% count_idx_s2 = 4;
% count_idx_s3 = 4;
% 
% count_s1 = 1136;
% count_s2 = 1268;
% count_s3 = 1539;

%sampling frequency
f = 200*10^3

R1 = (count_idx_s1 * uint_max + count_s1) * (1/f);
R2 = (count_idx_s2 * uint_max + count_s2) * (1/f)
R3 = (count_idx_s3 * uint_max + count_s3) * (1/f);

%
xmin = -1; 
xmax = 29.7 + 21; 
ymin = -1; 
ymax = 29.7 + 21; 

%wave velocity in m/s at 24 Celsius
velocity = 346; 

%center
x2 = 0; 
y2 = 0;
b=[x2 y2]; 

%location of receiver 1
x1 = 0; 
y1 = 29.7 + 21 - 5; 
a = [x1 y1];  

%location of receiver 3
x3 = 29.7 + 21; 
y3 = 0;
c = [x3 y3];



%recordered TDOA
R12 = R1 - R2 ;
R21 = -R12;
R32 = R3 - R2;
R23 = -R32;
R13 =  R1 - R3;
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
xlim([xmin xmax]);
ylim([ymin ymax]);
title({'Localization of epicenter', 'Graphical solution'});
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





