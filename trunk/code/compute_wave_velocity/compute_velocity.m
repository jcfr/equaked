
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


%compute velocity

%experiment 1 (1327, 1362) => 1697.1 m/s
%experiment 2 (837, 911) => 802 m/s
%experiment 3 (749, 828) => 752 m/s

%station 1: robot 57
t1 = 749;

%station 2: robot 70
t2 = 828;

%distance (cm)
distance = 29.7;

%sampling frequency (Hz)
f = 200 * 10^3; 

%---------------------------------------

t = (t2 - t1) * (1/f);
d = distance * 10^-2;

velocity = d / t

