measure=load('measure.txt');

plot(0:(length(measure)-1), measure);
grid
H=title('Shock perceived by the e-puck');
set(H, 'FontSize', 12);
H=xlabel('Time');
set(H, 'FontSize', 12);
H=ylabel('Accel. Z-Dim Value');
set(H, 'FontSize', 12);
