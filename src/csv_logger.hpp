#pragma once
#include <fstream>
#include <string>

class CsvLogger {
public:
    CsvLogger(const std::string& filename);
    ~CsvLogger();

    void write_header();
    void log(const std::string& timestamp,
             const std::string& product_id,
             double price,
             double best_bid,
             double best_ask,
             double mid_price,
             double ema_price,
             double ema_mid);

private:
    std::ofstream file_;
};