%
%

clear;

prewindow_size = 800;
uint_size = 65535;

[d70wave cidx70 cv70] = recompose_wave(70);
[d58wave cidx58 cv58] = recompose_wave(58);

c70 = cidx70 * uint_size + cv70;
c58 = cidx58 * uint_size + cv58;

min_val = min([c70 c58]);

%compute padding
pad70 = c70 - min_val;
pad58 = c58 - min_val;

xmax = 2600 + max([pad70 pad58]);

figure(1);
subplot(2,1,2), plot([zeros(pad70, 1);d70wave]);
title('Station 2 (id70)');
xlim([0 xmax]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Accel. Z-Dim Value');
hold on;
plot(prewindow_size+pad70, [1500:4500], 'r');


%figure(3);
subplot(2,1,1), plot([zeros(pad58, 1); d58wave]);
title('Station 1 (id58)');
xlim([0 xmax]);
ylabel('Accel. Z-Dim Value');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
plot(prewindow_size+pad58, [1500:4500], 'r');
