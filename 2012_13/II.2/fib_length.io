
fib := clone Object
fib last := BigNum clone
fib old_last := BigNum clone

fib last := last + 1

fib advance := method(temp := last; last = last + old_last; old_last = temp)

fib length := method(last asString size)

n0 := 2
n1 := 100000

for(i,n0,n1, 
	     fib advance; 
	     i print; 
	     " " print; 
	     fib length print ; 
	     "\n" print
	     )