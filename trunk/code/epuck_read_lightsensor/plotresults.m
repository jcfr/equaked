load d57.dat

figure(1);
plot(d57);
grid
H = title('Light detected by station 1 (id57)');
set(H, 'FontSize', 12);
H=xlabel('Timestep');
set(H, 'FontSize', 12);
H=ylabel('Light sensor Value');
set(H, 'FontSize', 12);
legend('ls0','ls1','ls2','ls3','ls4','ls5','ls6','ls7');

