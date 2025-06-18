# HFT Ticker EMA

A C++ project that connects to the Coinbase WebSocket feed, listens for live ticker data, computes Exponential Moving Averages (EMA) for price and mid-price, and logs results into a CSV file.

---

## ✅ Features

- WebSocket connection to [Coinbase public feed](https://docs.cloud.coinbase.com/exchange/docs/websocket-overview)
- JSON message parsing using `nlohmann/json`
- Real-time EMA calculation for:
  - price
  - mid_price = (best_bid + best_ask) / 2
- Logging to log.csv
- Unit tests using GoogleTest

---

## 📦 Dependencies

Install the following system packages:

```bash
sudo apt update
sudo apt install \
    build-essential \
    cmake \
    git \
    libssl-dev \
    zlib1g-dev \
    libboost-all-dev
```

## 🔌 External Libraries

This project depends on IXWebSocket.

Install ixwebsocket with TLS enabled:

```bash
git clone https://github.com/machinezone/IXWebSocket.git
cd IXWebSocket
mkdir build && cd build
cmake -DUSE_TLS=ON -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install
```

## 🛠 Build the Project

Clone this repo (or place the files) and run:

```bash
cd /path/to/project
mkdir build && cd build
cmake ..
make
```

## 🚀 Run the Client

```bash
./coinbase_ws_ix
```

You should see console output like:

```bash
Connected to Coinbase.
```

## 📝 CSV Logging

All parsed and processed ticker data will be written to log.csv in the same directory. Each line includes:

```bash
timestamp,product_id,price,best_bid,best_ask,mid_price,ema_price,ema_mid
2024-06-18T12:00:01Z,BTC-USD,66500.10,66499.99,66500.21,66500.10,EMA1,EMA2
...
```

The file is automatically flushed after each message to ensure persistence even on forced shutdown.

## ⚙️ EMA Logic
 • The formula used is:

EMA_t = α * x_t + (1 - α) * EMA_{t-1}


 • The alpha value used in the project is 0.039, which roughly corresponds to a 5-second smoothing window assuming ~10 messages per second.

## 🧪 Running Unit Tests

Unit tests are written using GoogleTest (gtest) and cover:
 • EmaCalculator correctness
 • TickerData JSON parsing

## To run tests:

```bash
cd build
ctest --output-on-failure
```

## Or individually:

```bash
./test_ema
./test_parser
```

## Expected output:

```bash
100% tests passed, 0 tests failed
```

## 🗂 Project Structure

.
├── CMakeLists.txt
├── README.md
├── main.cpp
├── ticker_data.hpp / .cpp        # JSON parser
├── ema_calculator.hpp / .cpp     # EMA logic
├── csv_logger.hpp / .cpp         # CSV logger
├── test/
│   ├── test_ema.cpp              # Unit test for EMA
│   └── test_parser.cpp           # Unit test for JSON parsing
└── log.csv                       # Output file

## 🧠 Design Summary
 • main.cpp sets up and starts the ix::WebSocket client.
 • On onMessage, it parses the JSON, calculates EMA, and logs values.
 • TickerData::from_json() safely parses required fields from incoming messages.
 • EmaCalculator implements standard EMA calculation with configurable alpha.
 • CsvLogger appends structured rows to a CSV file and flushes output for data safety.
 • GoogleTest is integrated via FetchContent in CMakeLists.txt.