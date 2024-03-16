// // Определите функции для решение алгебраических уравнений
// let abs_float (x: float) =
//     if x >= 0.0 then x
//     else -x
// let rec dichotomy (f: float -> float) a b =
//     let tol = 1e-6
//     if abs_float (b - a) < tol then (a + b) / 2.0
//     else
//         let c = (a + b) / 2.0
//         if f a * f c <= 0.0 then dichotomy f a c
//         else dichotomy f c b

// let rec iterations (phi: float -> float) x0 =
//     let tol = 1e-6
//     let rec iter x =
//         let next = phi x
//         if abs_float (next - x) < tol then next
//         else iter next
//     iter x0

// let rec newthon (f: float -> float) (f': float -> float) x0 =
//     let tol = 1e-6
//     let rec iter x =
//         let next = x - (f x) / (f' x)
//         if abs_float (next - x) < tol then next
//         else iter next
//     iter x0

// // Решите 3 уравнения (начиная со своего номера варианта) с использованием 3-х методов
// let f1 x = 3.0 * sin(sqrt x) + 0.35 * x - 3.8
// let f2 x = 0.25 * x ** 3.0 + x - 1250.2
// let f3 x = x + sqrt x + x ** (1.0 / 3.0) - 2.5

// let f1' x = 1.5 * cos(sqrt x) * (1.0 / (2.0 * sqrt x)) + 0.35
// let f2' x = 0.75 * x ** 2.0 + 1.0
// let f3' x = 1.0 + 0.5 * (1.0 / sqrt x) + (1.0 / 3.0) * x ** (-2.0 / 3.0)

// let phi1 x = (3.8 - 0.35 * x) / (3.0 * sin(sqrt x))
// let phi2 x = 1250.2 / (0.25 * x ** 2.0 + 1.0)
// let phi3 x = 2.5 - sqrt x - x ** (1.0 / 3.0)

// let main = 
//     printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f1 0.0 0.8) (iterations phi1 0) (newthon f1 f1' 0)
//     printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f2 0.0 1.0) (iterations phi2 0) (newthon f2 f2' 0)
//     printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f3 2.0 4.0) (iterations phi3 2) (newthon f3 f3' 2)




let eps = 0.000000001

let rec dichotomy f a b =
    let c = (b + a) / 2.0
    if abs (f c) < eps then c else
        if (f c) * (f a) >= 0.0
        then dichotomy f c b
        else dichotomy f a c

let rec iterations phi x0 =
    let x1 = phi x0
    if  abs (phi x1 - x1) < eps then x1 else iterations phi x1

let newthon f f' x0 = iterations (fun x -> x - ((f x) / (f' x))) x0

// let f1 x = tan x - 1.0/3.0 * (pown (tan x) 3) + 1.0/5.0 * (pown (tan x) 5) - 1.0/3.0
// let f2 x = acos x - sqrt (1.0 - 0.3 * x * x * x)
// let f3 x = 3.0 * x - 4.0 * log x - 5.0

// let f1' x = cos (2.0 * x) / (pown (cos x) 4)
// let f2' x = - 1.0 / sqrt (1.0 - x * x) + 9.0 * x * x / 2.0 / sqrt (100.0 - 30.0 * x * x * x)
// let f3' x = 3.0 - 4.0 / x

// let phi1 x = atan (1.0/3.0 * (pown (tan x) 3) - 1.0/5.0 * (pown (tan x) 5) + 1.0/3.0)
// let phi2 x = cos (sqrt (1.0 - 0.3 * x * x * x))
// let phi3 x = (4.0 * log x + 5.0) / 3.0


let f1 x = 3.0 * sin(sqrt x) + 0.35 * x - 3.8
let f2 x = 0.25 * x ** 3.0 + x - 1.2502
let f3 x = x + sqrt x + x ** (1.0 / 3.0) - 2.5

let f1' x = ((3.0 * cos(sqrt x)) / (2.0 * sqrt x)) + 0.35
let f2' x = 0.25 * 3.0 * x ** 2.0 + 1.0
let f3' x = ((3.0 * x ** (2.0 / 3.0)) + (2.0 * sqrt(x))) / (6.0 * x ** (7.0 / 6.0)) + 1.0

let phi1 x = (3.8 - 3.0 * sin(sqrt x)) / 0.35
let phi2 x =  -0.25 * x ** 3.0 + 1.2502
let phi3 x =  -1.0 * sqrt x - x ** (1.0 / 3.0) + 2.5

let main = 
    // printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f1 0.0 0.8) (iterations phi1 0) (newthon f1 f1' 0)
    // printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f2 0.0 1.0) (iterations phi2 0) (newthon f2 f2' 0)
    // printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f3 2.0 4.0) (iterations phi3 2) (newthon f3 f3' 2)

    printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f1 2.0 3.0) (iterations phi1 2) (newthon f1 f1' 2)
    printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f2 0.0 2.0) (iterations phi2 0) (newthon f2 f2' 0)
    printfn "%10.5f\t%10.5f\t%10.5f" (dichotomy f3 0.4 1.0) (iterations phi3 0.4) (newthon f3 f3' 0.4)

// (iterations phi3 0) (newthon f3 f3' 0)