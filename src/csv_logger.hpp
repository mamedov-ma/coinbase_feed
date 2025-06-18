#pragma once
#include <fstream>
#include <string>

class CsvLogger
{
public:
    CsvLogger(std::string const& filename);
    ~CsvLogger();

    void write_header();
    void log(std::string const& timestamp,
        std::string const& product_id,
        double price,
        double best_bid,
        double best_ask,
        double mid_price,
        double ema_price,
        double ema_mid);

private:
    std::ofstream file_;
};