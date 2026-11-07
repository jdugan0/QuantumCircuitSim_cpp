A quantum computer circuit simulator written in C++.

## Install
### Windows
`cmake -S . -B build` to configure the project (only do this once) and `cmake --build build` to build. Then run `.\build\QuantumCircuitSim.exe` to run the compiled executable. 
### Other 
While I have not tested on other operating systems, the code should still compile and run fine.

## Guide
The state of a circuit is represented by a single vector in $\mathbb{C}^{(2^n)}$. Each wire you add will multiply the dimension of the state by 2. 
A gate can be applied to a single Qbit by applying that gate to all independent pairs of Qbits in that state. For example, in a 3 Qbit state, if we want to apply a gate $U$ to bit 0, we would apply that gate independently to each pair as so:

$U\begin{pmatrix} \alpha_{000} \\ \alpha_{001} \end{pmatrix}$

$U\begin{pmatrix} \alpha_{010} \\ \alpha_{011} \end{pmatrix}$

$U\begin{pmatrix} \alpha_{100} \\ \alpha_{101} \end{pmatrix}$

$U\begin{pmatrix} \alpha_{110} \\ \alpha_{111} \end{pmatrix}$

A circuit is a list of operations that are applied sequentially. A circuit can be created and computed like so:
```c++
Circuit c{};
RunResult r = c.compute(); // circuit computation does not modify the inital state, so computation can be performed many times without resetting anything.
```
`r` stores the final state of the circuit and a list of all measurements performed, in order. To add a Qbit:
```c++
c.addWire(ZERO); // ZERO and ONE are the states |0> and |1>
c.addWire(ZERO, 5); // adds 5 wires in inital state 0
c.addWire({ZERO, ONE}); // adds 2 wires, in states |0> and |1>.
```
To add an operation:
```c++
c.addOp({Gate{Gates::X, 0, {1, 2}}}); // Adds a not gate on Qbit 0 that is controlled by Qbits 1 and 2.
c.addOp({Measure{0}}); // Measures Qbit 0.
```
Some helpful gate matrices are stored in the `Gates` namespace. You can also create your own: 
```c++
Gate{Mat2{{0,1}, {1,0}}, 0, {}}; // Custom gates are not enforced to be Unitary.
```
Some helpful "circuits" are stored in the `Circuits` namespace. These are just lists of operators that can be added to a circuit like so:
```c++
c.addOp(Circuits::Deutsch(0, 1, Circuits::U_f3(0, 1))); // performs Deutsch's algorithm with input 0, output 1, and function f3. 
```

## Credits
Eigen 5.0.1 is used for matrix math. 

All code in this project was written by me (Justin Dugan). No AI was used.