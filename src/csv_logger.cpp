#include "csv_logger.hpp"
#include <iostream>

CsvLogger::CsvLogger(const std::string& filename) {
    file_.open(filename, std::ios::out | std::ios::app);
    if (!file_.is_open()) {
        std::cerr << "[ERROR] Failed to open log file: " << filename << std::endl;
    }
}

CsvLogger::~CsvLogger() {
    if (file_.is_open()) file_.close();
}

void CsvLogger::write_header() {
    file_ << "timestamp,product_id,price,best_bid,best_ask,mid_price,ema_price,ema_mid\n";
}

void CsvLogger::log(const std::string& timestamp,
                    const std::string& product_id,
                    double price,
                    double best_bid,
                    double best_ask,
                    double mid_price,
                    double ema_price,
                    double ema_mid) {
    if (!file_.is_open()) return;
    file_ << timestamp << ","
          << product_id << ","
          << price << ","
          << best_bid << ","
          << best_ask << ","
          << mid_price << ","
          << ema_price << ","
          << ema_mid << "\n";
    file_.flush();
}