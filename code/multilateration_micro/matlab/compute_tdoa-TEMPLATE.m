
% This file is part of Equaked.

% Equaked is free software; you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation; either version 2 of the License, or
% any later version.

% Equaked is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.

% You should have received a copy of the GNU General Public License
% along with Foobar; if not, write to the Free Software
% Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

function [tdoa12, tdoa32, tdoa13]=compute_tdoa()

prewindow_size = 800;
uint_size = 65535;

[d#STATION1#wave cidx#STATION1# cv#STATION1#] = recompose_wave(#STATION1#);
[d#STATION3#wave cidx#STATION3# cv#STATION3#] = recompose_wave(#STATION3#);
[d#STATION2#wave cidx#STATION2# cv#STATION2#] = recompose_wave(#STATION2#);

c#STATION1# = cidx#STATION1# * uint_size + cv#STATION1#;
c#STATION3# = cidx#STATION3# * uint_size + cv#STATION3#;
c#STATION2# = cidx#STATION2# * uint_size + cv#STATION2#;

min_val = min([c#STATION1# c#STATION3# c#STATION2#]);

%compute padding
pad#STATION1# = c#STATION1# - min_val;
pad#STATION3# = c#STATION3# - min_val;
pad#STATION2# = c#STATION2# - min_val;

%axis
xmin_axis = 700;
xmax_axis = 1300;

%signal 
xmin = 1;
xmax = 2600 + max([pad#STATION1# pad#STATION3# pad#STATION2#]);


%avg on the first 100 samples
avglen = 100;
avg#STATION2# = sum(d#STATION2#wave(1:avglen)) / avglen;
avg#STATION1# = sum(d#STATION1#wave(1:avglen)) / avglen;
avg#STATION3# = sum(d#STATION3#wave(1:avglen)) / avglen;

%center
d#STATION2#wavec = d#STATION2#wave - avg#STATION2#;
d#STATION1#wavec = d#STATION1#wave - avg#STATION1#;
d#STATION3#wavec = d#STATION3#wave - avg#STATION3#;

%shift signals
d#STATION2#wavec_shift = [zeros(pad#STATION2#, 1); d#STATION2#wavec; zeros(xmax-size(d#STATION2#wavec,1)-pad#STATION2#, 1)];
d#STATION1#wavec_shift = [zeros(pad#STATION1#, 1); d#STATION1#wavec; zeros(xmax-size(d#STATION1#wavec,1)-pad#STATION1#, 1)];
d#STATION3#wavec_shift = [zeros(pad#STATION3#, 1); d#STATION3#wavec; zeros(xmax-size(d#STATION3#wavec,1)-pad#STATION3#, 1)];

%plot
figure(1);
subplot(3,1,1), plot(d#STATION1#wavec_shift);
title('Station 1 (id#STATION1#)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad#STATION1#, 'r');


subplot(3,1,3), plot(d#STATION3#wavec_shift);
title('Station 3 (id#STATION3#)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad#STATION3#, 'r');

subplot(3,1,2), plot(d#STATION2#wavec_shift);
title('Station 2 (id#STATION2#)');
xlim([xmin_axis xmax_axis]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Micro Value');
hold on;
vline(prewindow_size+pad#STATION2#, 'r');

%------------- XCorr --------------
xc12 = xcorr(d#STATION2#wavec_shift, d#STATION1#wavec_shift);
xc32 = xcorr(d#STATION2#wavec_shift, d#STATION3#wavec_shift);
xc13 = xcorr(d#STATION3#wavec_shift, d#STATION1#wavec_shift);

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
