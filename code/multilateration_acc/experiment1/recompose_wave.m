%
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
