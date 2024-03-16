// Print a table of a given function f, computed by taylor series
open System
// function to compute
let f x = (1.0 + 2.0 * x ** 2.0) * exp(x ** 2.0)

let a = 0.0
let b = 1.0
let n = 10

let rec fact n = if n = 0.0 then 1.0 else n * fact (n - 1.0)
let rec pow a n = if n = 0.0 then 1.0 else a * pow a (n - 1.0)
let eps = 0.000000001

let series n x = (n + n + 1.0) / (fact n) * pow (x) (n + n)

// Define a function to compute f using naive taylor series method
let taylor_naive x = 
    let p n = series n x
    let rec iter n = 
        if p (n + 1.0) < eps
        then p n
        else p n + iter (n + 1.0)
    iter 0.0


// Define a function to do the same in a more efficient way
let taylor_smart x =
    let smart n prev = prev * ((2.0 * n + 1.0) / (2.0 * n - 1.0)) * ((x ** 2.0) / n)
    let rec iter n p =
        if smart (n+1.0) p < eps
        then p
        else p + iter (n + 1.0) (smart (n+1.0) p)
    iter 0.0 1.0


let main =
   for i=0 to n do
     let x = a+(float i)/(float n)*(b-a)
     printfn "%5.2f  %10.6f  %10.6f   %10.6f" x (f x) (taylor_naive x) (taylor_smart x)

main