clear all; close all;

img = imread('text.jpg');
img = im2gray(img);
temp = imread('pp.jpg');
temp = im2gray(temp);

% img = imnoise(img,'gaussian');
I = img;

% img = medfilt2(img);
% img = imgaussfilt(img, 1.5);
% img = imgaussfilt(img, 1.2);
canny_I = edge(img,'sobel', 0.05);
%canny_I = edge(img,'sobel', 0.7);
figure;
imshow(canny_I);

%temp = medfilt2(temp);
canny_temp = edge(temp,'sobel');
%canny_temp = edge(temp,'canny', 0.4);

dy_I=imfilter(double(img),[1; -1],'same');
dx_I=imfilter(double(img),[1  -1],'same');
theta_I = atan2(dy_I,dx_I)*90/pi();

dy_temp=imfilter(double(temp),[1; -1],'same');
dx_temp=imfilter(double(temp),[1  -1],'same');
theta_temp = atan2(dy_temp,dx_temp)*90/pi();

refPointy = round(size(canny_temp,1)/2);
refPointx = round(size(canny_temp,2)/2);

%-----------------------------
%Generate the R-table
[y,x] = find(canny_temp > 0);
pointsRange = round(size(x,1));
angleRange = 50;
%angleRange = 50;
%theta_temp = Gradient(canny_temp);

Rtable = zeros(angleRange, pointsRange,360,20,2);
binCount = zeros(181,1);

%Write to Rtable

for i = 1:pointsRange
    %fi = round(theta_temp(y(i),x(i)) + 91);
    fi = theta_temp(y(i),x(i)) + 90;
    fi = round(fi/180*(angleRange-1) )+1;
    binCount(fi) = binCount(fi) + 1;
    h = binCount(fi);
    for scale = 1:20 %5:20
        delta_x = scale/10*(refPointx - x(i));
        delta_y = scale/10*(refPointy - y(i));
        for angle = 1:360
            Rtable(fi, h,angle,scale, 1) = round(delta_x*cosd(angle) - delta_y*sind(angle));
            Rtable(fi, h,angle,scale, 2) = round(delta_x*sind(angle) + delta_y*cosd(angle));
        end
    end
end

%-----------------------------
%Accumulator:

%get the image edge points
[y_I,x_I] = find(canny_I > 0);
pointRange_I = size(x_I,1);
%theta_I = Gradient(canny_I);
[M,N] = size(canny_I);

%generate accumulator:
count = zeros(M,N);


% for i=1:pointRange_I
%     %the gradient angle:
%     fi = round(theta_I(y_I(i),x_I(i)) + 181);
%     for j = 1:binCount(fi)
%         n_x = x_I(i) + Rtable(fi, j, 1);
%         n_y = y_I(i) + Rtable(fi, j, 2);
%         if (n_y>=1) && (n_y<=M) && (n_x>=1) && (n_x<=N)
%             count(n_y, n_x) = count(n_y, n_x)+1;
%         end
%     end
% end
% 

maxeach = zeros(360,20,1);
for scale = 1:20 %5:20
    for angle = 1:360
        for i=1:pointRange_I
            %the gradient angle:
    %         fi = theta_I(y_I(i),x_I(i)) - angle;
    %         fi = round(asind(sind(fi)) + 91);
            fi = theta_I(y_I(i),x_I(i)) + angle;
            fi = asind(sind(fi)) + 90;
            fi = round(fi/180*(angleRange-1) )+1;
            for j = 1:binCount(fi)
                n_x = x_I(i) + Rtable(fi, j,angle,scale, 1);
                n_y = y_I(i) + Rtable(fi, j,angle,scale, 2);
                if (n_y>=1) && (n_y<=M) && (n_x>=1) && (n_x<=N)
                    count(n_y, n_x) = count(n_y, n_x)+1;
                end
            end
        end
        maxpoint = max(count(:));
        maxeach(angle,scale) = maxpoint;
        count = zeros(M,N);
    end
end

bestvoting = max(maxeach(:));
[bestangle, bestscale] = find(maxeach >= bestvoting);


for i=1:pointRange_I
    %the gradient angle:
%     fi = round(theta_I(y_I(i),x_I(i)) + 91);
    fi = theta_I(y_I(i),x_I(i)) + bestangle;
        fi = asind(sind(fi)) + 90;
        fi = round(fi/180*(angleRange-1) )+1;
    for j = 1:binCount(fi)
        n_x = x_I(i) + Rtable(fi, j,bestangle,bestscale, 1);
        n_y = y_I(i) + Rtable(fi, j,bestangle,bestscale, 2);
        if (n_y>=1) && (n_y<=M) && (n_x>=1) && (n_x<=N)
            count(n_y, n_x) = count(n_y, n_x)+1;
        end
    end
end

%show hough space image
count = mat2gray(count);
figure;
%houghspace = uint8(count);
%imagesc(houghspace);
imshow(count);


maxpoint = max(count(:));
[loc_y,loc_x] = find(count == (maxpoint));

%[y, x] = find(count >= 0.8 * maxpoint);
% k = 2;
xx = [];
yy = [];
for i=1:M
    for j=1:N
        if (count(i,j) > 0.17 * maxpoint)
%             if ((xx(k-1)>i+10) && (yy(k-1)>j+10))
%                 xx = [xx i];
%                 yy = [yy j];
%                 k = k + 1;
%             end
            xx = [xx i];
            yy = [yy j];
        end
    end
end

% figure;
% houghspace1 = uint8(count1);
% imagesc(houghspace1);

%show hough space image
count = mat2gray(count);
figure;
%houghspace = uint8(count);
%imagesc(houghspace);
imshow(count);
hold on;
sita=0:0.05:2*pi;
r=30;

a = size(xx);
% plot(yy(1), xx(1), 'r*', 'LineWidth', 2, 'MarkerSize', 3);
plot(yy(1)+r*cos(sita),xx(1)+r*sin(sita), 'r', 'LineWidth', 3);
for i=1:a(2)
%     if ((i>1) && ((yy(i-1)+5<yy(i)) || (yy(i-1)-5>yy(i))) && ...
%             ((xx(i-1)+5<xx(i)) || (xx(i-1)-5>xx(i))))
%         plot(yy(i), xx(i), 'r*', 'LineWidth', 2, 'MarkerSize', 3);
        plot(yy(i)+r*cos(sita),xx(i)+r*sin(sita),'r','LineWidth', 3);
%     end
end
hold off;



figure;
I = uint8(I);
imshow(I);
hold on;
sita=0:0.05:2*pi;
r=30;

a = size(xx);
plot(yy(1), xx(1), 'r*', 'LineWidth', 2, 'MarkerSize', 3);
plot(yy(1)+r*cos(sita),xx(1)+r*sin(sita), 'r', 'LineWidth', 3);
for i=1:a(2)
%     if ((i>1) && ((yy(i-1)+5<yy(i)) || (yy(i-1)-5>yy(i))) && ...
%             ((xx(i-1)+5<xx(i)) || (xx(i-1)-5>xx(i))))
        plot(yy(i), xx(i), 'r*', 'LineWidth', 2, 'MarkerSize', 3);
        plot(yy(i)+r*cos(sita),xx(i)+r*sin(sita),'r','LineWidth', 3);
%     end
end
hold off;




