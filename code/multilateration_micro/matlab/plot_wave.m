%
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
%

clear;

prewindow_size = 800;
uint_size = 65535;

%[d58wave cidx58 cv58] = recompose_wave(58);
[d70wave cidx70 cv70] = recompose_wave(70);
%[d57wave cidx57 cv57] = recompose_wave(57);

%c58 = cidx58 * uint_size + cv58;
c70 = cidx70 * uint_size + cv70;
%c57 = cidx57 * uint_size + cv57;

%min_val = min([c58 c70 c57]);

%compute padding
%pad58 = c58 - min_val;
pad70 = 0;%c70 - min_val;
%pad57 = c57 - min_val;

xmax = 2600 ;%+ max([pad58 pad70 pad57]);

figure(1);
%subplot(3,1,3), plot([zeros(pad58, 1);d58wave]);
%title('Station 3 (id58)');
%xlim([0 xmax]);
%xlabel('Timestep (1 step = 1/200000 second)');
%ylabel('Accel. Z-Dim Value');
%hold on;
%plot(prewindow_size+pad58, [1500:4500], 'r');




%figure(2);
%subplot(3,1,2), 
plot([zeros(pad70, 1); d70wave]);
title('Station 2 (id70)');
xlim([0 xmax]);
xlabel('Timestep (1 step = 1/200000 second)');
ylabel('Accel. Z-Dim Value');
xlabel('Timestep (1 step = 1/200000 second)');
hold on;
plot(prewindow_size+pad70, [1500:4500], 'r');


%figure(3);
%subplot(3,1,1), plot([zeros(pad57, 1); d57wave]);
%title('Station 1 (id57)');
%xlim([0 xmax]);
%xlabel('Timestep (1 step = 1/200000 second)');
%ylabel('Accel. Z-Dim Value');
%xlabel('Timestep (1 step = 1/200000 second)');
%hold on;
%plot(prewindow_size+pad57, [1500:4500], 'r');
