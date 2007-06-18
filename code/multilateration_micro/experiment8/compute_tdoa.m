function [tdoa12, tdoa32, tdoa13]=compute_tdoa()

prewindow_size = 800;
uint_size = 65535;

[d58wave cidx58 cv58] = recompose_wave(58);
[d70wave cidx70 cv70] = recompose_wave(70);
[d57wave cidx57 cv57] = recompose_wave(57);

c58 = cidx58 * uint_size + cv58;
c70 = cidx70 * uint_size + cv70;
c57 = cidx57 * uint_size + cv57;

min_val = min([c58 c70 c57]);

%compute padding
pad58 = c58 - min_val;
pad70 = c70 - min_val;
pad57 = c57 - min_val;

%axis
xmin_axis = 700;
xmax_axis = 1300;

%signal 
xmin = 1;
xmax = 2600 + max([pad58 pad70 pad57]);


%avg on the first 100 samples
avglen = 100;
avg57 = sum(d57wave(1:avglen)) / avglen;
avg58 = sum(d58wave(1:avglen)) / avglen;
avg70 = sum(d70wave(1:avglen)) / avglen;

%center
d57wavec = d57wave - avg57;
d58wavec = d58wave - avg58;
d70wavec = d70wave - avg70;

%shift signals
d57wavec_shift = [zeros(pad57, 1); d57wavec; zeros(xmax-size(d57wavec,1)-pad57, 1)];
d58wavec_shift = [zeros(pad58, 1); d58wavec; zeros(xmax-size(d58wavec,1)-pad58, 1)];
d70wavec_shift = [zeros(pad70, 1); d70wavec; zeros(xmax-size(d70wavec,1)-pad70, 1)];

%plot
figure(1);
subplot(3,1,1), plot(d58wavec_shift);
title('Station 1 (id58)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad58, 'r');


subplot(3,1,3), plot(d70wavec_shift);
title('Station 3 (id70)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad70, 'r');

subplot(3,1,2), plot(d57wavec_shift);
title('Station 2 (id57)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad57, 'r');

%------------- XCorr --------------
xc12 = xcorr(d57wavec_shift, d58wavec_shift);
xc32 = xcorr(d57wavec_shift, d70wavec_shift);
xc13 = xcorr(d70wavec_shift, d58wavec_shift);

%plot xcorrelation

figure(2);
subplot(3,1,1), plot(xc12);
title('Cross-Correlation btw S1 and S2');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
vline(xmax, 'r');
vline(find(xc12==max(xc12)), 'g');

tdoa12 = ( xmax - find(xc12==max(xc12)) );

subplot(3,1,2), plot(xc32);
title('Cross-Correlation btw S3 and S2');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
vline(xmax, 'r');
vline(find(xc32==max(xc32)), 'g');

tdoa32 = ( xmax - find(xc32==max(xc32)) );

subplot(3,1,3), plot(xc13);
title('Cross-Correlation btw S1 and S3');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
vline(xmax, 'r');
vline(find(xc13==max(xc13)), 'g');

tdoa13 = ( xmax - find(xc13==max(xc13)) );
