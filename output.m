clear all
close all
clc

%%

x=dlmread('Histogram.txt')

dat=x(:,2);
graylevel=x(:,1);
figure
fill(graylevel,dat,'k')
xlabel('Gray level')
ylabel('Number of pixels')
title('Histogram of the Image')
set(gca,'fontsize',16)

