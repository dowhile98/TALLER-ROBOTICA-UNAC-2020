clear
close all
iptsetpref('ImshowBorder', 'tight')

FontSize=11;
FontName='Arial';
%% entrada
load('y.dat')
n = 0:length(y)-1;
figure("Name","salida del filtro");
stem(n,y(n+1),'filled','k');
lab=xlabel('n');
title("SEÑAL FILTRADA","Color",'r')
grid on
set(lab,'FontName',FontName,'FontSize',FontSize);
lab=ylabel('y[n]');
set(lab,'FontName',FontName,'FontSize',FontSize);

