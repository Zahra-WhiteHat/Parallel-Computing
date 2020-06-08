function mtx = pi
  
    f = fopen('file.txt');
    file2 =textscan(f, '%s', 'delimiter', '\n');
    
    Line_Number=(2:2:8);
    LT = {file2{1}{2},file2{1}{4},file2{1}{6},file2{1}{8}};
    time = file2{1}{11};
    
    numbers = regexp(LT,'[0-3]','once', 'match');
    t = regexp(time,'[0-9]', 'match');
    c0 = cell2mat(numbers);
    c2 = str2num(c0);
    r = mod(c2  , 1000 ); 
    c2_1 = (c2 - r) / 1000;
    r1 = mod(r, 100);
    c2_2 = (r - r1) / 100;
    r2 = mod(r1, 10);
    c2_3 = (r1 - r2) / 10;
    
    t0 = cell2mat(t);
    t2 = str2num(t0);
    
    x_param = [c2_1 , c2_2 , c2_3 , r2];
    t_param = [t2/4, t2/3 , t2/2 , t2];
    

    disp(numbers);
    disp(t);
    plot(x_param , t_param, 'o' , 'MarkerFaceColor','k')
    

    fclose('file.txt');
    

endfunction