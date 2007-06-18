%refactor window


function res = refactor_window(widx, data)
% widx - circular window current index
% data - arra to reorder

res = [ data(widx : size(data, 1) ); data(1: widx - 1) ]; 




