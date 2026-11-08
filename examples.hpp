#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Tovar {
private:
    std::string name;
    double price = 0;
    int quantity;

public:
    Tovar(std::string name, double price, int quantity)
        : name(std::move(name)), quantity(quantity) {
        if (quantity < 0) throw std::invalid_argument("Quantity cannot be negative");
        setPrice(price);
    }

    const std::string& getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    double totalValue() const { return price * quantity; }

    void setPrice(double value) {
        if (!std::isfinite(value) || value < 0) {
            throw std::invalid_argument("Price must be finite and nonnegative");
        }
        price = value;
    }

    void sell(int count) {
        if (count <= 0 || count > quantity) {
            throw std::invalid_argument("Invalid sale quantity");
        }
        quantity -= count;
    }

    void output(std::ostream& stream = std::cout) const {
        stream << name << ": price=" << price
               << ", quantity=" << quantity << ", total=" << totalValue() << '\n';
    }
};

class Prylad {
private:
    std::string name;
    double powerWatts;

public:
    Prylad(std::string name, double powerWatts)
        : name(std::move(name)), powerWatts(powerWatts) {
        if (!std::isfinite(powerWatts) || powerWatts < 0) {
            throw std::invalid_argument("Power must be finite and nonnegative");
        }
    }

    void output(std::ostream& stream = std::cout) const {
        stream << name << ": power=" << powerWatts << " W\n";
    }

    double energyKwh(double hours) const {
        if (!std::isfinite(hours) || hours < 0) {
            throw std::invalid_argument("Hours must be finite and nonnegative");
        }
        return powerWatts / 1000.0 * hours;
    }
};

class Payment {
private:
    long long amountKopiyky = 0;
    std::string currency = "UAH";

public:
    Payment() = default;

    Payment(long long amountKopiyky, std::string currency)
        : amountKopiyky(amountKopiyky), currency(std::move(currency)) {
        if (amountKopiyky < 0) throw std::invalid_argument("Amount cannot be negative");
        if (this->currency.empty()) throw std::invalid_argument("Currency is required");
    }

    long long getAmountKopiyky() const { return amountKopiyky; }
    const std::string& getCurrency() const { return currency; }

    void output(std::ostream& stream = std::cout) const {
        stream << "Amount in smallest units: " << amountKopiyky
               << ", currency: " << currency << '\n';
    }
};

class Vehicle {
private:
    std::string brand;

protected:
    explicit Vehicle(std::string brand) : brand(std::move(brand)) {}
    const std::string& getBrand() const { return brand; }

public:
    virtual ~Vehicle() = default;
    virtual std::string description() const = 0;
};

class Car : public Vehicle {
public:
    explicit Car(std::string brand) : Vehicle(std::move(brand)) {}
    std::string description() const override { return "Car: " + getBrand(); }
};

class Bicycle : public Vehicle {
public:
    explicit Bicycle(std::string brand) : Vehicle(std::move(brand)) {}
    std::string description() const override { return "Bicycle: " + getBrand(); }
};

class Scanner {
public:
    std::string status() const { return "Scanner ready"; }
};

class Printer {
public:
    std::string status() const { return "Printer ready"; }
};

class MultiFunctionDevice : public Scanner, public Printer {};

class OfficeDevice : public Scanner, public Printer {
public:
    std::string status() const {
        return Scanner::status() + "; " + Printer::status();
    }
};
