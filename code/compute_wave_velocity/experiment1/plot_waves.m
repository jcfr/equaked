%
%

clear;

prewindow_size = 800;
uint_size = 65535;

[d70wave cidx70 cv70] = recompose_wave(70);
[d57wave cidx57 cv57] = recompose_wave(57);

c70 = cidx70 * uint_size + cv70;
c57 = cidx57 * uint_size + cv57;

min_val = min([c70 c57]);

%compute padding
pad70 = c70 - min_val;
pad57 = c57 - min_val;

xmax = 2600 + max([pad70 pad57]);

figure(1);
subplot(2,1,2), plot([zeros(pad70, 1);d70wave]);
title('Station 2 (id70)');
xlim([0 xmax]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Accel. Z-Dim Value');
hold on;
plot(prewindow_size+pad70, [1500:4500], 'r');


%figure(3);
subplot(2,1,1), plot([zeros(pad57, 1); d57wave]);
title('Station 1 (id57)');
xlim([0 xmax]);
ylabel('Accel. Z-Dim Value');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
plot(prewindow_size+pad57, [1500:4500], 'r');
