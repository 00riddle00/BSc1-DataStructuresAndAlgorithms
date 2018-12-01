program euclid (input, output); 
var x,y: integer; 
function gcd(u,v: integer): integer; 
	var t: integer; 
	begin
	writeln('Inside fn');
	repeat 
    	if u<v then 
        begin t := u; u := v; v := t end; 
		u := u-v; 
	until u = 0; 
	gcd := v 
 	end; 
begin 
	writeln('Hello');
	while not eof do 
    begin         
	writeln('Before reading');
	readln (x, y); 
	writeln('Read line');
    if (x>0) and (y>0) then writeln (x, y, gcd(x, y)) 
    end; 
end. 
