program euclid (input, output); 
var x,y: integer; 
function gcd(u,v: integer): integer; 
	var t: integer; 
	begin
        writeln();
        writeln('u ', u);
        writeln('v ', v);
        writeln();
	repeat 
    	if u<v then 
        begin 
            writeln('true  ');
            t := u; u := v; v := t 
        end; 
		u := u-v; 
	until u = 0; 
	gcd := v 
 	end; 
begin 
    begin         
    x := 10;
    y := 6;
    if (x>0) and (y>0) then writeln(x, y, gcd(x, y)) 
    end; 
end. 
