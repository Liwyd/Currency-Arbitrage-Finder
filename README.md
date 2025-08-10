# Currency Arbitrage Finder

This C++ program identifies arbitrage opportunities in foreign exchange markets by detecting negative-weight cycles in a graph. It uses the Bellman-Ford algorithm to find a sequence of currency trades that can result in a risk-free profit.

## Core Concept: Arbitrage as a Graph Problem

Arbitrage is the practice of taking advantage of a price difference between two or more markets. In currency exchange, it means you can start with one currency, make a series of trades through other currencies, and end up with more money than you started with.

This problem can be modeled using a directed graph where:
* **Nodes** represent currencies.
* **Edges** represent exchange rates between currencies.

An arbitrage opportunity exists if the product of the exchange rates in a cycle is greater than 1.

$$
rate_1 \times rate_2 \times \dots \times rate_k > 1
$$

To make this problem solvable with standard graph algorithms, we can take the logarithm of this inequality. By using the property $log(a \times b) = log(a) + log(b)$, the condition becomes:

$$
log(rate_1) + log(rate_2) + \dots + log(rate_k) > 0
$$

If we then define the weight of each edge as $w = -log(rate)$, the condition for arbitrage transforms into finding a cycle with a negative total weight:

$$
-w_1 - w_2 - \dots - w_k > 0 \implies w_1 + w_2 + \dots + w_k < 0
$$

This is a classic **negative-weight cycle detection problem**, for which the Bellman-Ford algorithm is perfectly suited.

## Algorithm

The program implements the **Bellman-Ford algorithm** to find negative-weight cycles in the graph of currencies.

1.  **Graph Construction**: It reads the number of currencies (`n`) and exchange rates (`m`). It then constructs a graph where edge weights are calculated as `-log(rate)`.
2.  **Relaxation**: The algorithm iteratively relaxes all edges `n-1` times. Relaxation is the process of updating the cost to reach a node with a shorter path.
3.  **Cycle Detection**: In the `n`-th iteration, if any edge can still be relaxed, it means a negative-weight cycle has been found.
4.  **Cycle Reconstruction**: Once a node within a negative cycle is identified, the program backtracks through the `parent` pointers to reconstruct the sequence of trades that form the arbitrage opportunity.

## How to Compile and Run

1.  **Compile the code** using a C++ compiler like `g++`:
    ```bash
    g++ proj.cpp -o arbitrage_detector
    ```

2.  **Run the executable**. The program reads from standard input. You can either type the input directly or redirect it from a file:
    ```bash
    ./arbitrage_detector < input.txt
    ```

## Input Format

The program expects the input in the following format:

1.  The first line contains two integers, `n` and `m`, representing the number of currencies and the number of available exchange rates, respectively.
2.  The next `n` lines contain the string identifiers for each currency (e.g., `USD`, `EUR`, `JPY`).
3.  The next `m` lines define the exchange rates. Each line contains two integers `u` and `v` (the 1-based indices of the currencies) and a double `r` (the exchange rate from currency `u` to `v`).

## Output Format

* **If an arbitrage opportunity is found**, the program prints the number of trades in the cycle, followed by the 1-based indices of the currencies in the cycle.
* **If no arbitrage opportunity exists**, it prints:
    ```
    No negative cycle
    ```
## Example

3 3
USD
EUR
JPY
1 2 1.1
2 3 0.9
3 1 1.02

In this example:
* USD -> EUR: rate is 1.1
* EUR -> JPY: rate is 0.9
* JPY -> USD: rate is 1.02

The product of these rates is $1.1 \times 0.9 \times 1.02 = 1.0098$, which is greater than 1, indicating an arbitrage opportunity.

### Corresponding Output

3
1 2 3

This output shows a 3-step cycle involving currencies 1 (USD), 2 (EUR), and 3 (JPY).


------
# Rust Version Notes

This repository also includes a Rust implementation of the same arbitrage detection algorithm, which follows the exact same logic as the original C++ version.

### Differences in Rust Implementation:
- Uses `usize` indices internally (0-based), so input indices should be 0-based or adjusted accordingly.
- Reads the entire input at once and parses it efficiently using string splitting.
- Uses Rust’s standard library (`std::f64::INFINITY`, `f64::ln()`) for numeric operations.
- Prints the final result as either:
  - `"Arbitrage opportunity detected"` if a negative cycle is found,
  - or `"No arbitrage opportunity"` otherwise.

### How to Compile and Run the Rust Code

1. Compile with:
    ```bash
    rustc arbitrage_detector.rs -O
    ```

2. Run the executable, providing input in the same format (first line `n m`, then `m` lines of `u v rate`):
    ```bash
    ./arbitrage_detector < input.txt
    ```

### Input 

- The Rust version expects:
  - First line: two integers `n` and `m`.
  - Next `m` lines: each line contains three values:
    - `u` (starting currency index, zero-based),
    - `v` (ending currency index, zero-based),
    - `rate` (exchange rate from currency `u` to `v`).



### Output 

- Prints exactly one line:
  - `"Arbitrage opportunity detected"` if any negative cycle is found (arbitrage exists).
  - `"No arbitrage opportunity"` if none is found.


