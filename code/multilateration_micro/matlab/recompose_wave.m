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

function [thewave, count_idx, count_value] = recompose_wave(id)

%circular pre-window size
prewindows_size = 800;

cfgname = sprintf('d%dcfg', id);
prewname = sprintf('d%dprew', id);
postwname = sprintf('d%dpostw', id);


load(strcat(cfgname, '.dat'));
load(strcat(prewname, '.dat'));
load(strcat(postwname, '.dat'));

cfgdata = eval(cfgname);
prewdata = eval(prewname);
postwdata = eval(postwname);

%circular pre-window index
widx = cfgdata(1);
count_idx = cfgdata(2);
count_value = cfgdata(3);

prewdata_r = refactor_window(widx + 1, prewdata );

thewave = [prewdata_r; postwdata];
