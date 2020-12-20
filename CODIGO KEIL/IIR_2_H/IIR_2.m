clear
close all
iptsetpref('ImshowBorder', 'tight')

FontSize=11;
FontName='Arial';

load('x.dat')
n = 0:length(x)-1;
figure("Name","entrada");
stem(n,x(n+1),'filled','k.');
axis([0 255 min(x) max(x)]);
lab=xlabel('n');
set(lab,'FontName',FontName,'FontSize',FontSize);
lab=ylabel('x[n]');
set(lab,'FontName',FontName,'FontSize',FontSize);

load('y.dat')
figure("Name","salida");
stem(n,y(n+1),'filled','k.');
axis([0 255 min(y) max(y)]);
lab=xlabel('n');
set(lab,'FontName',FontName,'FontSize',FontSize);
lab=ylabel('y[n]');
set(lab,'FontName',FontName,'FontSize',FontSize);
