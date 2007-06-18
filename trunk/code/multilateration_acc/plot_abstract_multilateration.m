

%
xmin = -3; 
xmax = 15; 
ymin = -3; 
ymax = 15; 

%center
x2 = 0; 
y2 = 0;
b=[x2 y2]; 

%location of receiver A
x1 = 0; 
y1 = 10; 
a = [x1 y1];  

%location of receiver C
x3 = 10; 
y3 = 0;
c = [x3 y3];

%location of receiver D
x4 = 7; 
y4 = 5;
d = [x4 y4];

%epicenter
epicenter = [7 3];

R1 = sqrt((epicenter(1) - x1)^2+(epicenter(2) - y1)^2);
R2 = sqrt((epicenter(1) - x2)^2+(epicenter(2) - y2)^2); 
R3 = sqrt((epicenter(1) - x3)^2+(epicenter(2) - y3)^2); 
R4 = sqrt((epicenter(1) - x4)^2+(epicenter(2) - y4)^2);

%recordered TDOA
R12 = R1 - R2 ;
R21 = -R12;
R32 = R3 - R2;
R23 = -R32;
R13 =  R1 - R3;
R31 = -R13;
R34 = R3 - R4; 
R43 = -R34;


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

figure(1);
subplot(1,2,1);
xlabel('X location (cm)');
ylabel('Y location (cm)');
title({'Localization of epicenter', 'Graphical solution'});
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

%plot(x4, y4, 'x');
%text(x4, y4, 'Station 4','HorizontalAlignment','left', 'VerticalAlignment', 'top');

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

% ---------- butcher algorithm ----------------

subplot(1,2,2);
xlabel('X location (cm)');
ylabel('Y location (cm)');
title({'Localization of epicenter', 'Bucher algorithm'});
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

plot(x4, y4, 'x');
text(x4, y4, 'Station 4','HorizontalAlignment','left', 'VerticalAlignment', 'top');

%usefull identities
x12 = x1 - x2;
x21 = -x12;
x32 = x3 - x2;
x23 = -x32;
y32 = y3 - y2;
y23 = -y32;
y12 = y1 - y2;
y21 = -y12;
x13 = x1 - x3;
x31 = -x13;
y13 = y1 - y3;
y31 = -y13;
x43 = x4 - x3;
x34 = -x43;
y43 = y4 - y3;
y34 = -y43;


%equation 1
A1 = (R13 * x21 - R12 * x31) / (R12 * y31 - R13 * y21);
C1 = (R13 * ( R12^2 + x1^2 - x2^2 + y1^2 - y2^2)  - R12 * (R13^2 + x1^2 - x3^2 + y1^2 - y3^2)) / (2* (R12 * y31 - R13 * y21));

X3 = [xmin:0.01:xmax];
d1 = x * A1 + C1; 
zfund1 = @(x) eval(vectorize(d1));
y41=zfund1(X3);

plot(X3, y41, 'g');


%JC sol 2
%A2 = (Rca * x2c - Rcb * x1c) / (Rcb * y1c - Rca * y2c)
%C2 = (Rca * ( Rcb^2 + x3^2 - x2^2 + y3^2 - y2^2) - Rcb * (Rca^2 + x3^2 - x1^2 + y3^2 - y1^2)) / (2 * (Rcb * y1c - Rca * y2c) )

%Nath sol 2
%A2 = - (Rcb*x2a - Rab*x2c) / (Rab*y2c - Rcb*y2a)
%C2 = ( Rcb*(Rab^2 + x1^2 - x2^2 + y1^2 - y2^2) - Rab*(Rcb^2+x3^2-x2^2+y3^2-y2^2) ) / (2*(Rab*y2c - Rcb*y2a))

%With 4th receiver
A2 = (R34 * x23 - R32 * x43) / (R32 * y43 - R34 * y23);
C2 = (R34 * ( R32^2 + x3^2 - x2^2 + y3^2 - y2^2) - R32 * (R34^2 + x3^2 - x4^2 + y3^2 - y4^2)) / (2 * (R32 * y43 - R34 * y23) );

d2 = x * A2 + C2; 
zfund2 = @(x) eval(vectorize(d2));
y42=zfund2(X3);

plot(X3, y42, 'r');


%re-injection trial
% yjoker = x * A1 + C1;
% djoker = ((x-x1)^2+(yjoker-y1)^2)^(1/2) - ((x-x3)^2+(yjoker-y3)^2)^(1/2) - Rac; 
% 
% zfundjoker = @(x) eval(vectorize(djoker));
% y4Joker=zfundjoker(X3);
% 
% plot(X3, y4Joker, 'b');


%-------- solution using equation and exact TDOA -----
% subplot(2,2,3);
% xlabel('X location (cm)');
% ylabel('Y location (cm)');
% xlim([xmin xmax]);
% ylim([ymin ymax]);
% title({'Localization of epicenter', 'Using equation solutions'});
% hold on;
% 
% %plot the receiver locations
% plot(x1, y1, 'x');
% text(x1, y1,'Station 1','HorizontalAlignment','left', 'VerticalAlignment', 'top');
% 
% plot(x2, y2, 'x');
% text(x2, y2,'Station 2','HorizontalAlignment','left', 'VerticalAlignment', 'top');
% 
% plot(x3, y3, 'x');
% text(x3, y3, 'Station 3','HorizontalAlignment','left', 'VerticalAlignment', 'top');
% 
% 
% X = 5-1/20/(4*R32^2+4*R12^2-400)*(400*R12-4*R12^3+8*R32*R12^2+4*R32^3-400*R32-4*(2000000-200*R12^3*R32+400*R32^2*R12^2+100*R12^4+100*R32^4-R12^4*R32^2+2*R12^3*R32^3-200*R12*R32^3-R32^4*R12^2+20000*R12*R32-30000*R32^2-30000*R12^2)^(1/2))*R32+1/20*R32^2;
% 
% Y = 5-1/20/(4*R32^2+4*R12^2-400)*(400*R12-4*R12^3+8*R32*R12^2+4*R32^3-400*R32-4*(2000000-200*R12^3*R32+400*R32^2*R12^2+100*R12^4+100*R32^4-R12^4*R32^2+2*R12^3*R32^3-200*R12*R32^3-R32^4*R12^2+20000*R12*R32-30000*R32^2-30000*R12^2)^(1/2))*R12-1/20*R12^2+1/10*R12*R32;
% 
% plot(X, Y, 'or'); 




