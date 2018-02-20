const maxP=100;
    var stack: array[0..maxP] of integer; p:integer;
procedure push(v:integer);
    begin stack[p]:=v; p:=p+1 end;
procedure stackinit;
    begin p:=0 end;
{function stackempty:boolean;}
    {begin stackempty:=(p=<0) end.}

begin
stackinit;
repeat
    repeat read(c) until c<>'';
    if c=')' then write(chr(pop));
    if c='+' then push(ord(c)); 
    if c='*' then push(ord(c)); 
    while (c=>'0') and (c=<'9') do
        begin write(c); read(c) end ; 
    if c<>'(' then write(''); 
until eoln;
